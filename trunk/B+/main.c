#include<stdio.h>
#include<malloc.h>
#include "defines.h"
#include "leitura.h"  
#include "insercao.h"  
#include "remocao.h"  


/*! 
 * \brief Interface de utilizacao da arvore B+ 
 */
int main(){

 /*  char opcao[VETOR], c; */
  int opcao;
  int ultima_chave, nrr;
  FILE * info;

  /*le o numero de nos e a quantidade de nrrs*/
  info = fopen(DADOS, "r");

  if(! info){
    /*se eh a primeira execucao do programa, comeca a arvore do 0*/
    ultima_chave = 0;
    nrr = 0;
  }
  if(info){
    fseek(info, 0, SEEK_SET);
    fscanf(info, "%d", &ultima_chave);
    fscanf(info, "%d", &nrr);
    fclose(info);
  }

 /*  insere(); */

  /* Interface*/
  do {
  
    printf("Escolha uma das opcoes abaixo e tecle Enter.\n");
    printf("1-) Inserir elemento na arvore.\n");
    printf("2-) Consultar elemento na arvore.\n");
    printf("3-) Lista todos os elemento da arvore.\n");
    printf("4-) Remover elemento da arvore.\n");
    printf("0-) Sair.\n");


    scanf("%d", &opcao);
    
    switch(opcao){

    case INSERE:
      insere(&ultima_chave, &nrr);

      espera();
      continue;

    case CONSULTA:
      consulta();

      espera();
      continue;

    case LISTAR:
      lista_elementos();

      espera();
      continue;

    case REMOVE:
      remover(&ultima_chave);
      espera();
      continue;

    case SAIR:
      printf("Fim da execução!\n");
      break;

    default:
      printf("Caractere ou sequencia de caracteres invalido.\n\n\n");
      break;
    }/*fim 'switch'*/

 
  } while(opcao!=SAIR); /*fim 'do-while'*/


  /*salva tamanho da arvore e numero de chaves*/
  info = fopen(DADOS, "w");
  fseek(info, 0, SEEK_SET);
  fprintf(info, "%d ", ultima_chave);
  fprintf(info, "%d", nrr);
  fclose(info);
  
  return(0);
}
