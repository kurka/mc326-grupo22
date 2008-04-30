#include<stdio.h>
#include "defines.h" 
#include "fopen.h"

/*confere se existe e abre ou cria arquivo base22.dat*/
FILE * abre_base22(FILE *arq_base, int *n_registros){
 
  int temp;
  
  arq_base=fopen("base22.dat","r+");
  
  if(arq_base == NULL){
    if(DEBUG)
      printf("\n>>>Arquivo base22 inexistente: base sera criada\n");
    arq_base=fopen("base22.dat","w");
  }

  /* Esta rotina retorna o numero de registros do arquivo da base de dados*/
  fseek(arq_base,0,SEEK_END);
  temp = ftell(arq_base)/TAM_REGISTRO;

  *n_registros = temp;
  
  if(DEBUG)
    printf("\n>>>Numero de registros: %d\n",(*n_registros));

  return arq_base;
}

/*confere se existe e abre ou cria arquivo pk.dat*/
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
    /*se pk possui tamanho 0, as chaves primarias serao
      coletadas a partir do arquivo base.dat */ 
    temp = ftell(arq_pk);
  }

  if(temp==0){
    arq_pk=fopen("pk.dat","w");
  }
  
  *pk = temp;
  return arq_pk;
}


/*confere se existe e abre ou cria arquivo cabeca_avail_base.dat*/
FILE * abre_avail(FILE *arq_cabeca_avail_base, int *cabeca_avail_base){
  
  int temp = -1;
  /* Abre o arquivo que contem a cabeca da avail list da base em modo leitura e escrita */
  arq_cabeca_avail_base = fopen("cabeca_avail_base.dat","r+");
  
  /*Caso a avail list seja vazia, nao ha nenhum registro apagado*/
  if (arq_cabeca_avail_base==NULL) {
    
    if(DEBUG)
      printf("\n>>>Nao existe arq com a cabeca da avail. Criando...\n\n");
    /* O arquivo eh criado com valor -1*/
    arq_cabeca_avail_base = fopen("cabeca_avail_base.dat","w+");
    fprintf(arq_cabeca_avail_base, "%05d", temp);
  }
  else{
    /*guarda em cabeca_avail_base a cabeca do avail list*/
    fscanf(arq_cabeca_avail_base, "%05d", &temp);
  }
  
  if(DEBUG)
    printf(">>>Cabeca avail list = %d", temp);

  *cabeca_avail_base = temp;
  return arq_cabeca_avail_base;
}






