#include<stdio.h>
#include "arvore.c"
#include "defines.h"


/* Interface de utilizacao da arvore B+ */
int main(){


  tipoNo *arvore = (tipoNo *) malloc(sizeof(tipoNo)*100);
  char opcao, c;

  insere();

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
      /* ... */
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
