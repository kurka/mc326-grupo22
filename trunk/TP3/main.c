/*Programa de criação e manipulação de um banco de dados 
com informações sobre obras de arte
Funções disponiveis:
1)Criacao/adicao do banco de dados;
2)Listagem de obras presentes no banco de dados;
3)Busca de obras no banco de dados por chave primária;
4)Busca de obras no banco de dados por chave secundaria;
5)Remoção de obras.

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "defines.h"
#include "base.h"
#include "pk.h"
#include "sk.h"
#include "fopen.h"


int main() {

  char c,opcao;
  char str_final[TAM_REGISTRO+1];
  int n_registros, pk, sk, cabeca_avail;
  FILE *arq_base,*arq_pk, *arq_avail, *arq_sk;
  ap_tipo_registro_pk vetor_registros;
  int limite[2];
  tipo_vetores_sk *vetores_sk;

  /* limite[] possui no primeiro o numero de registros e no segundo a 
     quantidade de memoria alocada no vetor de registros */
  limite[0] = 0;
  limite[1] = MEM_INIT;

  /* Aloca memoria a ser usada durante a execucao (vetor de PKs + NRR) */
  vetor_registros =  realoca_memoria(vetor_registros, limite);
 
  /* Atribui o caractere '\0' ao final da string 
     para imprimir corretamente o string no arquivo */  
  str_final[TAM_REGISTRO] = '\0';
 
  /*consulta ou cria arquivos .dat*/
  arq_base = abre_base22(arq_base, &n_registros);
  arq_pk = abre_pk(arq_pk, &pk); 
  arq_avail = abre_avail(arq_avail, &cabeca_avail);

	

  /* verificando a existência de um arquivo de sk */
  arq_sk=fopen("sk.dat","r");
	
  if(arq_sk == NULL) /*se não existe um arquivo de sk*/
    {       			 /*então o vetor de sk e a lista invertida devem ser gerados a partir de base22.dat*/
      vetores_sk = criarVetorSK(arq_base, n_registros);
    }
  if(arq_sk){
    fseek(arq_sk,0,SEEK_END);
    /*se sk possui tamanho 0, as chaves primarias serao
      coletadas a partir do arquivo base.dat */ 
    sk = ftell(arq_sk);
  }	
  
  
  if(DEBUG)
    printf("\n>>>Numero de registros: %d\n",n_registros);

  /* Se existirem no arquivo pk.dat, carrega as 
     chaves primarias vindas do arquivo */
  if(pk!=0){
    if(DEBUG)
      printf("\n>>>Lendo arquivo de chaves primarias (pk.dat)...\n\n");   
    vetor_registros = lerArquivoPK(arq_pk, vetor_registros, limite, n_registros);
    /* Fecha o arquivo com os registros atuais */
    fclose(arq_pk);
  }

  /* Caso o arquivo pk.dat nao exista, ou seja vazio, pega os valores 
     da base (se existirem) e os coloca no vetor_registro, para serem
     adicionados posteriormente ao arquivo pk.dat*/
  if(pk==0){
    
    if(DEBUG)
      printf("\n>>>Criando arquivo de chaves primarias (pk.dat)...\n\n");   
    
    vetor_registros = inserePKBase(arq_base, vetor_registros, limite, n_registros);
  }


  /* Interface*/
  do {

    printf("Escolha uma das opcoes abaixo e tecle Enter.\n");
    printf("1-) Adicionar uma obra ao catalogo.\n");
    printf("2-) Listar obras do catalogo.\n");
    printf("3-) Procurar por uma obra no catalogo via chave primaria (titulo).\n");
    printf("4-) Procurar por uma obra no catalogo via chave secundaria.\n");
    printf("5-) Remover uma obra do catalogo.\n");
    printf("6-) Sair.\n");

    opcao=getchar();
    c=getchar();

    /* Tratamento de caractere invalido ou caractere(s) a mais */
    if( (c!='\n') || ((opcao!=INSERIR)&&(opcao!=LISTAR)&&(opcao!=CONSULTA_PK)&&(opcao!=CONSULTA_SK)&&(opcao!=REMOVER)&&(opcao!=SAIR)) ) {
      while(c!='\n') {
	c=getchar();
      }
      printf("Caractere ou sequencia de caracteres invalido.\n\n\n");
      opcao=0;
    }
    
    switch(opcao) {
      
      /* Insercao no catalogo */
    case INSERIR:
      /*le da entrada padrao os dados da obra*/
      Insere_base(arq_base, str_final, vetor_registros, limite[0]);
      /*pega o ultimo titulo lido e insere no vetor de registros*/
      vetor_registros = novopk(str_final, vetor_registros, limite);   
      if(DEBUG)     
	printf(">>>Numero de registros: %d\n\n",limite[0]);
      break;
      
      /* Listar os registros do catalogo */
    case LISTAR:
      lista_registros(limite[0],vetor_registros);
      break;
      
      /* Procurar por registro via chave primaria */
    case CONSULTA_PK:
      consulta_pk(limite[0],vetor_registros, arq_base);
      break;

      /* Procurar pro registro via chave secundaria */
    case CONSULTA_SK:
      printf("Consulta SK.\n\n");
      /* ***Definir funcao!*** */
      /* consulta_sk(); */
      break;

      /* Remove um registro do catalogo */
    case REMOVER:
      remove_registro(n_registros, vetor_registros, arq_base, arq_avail, &cabeca_avail);
      break;

    }
    
  } while(opcao!=SAIR);
  

  /* se o arquivo nao era vazio, abre soh no final, 
     evitando perder dados em caso de erro de execucao*/
  if(pk!=0)
    arq_pk=fopen("pk.dat","w");    
  
  
  /*guarda o indice de chaves primarias no arquivo*/
  if(DEBUG)
    printf("\n>>>Salvando arquivos e liberando memoria\n");  
  salvarArquivoPK(vetor_registros, arq_pk, limite[0]);

  free(vetor_registros);
  /*fecha os arquivos*/
  fclose(arq_pk);
  fclose(arq_base);
  fclose(arq_avail);

  if(DEBUG)
    printf(">>>Fim da execucao!\n");

  return(0);

}

