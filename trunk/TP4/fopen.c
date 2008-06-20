#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include "defines.h" 
#include "fopen.h"

/*!
 * \brief Confere se existe e abre ou cria arquivo base22.dat
 */
FILE * abre_base22(FILE *arq_base, int *n_registros){
  
  int temp;
  
  arq_base=fopen(ARQBASE,"r+");
  
  if(arq_base == NULL){
    if(DEBUG)
      printf("\n>>>Arquivo base22 inexistente: base sera criada\n");
    arq_base=fopen(ARQBASE,"w");
  }

  /* Esta rotina retorna o numero de registros do arquivo da base de dados */
  fseek(arq_base,0,SEEK_END);
  temp = ftell(arq_base)/TAM_REGISTRO;

  *n_registros = temp;
  

  return arq_base;
}



/*!
 * \brief confere se existe e abre ou cria arquivo cabeca_avail_base.dat
 */
FILE * abre_avail(FILE *arq_cabeca_avail_base, int *cabeca_avail_base){
  
  int temp = -1;
  /* Abre o arquivo que contem a cabeca da avail list da base em modo leitura e escrita */
  arq_cabeca_avail_base = fopen(ARQAVAIL,"r+");
  
  /* Caso a avail list seja vazia, nao ha nenhum registro apagado */
  if (arq_cabeca_avail_base==NULL) {
    
    if(DEBUG)
      printf("\n>>>Nao existe arq com a cabeca da avail. Criando...\n\n");
    /* O arquivo eh criado com valor -1 */
    arq_cabeca_avail_base = fopen(ARQAVAIL,"w+");
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
 * \brief Confere se existem arquivos de chaves primarias 
 */
int abre_pk(){

  /* temp (depois sk) indica se *algum* arquivo sk.dat possui 
     conteudo (1 sim, 0 nao) para ser gerado ou nao a partir da base */
  int temp=0;
  int i;
  char arquivo[TAM_NOME_ARQ];
  FILE * teste;
  /*abre cada um dos arquivos de chaves secundarias de titulos (amostra) para ver se algum existe*/

  for(i=0; i<NUM_HASH; i++){
      sprintf(arquivo, "%s%d.dat", ARQPK, i);
  
      teste = fopen(arquivo,"r");
      if(teste){
	fseek(teste,0,SEEK_END);
	temp = ftell(teste);
      }
    }
  return temp;
}


/*! 
 * \brief Confere se existem arquivos de chaves secundarias 
 */
int abre_sk(){

  /* temp (depois sk) indica se *algum* arquivo sk.dat possui 
     conteudo (1 sim, 0 nao) para ser gerado ou nao a partir da base */
  int temp=0;
  int i;
  char arquivo[TAM_NOME_ARQ];
  FILE * teste;
  /*abre cada um dos arquivos de chaves secundarias de titulos (amostra) para ver se algum existe*/

  for(i=0; i<NUM_HASH; i++){
      sprintf(arquivo, "%s%d.dat", ARQSK_TIT, i);
  
      teste = fopen(arquivo,"r");
      if(teste){
	fseek(teste,0,SEEK_END);
	temp = ftell(teste);
      }
  }
  return temp;
}

/*! 
 * \brief Funcao responsavel por calcular o hash de uma chave e retornar o 
    arquivo em que ela deve ser inserida
*/
char *calculaHash(char *chave, char *prefixo){
  int i=0;
  int hash = 0;
  char arquivo[TAM_NOME_ARQ];
  char * retorno;
  
  while(chave[i]!= '\0'){
    hash += (int) chave[i];
    i++;
  }
  hash = hash % NUM_HASH;

 
  sprintf(arquivo, "%s%d.dat", prefixo, hash);

 

  retorno = (char *) malloc(sizeof(char)*(strlen(arquivo)+1)); 
  strcpy(retorno, arquivo);
  return retorno;

}



/*! 
 * \brief Para nao voltar abruptamente para o menu, pede para o usuario digitar algo para prosseguir 
 */
void espera(){
  printf("\nPressione a tecla enter para voltar ao menu...\n");
  getchar();
}


