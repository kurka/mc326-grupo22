#include<stdio.h>
#include<strings.h>
#include<malloc.h>
#include "defines.h"


void montar_nome_arquivo(int n, char *nome_arq);
int insere();
void abre_raiz();
FILE *abre_folha(int numero);
void fecha_no(tipoNo arvore, int numero);

int acha_folha();


void abre_raiz(){
  tipoNo *arvore;
  FILE *arq;
  
  /*abre ou inicializa arquivo 0*/

  arq = fopen("0.dat", "r");
  
  if(arq == NULL) /* se o n� ra�z n�o existe, ou seja, n�o existe nem �rvore, nem mato, nem nada...*/
    {             
      
      /*Criamos o n� ra�z, inserimos o primeiro elemento; A Ra�z � uma folha*/
      arvore = (tipoNo *)(malloc(sizeof(tipoNo)));
      arvore->tipo = 1; /*a ra�z � folha;*/
      arvore->n_elementos = 0;
      arvore->prox_esq = -1;
      arvore->prox_dir = -1; /*-1 significa apontar pra ningu�m*/
      arvore->prox_esq = -1;
      
      fecha_no(arvore, 0);
    }
  else
    fclose(arq);
  
  return;
}

/*imprime no arquivo informacoes sobre o no*/
void fecha_no(tipoNo arvore, int numero){

  FILE * arq;
  char nome_arq[TAM_NOME_ARQ];
  int i;
  
  itoa(i,nome_arq,10);
  /*dados ficam nessa disposicao no arquivo:
    tipo
    n_elementos
    chave0 chave1 chave2 ...
    apontador0 apontador1 apontador2 apontador3 ...
    prox_esq (se for folha)
    prox_dir (se for folha)
*/
  fseek(nome_arq,0,SEEK_SET);
  fprintf(arq, "%d\n", arvore->tipo);
  fprintf(arq, "%d\n", arvore->n_elementos);
  for(i=0; i<n_elementos; i++)
    fprintf(arq, "%d ", arvore->apontadores[i]);
  fprintf(arq, "\n ");
  for(i=0; i<n_elementos+1; i++)
    fprintf(arq, "%d ", arvore->apontadores[i]);
  fprintf(arq, "\n ");
  if(arvore->tipo == 1){
    fprintf(arq, "%d\n", arvore->prox_esq);
    fprintf(arq, "%d\n", arvore->prox_dir);
  }


  fclose(arq);
  free(arvore);
}


/*insere retorna 1 se a inser��o foi efetuada corretamente, e 0 se n�o*/
int insere()
{
  int chave;
  FILE *arq;
  tipoNo *arvore;
  int i;
  char nome_arq[TAM_NOME_ARQ]; /*o 7 deve virar constante depois*/
  
  
  /*le a chave a ser inserida*/
  printf("Digite a chave a ser inserida\n");
  scanf("%d", &chave);
  
    

  //acha a folha
  acha_folha()

  //insere na folha


  //volta inserindo


  /*caso exista uma ra�z, ent�o continuamos a execu��o...*/
  
  
  /*Este c�digo abaixo ter� que ser recursivo*/
  /*chegando at� a folha que deve ser inserida*/
  i=0;
  fread(arvore, sizeof(tipoNo), 1, arq);
  while(arvore->tipo == 0)
  {
      /*este while abaixo encontra em qual apontador do n� devemos entrar, a vari�vel i armazena ele*/             
      while(i<CHAVES && chave > arvore->chaves[i])
         i++;
      
      montar_nome_arquivo(i, nome_arq);
      fclose(arq);
      arq = fopen(nome_arq , "r");
      
      fread(arvore, sizeof(tipoNo), 1, arq);
      
  }
 
  /*se a execu��o n�o morreu at� aqui, significa que estamos na folha onde o valor deve ser inserido*/
  
  
  
  
  
  /*Comentei a parte do Kurka*/
  
  /*{
      /*este while abaixo encontra em qual apontador do n� devemos entrar, a vari�vel i armazena ele*/             
      while(i<CHAVES && chave > arvore->chaves[i])
         i++;
      
      montar_nome_arquivo(i, nome_arq);
      fclose(arq);
      arq = fopen(nome_arq , "r");
      
      fread(arvore, sizeof(tipoNo), 1, arq);
      
  }
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

/*
  if(insere_folha){
    /*insere na folha*/
  /*  if(n < CHAVES)
      //insercao simples
      n++;
    
    if(n = CHAVES)
      /*
      //futuro: rotacao
      */

      /*
      //split
      */


   /*   }*/



}

int acha_folha(int folha){

  //abre arquivo e le ele;

  if( tipo == 1)
    return insere_folha(folha);

  else{
    //acha proxima folha
    chave = acha_folha(prox);
    
    if(chave != -1)
      return insere_arvore(chave);
  
    return -1;  
  }

}


int insere_folha(){

  insere na folha
  if(n < CHAVES)
    //insercao simples
    n++;
  
  if(n == CHAVES)
    /*
    //futuro: rotacao
    */
    /* 
    //split
    */

}


int insere_arvore(){


}

/**/
void montar_nome_arquivo(int n, char *nome_arq)
{
     int i=0;
     sprintf(nome_arq, "%8d", n);

}
