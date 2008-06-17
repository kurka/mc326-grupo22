#include <stdio.h>
#include "defines.h"
#include "pk.h"
#include "descritor.h"
#include "libimg.h"


/* main para testes */
int main(){

  int i;
  FILE *teste;
  char titulo[TAM_TIT];

  for(i=0 ; i<TAM_TIT ; i++)
    titulo[i]='a';

  insereDescritor(titulo , 1 , NULL);
  

  return(0);
}

/* Verifica se ja existem arquivos com os descritores. */
/* Retorna OK(0) ou ERRO(-1) */
int verificaDescritores(){

  int i;
  FILE * arq_dsc_generico;

  /* Testa a abertura de cada um dos arquivos. Caso um deles nao existe, a funcao retorna ERRO */
  for(i=DSC0 ; i<=DSC8 ; i++) {
    
    switch(i){
      
    case DSC0:
      arq_dsc_generico=fopen(ARQDSC0,"r");
      if(arq_dsc_generico==NULL)
	return(ERRO);
      else
	fclose(arq_dsc_generico);
      break;

    case DSC1:
      arq_dsc_generico=fopen(ARQDSC1,"r");
      if(arq_dsc_generico==NULL)
	return(ERRO);
      else
	fclose(arq_dsc_generico);
      break;

    case DSC2:
      arq_dsc_generico=fopen(ARQDSC2,"r");
      if(arq_dsc_generico==NULL)
	return(ERRO);
      else
	fclose(arq_dsc_generico);
      break;

    case DSC3:
      arq_dsc_generico=fopen(ARQDSC3,"r");
      if(arq_dsc_generico==NULL)
	return(ERRO);
      else
	fclose(arq_dsc_generico);
      break;

    case DSC4:
      arq_dsc_generico=fopen(ARQDSC4,"r");
      if(arq_dsc_generico==NULL)
	return(ERRO);
      else
	fclose(arq_dsc_generico);
      break;

    case DSC5:
      arq_dsc_generico=fopen(ARQDSC5,"r");
      if(arq_dsc_generico==NULL)
	return(ERRO);
      else
	fclose(arq_dsc_generico);
      break;
      
    case DSC6:
      arq_dsc_generico=fopen(ARQDSC6,"r");
      if(arq_dsc_generico==NULL)
	return(ERRO);
      else
	fclose(arq_dsc_generico);
      break;

    case DSC7:
      arq_dsc_generico=fopen(ARQDSC7,"r");
      if(arq_dsc_generico==NULL)
	return(ERRO);
      else
	fclose(arq_dsc_generico);
      break;

    case DSC8:
      arq_dsc_generico=fopen(ARQDSC8,"r");
      if(arq_dsc_generico==NULL)
	return(ERRO);
      else
	fclose(arq_dsc_generico);
      break;
    } /* fim do switch */
  } /* fim do for */

  /* Caso a funcao nao retornou no for, entao todos os arquivos existem */
  return(OK);
}


/* Cria os arquivos dos descritores a partir dos registros ja existentes */
void criaDescritores(ap_tipo_registro_pk vetor_registros , int n_registros){

  int i;
  FILE *arq_dsc_generico;

  /* Cria os arquivos vazios (como um "touch") */
  arq_dsc_generico=fopen(ARQDSC0,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC1,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC2,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC3,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC4,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC5,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC6,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC7,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC8,"a"); fclose(arq_dsc_generico);

  /* Chama a funcao de insercao de descritores para cada uma das PKs ja inseridas na base */
  for(i=0 ; i<n_registros ; i++){
    

  }

  return;
}


/* Carrega os descritores dos arquivos para um vetor de PKs */
void carregaDescritores(ap_tipo_registro_pk vetor_pks_descritores, int *limite_descritores){

  FILE *arq_dsc_generico;
  int i,j,k, n_pks;
  char *pk_lida;

  /* Para cada descritor */
  for(i=DSC0 ; i<=DSC8 ; i++){

    switch(i){
      
    case DSC0:
      arq_dsc_generico=fopen(ARQDSC0,"r");
      fseek(arq_dsc_generico , 0 , SEEK_END);
      n_pks=ftell(arq_dsc_generico);
      for(j=0 ; j<n_pks ; j++) {
	fseek(arq_dsc_generico , j*450 , SEEK_SET);
	for(k=0 ; k<TAM_TIT ; k++)
	  pk_lida[k]=fgetc(arq_dsc_generico);
	/* insere pk_lida em vetor_pks_descritores[DSC0==0] */
	
	/*Orientacoes para uso da funcao:
	  1)vc precisa ja ter inicializado vetor_pks_descritores
	  2)pk_lida eh do tipo_registro_pk, ou seja, tem um campo 
	  pra chave primaria e outro pra NRR...
	  3)limite tem no campo limite[0] o numero de registros 
	  presentes no vetor_pks_descritores e no limite[1] o 
	  tamanho de memoria alocada para o vetor (se for estourar o tamanho, 
	  a funcao realoca o vetor)
	  
	  essa funcao tb ordena as chaves primarias inseridas...
	  vc tem q julgar se isso vai ser interesante ou nao pra sua aplicacao..
	  
	*/
	/*insere_pk(vetor_pks_descritores, pk_lida, limite[2]);*/
	
      }
      fclose(arq_dsc_generico);
      
      
    }/* fim do switch */
  }/* fim do for */


  return;
}


/* Insere a PK fornecida no arquivo e no vetor correspondentes ao seu descritor */
void insereDescritor(char *titulo , int NRR , tipo_pks_descritores *vetores_descritores_pks){

  int i, descritor;
  FILE *base, *arq_descritor;
  char arquivo_img[TAM_IMG+1], path[TAM_DIR+TAM_IMG+1];

  /* Procura PK_inserida no vetor de PKs */
  /* Encontra o NRR do registro */

  /* A partir do nrr, le o identificador da obra na base */
  base=fopen(ARQBASE,"r");
  fseek(base , ((NRR-1)*TAM_REGISTRO)+MAX_VAL , SEEK_SET);

  /* Obtem o nome do arquivo da imagem */
  for(i=0 ; i<(TAM_IMG-TAM_FORM) ; i++)
    arquivo_img[i]=fgetc(base);
  arquivo_img[i]='.'; i++;
  for( ; i<(TAM_IMG+1) ; i++)
    arquivo_img[i]=fgetc(base);
  fclose(base);
  
  /* Calcula o descritor daquela img */
  sprintf(path,"%s%s",DIRIMG,arquivo_img);
  descritor=ContaUns(CalculaDescritor(path));

  /* Abre o arquivo correspondente aquele descritor */
  switch(descritor){
    
  case DSC0:
    arq_descritor=fopen(ARQDSC0,"a");
    break;
  case DSC1:
    arq_descritor=fopen(ARQDSC1,"a");
    break;
  case DSC2:
    arq_descritor=fopen(ARQDSC2,"a");
    break;
  case DSC3:
    arq_descritor=fopen(ARQDSC3,"a");
    break;
  case DSC4:
    arq_descritor=fopen(ARQDSC4,"a");
    break;
  case DSC5:
    arq_descritor=fopen(ARQDSC5,"a");
    break;
  case DSC6:
    arq_descritor=fopen(ARQDSC6,"a");
    break;
  case DSC7:
    arq_descritor=fopen(ARQDSC7,"a");
    break;
  case DSC8:
    arq_descritor=fopen(ARQDSC8,"a");
    break;
  }/*fim do switch*/

  /* Insere o titulo no arquivo */
  for(i=0 ; i<TAM_TIT ; i++)
    fputc(titulo[i],arq_descritor);
  fclose(arq_descritor);

  /* Insere o titulo no vetor */


  return;
}


/* Recebe o descritor e retorna o numero de 1's de seu correspondente binario */
int ContaUns(char descritor){

  char mask=0x01;
  int i,uns=0;
  
  for(i=0 ; i<TAM_BIN ; i++){
    uns+=((mask & descritor)>0);
    mask=mask<<1;
  }
  
  return(uns);
}



void comparaSimilaridade(){
  
  char PK_procurada[TAM_TIT], arquivo_img[TAM_IMG+1];
  int descritor, NRR, i;
  FILE *base;

  printf("Digite a obra que deseja comparar com outras obras por similaridade (max 200 caracteres).\n ");
  /* le PK_procurada */
  /* procura nrr da obra lida */
  
  /* A partir da base, le o identificador da obra */
  base=fopen(ARQBASE,"r");
  fseek(base , ((NRR-1)*TAM_REGISTRO)+MAX_VAL , SEEK_SET);

  /* Obtem o nome do arquivo da imagem */
  for(i=0 ; i<(TAM_IMG-TAM_FORM) ; i++)
    arquivo_img[i]=fgetc(base);
  i++; arquivo_img[i]='.';
  for(i+=1 ; i<(TAM_IMG+1) ; i++)
    arquivo_img[i]=fgetc(base);
  fclose(base);
  
  /* Calcula o descritor daquela img */
  /* Transforma o descritor de hexa para binario e encontra o numero de 1's */
  /*descritor=hexaToInt(CalculaDescritor(arquivo_img));*/

  /* Funcoes que procuram dentre as obras com descritor proximo do da obra procurada e gera um HTML de consulta */
  /*procuraSimilares(descritor-1);
  procuraSimilares(descritor);
  procuraSimilares(descritor+1);*/

  return;
}
