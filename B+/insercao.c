/*implementacao de funcoes de insercao em arvore B+*/

#include<stdio.h>
#include<strings.h>
#include<malloc.h>
#include "defines.h"
#include "leitura.h"
#include "insercao.h"


/*faz a insercao de chave na arvore*/
void insere(int *prox_chave, int *nrr) { 
  int chave[2]; 

  tipoNo *nova, *raiz_velha, *raiz_velha_dir; 
  int resposta[3];
   
   
   /*le a chave a ser inserida*/
   printf("Digite a chave a ser inserida\n"); 
   scanf("%d", &chave[0]);
   /*guarda o nrr da chave*/
   *nrr = *nrr + 1;
   chave[1] = *nrr;
      
   /*acha a folha */
   acha_folha(chave, 0, resposta, prox_chave);

   if(resposta[2] != -1){
     /*se a funcao retornar algo diferente de -1, significa que a raiz sofreu split*/   
     *prox_chave = *prox_chave+1;
     nova = abre_no(*prox_chave, NO);
     /*  insere na folha*/
     nova->chaves[0] = resposta[0];
     nova->apontadores[0] = resposta[1];
     nova->apontadores[1] = resposta[2];
     nova->n_elementos++;  

     /*faz com que arquivo 0 sempre seja o arquivo raiz*/
     raiz_velha = abre_no(0, FOLHA);
     nova->posicao = 0;
     raiz_velha->posicao = *prox_chave;
     nova->apontadores[0] = *prox_chave;

     if(raiz_velha->tipo == FOLHA){
       raiz_velha_dir = abre_no(raiz_velha->prox_dir, FOLHA);
       raiz_velha_dir->prox_esq = *prox_chave;
       fecha_no(raiz_velha_dir);  
     }


     /*salva os arquivos*/
     fecha_no(raiz_velha);
     fecha_no(nova);
   }

 }


 


/*procura recursivamente pela folha onde se deve inserir a chave. Na volta da recursao, insere nos niveis superiores*/
void acha_folha(int chave[2], int pagina, int retorno[3], int *prox_chave){ 
  
  tipoNo *no;

  int i;
  
  /*abre arquivo e le ele*/
  no = abre_no(pagina, FOLHA);
  
  if(no->tipo == 1){ 
    insere_folha(no, chave, retorno, prox_chave); 
    printf("Chave inserida com sucesso!\n\n");  
  } 
  else{ 
    /*acha proxima folha*/ 
    for(i=0; i<no->n_elementos; i++){
      if(chave[0] <= no->chaves[i])
	break;
    }
    acha_folha(chave, no->apontadores[i], retorno, prox_chave);
    
  
    /*em caso de split insere na arvore novos elementos*/  
    if(retorno[1] != -1) 
      insere_arvore(no, retorno, prox_chave); 
  } 
  fecha_no(no);
}
 

/*insre elemento na folha correta*/
void insere_folha(tipoNo *no, int chave[2], int retorno[3], int *prox_chave){

  int i, j;
  tipoNo *nova;
  /*vetor que contem a chave a ser inserida no nivel acima.
    Se os valores forem -1, -1, -1, significa que novas chaves nao precisam ser inseridas*/
  retorno[0] = -1;
  retorno[1] = -1;
  retorno[2] = -1;

  /*  insere na folha*/
  if(no->n_elementos <= CHAVES){
    /*insercao simples*/
    for(i=0; i<no->n_elementos; i++){
      if(chave[0] == no->chaves[i]){
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

  /*verifica se deu overflow*/
  if(no->n_elementos == CHAVES+1){
      
    /*split:*/

    *prox_chave = *prox_chave +1;

    nova = abre_no(*prox_chave, FOLHA);
    /*copia chaves para nova estrutura*/
    for(i=CHAVES/2 + CHAVES%2; i<=CHAVES; i++){
      chave[0] = no->chaves[i];
      chave[1] = no->nrr[i];
      insere_folha(nova, chave, retorno, prox_chave);
    }
    
    no->n_elementos = CHAVES/2 + CHAVES%2;
    nova->prox_dir = no->prox_dir;
    nova->prox_esq = no->posicao;
    no->prox_dir = *prox_chave;
    
    /*retorno[0] possui o delimitador (copia da ultima chave do no da esquerda*/
    retorno[0] = no->chaves[(CHAVES/2 + CHAVES%2)-1];
    /*retorno[1] e [2] possuem os apontadores para as novas folhas*/
    retorno[1] = no->posicao;
    retorno[2] = nova->posicao; 

    fecha_no(nova);
  }
}


/*insere elemento em noh da arvore*/  
void insere_arvore(tipoNo *no, int dados[3], int *prox_chave){
  int i, j;
  tipoNo *nova;
  
  /*  insere na folha*/
  if(no->n_elementos <= CHAVES){
    /*insercao simples*/
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
    /*muda os valores de dados, para nao inserir mais nenhum elemento*/
    dados[0] = -1;
    dados[1] = -1;
    dados[2] = -1;
  }
  else 
    if(no->n_elementos == CHAVES+1){
    
      
      /*split:*/
      
      *prox_chave = *prox_chave + 1;
      nova = abre_no(*prox_chave, NO);
      /*copia chaves para nova estrutura*/
      for(i=CHAVES/2 + 1; i<=CHAVES; i++){
	dados[0]=no->chaves[i];
	dados[1]=no->apontadores[i];
	dados[2]=no->apontadores[i+1];
	insere_arvore(nova, dados, prox_chave);
      }
      
      no->n_elementos = CHAVES/2;
      
      
      /*resposta[0] possui o delimitador (copia da ultima chave do no da esquerda*/
      dados[0] = no->chaves[CHAVES/2];
      /*resposta[1] e [2] possuem os apontadores para as novas folhas*/
      dados[1] = no->posicao;
      dados[2] = nova->posicao;

      fecha_no(nova);
    } 
}
