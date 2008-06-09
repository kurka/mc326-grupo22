#include<stdio.h>
#include<malloc.h>
#include "defines.h" 
#include "fopen.h"

/*!
 * \brief Confere se existe e abre ou cria arquivo base22.dat
 */
FILE * abre_base22(FILE *arq_base, int *n_registros){
  
  int temp;
  
  arq_base=fopen("base22.dat","r+");
  
  if(arq_base == NULL){
    if(DEBUG)
      printf("\n>>>Arquivo base22 inexistente: base sera criada\n");
    arq_base=fopen("base22.dat","w");
  }

  /* Esta rotina retorna o numero de registros do arquivo da base de dados */
  fseek(arq_base,0,SEEK_END);
  temp = ftell(arq_base)/TAM_REGISTRO;

  *n_registros = temp;
  

  return arq_base;
}

/*!
 * \brief Confere se existe e abre ou cria arquivo pk.dat
 */
FILE * abre_pk(FILE *arq_pk, int *pk){
  /* temp (depois pk) indica se o arquivo pk.dat possui 
     conteudo (1 sim, 0 nao) para ser gerado ou nao a partir da base */
  int temp=1;
  arq_pk=fopen("pk.dat","r");
  
  if(!arq_pk){
    temp=0;
  }
  if(arq_pk){
    fseek(arq_pk,0,SEEK_END);
    /* Se pk possui tamanho 0, as chaves primarias serao
      coletadas a partir do arquivo base.dat */ 
    temp = ftell(arq_pk)/TAM_PK;
  }

  if(temp==0){
    arq_pk=fopen("pk.dat","w");
  }
  
  *pk = temp;
  return arq_pk;
}


/*!
 * \brief confere se existe e abre ou cria arquivo cabeca_avail_base.dat
 */
FILE * abre_avail(FILE *arq_cabeca_avail_base, int *cabeca_avail_base){
  
  int temp = -1;
  /* Abre o arquivo que contem a cabeca da avail list da base em modo leitura e escrita */
  arq_cabeca_avail_base = fopen("cabeca_avail_base.dat","r+");
  
  /* Caso a avail list seja vazia, nao ha nenhum registro apagado */
  if (arq_cabeca_avail_base==NULL) {
    
    if(DEBUG)
      printf("\n>>>Nao existe arq com a cabeca da avail. Criando...\n\n");
    /* O arquivo eh criado com valor -1 */
    arq_cabeca_avail_base = fopen("cabeca_avail_base.dat","w+");
    fseek(arq_cabeca_avail_base,0,SEEK_SET);
    fprintf(arq_cabeca_avail_base, "%05d", temp);
  }
  else{
    /* Guarda em cabeca_avail_base a cabeca do avail list */
    fseek(arq_cabeca_avail_base,0,SEEK_SET);
    fscanf(arq_cabeca_avail_base, "%05d", &temp);
  }
   
  if(DEBUG)
    printf(">>>Cabeca avail list = %d", temp);

  *cabeca_avail_base = temp;
  return arq_cabeca_avail_base;
}


/*! 
 * \brief Abre ou cria arquivos de chaves secundarias 
 */

FILE * abre_sk(FILE *arq_sk, tipo_arqs_li *arqs_li, int *sk){

  /* temp (depois sk) indica se o arquivo sk.dat possui 
     conteudo (1 sim, 0 nao) para ser gerado ou nao a partir da base */
  int temp=1;
  arq_sk=fopen("sk.dat","r");
  
  if(!arq_sk){
    temp=0;
  }
  if(arq_sk){
    fseek(arq_sk,0,SEEK_END);
    /* Se pk possui tamanho 0, as chaves secundarias serao
      coletadas a partir do arquivo base.dat */ 
    temp = ftell(arq_sk);
  }
  
  if(temp==0){
    arq_sk=fopen("sk.dat","w");
    arqs_li->arq_tit_li = fopen("li_titulos.dat", "w+");
    arqs_li->arq_tip_li = fopen("li_tipos.dat", "w+");  
    arqs_li->arq_aut_li = fopen("li_autores.dat", "w+");  
    arqs_li->arq_ano_li = fopen("li_anos.dat", "w+");  
  }

  else
    arqs_li->arq_tit_li = fopen("li_titulos.dat", "r+");
    arqs_li->arq_tip_li = fopen("li_tipos.dat", "r+");  
    arqs_li->arq_aut_li = fopen("li_autores.dat", "r+");  
    arqs_li->arq_ano_li = fopen("li_anos.dat", "r+");  
  
  *sk = temp;
  return arq_sk;



 }


/*! 
 * \brief Para nao voltar abruptamente para o menu, pede para o usuario digitar algo para prosseguir 
 */
void espera(){
  printf("\nPressione a tecla enter para voltar ao menu...\n");
  getchar();
}


/*!
 * \brief Desaloca memoria alocada nas estruturas durante a execucao
 */
void liberamemoria(tipo_registro_pk *vetor_registros, tipo_arqs_li *arqs_li, tipo_vetores_sk *vetores_sk){
  int i;

 
  free(vetor_registros);
  free(arqs_li);
  
  for(i=0;i<vetores_sk->titulo->n_sk;i++)
    free(vetores_sk->titulo->vetor_SK[i].chave);
  for(i=0;i<vetores_sk->tipo->n_sk;i++)
    free(vetores_sk->tipo->vetor_SK[i].chave);
  for(i=0;i<vetores_sk->autor->n_sk;i++)
    free(vetores_sk->autor->vetor_SK[i].chave);
  for(i=0;i<vetores_sk->ano->n_sk;i++)
    free(vetores_sk->ano->vetor_SK[i].chave);
  
  free(vetores_sk->titulo->vetor_SK);
  free(vetores_sk->tipo->vetor_SK);
  free(vetores_sk->autor->vetor_SK);
  free(vetores_sk->ano->vetor_SK);
  free(vetores_sk->titulo);
  free(vetores_sk->tipo);
  free(vetores_sk->autor);
  free(vetores_sk->ano);
  free(vetores_sk);
  
}
