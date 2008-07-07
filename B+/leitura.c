
#include<stdio.h>
#include<strings.h>
#include<malloc.h>
#include "defines.h"
#include "leitura.h"





/*!
 * \brief Imprime no arquivo informacoes sobre o no
 */
void fecha_no(tipoNo *arvore){

  FILE * arq;
  char nome_arq[TAM_NOME_ARQ];
  int i;
  
  sprintf(nome_arq, "%s%d", DIRETORIO, arvore->posicao);

  /* Dados ficam nessa disposicao no arquivo:
     posicao
     tipo
     n_elementos
     chave0 chave1 chave2 ...
     nrr0   nrr1   nrr2   ... (se for folha)
     apontador0 apontador1 apontador2 apontador3 ...(se for no)
     prox_esq (se for folha)
     prox_dir (se for folha)
  */
  arq = fopen(nome_arq, "w");
  fseek(arq,0,SEEK_SET); 
  fprintf(arq, "%d\n", arvore->posicao);
  fprintf(arq, "%d\n", arvore->tipo);
  
  fprintf(arq, "%d\n", arvore->n_elementos);
  for(i=0; i<arvore->n_elementos; i++)
    fprintf(arq, "%d ", arvore->chaves[i]);
  fprintf(arq, "\n");

  if(arvore->tipo == FOLHA){
    for(i=0; i<arvore->n_elementos; i++)
      fprintf(arq, "%d ", arvore->nrr[i]);
    fprintf(arq, "\n");
  }

  if(arvore->tipo == NO){
    for(i=0; i<arvore->n_elementos+1; i++)
      fprintf(arq, "%d ", arvore->apontadores[i]);
    fprintf(arq, "\n");
  }

  if(arvore->tipo == FOLHA){

    fprintf(arq, "%d\n", arvore->prox_esq);
    fprintf(arq, "%d\n", arvore->prox_dir);
  }

  fclose(arq);
  free(arvore);
  return;
}


/*!
 * \brief Carrega conteudo de uma folha na memoria 
 */
tipoNo *abre_no(int numero, int tipo){
  tipoNo *arvore;
  FILE *arq;
  char arquivo[TAM_NOME_ARQ];
  int i;

  /* Abre ou inicializa arquivo */
  sprintf(arquivo, "%s%d", DIRETORIO, numero);

  arq = fopen(arquivo, "r");
  
  if(arq == NULL) /* se o noh não existe -> criacao de uma folha*/
    {  
      
      /*Criamos o noh, com elementos nulos */
      arvore = (tipoNo *)(malloc(sizeof(tipoNo)));
      arvore->posicao = numero;
      arvore->tipo = tipo; 
      arvore->n_elementos = 0;

      if(tipo == FOLHA){
	arvore->prox_dir = NADA; /*NADA significa apontar pra ninguem*/
	arvore->prox_esq = NADA;
      }
    }
  
  else if(arq != NULL) 
    {             
      /* Alocamos o no e registramos seus dados, lendo do arquivo */
      arvore = (tipoNo *)malloc(sizeof(tipoNo));

      fseek(arq,0,SEEK_SET);
      fscanf(arq, "%d", &arvore->posicao);
      fscanf(arq, "%d", &arvore->tipo);
      
      fscanf(arq, "%d", &arvore->n_elementos);
      
      for(i=0; i<arvore->n_elementos; i++)
	fscanf(arq, "%d ", &arvore->chaves[i]);

      if(arvore->tipo == FOLHA){
	for(i=0; i<arvore->n_elementos; i++)
	  fscanf(arq, "%d ", &arvore->nrr[i]);
      }
      if(arvore->tipo == NO){
	for(i=0; i<arvore->n_elementos+1; i++)
	  fscanf(arq, "%d ", &arvore->apontadores[i]);
      }
      if(arvore->tipo == FOLHA){
	fscanf(arq, "%d", &arvore->prox_esq);
	fscanf(arq, "%d", &arvore->prox_dir);
      }
      fclose(arq);      
    }
  
  return arvore;
}

/*!
 * \brief Cria uma nova raiz, no caso da arvore subir de nivel
 */
tipoNo *cria_raiz(int numero){
  tipoNo *arvore;


  
  /* Criamos o noh, com elementos nulos */
  arvore = (tipoNo *)(malloc(sizeof(tipoNo)));
  arvore->posicao = numero;
  arvore->tipo = NO; /*a raiz nao eh folha;*/
  arvore->n_elementos = 0;
  
  return arvore;
}

  
/*!
 * \brief Lista as chaves e os respectivos nrrs armazenados na arvore
 */
void lista_elementos(){
  tipoNo *no;
  int prox;
  int i;
  
  /* Abre arquivo e le ele */
  no = abre_no(ROOT, FOLHA);
  /* Procura folha */
  while(no->tipo != 1){
    /* Vai para a folha com elementos de menor valor */
    prox = no->apontadores[0];
    fecha_no(no);
    no = abre_no(prox, FOLHA);
  }

  do{
    printf("Elementos na folha %d:\n", no->posicao); 
    for(i=0; i<no->n_elementos; i++){
      printf("Chave = %d  ", no->chaves[i]); 
      printf("NRR = %d\n", no->nrr[i]); 
    }
    printf("\n");
    prox = no->prox_dir;
    fecha_no(no);  
    if(prox != NADA)
      no = abre_no(prox, FOLHA);
    else
      no = NULL;
  }while(no);
  
  printf("\n\n");

}

/*!
 * \brief Consulta por uma chave secundaria, a pedido do usuario
 */
void consulta(){
  tipoNo *no;
  int busca, prox;
  int i;
  
  printf("Digite a chave que voce deseja buscar\n");

  scanf("%d", &busca);

  /* Abre arquivo e o le */
  no = abre_no(ROOT, FOLHA);
  /* Procura folha */
  while(no->tipo != 1){
    /* Procura a folha onde deve estar o elemento */
    for(i=0; i<no->n_elementos; i++){
      if(busca <= no->chaves[i])
	break;
    }

    prox = no->apontadores[i];
    fecha_no(no);
    no = abre_no(prox, FOLHA);
  }

  for(i=0; i<no->n_elementos; i++){
    if(busca == no->chaves[i]){
      break;
    }
  }
  
  if(i==no->n_elementos){
    printf("A chave procurada nao existe na arvore!\n\n\n");
  }

  else{
    printf("Chave %d encontrada!\n", no->chaves[i]); 
    printf("Chave = %d  ", no->chaves[i]); 
    printf("NRR = %d\n", no->nrr[i]);   

    printf("Para visualizar sua folha, consulte arquivo %d, na pasta files.\n\n\n", no->posicao);
    
    fecha_no(no);  
  }
  
}



/*! 
 *\brief  Para nao voltar abruptamente para o menu, pede para o usuario digitar algo para prosseguir 
 */
void espera(){
  printf("\nPressione a tecla enter para voltar ao menu...\n");
  getchar();
  getchar();
}
