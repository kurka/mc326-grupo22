/* Esta biblioteca realiza manipulações no arquivo de chaves primarias da
   base de dados, permitindo consultas, listagem e exibicao (em pagina HTML)
   dos registros contidos no banco de dados.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "base.h"
#include "pk.h"

/* le todos os dados do arquivo PK.dat e os adiciona em um vetor,
   mantendo a ordem de registros, que é alfabética */
tipo_registro_pk * lerArquivoPK(FILE *arqPK, int numberOfPKs)
{
  int i, j;
  tipo_registro_pk novo;
  tipo_registro_pk *vetor = malloc(sizeof(tipo_registro_pk)*(numberOfPKs));

  fseek(arqPK,0,SEEK_SET);
  
  for(i=0;i<numberOfPKs;i++)
    {
      for(j=0; j<TAM_TIT; j++)
        fscanf(arqPK, "%c", &(novo.titulo[j]));
      fscanf(arqPK, "%d", &(novo.nrr));

      vetor[i] = novo;
    }

  return vetor;
}


/*(funcao auxiliar usada na funcao qsort)*/
int compara_qsort(const void * vetora, const void * vetorb) {
  return(strncmp( ((tipo_registro_pk *)vetora)->titulo, 
		  ((tipo_registro_pk *)vetorb)->titulo, TAM_TIT));
}

/*caso a lista em PK.dat nao estivesse criada, le os dados da base.dat 
  e cria os indices no arquivo.*/
tipo_registro_pk * inserePKBase(FILE *arqBase, int numberOfPKs){
  
  int i, j;
  tipo_registro_pk novo;
  tipo_registro_pk *vetor;

  if(numberOfPKs)
    vetor = malloc(sizeof(tipo_registro_pk)*(numberOfPKs));
 

  for(i=0;i<numberOfPKs;i++){
    /*encontra a posicao onde o titulo esta registrado*/
    fseek(arqBase,i*TAM_REGISTRO,SEEK_SET);     
    /*copia o titulo*/
    for(j=0; j<TAM_TIT; j++)
      fscanf(arqBase, "%c", &(novo.titulo[j]));
    /*guarda o numero do registro junto com o campo*/
    novo.nrr = i+1;   
    
    vetor[i] = novo;
  }  
  /*ordena o vetor em ordem alfabetica*/
  qsort(vetor, numberOfPKs, sizeof(tipo_registro_pk), compara_qsort);
  
 

  return vetor;
} 


/*pega o ultimo titulo lido e registra ele como novo, 
para ser inserido no vetor de chaves primarias*/
tipo_registro_pk  novopk(char *str_final, int numberOfPKs){

  int i;
  tipo_registro_pk novo;
 
  /*copia o ultimo titulo inserido*/
  for(i=0;i<TAM_TIT;i++)
    novo.titulo[i]=str_final[i];


  /*imprime no vetor nrr o numero numberOfPks (transformando int em string)*/
  novo.nrr = numberOfPKs;
  return novo;
}

/* insere um novo registro no nosso vetor dinamico de PKs, essa inserção é ordenada e mantém a ordem alfabética do vetor */
int inserirPK(tipo_registro_pk *vetor, tipo_registro_pk novo, int numberOfPKs)
{
  int i, j;
  

  /*realoca vetor, para inserir novo elemento*/
  vetor = realloc(vetor, sizeof(tipo_registro_pk)*(numberOfPKs));

  for(i=0; i<numberOfPKs-1; i++){ 
    
    if(strncmp(novo.titulo, vetor[i].titulo, TAM_TIT) == 0){
      printf("Erro! Titulo inserido já existente!\n");
      printf("Todos os titulos de obras devem ser diferentes! Repita a operação!\n\n");
      return -1;  
    }
    
    if(strncmp(novo.titulo, vetor[i].titulo, TAM_TIT) < 0){
      /*desloca os elementos depois da posicao a ser inserida*/
      for(j=numberOfPKs-2; j>=i; j--){
	vetor[j+1] = vetor[j];
      }
      
      break;
    }
  }
 
  vetor[i] = novo;    

/* printf("\n>>>impressao do vetor de chaves primarias:\n"); */
/* for(i=0; i< numberOfPKs; i++){  */
/*   printf("vetor.titulo = "); */
/*   for(j=0;j<TAM_TIT/5;j++) */
/*     printf("%c", vetor[i].titulo[j]); */
/*   printf("vetor.nrr = %d\n", vetor[i].nrr); */
/*  } */

return 0;
}


/* salva todos os registros do nosso vetor de PKs no arquivo PK.dat*/
void salvarArquivoPK(tipo_registro_pk *vetor, FILE *arq_pk, int numberOfPKs)
{
  int i,j;
  
  fseek(arq_pk,0,SEEK_SET);
  
  for(i=0; i<numberOfPKs; i++){
    for(j=0; j<TAM_TIT; j++)
      fprintf(arq_pk, "%c", vetor[i].titulo[j]);
    
    fprintf(arq_pk, "%d", vetor[i].nrr);     
  }
}



/* Funcao de listagem de registros. A partir do arquivo de chaves primarias,
 gera um arquivo em html com todos os titulos das obras. */
void lista_registros(int n_registros, tipo_registro_pk *vetor_de_registros) {

  FILE *arq_html;
  int i,j;

  /* Caso nao haja registros, retorna a funcao. */
  if(n_registros==0) {
    printf("Nao ha obras cadastradas.\n\n");
  }
  /* Caso haja, gera o arquivo de consulta em HTML */
  else {
    arq_html=fopen("tp2.html","w");
    /* Cabecalho do arquivo */
    fprintf(arq_html,"<html><head></head><body>\n<div align=\"center\">\n");
    fprintf(arq_html,"<br><b>Lista de obras cadastradas</b><br>");
    /* Para cada registro, insere o titulo caractere por caractere */
    for(i=0;i<n_registros;i++) {
      fprintf(arq_html,"<br>");
      for(j=0;j<TAM_TIT;j++) {
	fprintf(arq_html,"%c",vetor_de_registros[i].titulo[j]);
      }
    }
    fprintf(arq_html,"<br></div></body></html>");
    fclose(arq_html);
    printf("Listagem efetuada com sucesso. Para visualiza-la, consulte\n");
    printf("sua pasta atual e abra o arquivo ./tp2.html\n\n");
  }

  return;
}


/*(funcao auxiliar usada na funcao bsearch)*/
int compara_bsearch(const void * titulo_procurado, const void * vetor_de_registros) {
  return(strncmp( (char*)titulo_procurado, 
		  ((tipo_registro_pk*)vetor_de_registros)->titulo,TAM_TIT));
}

/* Funcao principal de consulta por chave primaria.
   Le o titulo procurado e verifica no arquivo de chaves primarias se ele
   esta la. Em caso positivo, chama uma funcao da biblioteca da base de dados
   que busca o registro e gera o HTML da consulta. */
void consulta_pk(int n_registros, tipo_registro_pk *vetor_de_registros, FILE *arq_base) {

  int NRR;
  char titulo_procurado[MAX_TIT];
  tipo_registro_pk *elto_encontrado;

  if(n_registros==0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta pelo titulo no catalogo:\n");
  /* titulo_procurado eh lido pela mesma funcao de insercao de registro */
  Insere_titulo(titulo_procurado);

  /* Busca o titulo procurado no vetor de structs. */
  elto_encontrado=bsearch(titulo_procurado, vetor_de_registros, n_registros, sizeof(tipo_registro_pk), compara_bsearch);

  /* Caso o titulo nao esteja registrado, resposta==NULL. Retorna a funcao. */
  if(elto_encontrado==NULL) {
    printf("O titulo nao foi encontrado.\n\n");
  }
  /* Caso contrario, chama a funcao de busca na base de dados com o NRR. */
  else {
    NRR=((*elto_encontrado).nrr);
    busca_registro(NRR, arq_base); /* funcao definida em base.c */
    printf("Obra encontrada. Para visualizar suas informações consulte\n");
    printf("sua pasta atual e abra o arquivo ./tp2.html\n\n"); 
  }

  return;
}
 
