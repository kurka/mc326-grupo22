#include<stdio.h>
#include<malloc.h>
/* #include "arvore.c"  */
#include "defines.h"

void fecha_no(tipoNo *arvore, int a);
void abre_raiz(){
  tipoNo *arvore;
  FILE *arq;
  
  /*abre ou inicializa arquivo 0*/

  arq = fopen("0.dat", "r");
  
  if(arq == NULL) /* se o nó raíz não existe, ou seja, não existe nem árvore, nem mato, nem nada...*/
    {             
      
      /*Criamos o nó raíz, inserimos o primeiro elemento; A Raíz é uma folha*/
      arvore = (tipoNo *)(malloc(sizeof(tipoNo)));
      arvore->tipo = 1; /*a raíz é folha;*/
      arvore->n_elementos = 0;
      arvore->prox_esq = -1;
      arvore->prox_dir = -1; /*-1 significa apontar pra ninguém*/
      arvore->prox_esq = -1;

      printf("a");
      fecha_no(arvore, 0);
    }
  else
    fclose(arq);
  
  return;
}

/*imprime no arquivo informacoes sobre o no*/
void fecha_no(tipoNo *arvore, int numero){

  FILE * arq;
  char nome_arq[TAM_NOME_ARQ];
  int i;
  
  sprintf(nome_arq, "%d", i);
  printf("oi, nome_arq = %s", nome_arq);
  /*dados ficam nessa disposicao no arquivo:
    tipo
    n_elementos
    chave0 chave1 chave2 ...
    apontador0 apontador1 apontador2 apontador3 ...
    prox_esq (se for folha)
    prox_dir (se for folha)
*/
  arq = fopen(nome_arq, "w");
  fseek(arq,0,SEEK_SET); 
  fprintf(arq, "%d\n", arvore->tipo);
  fprintf(arq, "%d\n", arvore->n_elementos);
  for(i=0; i<arvore->n_elementos; i++)
    fprintf(arq, "%d ", arvore->apontadores[i]);
  fprintf(arq, "\n ");
  for(i=0; i<arvore->n_elementos+1; i++)
    fprintf(arq, "%d ", arvore->apontadores[i]);
  fprintf(arq, "\n ");
  if(arvore->tipo == 1){
    fprintf(arq, "%d\n", arvore->prox_esq);
    fprintf(arq, "%d\n", arvore->prox_dir);
  }

  fclose(arq);
  free(arvore);
}


/* Interface de utilizacao da arvore B+ */
int main(){


  tipoNo *arvore = (tipoNo *) malloc(sizeof(tipoNo)*100);
  char opcao, c;

 /*  insere(); */

  /* Interface*/
  do {
    
    printf("Escolha uma das opcoes abaixo e tecle Enter.\n");
    printf("1-) Inserir elemento na arvore.\n");
    printf("2-) Consultar elemento na arvore.\n");
    printf("3-) Remover elemento da arvore.\n");
    printf("4-) Sair.\n");

    opcao=getchar();
    c=getchar();
    
    /* Tratamento de caractere invalido ou caractere(s) a mais */
    if( (c!='\n') || ((opcao!=INSERE)&&(opcao!=CONSULTA)&&(opcao!=REMOVE))){
      while(c!='\n') c=getchar();
      printf("Caractere ou sequencia de caracteres invalido.\n\n\n");
      opcao=0;
    }
    
    switch(opcao){

    case INSERE:
      abre_raiz();
      break;

    case CONSULTA:
      /* ... */
      break;

    case REMOVE:
      /* ... */
      break;

    }/*fim 'switch'*/

  } while(opcao!=SAIR); /*fim 'do-while'*/

  /*

  //remove();
  //consulta();  
  */

  /* 
  //Lembrar: frees e fcloses...
  */

  return(0);
}
