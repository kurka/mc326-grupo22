#include <stdio.h>
#include "defines.h"

//insere retorna 1 se a inser��o foi efetuada corretamente, e 0 se n�o
int insere(tipoNo *arvore)
{
  int chave;
  File *arq;
  tipoNo *arvore;
  int i;
  char nome_arq[7];
  
  
  /*le a chave a ser inserida*/
  printf("Digite a chave a ser inserida\n");
  scanf("%d", &chave);
  
    
  
    
  /*abre arquivo 0*/
  arq = fopen("0.dat", "r");

  if(arq == NULL) // se o n� ra�z n�o existe, ou seja, n�o existe nem �rvore, nem mato, nem nada...
  {
     //Criamos o n� ra�z, inserimos o primeiro elemento; A Ra�z � uma folha
     arvore = (tipoNo *)(malloc(sizeof(tipoNo));
     arvore->tipo = 1; //a ra�z � folha;
     arvore->n_elementos = 1; 
     arvore->chaves[0] = chave;
     arvore->prox_dir = -1; //-1 significa apontar pra ningu�m
     arvore->prox_esq = -1;
     
     
     arq = fopen("0.dat", "w"); //criando o arquivo 0.dat
     fwrite(arvore, sizeof(tipoNo), 1, arq);

     return 1;
  }
  
  //caso exista um ra�z, ent�o continuamos a execu��o...
  
  
  i=0;
  fread(arvore, sizeof(tipoNo), 1, arq);
  while(arvore->tipo == 0)
  {
      //este while abaixo encontra em qual apontador do n� devemos entrar, a vari�vel i armazena ele             
      while(i<CHAVES && chave > arvore->chaves[i])
         i++;
      
     
      
      montar_nome_arquivo(i, nome_arq);

      arq = fopen(nome_arq , "r");
      fread(arvore, sizeof(tipoNo), 1, arq);
      
  }
  //se a execu��o n�o morreu at� aqui, significa que estamos na folha onde o valor deve ser inserido
  
  
  
  for(i=0; i<arvore[0].n_elementos; i++){
    if(chave < arvore[0].chaves[i] == 0){
      if(arvore[0].n_elementos < CHAVES)
	}
    else
      chave < arvore[0].chaves[i] == 0
      procura_folha();
    }
  /* fopen(ROOT, "a+");*/
  /*acha chave certa*/


  if(insere_folha){
    /*insere na folha*/
    if(n < CHAVES)
      //insercao simples
      n++;
    
    if(n = CHAVES)
      /*
      //futuro: rotacao
      */

      /*
      //split
      */


      }



}


int insere_folha(){

  /*insere na folha*/
  if(n < CHAVES)
    //insercao simples
    n++;
  
  if(n = CHAVES)
    /*
    //futuro: rotacao
    */

    /*
    //split
    */

}

char * montar_nome_arquivo(int n, char *nome_arq)
{
     int i=0;
     sprintf(nome_arq, "%d", n);

     while(nome_arq[i]!='\0')
        i++;
     nome_arq[i++]= '.';
     nome_arq[i++]= 'd';
     nome_arq[i++]= 'a';
     nome_arq[i++]= 't';
     nome_arq[i]= '\0';  
     
}
