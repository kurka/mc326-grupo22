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
void criaDescritores(ap_tipo_registro_pk vetor_registros , int n_registros , estrutura_descritores_pks vetores_descritores_pks, int *limite_descritores){

  int i;
  FILE *arq_descritor;

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

  /* Chama a funcao de insercao de descritores para cada uma das PKs ja inseridas na base */
  for(i=0 ; i<n_registros ; i++){
    insereDescritor(vetor_registros[i].titulo , vetor_registros[i].nrr , vetores_descritores_pks, limite_descritores);
  }

  return;
}


/* Carrega as PKs dos arquivos de descritores para os vetores */
void carregaDescritores(estrutura_descritores_pks vetores_descritores_pks, int *limite_descritores){

  ap_tipo_registro_pk vetor_pks;
  FILE *arq_descritor;
  int i,j;
  char pk_lida[TAM_TIT];

  /* Para cada arquivo */
  for(i=DSC0 ; i<=DSC8 ; i++){
    
    /* Abre cada um dos arquivos */
    n_pks=abreArqDsc(i, arq_descritor , vetores_descritores_pks , vetor_pks);
    
    fseek(arq_descritor,0,SEEK_SET);

    /* Para cada PK no arquivo */
    for(j=0 ; j<n_pks ; j++)
      carregaPk(arq_descritor , vetores_descritores_pks , limite_descritores);
    
    fclose(arq_descritor);

  }/* fim do for */
  
  return;
}


void carregaPk(FILE * arq_descritor , estrutura_descritores_pks vetores_descritores_pks , int *limite_descritores){

  char novaPK[MAX_TIT];
  int i;

  /* Observacao: a funcao deixa o cursor na posicao para a proxima PK (se houver) */
  for(i=0 ; i<MAX_TIT ; i++)
    novaPK[i]=fgetc(arq_descritor);

  /* Inserir novaPK no vetor correspondente */

  return;
}




/* Abre o arquivo correto e retorna o numero de PKs nele contido. Alem disso, instancia o apontador 
   para o vetor de PKs na estrutura dos descritores_PKs */
int abreArqDsc(int descritor , FILE * arq_descritor){

  switch(descritor){

  case DSC0:
    arq_descritor=fopen(ARQDSC0,"r");
    break;
  case DSC1:
    arq_descritor=fopen(ARQDSC1,"r");
    break;
  case DSC2:
    arq_descritor=fopen(ARQDSC2,"r");
    break;
  case DSC3:
    arq_descritor=fopen(ARQDSC3,"r");
    break;
  case DSC4:
    arq_descritor=fopen(ARQDSC4,"r");
    break;
  case DSC5:
    arq_descritor=fopen(ARQDSC5,"r");
    break;
  case DSC6:
    arq_descritor=fopen(ARQDSC6,"r");
    break;
  case DSC7:
    arq_descritor=fopen(ARQDSC7,"r");
    break;
  case DSC8:
    arq_descritor=fopen(ARQDSC8,"r");
    break;
    
  }/*fim do switch*/
  
  fseek(arq_descritor,0,SEEK_END);
  
  return(ftell(arq_descritor)/TAM_TIT);

}


/* Insere a PK fornecida no arquivo e no vetor correspondentes ao seu descritor */
void insereDescritor(char *titulo , int NRR , estrutura_descritores_pks vetores_descritores_pks, int *limite_descritores){

  int i, descritor, limite[2];
  FILE *base, *arq_descritor;
  char arquivo_img[TAM_IMG+1], path[TAM_DIR+TAM_IMG+1];
  ap_tipo_registro_pk vetor_pks;

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
    vetor_pks = vetores_descritores_pks.vetor_pks_dsc0;
    limite[0]=limite_descritores[DSC0][0];
    limite[1]=limite_descritores[DSC0][1];
    break;
  case DSC1:
    arq_descritor=fopen(ARQDSC1,"a");
    vetor_pks = vetores_descritores_pks.vetor_pks_dsc1;
    limite[0]=limite_descritores[DSC1][0];
    limite[1]=limite_descritores[DSC1][1];
    break;
  case DSC2:
    arq_descritor=fopen(ARQDSC2,"a");
    vetor_pks = vetores_descritores_pks.vetor_pks_dsc2;
    limite[0]=limite_descritores[DSC2][0];
    limite[1]=limite_descritores[DSC2][1];
    break;
  case DSC3:
    arq_descritor=fopen(ARQDSC3,"a");
    vetor_pks = vetores_descritores_pks.vetor_pks_dsc3;
    limite[0]=limite_descritores[DSC3][0];
    limite[1]=limite_descritores[DSC3][1];
    break;
  case DSC4:
    arq_descritor=fopen(ARQDSC4,"a");
    vetor_pks = vetores_descritores_pks.vetor_pks_dsc4;
    limite[0]=limite_descritores[DSC4][0];
    limite[1]=limite_descritores[DSC4][1];
    break;
  case DSC5:
    arq_descritor=fopen(ARQDSC5,"a");
    vetor_pks = vetores_descritores_pks.vetor_pks_dsc5;
    limite[0]=limite_descritores[DSC5][0];
    limite[1]=limite_descritores[DSC5][1];
    break;
  case DSC6:
    arq_descritor=fopen(ARQDSC6,"a");
    vetor_pks = vetores_descritores_pks.vetor_pks_dsc6;
    limite[0]=limite_descritores[DSC6][0];
    limite[1]=limite_descritores[DSC6][1];
    break;
  case DSC7:
    arq_descritor=fopen(ARQDSC7,"a");
    vetor_pks = vetores_descritores_pks.vetor_pks_dsc7;
    limite[0]=limite_descritores[DSC7][0];
    limite[1]=limite_descritores[DSC7][1];
    break;
  case DSC8:
    arq_descritor=fopen(ARQDSC8,"a");
    vetor_pks = vetores_descritores_pks.vetor_pks_dsc8;
    limite[0]=limite_descritores[DSC8][0];
    limite[1]=limite_descritores[DSC8][1];
    break;
  }/*fim do switch*/

  /* Insere o titulo no arquivo e fecha-o */
  for(i=0 ; i<TAM_TIT ; i++)
    fputc(titulo[i],arq_descritor);
  fclose(arq_descritor);

  /* Insere o titulo no vetor das PKs daquele descritor */
  vetor_pks = novopk(titulo, vetor_pks, limite, NRR);

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



void consultaSingulares(estrutura_descritores_pks vetores_descritores_pks){
  
  char PK_procurada[TAM_TIT], arquivo_img[TAM_IMG+1], path[TAM_DIR+TAM_IMG+1];
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
  arquivo_img[i]='.'; i++;
  for( ; i<(TAM_IMG+1) ; i++)
    arquivo_img[i]=fgetc(base);
  fclose(base);
  
  sprintf(path,"%s%s",DIRIMG,arquivo_img);

  /* Calcula o descritor daquela img */
  descritor=ContaUns(CalculaDescritor(path));
  
  /* Funcoes que, para cada descritor proximo do procurado, gera um vetor com as PKs das obras mais similares */
  verificaSimilares(descritor-1);
  verificaSimilares(descritor);
  verificaSimilares(descritor+1);
 
  /* Gera um HTML com as obras similares */
  listaSimilares();
  
  return;
}

void inicia_limite_descritores(int *limite_descritores){

  int i;

  for(i=0 ; i<DSC8 ; i++){
    limite_descritores[i][0]=0;
    limite_descritores[i][1]=MEM_INIT;
  }

  return;
}
