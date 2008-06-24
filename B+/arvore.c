#include <stdio.h>
#include "defines.h"

//insere retorna 1 se a inserção foi efetuada corretamente, e 0 se não
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

  if(arq == NULL) // se o nó raíz não existe, ou seja, não existe nem árvore, nem mato, nem nada...
  {
     //Criamos o nó raíz, inserimos o primeiro elemento; A Raíz é uma folha
     arvore = (tipoNo *)(malloc(sizeof(tipoNo));
     arvore->tipo = 1; //a raíz é folha;
     arvore->n_elementos = 1; 
     arvore->chaves[0] = chave;
     arvore->prox_dir = -1; //-1 significa apontar pra ninguém
     arvore->prox_esq = -1;
     
     
     arq = fopen("0.dat", "w"); //criando o arquivo 0.dat
     fwrite(arvore, sizeof(tipoNo), 1, arq);

     return 1;
  }
  
  //caso exista um raíz, então continuamos a execução...
  
  
  i=0;
  fread(arvore, sizeof(tipoNo), 1, arq);
  while(arvore->tipo == 0)
  {
      //este while abaixo encontra em qual apontador do nó devemos entrar, a variável i armazena ele             
      while(i<CHAVES && chave > arvore->chaves[i])
         i++;
      
     
      
      montar_nome_arquivo(i, nome_arq);

      arq = fopen(nome_arq , "r");
      fread(arvore, sizeof(tipoNo), 1, arq);
      
  }
  //se a execução não morreu até aqui, significa que estamos na folha onde o valor deve ser inserido
  
  
  
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
