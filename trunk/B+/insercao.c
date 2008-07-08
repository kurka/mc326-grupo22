/* Implementacao de funcoes de insercao em arvore B+ */

#include<stdio.h>
#include<strings.h>
#include<malloc.h>
#include "defines.h"
#include "leitura.h"
#include "insercao.h"


/*!
 * \brief Faz a insercao de chave na arvore 
 */
void insere(int *prox_chave, int *nrr) { 
  int chave[2]; 

  tipoNo *nova, *raiz_velha, *raiz_velha_dir; 
  int resposta[3];
   
   
   /* Le a chave a ser inserida */
   printf("Digite a chave a ser inserida\n"); 
   scanf("%d", &chave[0]);
   /* Guarda o nrr da chave */
   *nrr = *nrr + 1;
   chave[1] = *nrr;
      
   /* Acha a folha */
   acha_folha_ins(chave, 0, resposta, prox_chave);

   if(resposta[2] != OK){
     /* Se a funcao retornar algo diferente de OK, significa que a raiz sofreu split */   
     *prox_chave = *prox_chave+1;
     nova = abre_no(*prox_chave, NO);
     /* Insere na folha */
     nova->chaves[0] = resposta[0];
     nova->apontadores[0] = resposta[1];
     nova->apontadores[1] = resposta[2];
     nova->n_elementos++;  

     /* Faz com que arquivo 0 sempre seja o arquivo raiz */
     raiz_velha = abre_no(ROOT, FOLHA);
     nova->posicao = ROOT;
     raiz_velha->posicao = *prox_chave;
     nova->apontadores[0] = *prox_chave;

     if(raiz_velha->tipo == FOLHA){
       raiz_velha_dir = abre_no(raiz_velha->prox_dir, FOLHA);
       raiz_velha_dir->prox_esq = *prox_chave;
       fecha_no(raiz_velha_dir);  
     }


     /* Salva os arquivos */
     fecha_no(raiz_velha);
     fecha_no(nova);
   }

 }


 


/*!
 * \brief procura recursivamente pela folha onde se deve inserir a chave. Na volta da recursao, insere nos niveis superiores
 */
void acha_folha_ins(int chave[2], int pagina, int retorno[3], int *prox_chave){ 
  
  tipoNo *no;

  int i;
  
  /* Abre arquivo e o le */
  no = abre_no(pagina, FOLHA);
  
  if(no->tipo == FOLHA){ 
    insere_folha(no, chave, retorno, prox_chave); 
    if(retorno[2] != ERRO)
      printf("Chave inserida com sucesso!\n\n");  
  } 
  else{ 
    /* Acha proxima folha */ 
    for(i=0; i<no->n_elementos; i++){
      if(chave[0] < no->chaves[i])
	break;
    }
    acha_folha_ins(chave, no->apontadores[i], retorno, prox_chave);
    
  
    /* Em caso de split insere na arvore novos elementos */  
    if(retorno[1] != OK && retorno[2]  != ERRO) 

      insere_arvore(no, retorno, prox_chave); 
  } 
  fecha_no(no);
}
 

/*!
 * \brief Insre elemento na folha correta
 */
void insere_folha(tipoNo *no, int chave[2], int retorno[3], int *prox_chave){

  int i, j;
  tipoNo *nova;
  /* Vetor que contem a chave a ser inserida no nivel acima.
     Se os valores forem OK, OK, OK, significa que novas chaves nao precisam ser inseridas */
  retorno[0] = OK;
  retorno[1] = OK;
  retorno[2] = OK;

  /* Insere na folha */
  if(no->n_elementos <= CHAVES){
    /* Insercao simples */
    for(i=0; i<no->n_elementos; i++){
      if(chave[0] == no->chaves[i]){
	retorno[2] = ERRO;
	printf("Erro! Chave repetida! Por favor, adicione uma nova chave\n\n\n");
	return;
      }
      if(chave[0] < no->chaves[i])
	break;
    }

    
    for(j=no->n_elementos; j>i; j--){
      no->chaves[j] = no->chaves[j-1];
      no->nrr[j] = no->nrr[j-1];
    }
    
    no->chaves[i] = chave[0];
    no->nrr[i] = chave[1];
    no->n_elementos++;  
   
   }

  /* Verifica se deu overflow */
  if(no->n_elementos == CHAVES+1){
      
   /*split:*/

    *prox_chave = *prox_chave +1;

    nova = abre_no(*prox_chave, FOLHA);
    /* Copia chaves para nova estrutura */
    for(i=CHAVES/2 + CHAVES%2; i<=CHAVES; i++){
      chave[0] = no->chaves[i];
      chave[1] = no->nrr[i];
      insere_folha(nova, chave, retorno, prox_chave);
    }
    
    no->n_elementos = CHAVES/2 + CHAVES%2;
    nova->prox_dir = no->prox_dir;
    nova->prox_esq = no->posicao;
    no->prox_dir = *prox_chave;
    
    /* retorno[0] possui o delimitador (copia da primeira chave do no da direita */
    retorno[0] = nova->chaves[0];
    /* retorno[1] e [2] possuem os apontadores para as novas folhas */
    retorno[1] = no->posicao;
    retorno[2] = nova->posicao; 

    fecha_no(nova);
  }
}


/*!
 * \brief Insere elemento em noh da arvore 
 */  
void insere_arvore(tipoNo *no, int dados[3], int *prox_chave){
  int i, j;
  tipoNo *nova;
  
  /* Insere na folha */
  if(no->n_elementos <= CHAVES){
    /* Insercao simples */
    for(i=0; i<no->n_elementos; i++){
      if(dados[0] < no->chaves[i])
	break;
    }
    
    
    for(j=no->n_elementos;  j>i; j--){
      no->chaves[j] = no->chaves[j-1];
      no->apontadores[j+1] = no->apontadores[j]; 
    }
    
    
    no->chaves[i] = dados[0];
    no->apontadores[i] = dados[1];
    no->apontadores[i+1] = dados[2];
    no->n_elementos++;  

  }
  if(no->n_elementos <= CHAVES){
    /* Muda os valores de dados, para nao inserir mais nenhum elemento */
    dados[0] = OK;
    dados[1] = OK;
    dados[2] = OK;
  }
  else 
    if(no->n_elementos == CHAVES+1){
    
      
      /*split:*/
      
      *prox_chave = *prox_chave + 1;
      nova = abre_no(*prox_chave, NO);
      /* Copia chaves para nova estrutura */
      for(i=CHAVES/2 + 1; i<=CHAVES; i++){
	dados[0]=no->chaves[i];
	dados[1]=no->apontadores[i];
	dados[2]=no->apontadores[i+1];
	insere_arvore(nova, dados, prox_chave);
      }
      
      no->n_elementos = CHAVES/2;
      
      
      /* resposta[0] possui o delimitador (elemento do meio dos nos) */
      dados[0] = no->chaves[CHAVES/2];
      /* resposta[1] e [2] possuem os apontadores para as novas folhas */
      dados[1] = no->posicao;
      dados[2] = nova->posicao;

      fecha_no(nova);
    } 
}
