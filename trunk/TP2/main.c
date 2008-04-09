
/*Programa de criação e manipulação de um banco de dados 
com informações sobre obras de arte
Funções disponiveis:
1)Criacao/adicao do banco de dados;
2)Listagem de obras presentes no banco de dados;
3)Busca de obras no banco de dados;
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "defines.h"
#include "base.h"
#include "pk.h"


int main() {

  char c,opcao,n_registros=0;
  char str_final[TAM_REGISTRO+1];
  int res, pk;
  FILE *arq_base,*arq_pk;
  ap_tipo_registro_pk vetor_registros;
  tipo_registro_pk ultimo;
  
   /* Atribui o caractere '\0' ao final da string 
     para imprimir corretamente o string no vetor */  
  str_final[TAM_REGISTRO] = '\0';

 
  arq_base=fopen("base22.dat","a+");
  
  /*pk indica se o arquivo pk.dat possui conteudo (1 sim, 0 nao)
    para ser gerado ou nao a partir da base*/
  pk=1;
  arq_pk=fopen("pk.dat","r");

  if(!arq_pk){
    pk=0;
  }
  if(arq_pk){
    fseek(arq_pk,0,SEEK_END);
    /*se pk possui tamanho 0, as chaves primarias serao
      coletadas a partir do arquivo base.dat */ 
    pk = ftell(arq_pk);
  }
  
  /* Esta rotina retorna o numero de registros do arquivo da base de dados
     caso o programa comece com um arquivo ja existente. */
  fseek(arq_base,0,SEEK_END);
  n_registros=ftell(arq_base)/TAM_REGISTRO;
  
  if(DEBUG)
    printf(">>>Numero de registros: %d\n\n",n_registros);

  /* Carrega um vetor com os registros ja existentes*/

  /* Se existirem no arquivo pk.dat, carrega as 
     chaves primarias vindas do arquivo*/
  if(pk!=0){
    if(DEBUG)
      printf("\n>>>Lendo arquivo de chaves primarias (pk.dat)...\n\n");   
    vetor_registros = lerArquivoPK(arq_pk, n_registros);
    fclose(arq_pk);
    /*fecha o arquivo com os registros atuais*/
  }
  /* Caso o arquivo pk.dat nao exista, ou seja vazio, pega os valores 
     da base (se existirem) e os coloca no vetor_registro, para serem
     adicionados posteriormente ao arquivo pk.dat*/
  if(pk==0){
   
    if(DEBUG)
      printf("\n>>>Criando arquivo de chaves primarias (pk.dat)...\n\n");   
    arq_pk=fopen("pk.dat","w");    
    vetor_registros = inserePKBase(arq_base, n_registros);
  }


  /* Interface*/
  do {

    printf("Escolha uma das opcoes abaixo (1 ou 2) e tecle Enter.\n");
    printf("1-) Adicionar uma obra ao catalogo.\n");
    printf("2-) Listar obras do catalogo.\n");
    printf("3-) Procurar por uma obra no catalogo.\n");
    printf("4-) Sair.\n");

    opcao=getchar();
    c=getchar();

    /* Tratamento de caractere invalido ou caractere(s) a mais */
    if( (c!='\n') || ((opcao!=INSERIR)&&(opcao!=LISTAR)
		      &&(opcao!=CONSULTA)&&(opcao!=SAIR)) ) {
      while(c!='\n') {
	c=getchar();
      }
      printf("Caractere ou sequencia de caracteres invalido.\n\n\n");
      opcao=0;
    }
    
    switch(opcao) {
      
      /* Insercao no catalogo */
    case INSERIR:
      res=-1;
      /*repete a insercao ate inserir um titulo novo*/
      while(res==-1){
	/*le da entrada padrao os dados da obra*/
	Insere_base(arq_base, str_final);
	n_registros++;
	/*pega o ultimo titulo lido*/
	ultimo = novopk(str_final, n_registros);
	/*guarda a chave primaria no vetor_registros 
	  (conferindo se eh unica)*/
	res = inserirPK(vetor_registros, ultimo, n_registros);
	
	if(res==-1)	
	  n_registros--;
      }
      if(DEBUG)
	printf(">>>Numero de registros: %d\n\n",n_registros);
      fprintf(arq_base,"%s",str_final);
      printf("Obra adicionada com sucesso.\n\n\n");
      break;
      
      /* Listar os registros do catalogo */
    case LISTAR:
      lista_registros(n_registros,vetor_registros);
      break;
      
      /* Procurar por registro */
    case CONSULTA:
      consulta_pk(n_registros,vetor_registros, arq_base);
      break;
    }
    
  } while(opcao!=SAIR);
  
  printf("Obrigado por usar nosso programa!\n\n");

  
  /* se o arquivo nao era vazio, abre soh no final, 
     evitando perder dados em caso de erro de execucao*/
  if(pk!=0)
    arq_pk=fopen("pk.dat","w");    

  /*guarda o indice de chaves primarias no arquivo*/  
  salvarArquivoPK(vetor_registros, arq_pk, n_registros);

  /*fecha os arquivos*/
  fclose(arq_pk);
  fclose(arq_base);

  return(0);

}

