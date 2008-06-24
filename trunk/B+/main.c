#include<stdio.h>


insere(tipoNo *arvore){
  
  int chave;
  
  /*le a chave a ser inserida*/
  printf("Digite a chave a ser inserida\n");
  scanf("%d", &chave);
    
    
  /*abre arquivo 0*/
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



/* Interface de utilizacao da arvore B+ */
int main(){

  tipoNo *arvore = (tipoNo *) malloc(sizeof(tipoNo)*100);
  char opcao, c;

  insere(arvore);

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
