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
  char * str_final;
  int res;
  FILE *arq_base,*arq_pk;
  ap_tipo_registro_pk vetor_registros;
  tipo_registro_pk ultimo;

  arq_base=fopen("base22.dat","a");
  arq_pk=fopen("pkteste.dat","r");

  /* Esta rotina retorna o numero de registros do arquivo da base de dados
     caso o programa comece com um arquivo ja existente. */
  fseek(arq_base,0,SEEK_END);
  n_registros=ftell(arq_base)/TAM_REGISTRO;

  /* Carrega um vetor com os registros ja existentes*/
  vetor_registros = lerArquivoPK(arq_pk, n_registros);
  printf("Numero de registros: %d\n\n",n_registros);

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
    if( (c!='\n') || ((opcao!=INSERIR)&&(opcao!=LISTAR)&&(opcao!=CONSULTA)&&(opcao!=SAIR)) ) {
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
	  str_final = Insere_base(arq_base);
	  n_registros++;
	  /*pega o ultimo titulo lido*/
	  ultimo = novopk(str_final, n_registros);
	  /*guarda a chave primaria no vetor_registros 
	    (conferindo se eh unica)*/
	  res = inserirPK(vetor_registros, ultimo, n_registros);
	  if(res==-1)	
	    n_registros--;
	}
	printf("Numero de registros: %d\n\n",n_registros);

	fprintf(arq_base,"%s",str_final);
	printf("Obra adicionada com sucesso.\n\n\n");
	break;

      /* Listar os registros do catalogo */
      case LISTAR:
	lista_registros(n_registros,vetor_registros);
	break;

      /* Procurar por registro */
      case CONSULTA:
	consulta_pk(n_registros,vetor_registros);
	printf("Consulta.\n\n");
	break;
    }

  } while(opcao!=SAIR);

  /*guarda o indice de chaves primarias no arquivo*/  
  salvarArquivoPK(vetor_registros, arq_pk, n_registros);

  /*fecha os arquivos*/
  fclose(arq_pk);
  fclose(arq_base);

  return(0);

}

