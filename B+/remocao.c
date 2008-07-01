/*implementacao de funcoes de remocao em arvore B+*/

#include<stdio.h>
#include<strings.h>
#include<malloc.h>
#include "defines.h"
#include "leitura.h"
#include "insercao.h"


/*rotirna de remocao de no em uma arvore B+*/
void remove(&ultima_chave, &nrr){

  int chave, resposta[3];
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
    acha_folha_rem(chave, no->apontadores[i], retorno, prox_chave);
    
  
    /*em caso de split insere na arvore novos elementos*/  
    if(retorno[1] != OK) 
      remove_arvore(no, retorno, prox_chave); 
  } 
  fecha_no(no);
}


