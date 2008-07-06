/*implementacao de funcoes de remocao em arvore B+*/

#include<stdio.h>
#include<strings.h>
#include<malloc.h>
#include "defines.h"
#include "leitura.h"
#include "insercao.h"


/*rotirna de remocao de no em uma arvore B+*/
void remove(&ultima_chave, &nrr){

  int chave, resposta[3] = {NADA, NADA, NADA};
  /*le chave a ser removida*/
  printf("Digite a chave a ser inserida\n"); 
  scanf("%d", &chave);

  /*acha a folha onde acontecera a remocao*/
  acha_folha_rem(chave, ROOT, resposta, ultima_chave);
}


/*procura recursivamente pela folha onde se deve remover a chave. 
  Na volta da recursao, se necessario, faz merge dos nos superiores*/
void acha_folha_rem(int chave, int pagina, int retorno[3], int *prox_chave){ 
  
  tipoNo *no;

  int i;
  
  /*abre arquivo e le ele*/
  no = abre_no(pagina, FOLHA);
  
  /*se eh uma folha, remove a chave desejada*/
  if(no->tipo == FOLHA){ 
    remove_folha(no, chave, retorno, prox_chave); 
    if(retorno[2] != ERRO)
      printf("Chave removida com sucesso!\n\n");  
  } 
  else{ 
    /*acha proxima folha*/ 
    for(i=0; i<no->n_elementos; i++){
      if(chave <= no->chaves[i])
	break;
    }

    /*retorno[0] e [1] possuem o endereco dos irmaos da esquerda e da direita da folha em que a chave sera removida
     
    /*se a folha corresponde ao primeiro apontador do noh, ela nao tem irmao a esquerda.*/
    if(i==0)
      retorno[0] = NADA; 
    else
      retorno[0] = apontadores[i-1];
   
    /*se a folha corresponde ao ultimo apontador do noh, ela nao tem irmao a direita*/
    if(i == CHAVES-1)
      retorno[1] = NADA;
    else
      retorno[1] = apontadores[i+1]

    acha_folha_rem(chave, no->apontadores[i], retorno, prox_chave);
    
  
    /*em caso de split insere na arvore novos elementos*/  
    if(retorno[1] != OK) 
      remove_arvore(no, retorno, prox_chave); 
  } 
  fecha_no(no);
}


/*insre elemento na folha correta*/
void remove_folha(tipoNo *no, int chave, int retorno[3], int *prox_chave){

  int i, j, chave_viz[2];
  tipoNo *nova, *pai;

  /*remove elemento da folha*/
     
  for(i=0; i<no->n_elementos; i++){
    if(chave[0] == no->chaves[i]){
      break;
    }
  }
  
  if(i==no->n_elementos){
    retorno[2] = ERRO;
    printf("Erro! A chave nao foi encontrada! Por favor, tente de novo!\n\n\n");
    return;
  }
    
  for(j=i j<no->n_elementos;j++){
    no->chaves[j] = no->chaves[j+1];
    no->nrr[j] = no->nrr[j+1];
  }
  
  no->n_elementos--;  
  
    


  /*remocao simples*/ 
  if(no->n_elementos >= CHAVES/2 || no->posicao == 0){
    
    /*vetor que contem informacoes sobre o que deve acontecer com o resto da arvore, apos remocao
      de elementos da lista. Se os valores forem -1, -1, -1 nada deve ser feito.*/
    retorno[0] = OK;
    retorno[1] = OK;
    retorno[2] = OK;
  }
  
  /*verifica se deu underflow*/
  else 
    if(no->n_elementos < CHAVES/2){
      
      /*rotacao*/
      
      /*rotacao com a esquerda*/
      /*confere se a folha da esquerda eh "filha" do mesmo pai*/
      if(retorno[0] != NADA){
	nova = abre_no(no->prox_esq);
	
	/*confere se a folha da esquerda pode "emprestar" sua chave*/ 
	if(nova->n_elementos > CHAVES/2){
	
	  /*insere a ultima chave da esquerda como primeiro elemento do no atual, evitando underflow*/
	  chave_viz[0] = nova->chaves[nova->n_elementos-1];
	  chave_viz[1] = nova->nrr[nova->n_elementos-1];

	  remove_folha(nova, chave_viz[0], retorno, prox_chave); 
	  insere_folha(no, chave_viz, retorno, prox_chave);

	  /*atualiza delimitador (se a folha nao for a raiz)*/
	  if(no->posicao != NADA){
	    pai = abre_no(retorno[2]);
	    for(i=0; i<pai->n_elementos; i++){
	      if(pai->chaves[i] > no->chaves[0] && pai->chaves[i] < no->chaves[1])
		break;
	    }
	    /*o novo delimitador corresponde ao primeiro elemento da arvore */
	    pai->chaves[i] = no->chaves[0];
	  
	    fecha_no(pai);  
	  }
	}
	retorno[0] = OK;
	retorno[1] = OK;
	retorno[2] = OK;
	fecha_no(nova);

	return;
      }

      /*rotacao com a direita*/
      /*confere se a folha da direita eh "filha" do mesmo pai*/
      if(retorno[1] != NADA){
	nova = abre_no(no->prox_dir);
	
	/*confere se a folha da direita pode "emprestar" sua chave*/ 
	if(nova->n_elementos > CHAVES/2){
	
	  /*insere a primeira chave da direita como ultimo elemento do no atual, evitando underflow*/
	  chave_viz[0] = nova->chaves[0];
	  chave_viz[1] = nova->nrr[0];

	  remove_folha(nova, chave_viz[0], retorno, prox_chave); 
	  insere_folha(no, chave_viz, retorno, prox_chave);

	  /*atualiza delimitador (se a folha nao for a raiz)*/
	  if(no->posicao != NADA){
	    pai = abre_no(retorno[2]);
	    for(i=0; i<pai->n_elementos; i++){
	      if(pai->chaves[i] > no->chaves[no->n_elementos-1] && pai->chaves[i] < no->chaves[no->n_elementos-2])
		break;
	    }
	    /*o novo delimitador corresponde ao primeiro elemento da folha da direita*/
	    pai->chaves[i] = nova->chaves[0];
	  
	    fecha_no(pai);  
	  }
	}
	retorno[0] = OK;
	retorno[1] = OK;
	retorno[2] = OK;
	fecha_no(nova);

	return;
      }




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



