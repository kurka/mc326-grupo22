#include <stdio.h>
#include "defines.h"
#include "sk.h"
#include "descritor.h"
#include "libimg.h"


/* main para testes */
int main(){

  int i;
  FILE *teste;
  char titulo[TAM_TIT];

  printf("Testando criacao dos descritores...\n\n");

  printf("verificaDescritores: %d\n\n", verificaDescritores());
  printf("Chamando funcao criaDescritores para a base toda... (carrega PKs apenas em DSC0!\n\n");
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

    printf("nome_arq_img[0]: %c",nome_arq_img[0]);
    FILE *arq_teste=fopen("teste.dat","a");
    fputc(nome_arq_img[0],arq_teste);

    /* Identificador de obra apagada: '*' no PRIMEIRO CAMPO da imagem */
    if(nome_arq_img[0]!='*'){
      
      /* path = diretorio + arquivo */
      sprintf(path,"%s%s",DIRIMG,nome_arq_img);
      
      /* Calcula descritor da obra */
      /*descritor=ContaUns(CalculaDescritor(path));*/
      descritor=0; /* TESTE!! */

      /* Abre o arquivo correspondente aquele descritor no modo "a" */
      arq_descritor = (FILE *)abreArquivoDescritor(descritor,MODOA);

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

/* Funcao chamada pelo main para pesquisa por similaridade */
void listaObrasSimilares(){

  printf("chamada funcao listaObrasSimilares\n\n");

  /*estrutura_pk_imagem entrada;
  int n_obras_a_listar, *descritor_entrada, n_obras_similares;
  estrutura_pk_imagem_similaridade *obras_similares;
  
  printf("Pesquisa por similaridade de obras:\n");*/

  /* Le o nome da obra e grava em entrada.titulo[] */
  /*leTitulo(entrada.titulo);*/

  /* Caso a funcao aux nao encontre a PK, exibe msg de erro e retorna */
  /*if(verificaPKDescritores(entrada, descritor_entrada)==ERRO){
    printf("A chave procurada nao consta nos registros.\n\n");
    return;
    }*/

  /* Conta quantas obras similares existem para d-1, d e d+1 */
  /*n_obras_similares=contaObrasSimilares(*descritor_entrada - 1) + contaObrasSimilares(*descritor_entrada) + contaObrasSimilares(*descritor_entrada + 1);

  printf("Digite quantas dentre as %d obras similares voce deseja visualizar:\n",n_obras_similares);
  scanf("%d",&n_obras_a_listar);

  if((n_obras_a_listar > n_obras_similares) || (n_obras_a_listar < MIN_OBRAS)){
    printf("Entrada invalida.\n\n");
    return;
  }*/


  /* Carrega TODAS as obras similares para o vetor obras_similares (vetor ordenado por similaridade) */
  obras_similares=(estrutura_pk_imagem_similaridade *)malloc(n_obras_similares*(sizeof(estrutura_pk_imagem_similaridade)));
  carregaObrasSimilares(*descritor_entrada, obras_similares);
  /* !!! Implementar: !!! */void carregaObrasSimilares(int descritor, estrutura_pk_imagem_similaridade *obras_similares);

  /*  */
  geraHtmlSimilares(obras_similares, n_obras_a_listar);
  /* !!! Implementar: !!! */void geraHTMLSimilares(estrutura_pk_imagem_similaridade *obras_similares, int n_obras_a_listar);

  printf("Consulta realizada com sucesso!\n Verifique o arquivo ./tp4.html para visualizar o resultado da pesquisa.\n\n");
  
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
int verificaPKDescritores(estrutura_pk_imagem entrada, int *descritor_entrada){

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
      if(1/*strcmpinsensitive(PK_lida , entrada.titulo)==0*/){
	*descritor_entrada=i;
	
	/* Le o nome do arquivo da imagem */
	for(z=0 ; z<(TAM_IMG+1) ; z++)
	  img_lida[z]=fgetc(arq_descritor);
	/* Passagem por referencia do arquivo... entrada.path = dir + arq */
	sprintf(entrada.path , "%s%s" , DIRIMG , img_lida);

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

  FILE *arq_descritor;

  /* Caso a funcao seja chamada para os limites inferior ou superior, retorna ZERO  */
  if((descritor<DSC0) || (descritor>DSC8))
    return(0);

  arq_descritor = (FILE *)abreArquivoDescritor(descritor,MODOR);
  fseek(arq_descritor,0,SEEK_END);

  return(ftell(arq_descritor)/(TAM_TIT+TAM_IMG+1));
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
    /*c = come_espaco(c);*/
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') resposta=ERRO;
    
    i=0;
    
    /* Caracteres a serem inseridos */
    while(c!='\n' && resposta == OK) {
      titulo[i]=c;
      i++;
      /* Remove os espacos entre palavras */
      if(c==' ') /*c=come_espaco(c);*/ i=i;
      else c=getchar();

      /* CASO DE ERRO */
      /* Caso a entrada seja maior que o tamanho limite */
      if((i>=TAM_TIT) && (c!='\n')) {
	/*resposta = come_excesso(c);*/
	
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


/* Funcao que verifica se a entrada eh um inteiro */
int leInt(){

  int i, resposta;
  char c, str[N_MAX_REG];
  
  for(i=0 ; i<N_MAX_REG ; i++){
    
    

  }/*fim do for*/


}