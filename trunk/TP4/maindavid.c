#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "defines.h"
#include "base.h"
#include "pk.h"
#include "sk.h"
#include "fopen.h"

/*!
 * \brief Programa de criação e manipulação de um banco de dados 
 * com informações sobre obras de arte
 * Funções disponiveis:
 * 1)Criacao/adicao do banco de dados;
 * 2)Listagem de obras presentes no banco de dados;
 * 3)Busca de obras no banco de dados por chave primária;
 * 4)Busca de obras no banco de dados por chave secundaria;
 * 5)Remoção de obras.
 */
int main() {

  char c,opcao;
  char str_final[TAM_REGISTRO+1];
  int n_registros, pk, sk, cabeca_avail, nrr;
  FILE *arq_base,*arq_pk, *arq_avail;
  ap_tipo_registro_pk vetor_pks_descritores;
  int limite[2], limite_descritores[DSC8][2];
  tipo_vetores_sk *vetores_sk; 


  /* Atribui o caractere '\0' ao final da string 
     para imprimir corretamente o string no arquivo */  
  str_final[TAM_REGISTRO] = '\0';
 
  /* Consulta ou cria arquivos .dat */
  arq_base = abre_base22(arq_base, &n_registros);
  /*  arq_avail = abre_avail(arq_avail, &cabeca_avail); */
  /*  abre_sk(arqs_sk, arqs_li, &sk); */

  /* Pega as chaves primarias da base (se existirem) e as guarda em arquivos de chaves primarias.*/
  
  if(DEBUG)
    printf("\n>>>Criando arquivo de chaves primarias (pk.dat)...\n");   
  
  inserePKBase(arq_base,limite, n_registros);
  
    /* Se existir uma avail list, apaga os registros apontados por ela */
/*     if(cabeca_avail != -1){ */
/*       if(DEBUG) */
/* 	printf(">>>limpando chaves primarias\n\n"); */
/*       vetor_registros = limpa_pk(arq_base, vetor_registros, limite, cabeca_avail); */
/*     } */
/*   } */

  /* Criacao de estrutura de chaves secundarias*/
  /* Se o arquivo sk.dat existir, carrega as estruturas de chaves secundarias do arquivo*/
/*   if(sk!=0){ */
/*     if(DEBUG) */
/*       printf("\n>>>lendo vetores sk do arquivo\n"); */
    
/*     vetores_sk = ler_arquivo_sk(arqs_sk);  */
    
/*     fclose(arqs_sk->arq_sk_tit); */
/*     fclose(arqs_sk->arq_sk_tip); */
/*     fclose(arqs_sk->arq_sk_aut); */
/*     fclose(arqs_sk->arq_sk_ano); */
/*   } */
  /* Criacao das chaves secundarias */
  /* Caso nao exista, cria as estruturas de chaves secundarias a partir do arquivo base.dat*/
  /* if(sk==0){ */
/*     if(DEBUG) */
/*       printf("\n>>>criando vetores sk a partir da base\n"); */
/*   criaRegistrosSK(n_registros, arq_base);   */
/*   } */
   
  criaRegistrosSK(n_registros, arq_base);   


  if(DEBUG)
    printf("\n>>>Numero de registros: %d\n\n\n",limite[0]);


/*   /\* Verifica se os arquivos de descritores existem. Caso nao, cria-os a partir do vetor de chaves primarias *\/ */
/*   if(verificaDescritores()==ERRO) */
/*     criaDescritores(vetor_registros, n_registros, vetor_pks_descritores); */
/*   /\* Caso os arquivos existam, carrega-os para a memoria *\/ */
/*   else */
/*     carregaDescritores(vetor_pks_descritores, limite_descritores); */
  
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
    printf("8-) Procurar por descritor.\n");
    printf("9-) Remover uma obra do catalogo.\n");
    printf("0-) Sair.\n");

    opcao=getchar();
    c=getchar();

    /* Tratamento de caractere invalido ou caractere(s) a mais */
    if( (c!='\n') || ((opcao!=INSERIR)&&(opcao!=LISTAR)&&(opcao!=CONSULTA_PK)&&
                      (opcao!=CONSULTA_SK_TIT)&&(opcao!=CONSULTA_SK_TIP)&&
                      (opcao!=CONSULTA_SK_AUT)&&(opcao!=CONSULTA_SK_ANO)&&
		      (opcao!=REMOVER)&&(opcao!=SAIR)) ) {
 /*   (opcao!=CONSULTA_SK_DSC)&&(opcao!=REMOVER)&&(opcao!=SAIR)) ) { */
      while(c!='\n') {
        c=getchar();
      }
      printf("Caractere ou sequencia de caracteres invalido.\n\n\n");
      opcao=0;
    }
    
  /*   switch(opcao) { */
      
/*       /\* Insercao no catalogo *\/ */
/*     case INSERIR: */
/*       /\* Le da entrada padrao os dados da obra *\/ */
/*       Insere_base(arq_base, str_final, vetor_registros, limite[0]); */
/*       /\* Pega o ultimo titulo lido e insere no vetor de registros *\/ */
/*       nrr = escreve_base(arq_base, arq_avail, str_final, &cabeca_avail); */
/*       vetor_registros = novopk(str_final, vetor_registros, limite, nrr); */
/*       /\* Insere as novas sks *\/ */
/*       vetores_sk = insereVetorSK(str_final, vetores_sk, arqs_li); */
 
/*       if(DEBUG) */
/* 	printf(">>>Numero de registros: %d\n\n",limite[0]); */
 
/*       espera(); */
/*       break; */
      
/*       /\* Listar os registros do catalogo *\/ */
/*     case LISTAR: */
/*       lista_registros(limite[0],vetor_registros); */
/*       espera(); */
/*       break; */
      
/*       /\* Procurar por registro via chave primaria *\/ */
/*     case CONSULTA_PK: */
/*       consulta_pk(limite[0],vetor_registros, arq_base); */
/*       espera(); */
/*       break; */

/*       /\* Procurar por registros via chave secundaria *\/ */
/*     case CONSULTA_SK_TIT: */
/*       consulta_sk_tit(vetores_sk->titulo, vetor_registros, limite[0], arqs_li->arq_tit_li, arq_base); */
/*       espera(); */
/*       break; */
/*     case CONSULTA_SK_TIP: */
/*       consulta_sk_tip(vetores_sk->tipo, vetor_registros, limite[0], arqs_li->arq_tip_li, arq_base); */
/*       espera(); */
/*       break; */
/*     case CONSULTA_SK_AUT: */
/*       consulta_sk_aut(vetores_sk->autor, vetor_registros, limite[0], arqs_li->arq_aut_li, arq_base); */
/*       espera(); */
/*       break; */
/*     case CONSULTA_SK_ANO: */
/*       consulta_sk_ano(vetores_sk->ano, vetor_registros, limite[0], arqs_li->arq_ano_li, arq_base); */
/*       espera(); */
/*       break; */

/*       /\* Remove um registro do catalogo *\/ */
/*     case REMOVER: */
/*       remove_registro(n_registros, vetor_registros, arq_base, arq_avail, &cabeca_avail); */
/*       vetor_registros = remove_pk(vetor_registros, limite, cabeca_avail); */
/*       if(DEBUG) */
/* 	printf(">>>Numero de registros: %d\n\n",limite[0]); */
 
/*       espera(); */
/*       break; */
/*     } */
    
   } while(opcao!=SAIR); 
  

/*   /\* Se os arquivos  sk_*.dat nao eram vazios, abre para escrita  */
/*      somente no final, evitando perder dados em caso de erro de execucao *\/ */
/*   if(sk!=0){ */
/*     arqs_sk->arq_sk_tit = fopen(ARQSK_TIT, "w"); */
/*     arqs_sk->arq_sk_tip = fopen(ARQSK_TIP, "w"); */
/*     arqs_sk->arq_sk_aut = fopen(ARQSK_AUT, "w"); */
/*     arqs_sk->arq_sk_ano = fopen(ARQSK_ANO, "w"); */
/*   } */
  

/*   /\* Guarda o indice de chaves primarias e secundarias no arquivo *\/ */
/*   if(DEBUG) */
/*     printf("\n>>>Salvando arquivos e liberando memoria\n");   */
  
/*   salvar_arquivo_sk(vetores_sk, arqs_sk); */
  

  /* Fecha os arquivos */
  fclose(arq_base);
  /* fclose(arq_avail); */


  /* Libera memoria */
/*   liberamemoria(vetor_registros, arqs_sk, arqs_li, vetores_sk); */
 
  if(DEBUG)
    printf(">>>Fim da execucao!\n");

  return(0);

}
