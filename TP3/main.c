
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "defines.h"
#include "base.h"
#include "pk.h"
#include "sk.h"
#include "fopen.h"

/**
   \brief Programa de criação e manipulação de um banco de dados 
   com informações sobre obras de arte
   Funções disponiveis:
   1)Criacao/adicao do banco de dados;
   2)Listagem de obras presentes no banco de dados;
   3)Busca de obras no banco de dados por chave primária;
   4)Busca de obras no banco de dados por chave secundaria;
   5)Remoção de obras.
*/
int main() {

  char c,opcao;
  char str_final[TAM_REGISTRO+1];
  int n_registros, pk, sk, cabeca_avail, nrr;
  FILE *arq_base,*arq_pk, *arq_avail, *arq_sk;
  ap_tipo_registro_pk vetor_registros;
  int limite[2];
  tipo_arqs_li * arqs_li = (tipo_arqs_li *) malloc(sizeof(tipo_arqs_li));
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
      {
	/*então o vetor de sk e a lista invertida devem ser gerados a partir de base22.dat*/
	if(DEBUG)
	  printf("\n>>>criando vetores sk\n");
 	vetores_sk = criarVetorSK(n_registros, arqs_li, arq_base); 
      }
    if(arq_sk){
      fseek(arq_sk,0,SEEK_END);
      /*se sk possui tamanho 0, as chaves primarias serao
        coletadas a partir do arquivo base.dat */
      sk = ftell(arq_sk);
    }
  
  

  /* Se existirem no arquivo pk.dat, carrega as 
     chaves primarias vindas do arquivo */
  if(pk!=0){
    if(DEBUG)
      printf("\n>>>Lendo arquivo de chaves primarias (pk.dat)...\n\n");   
    vetor_registros = lerArquivoPK(arq_pk, vetor_registros, limite, pk);
    /* Fecha o arquivo com os registros atuais */
    fclose(arq_pk);
  }

  /* Caso o arquivo pk.dat nao exista, ou seja vazio, pega os valores 
     da ase (se existirem) e os coloca no vetor_registro, para serem
     adicionados posteriormente ao arquivo pk.dat*/
  if(pk==0){
    
    if(DEBUG)
      printf("\n>>>Criando arquivo de chaves primarias (pk.dat)...");   
    
    vetor_registros = inserePKBase(arq_base, vetor_registros, limite, n_registros);

    /*se existir uma avail list, apaga os registros apontados por ela*/
    if(cabeca_avail != -1){
      if(DEBUG)
	printf(">>>limpando chaves primarias\n\n");
      vetor_registros = limpa_pk(arq_base, vetor_registros, limite, cabeca_avail);
    }
  }

  if(DEBUG)
    printf("\n>>>Numero de registros: %d\n\n\n",limite[0]);
  
  /* Interface*/
  do {

    printf("Escolha uma das opcoes abaixo e tecle Enter.\n");
    printf("1-) Adicionar uma obra ao catalogo.\n");
    printf("2-) Listar obras do catalogo.\n");
    printf("3-) Procurar por um titulo de obra no catalogo.\n");
    printf("4-) Procurar por palavra do titulo no catalogo.\n");
    printf("5-) Procurar por um tipo de obra no catalogo.\n");
    printf("6-) Procurar por um autor no catalogo.\n");
    printf("7-) Procurar por um ano de obra no catalogo.\n");
    printf("8-) Remover uma obra do catalogo.\n");
    printf("0-) Sair.\n");

    opcao=getchar();
    c=getchar();

    /* Tratamento de caractere invalido ou caractere(s) a mais */
    if( (c!='\n') || ((opcao!=INSERIR)&&(opcao!=LISTAR)&&(opcao!=CONSULTA_PK)&&
		      (opcao!=CONSULTA_SK_TIT)&& (opcao!=CONSULTA_SK_TIP)&& 
		      (opcao!=CONSULTA_SK_AUT)&& (opcao!=CONSULTA_SK_ANO)&&
		      (opcao!=REMOVER)&&(opcao!=SAIR)) ) {
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
      nrr = escreve_base(arq_base, arq_avail, str_final, &cabeca_avail);
      vetor_registros = novopk(str_final, vetor_registros, limite, nrr);   
      /*insere as novas sks*/
      vetores_sk = insereVetorSK(str_final, vetores_sk, arqs_li);


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

      /* Procurar por registros via chave secundaria */
    case CONSULTA_SK_TIT:
      consulta_sk_tit(vetores_sk, vetor_registros, limite[0], arqs_li->arq_tit_li, arq_base);
      break;
    case CONSULTA_SK_TIP:
      consulta_sk_tip(vetores_sk, vetor_registros, limite[0], arqs_li->arq_tip_li, arq_base);
      break;
    case CONSULTA_SK_AUT:
      consulta_sk_aut(vetores_sk, vetor_registros, limite[0], arqs_li->arq_aut_li, arq_base);
      break;
    case CONSULTA_SK_ANO:
      consulta_sk_ano(vetores_sk, vetor_registros, limite[0], arqs_li->arq_ano_li, arq_base);
      break;

      /* Remove um registro do catalogo */
    case REMOVER:
      remove_registro(n_registros, vetor_registros, arq_base, arq_avail, &cabeca_avail);
      vetor_registros = remove_pk(vetor_registros, limite, cabeca_avail);
      if(DEBUG)     
	printf(">>>Numero de registros: %d\n\n",limite[0]);
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

  /*fecha os arquivos*/
  fclose(arq_pk);
  fclose(arq_base);
  fclose(arq_avail);
  
  fclose(arqs_li->arq_tit_li); 
  fclose(arqs_li->arq_tip_li); 
  fclose(arqs_li->arq_aut_li); 
  fclose(arqs_li->arq_ano_li); 

  /*libera memoria*/
  free(vetor_registros);
  free(arqs_li);
  free(vetores_sk->titulo);
  free(vetores_sk->autor);
  free(vetores_sk->ano);
  free(vetores_sk->tipo);
  free(vetores_sk);

  if(DEBUG)
    printf(">>>Fim da execucao!\n");

  return(0);

}

