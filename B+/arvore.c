
#include<stdio.h>
#include<strings.h>
#include<malloc.h>
#include "defines.h"
#include "arvore.h"





/*imprime no arquivo informacoes sobre o no*/
void fecha_no(tipoNo *arvore){

  FILE * arq;
  char nome_arq[TAM_NOME_ARQ];
  int i;
  
  sprintf(nome_arq, "%s%d", DIRETORIO, arvore->posicao);

  /*dados ficam nessa disposicao no arquivo:
    posicao
    tipo
    n_elementos
    chave0 chave1 chave2 ...
    apontador0 apontador1 apontador2 apontador3 ...
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

  if(arvore->tipo == 2){
    for(i=0; i<arvore->n_elementos+1; i++)
      fprintf(arq, "%d ", arvore->apontadores[i]);
    fprintf(arq, "\n");
  }

  if(arvore->tipo == 1){
    fprintf(arq, "%d\n", arvore->prox_esq);
    fprintf(arq, "%d\n", arvore->prox_dir);
  }

  fclose(arq);
  free(arvore);
  return;
}


/*carrega conteudo de uma folha na memoria*/
tipoNo *abre_folha(int numero){
  tipoNo *arvore;
  FILE *arq;
  char arquivo[TAM_NOME_ARQ];
  int i;

  /*abre ou inicializa arquivo 0*/
  sprintf(arquivo, "%s%d", DIRETORIO, numero);

  arq = fopen(arquivo, "r");
  
  if(arq == NULL) /* se o noh não existe*/
    {  
      
      /*Criamos o noh, com elementos nulos */
      arvore = (tipoNo *)(malloc(sizeof(tipoNo)));
      arvore->posicao = numero;
      arvore->tipo = 1; /*a raíz é folha;*/
      arvore->n_elementos = 0;
      arvore->prox_dir = -1; /*-1 significa apontar pra ninguém*/
      arvore->prox_esq = -1;
    }

  else if(arq != NULL) 
    {             
      /*Alocamos o no e registramos seus dados, lendo do arquivo*/
      arvore = (tipoNo *)malloc(sizeof(tipoNo));

      fseek(arq,0,SEEK_SET);
      fscanf(arq, "%d", &arvore->posicao);
      fscanf(arq, "%d", &arvore->tipo);
      
      fscanf(arq, "%d", &arvore->n_elementos);
      
      for(i=0; i<arvore->n_elementos; i++)
	fscanf(arq, "%d ", &arvore->chaves[i]);
      /*fscanf(arq, "\n");*/
      if(arvore->tipo == 2){
	for(i=0; i<arvore->n_elementos+1; i++)
	  fscanf(arq, "%d ", &arvore->apontadores[i]);
      }
      /*fscanf(arq, "\n");*/
      if(arvore->tipo == 1){
	fscanf(arq, "%d", &arvore->prox_esq);
	fscanf(arq, "%d", &arvore->prox_dir);
      }
      fclose(arq);      
    }

  
  
  
  return arvore;
}


/*faz a insercao de chave na arvore*/
void insere(int *prox_chave) { 
  int chave; 
  tipoNo *nova; 
  int resposta[3];
 
   
   
   /*le a chave a ser inserida*/
   printf("Digite a chave a ser inserida\n"); 
   scanf("%d", &chave); 
  
    

   /*acha a folha */
   acha_folha(chave, 0, resposta, prox_chave);

   if(resposta[2] != -1){
     /*se a funcao retornar algo diferente de -1, significa que a raiz sofreu split*/   
     *prox_chave = *prox_chave+1;
     nova = abre_folha(*prox_chave);
     /*  insere na folha*/
     nova->chaves[0] = resposta[0];
     nova->apontadores[0] = resposta[1];
     nova->apontadores[1] = resposta[2];
     nova->n_elementos++;  
     fecha_no(nova);
   }
 }


 
/*   //insere na folha */


/*   //volta inserindo */


/*   /\*caso exista uma raíz, então continuamos a execução...*\/ */
  
  
/*   /\*Este código abaixo terá que ser recursivo*\/ */
/*   /\*chegando até a folha que deve ser inserida*\/ */
/*   i=0; */
/*   fread(arvore, sizeof(tipoNo), 1, arq); */
/*   while(arvore->tipo == 0) */
/*   { */
/*       /\*este while abaixo encontra em qual apontador do nó devemos entrar, a variável i armazena ele*\/              */
/*       while(i<CHAVES && chave > arvore->chaves[i]) */
/*          i++; */
      
/*       montar_nome_arquivo(i, nome_arq); */
/*       fclose(arq); */
/*       arq = fopen(nome_arq , "r"); */
      
/*       fread(arvore, sizeof(tipoNo), 1, arq); */
      
/*   } */
 
/*   /\*se a execução não morreu até aqui, significa que estamos na folha onde o valor deve ser inserido*\/ */
  
  
  
  
  
/*   /\*Comentei a parte do Kurka*\/ */
  
/*   /\*{ */
/*       /\*este while abaixo encontra em qual apontador do nó devemos entrar, a variável i armazena ele*\/              */
/*       while(i<CHAVES && chave > arvore->chaves[i]) */
/*          i++; */
      
/*       montar_nome_arquivo(i, nome_arq); */
/*       fclose(arq); */
/*       arq = fopen(nome_arq , "r"); */
      
/*       fread(arvore, sizeof(tipoNo), 1, arq); */
      
/*   } */
/*   for(i=0; i<arvore[0].n_elementos; i++){ */
/*     if(chave < arvore[0].chaves[i] == 0){ */
/*       if(arvore[0].n_elementos < CHAVES) */
/* 	} */
/*     else */
/*       chave < arvore[0].chaves[i] == 0 */
/*       procura_folha(); */
/*     } */
/*   /\* fopen(ROOT, "a+");*\/ */
/*   /\*acha chave certa*\/ */

/* /\* */
/*   if(insere_folha){ */
/*     /\*insere na folha*\/ */
/*   /\*  if(n < CHAVES) */
/*       //insercao simples */
/*       n++; */
    
/*     if(n = CHAVES) */
/*       /\* */
/*       //futuro: rotacao */
/*       *\/ */

/*       /\* */
/*       //split */
/*       *\/ */


/*    /\*   }*\/ */



/* } */

/*procura recursivamente pela folha onde se deve inserir a chave. Na volta da recursao, insere nos niveis superiores*/
void acha_folha(int chave, int pagina, int retorno[3], int *prox_chave){ 
  
  tipoNo *no;

  int i;
  
  /*abre arquivo e le ele*/
  no = abre_folha(pagina);
  
  if(no->tipo == 1) 
    insere_folha(no, chave, retorno, prox_chave); 
  
  else{ 
    /*acha proxima folha*/ 
    for(i=0; i<no->n_elementos; i++){
      if(chave < no->chaves[i])
	break;
    }
    acha_folha(chave, no->apontadores[i], retorno, prox_chave);
    
  
    /*em caso de split insere na arvore novos elementos*/  
    if(retorno[1] != -1) 
      insere_arvore(no, retorno, prox_chave); 
  } 
  fecha_no(no);
}
 

/*insre elemento na folha correta*/
void insere_folha(tipoNo *no, int chave, int retorno[3], int *prox_chave){

  int i, j;
  tipoNo *nova;
  /*vetor que contem a chave a ser inserida no nivel acima.
    Se os valores forem -1, -1, -1, significa que novas chaves nao precisam ser inseridas*/
  retorno[0] = -1;
  retorno[1] = -1;
  retorno[2] = -1;

  /*  insere na folha*/
  if(no->n_elementos <= CHAVES){
    /*insercao simples*/
    for(i=0; i<no->n_elementos; i++){
      if(chave == no->chaves[i]){
	printf("Erro! Chave repetida! Por favor, adicione uma nova chave\n");
	return;
      }
      if(chave < no->chaves[i])
	break;
    }

    
    for(j=no->n_elementos; j>i; j--){
      no->chaves[j] = no->chaves[j-1];

    }
    
    no->chaves[i] = chave;
    no->n_elementos++;  
   
   }

  /*verifica se deu overflow*/
  if(no->n_elementos == CHAVES+1){
    /*
    //futuro: rotacao
    */
    
    /*split:*/

    *prox_chave = *prox_chave +1;

    nova = abre_folha(*prox_chave);
    /*copia chaves para nova estrutura*/
    for(i=CHAVES/2 + CHAVES%2; i<=CHAVES; i++){
      insere_folha(nova, no->chaves[i], retorno, prox_chave);
    }
    
    no->n_elementos = CHAVES/2 + CHAVES%2;
    no->prox_dir = *prox_chave;
    nova->prox_esq = no->posicao;

    
    /*retorno[0] possui o delimitador (copia da ultima chave do no da esquerda*/
    retorno[0] = no->chaves[(CHAVES/2 + CHAVES%2)-1];
    /*retorno[1] e [2] possuem os apontadores para as novas folhas*/
    retorno[1] = no->posicao;
    retorno[2] = nova->posicao; 

    fecha_no(nova);
  }
}


/*insere elemento em noh da arvore*/  
void insere_arvore(tipoNo *no, int dados[3], int *prox_chave){
  int i, j;
  tipoNo *nova;
  
  /*  insere na folha*/
  if(no->n_elementos <= CHAVES){
    /*insercao simples*/
    for(i=0; i<no->n_elementos; i++){
      if(dados[0] < no->chaves[i])
	break;
    }
    
    
    for(j=no->n_elementos;  j>i; j--){
      no->chaves[j] = no->chaves[j-1];
      no->apontadores[j+1] = no->apontadores[j]; 
    }
    
    
    no->chaves[i] = dados[0];
    no->apontadores[i] = dados[1];
    no->apontadores[i+1] = dados[2];
    no->n_elementos++;  

  }
  if(no->n_elementos <= CHAVES){
    /*muda os valores de dados, para nao inserir mais nenhum elemento*/
    dados[0] = -1;
    dados[1] = -1;
    dados[2] = -1;
  }
  else 
    if(no->n_elementos == CHAVES+1){
      /*
      //futuro: rotacao
      */
      
      /*split:*/
      
      *prox_chave = *prox_chave + 1;
      nova = abre_folha(*prox_chave);
      /*copia chaves para nova estrutura*/
      for(i=CHAVES/2 + CHAVES%2; i<CHAVES; i++){
	dados[0]=no->chaves[i];
	dados[1]=no->apontadores[i];
	dados[2]=no->apontadores[i+1];
	insere_arvore(nova, dados, prox_chave);
      }
      
      nova->n_elementos = CHAVES/2;
      no->n_elementos = CHAVES/2 + CHAVES%2;
      nova->prox_dir = *prox_chave;
      nova->prox_esq = no->posicao;
      fecha_no(nova);
      
      /*resposta[0] possui o delimitador (copia da ultima chave do no da esquerda*/
      dados[0] = no->chaves[(CHAVES/2 + CHAVES%2)-1];
      /*resposta[1] e [2] possuem os apontadores para as novas folhas*/
      dados[1] = no->posicao;
      dados[2] = nova->posicao;

    } 
}
  
  

