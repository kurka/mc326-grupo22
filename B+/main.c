#include<stdio.h>
#include<malloc.h>
#include "defines.h"
#include "arvore.h"  


/* Interface de utilizacao da arvore B+ */
int main(){

 /*  char opcao[VETOR], c; */
  int opcao;
  int ultima_chave = 0;

 /*  insere(); */

  /* Interface*/
  do {
  
    printf("Escolha uma das opcoes abaixo e tecle Enter.\n");
    printf("1-) Inserir elemento na arvore.\n");
    printf("2-) Consultar elemento na arvore.\n");
    printf("3-) Remover elemento da arvore.\n");
    printf("0-) Sair.\n");


    scanf("%d", &opcao);
    
    switch(opcao){

    case INSERE:
     /*  abre_raiz(); */
      insere(&ultima_chave);
      continue;

    case CONSULTA:
      /* ... */
      continue;

    case REMOVE:
      /* ... */
      continue;

    case SAIR:
      break;

    default:
      printf("Caractere ou sequencia de caracteres invalido.\n\n\n");
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
