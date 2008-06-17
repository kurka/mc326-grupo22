#include <stdio.h>
#include "defines.h"
#include "pk.h"
#include "descritor.h"


/* main para testes */
int main(){

  int a;
  FILE *teste;

  a = verificaDescritores();
  printf("Saida do verificaDescritores(): %d\n", a);

  teste=fopen("teste.dat","a");
  fclose(teste);

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

  /* Cria os arquivos vazios (como um "touch") e n faz nada caso eles existam */
  arq_dsc_generico=fopen(ARQDSC0,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC1,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC2,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC3,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC4,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC5,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC6,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC7,"a"); fclose(arq_dsc_generico);
  arq_dsc_generico=fopen(ARQDSC8,"a"); fclose(arq_dsc_generico);

  base=fopen(ARQBASE,"r"); 
  fseek(base,0,SEEK_SET);

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


/* Insere uma PK fornecida no arquivo correspondente ao seu descritor */
void insereDescritor(int descritor , char *titulo , int NRR){

  FILE *base;
  char arquivo_img;

  /* Procura PK_inserida no vetor de PKs */
  /* Encontra o NRR do registro */
  /* A partir da base, lê o identificador da obra */
  base=fopen(ARQBASE,"r");
  fseek(base , ((NRR-1)*TAM_REGISTRO)+MAX_VAL , SEEK_SET);

  /* Obtem o nome do arquivo da imagem */
  /* Calcula o descritor daquela img */
  /* Transforma o descritor de hexa para binario e encontra o numero de 1's */
  /* Abre o pks_dscX.dat correspondente */
  /* Insere a PK no arquivo daquele descritor */
  /* Fecha o arquivo */

  return;
}


/* Recebe o descritor em hexadecimal e retorna o numero de 1's de seu correspondente binario */
int hexaToInt(char *descritor_hexa){

  char mask=0x01;
  int i,resposta=0;
  
  for(i=0 ; i<TAM_HEXA ; i++){
    resposta+=((mask & descritor_hexa)>0);
    mask=mask<<1;
  }
  
  return(resposta);
}
