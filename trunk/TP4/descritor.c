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

  printf("verificaDescritores: %d\n\n", verificaDescritores());
  printf("Chamando funcao criaDescritores para a base toda...\n\nDar um ls pks_dsc*\n");
  criaDescritores();

  return(0);
}

/* Verifica se ja existem arquivos com os descritores. */
/* Retorna OK(0) ou ERRO(-1) */
int verificaDescritores(){

  int i;
  FILE * arq_dsc_generico;

  /* Testa a abertura de cada um dos arquivos. Caso um deles nao exista, a funcao retorna ERRO */
  for(i=DSC0 ; i<=DSC8 ; i++) {
    
    switch(i){
      
    case DSC0:
      arq_dsc_generico=fopen(ARQDSC0,"r");
      break;
    case DSC1:
      arq_dsc_generico=fopen(ARQDSC1,"r");
      break;
    case DSC2:
      arq_dsc_generico=fopen(ARQDSC2,"r");
      break;
    case DSC3:
      arq_dsc_generico=fopen(ARQDSC3,"r");
      break;
    case DSC4:
      arq_dsc_generico=fopen(ARQDSC4,"r");
      break;
    case DSC5:
      arq_dsc_generico=fopen(ARQDSC5,"r");
      break;
    case DSC6:
      arq_dsc_generico=fopen(ARQDSC6,"r");
      break;
    case DSC7:
      arq_dsc_generico=fopen(ARQDSC7,"r");
      break;
    case DSC8:
      arq_dsc_generico=fopen(ARQDSC8,"r");
      break;

    } /* fim do switch */

    if(arq_dsc_generico==NULL)
      return(ERRO);
    else
      fclose(arq_dsc_generico);
    
  } /* fim do for */

  /* Caso a funcao nao retornou no for, entao todos os arquivos existem */
  return(OK);
}


/* Cria os arquivos dos descritores a partir dos registros ja existentes */
void criaDescritores(){

  FILE *arq_descritor, *base;
  int i, j, descritor, n_registros;
  char PK_lida[TAM_TIT], nome_arq_img[TAM_IMG+1], path[TAM_DIR+TAM_IMG+1];

  /* Cria os arquivos vazios (como um "touch") */
  arq_descritor=fopen(ARQDSC0,"a"); fclose(arq_descritor);
  arq_descritor=fopen(ARQDSC1,"a"); fclose(arq_descritor);
  arq_descritor=fopen(ARQDSC2,"a"); fclose(arq_descritor);
  arq_descritor=fopen(ARQDSC3,"a"); fclose(arq_descritor);
  arq_descritor=fopen(ARQDSC4,"a"); fclose(arq_descritor);
  arq_descritor=fopen(ARQDSC5,"a"); fclose(arq_descritor);
  arq_descritor=fopen(ARQDSC6,"a"); fclose(arq_descritor);
  arq_descritor=fopen(ARQDSC7,"a"); fclose(arq_descritor);
  arq_descritor=fopen(ARQDSC8,"a"); fclose(arq_descritor);

  base=fopen(ARQBASE,"r");
  fseek(base,0,SEEK_END);
  n_registros=(ftell(base))/TAM_REGISTRO;
  fseek(base,0,SEEK_SET);

  /* Para cada registro contido na base, verifica se ele ja foi removido. Se sim, pula para o proximo. 
     Caso contrario, calcula seu descritor e insere-o no arquivo correspondente */
  for(i=0 ; i<n_registros ; i++){

    /* Le a PK da base */
    fseek(base , i*TAM_REGISTRO , SEEK_SET);
    for(j=0 ; j<TAM_TIT ; j++)
      PK_lida[j]=fgetc(base);
    /* Leva o cursor para o nome do arquivo da imagem */
    fseek(base , (i*TAM_REGISTRO)+MAX_VAL , SEEK_SET);
    /* Le o nome do arquivo da imagem */
    for(j=0 ; j<(TAM_IMG-TAM_FORM) ; j++)
      nome_arq_img[j]=fgetc(base);
    nome_arq_img[j]='.'; j++;
    for( ; j<(TAM_IMG+1) ; j++)
      nome_arq_img[j]=fgetc(base);

    /* Identificador de obra apagada: '*' no PRIMEIRO CAMPO da imagem */
    if(nome_arq_img[0]!='*'){
      
      /* path = diretorio + arquivo */
      sprintf(path,"%s%s",DIRIMG,nome_arq_img);
      
      /* Calcula descritor da obra */
      /*descritor=ContaUns(CalculaDescritor(path));*/
      descritor=0; /* TESTE!! */

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

      /* Escreve PK no arquivo pks_dscX.dat */
      for(j=0 ; j<TAM_TIT ; j++)
	fputc(PK_lida[j] , arq_descritor);
      /* Escreve o nome do arquivo daquela obra */
      for(j=0 ; j<(TAM_IMG+1) ; j++)
	fputc(nome_arq_img[j] , arq_descritor);

      fclose(arq_descritor);

    }/*fim do if*/
  }/*fim do for*/

  fclose(base);

  return;
}



/**********************************/
/******* FUNCOES AUXILIARES *******/
/**********************************/

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

