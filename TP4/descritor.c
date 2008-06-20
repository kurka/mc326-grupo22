/* Definicao da biblioteca das funcoes de manipulacao dos descritores */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "base.h"
#include "pk.h"
#include "descritor.h"
#include "libimg.h"


/* Verifica se ja existem arquivos com os descritores. */
/* Retorna OK(0) ou ERRO(-1) */
int verificaDescritores(){

  int i;
  FILE * arq_dsc_generico;

  /* Testa a abertura de cada um dos arquivos. Caso um deles nao exista, a funcao retorna ERRO */
  for(i=DSC0 ; i<=DSC8 ; i++) {
    
    arq_dsc_generico = (FILE *)abreArquivoDescritor(i,MODOR);

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
  char PK_lida[TAM_TIT], nome_arq_img[TAM_IMG+2], nome_arq_img2[TAM_IMG+2], path[TAM_DIR+TAM_IMG+1];

  if(DEBUG) printf(">>> Criando arquivos pks_dscX.dat a partir da base...\n");

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

  if(DEBUG) printf(">>> Criados arquivos pks_dscX.dat vazios!\n");

  base=fopen(ARQBASE,"r");
  fseek(base,0,SEEK_END);
  n_registros=(ftell(base))/TAM_REGISTRO;

  /* Para cada registro contido na base, verifica se ele ja foi removido. Se sim, pula para o proximo. 
     Caso contrario, calcula seu descritor e insere-o no arquivo correspondente */
  for(i=0 ; i<n_registros ; i++){

    if(DEBUG) printf(">>> Lendo registro %d e inserindo-o em pks_dscX.dat...\n",i);

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

    nome_arq_img[TAM_IMG+1] = '\0';
      /* Identificador de obra apagada: '*' no PRIMEIRO CAMPO da imagem */
    if(nome_arq_img[0]!='*'){
      strcpy(nome_arq_img2, nome_arq_img);
        /* path = diretorio + arquivo */
      sprintf(path,"%s%s", DIRIMG, nome_arq_img);
        
      /* Calcula descritor da obra */
      descritor=ContaUns(CalculaDescritor(path));
      /* Abre o arquivo correspondente aquele descritor no modo "a" */
      arq_descritor = (FILE *)abreArquivoDescritor(descritor,MODOA);
      /* Escreve PK no arquivo pks_dscX.dat */
      for(j=0 ; j<TAM_TIT ; j++)
	fputc(PK_lida[j] , arq_descritor);
      /* Escreve o nome do arquivo daquela obra */
/*       for(j=0 ; j<(TAM_IMG+1) ; j++) */
/* 	fputc(nome_arq_img[j] , arq_descritor); */
      fprintf(arq_descritor, "%s", nome_arq_img);

      fclose(arq_descritor);

    }/*fim do if*/
  }/*fim do for*/

  fclose(base);

  return;
}

/* Funcao chamada pelo main para pesquisa por similaridade */
void listaObrasSimilares(){

  estrutura_pk_imagem entrada;
  int n_obras_a_listar, descritor_entrada, n_obras_similares, n;
  estrutura_pk_imagem_similaridade *obras_similares;
  
  printf("Pesquisa por similaridade de obras:\n");

  /* Le o nome da obra e grava em entrada.titulo[] */
  leTitulo(entrada.titulo);

  if(DEBUG) printf(">>> PK lida por leTitulo (ja esta errada!): %s\n", entrada.titulo);
  if(DEBUG) printf(">>> Chamando funcao verificaPKDescritores...\n");
  
  /* Caso a funcao aux nao encontre a PK, exibe msg de erro e retorna */
  if(verificaPKDescritores(&entrada, &descritor_entrada)==ERRO){
    printf("A chave procurada nao consta nos registros.\n\n");
    return;
  }
  
  if(DEBUG) printf(">>> A chave foi encontrada! Descritor da obra: %d\n",descritor_entrada);
  
  
  /* Conta quantas obras similares existem para d-1, d e d+1 */
  n_obras_similares=contaObrasSimilares(descritor_entrada - 1) + contaObrasSimilares(descritor_entrada) + contaObrasSimilares(descritor_entrada + 1);
  
  printf("Digite quantas dentre as %d obras similares voce deseja visualizar:\n",n_obras_similares);
  scanf("%d",&n_obras_a_listar);
  
  if((n_obras_a_listar > n_obras_similares) || (n_obras_a_listar < MIN_OBRAS)){
    printf("Entrada invalida.\n\n");
    return;
  }
    
  /* Carrega TODAS as obras similares para o vetor obras_similares (vetor ordenado por similaridade) */
  obras_similares=(estrutura_pk_imagem_similaridade *)malloc(n_obras_similares*(sizeof(estrutura_pk_imagem_similaridade)));

  n=0; /*contador das obras inseridas no vetor*/
  carregaObrasSimilares(descritor_entrada -1 , obras_similares, entrada.path, &n);
  carregaObrasSimilares(descritor_entrada , obras_similares, entrada.path, &n);
  carregaObrasSimilares(descritor_entrada +1 , obras_similares, entrada.path, &n);
  if(DEBUG) printf(">>> Chamando o qsort para ordenar o vetor em funcao da similaridade...\n");
  qsort(obras_similares , n_obras_similares , sizeof(estrutura_pk_imagem_similaridade) , comparaQsortSimilaridade);
  if(DEBUG) printf(">>> Chamando o geraHTML... \n");
  geraHTMLSimilares(obras_similares, n_obras_a_listar);

  printf("Consulta realizada com sucesso!\n Verifique o arquivo %s para visualizar o resultado da pesquisa.\n\n",ARQHTML);

  free(obras_similares);
  
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

/* Esta funcao verifica se uma dada PK existe dentre os arquivos descritores. 
   Seu valor de retorno eh um inteiro OK(se existe) ou ERRO(se nao).
   Alem disso, ela modifica os valores de entrada.path e descritor_entrada, inserindo
   o nome do arquivo da PK procurada e seu descritor.
*/
int verificaPKDescritores(estrutura_pk_imagem *entrada, int *descritor_entrada){

  int i, j, z, n_pks_descritor;
  FILE *arq_descritor;
  char PK_lida[TAM_TIT], img_lida[TAM_IMG+1];

  /* Para cada arquivo de descritores... */
  for(i=DSC0 ; i<=DSC8 ; i++){

    /* Abre o arquivo no modo "r" e calcula o n de pks nele contidas */
    arq_descritor = (FILE *)abreArquivoDescritor(i,MODOR);
    fseek(arq_descritor,0,SEEK_END);
    n_pks_descritor=ftell(arq_descritor)/(TAM_TIT+TAM_IMG+1);

    /* Para cada PK dentro do arquivo... */
    for(j=0 ; j<n_pks_descritor ; j++){

      /* Le PK... */
      fseek(arq_descritor , j*(TAM_TIT+TAM_IMG+1) , SEEK_SET);
      for(z=0 ; z<TAM_TIT ; z++)
	PK_lida[z]=fgetc(arq_descritor);
      
      /* Caso a PK lida seja igual a procurada, retorna o valor para o descritor
	 do registro, retorna o nome do arquivo do registro e a funcao retorna OK*/
      if(strncmpinsensitive(PK_lida , entrada->titulo, TAM_TIT)==0){
	if(DEBUG) printf(">>> Encontrou a PK igual...(entrou no if)\n");
	(*descritor_entrada)=i;
	      
	/* Le o nome do arquivo da imagem */
	for(z=0 ; z<(TAM_IMG+1) ; z++)
	  img_lida[z]=fgetc(arq_descritor);
	/* Passagem por referencia do arquivo... entrada.path = dir + arq */
	sprintf(entrada->path , "%s%s" , DIRIMG , img_lida);

	return(OK);
      }
      
    }/*fim do for (pks internas)*/
    
    fclose(arq_descritor);
    
  }/*fim do for (arquivos)*/

  /* Se a execucao chegar aqui, entao a PK nao foi encontrada dentre os registros */
  return(ERRO);
}


/* Retorna o numero de obras no arquivo de descritores */
int contaObrasSimilares(int descritor){

  int n;
  FILE *arq_descritor;

  /* Caso a funcao seja chamada para os limites inferior ou superior, retorna ZERO  */
  if((descritor<DSC0) || (descritor>DSC8))
    return(0);

  arq_descritor = (FILE *)abreArquivoDescritor(descritor,MODOR);
  fseek(arq_descritor,0,SEEK_END);
  n=ftell(arq_descritor)/(TAM_TIT+TAM_IMG+1);
  fclose(arq_descritor);

  return(n);
}


/* Abre o arquivo de descritor correspondente ao valor de entrada e o modo de abertura ("a","r","a+",etc) */
FILE *abreArquivoDescritor(int descritor, char *modo){

  FILE *arq_descritor;

  switch(descritor){
  case DSC0:
    arq_descritor=fopen(ARQDSC0,modo);
    break;
  case DSC1:
    arq_descritor=fopen(ARQDSC1,modo);
    break;
  case DSC2:
    arq_descritor=fopen(ARQDSC2,modo);
    break;
  case DSC3:
    arq_descritor=fopen(ARQDSC3,modo);
    break;
  case DSC4:
    arq_descritor=fopen(ARQDSC4,modo);
    break;
  case DSC5:
    arq_descritor=fopen(ARQDSC5,modo);
    break;
  case DSC6:
    arq_descritor=fopen(ARQDSC6,modo);
    break;
  case DSC7:
    arq_descritor=fopen(ARQDSC7,modo);
    break;
  case DSC8:
    arq_descritor=fopen(ARQDSC8,modo);
    break;
  }/*fim do switch*/

  return(arq_descritor);

}


/* Funcao que le o titulo da entrada padrao */
void leTitulo(char *titulo) {
  
  int i,resposta;
  char c;
  
  do {
    
    resposta=OK;
    
    printf("Digite o titulo da obra (no maximo 200 caracteres).\n");
    c=getchar();
    
    /* Eliminacao de espacos antes dos caracteres */
    c = come_espaco(c);
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') resposta=ERRO;
    
    i=0;
    
    /* Caracteres a serem inseridos */
    while(c!='\n' && resposta == OK) {
      titulo[i]=c;
      i++;
      /* Remove os espacos entre palavras */
      if(c==' ') c=come_espaco(c);
      else c=getchar();

      /* CASO DE ERRO */
      /* Caso a entrada seja maior que o tamanho limite */
      if((i>=TAM_TIT) && (c!='\n')) {
	resposta = come_excesso(c);
	
	if(resposta==ERRO) printf("ERRO: Tamanho de titulo excedido!\n");
	break;	
      }
    }
    
    if(resposta==OK){
      /* Preenche o resto do vetor com espacos */
      for(;i<TAM_TIT;i++)
	titulo[i]=' ';
    }

  } while(resposta==ERRO);
  
  
  if(DEBUG) printf("Titulo lido.\n");
  
  return;
  
}


/* Funcao que, a partir de um descritor, carrega todas as chaves dos arquivos d-1, d e d+1 em um vetor
   obras_similares[]{ titulo; path; similaridade }. O vetor eh ordenado em funcao da similaridade. */
void carregaObrasSimilares(int descritor, estrutura_pk_imagem_similaridade *obras_similares, char *path_obra_procurada, int *n){

  estrutura_pk_imagem_similaridade obra_lida;
  char nome_arq_img[TAM_IMG+1];
  FILE *arq_descritor;
  int i, j, n_pks_dsc;

  if(descritor<DSC0)
    return;

  arq_descritor = abreArquivoDescritor(descritor , MODOR);
  fseek(arq_descritor , 0 , SEEK_END);
  n_pks_dsc=ftell(arq_descritor)/(TAM_TIT+TAM_IMG+1);

  /* Para cada PK dentro do arquivo pks_dscX.dat */
  for(i=0 ; i<n_pks_dsc ; i++){

    if(DEBUG) printf(">>> Lendo PK e nome do arquivo do registro %d do descritor.\n",i);
    /* Le PK e nome do arquivo e preenche a estrutura com PK, nome do arquivo e similaridade */
    fseek(arq_descritor , i*(TAM_TIT+TAM_IMG+1) , SEEK_SET);
    for(j=0 ; j<TAM_TIT ; j++)
      obra_lida.titulo[j] = fgetc(arq_descritor);
    if(DEBUG) printf(">>>obra_lida.titulo: %s\n",obra_lida.titulo);
    for(j=0 ; j<(TAM_IMG+1) ; j++)
      nome_arq_img[j] = fgetc(arq_descritor);
    if(DEBUG) printf(">>>nome_arq_img: %s\n",nome_arq_img);
    sprintf(obra_lida.path,"%s%s",DIRIMG,nome_arq_img);
    if(DEBUG) printf(">>>obra_lida.path: %s\n",obra_lida.path);
    if(DEBUG) printf(">>>path_obra_lida: %s\n",path_obra_procurada);
    if(DEBUG) printf(">>> Chamada da ComputaSimilaridade...\n");
    obra_lida.similaridade=ComputaSimilaridade(obra_lida.path , path_obra_procurada);

    /* Insere a estrutura obra_lida no vetor de estruturas obras_similares[] */
    obras_similares[(*n)]=obra_lida;
    (*n)++;

  }/*fim do for*/

  fclose(arq_descritor);

  return;
}

/* Funcao auxiliar para a ordenacao usando o qsort */
int comparaQsortSimilaridade(const void *obra1 , const void *obra2){
  return((int)(1000* (((estrutura_pk_imagem_similaridade *)obra2)->similaridade - ((estrutura_pk_imagem_similaridade *)obra2)->similaridade) ));
}


/* Funcao que gera o arquivo html a partir das obras similares */
void geraHTMLSimilares(estrutura_pk_imagem_similaridade *obras_similares, int n_obras_a_listar){

  FILE *arq_html=fopen(ARQHTML,MODOA);
  int i;
  
  fprintf(arq_html,"<html><head></head><body>\n<div align=\"center\">\n");
  fprintf(arq_html,"<br><b>Lista das %d obras similares</b><br><br>", n_obras_a_listar);

  for(i=0 ; i<n_obras_a_listar ; i++){

    fprintf(arq_html, "<b>Obra:</b> %s<br>", obras_similares[i].titulo);
    fprintf(arq_html, "<b>Similaridade:</b> %f<br><br>", obras_similares[i].similaridade);
    fprintf(arq_html, "<b>Imagem:</b><br><br><p><img src=\"%s\"</p><br><hr><br><br>", obras_similares[i].path);
    
  }/*fim do for*/

  fprintf(arq_html,"<br></div></body></html>");

  fclose(arq_html);
  return;
}

