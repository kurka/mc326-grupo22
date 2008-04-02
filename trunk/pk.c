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
      for(j=0; j<TAM_NRR; j++)
	fscanf(arqPK, "%c", &(novo.nrr[j]));
      
      
      vetor[i] = novo;
    }

  return vetor;
}


/*(funcao auxiliar usada na funcao qsort)*/
int compara_qsort(const void * a, const void * b) {
  return(strcmp( (tipo_registro_pk*)vetor->titulo, 
		 (tipo_registro_pk*)vetor->titulo));
}

/*caso a lista em PK.dat nao estivesse criada, le os dados da base.dat 
  e cria os indices no arquivo.*/
tipo_registro_pk * inserePKbase(FILE *arqBase, int numberOfPKs){
  
  int i, j;
  tipo_registro_pk novo;
  tipo_registro_pk *vetor = malloc(sizeof(tipo_registro_pk)*(numberOfPKs));

  for(i=0;i<numberOfPKs;i++){
    /*encontra a posicao onde o titulo esta registrado*/
    fseek(arq_base,i*TAM_REGISTRO,SEEK_SET);     
    /*copia o titulo*/
    for(j=0; j<TAM_TIT; j++)
      fscanf(arqBase, "%c", &(novo.titulo[j]));
    /*guarda o numero do registro junto com o campo*/
    sprintf(novo.nrr,"%d",i+1);   
    
    vetor[i] = novo;
  }  
  /*ordena o vetor em ordem alfabetica*/
  qsort(vetor, numberOfPKs, sizeof(tipo_registro_pk), compara_qsort);} 


/*pega o ultimo titulo lido e registra ele como novo, 
para ser inserido no vetor de chaves primarias*/
tipo_registro_pk  novopk(char *str_final, int numberOfPKs){

  int i, inicio;
  tipo_registro_pk novo;
 

  /*posicao do ultimo titulo inserido*/
  inicio = TAM_REGISTRO*(numberOfPKs-1);
  /*copia o ultimo titulo inserido*/
  for(i=inicio;i<inicio+TAM_TIT;i++)
    novo.titulo[i-inicio]=str_final[i];

  /*imprime no vetor nrr o numero numberOfPks (transformando int em string)*/
  sprintf(novo.nrr,"%d",numberOfPKs);
  return novo;
}

/* insere um novo registro no nosso vetor dinamico de PKs, essa inserção é ordenada e mantém a ordem alfabética do vetor */
int inserirPK(tipo_registro_pk *vetor, tipo_registro_pk novo, int numberOfPKs)
{
  int i, j;
  

  /*realoca vetor, para inserir novo elemento*/
  vetor = realloc(vetor, sizeof(tipo_registro_pk)*(numberOfPKs));
    
  for(i=0; i< numberOfPKs; i++){ 
    
    printf("novo.titulo = %s", novo.titulo);
    printf("vetor.titulo = %s", vetor[i].titulo);
    
    if(strcmp(novo.titulo, vetor[i].titulo) == 0){
      printf("Erro! chave primaria ja existente!\n");
      
      /*realoca vetor, eliminando o registro criado acima*/
      vetor = realloc(vetor, sizeof(tipo_registro_pk)*(numberOfPKs-1));  
  return -1;
    }
    
    if(strcmp(novo.titulo, vetor[i].titulo) < 0){
      
      
      /*desloca os elementos depois da posicao a ser inserida*/
      for(j=numberOfPKs-2; j>=i; j--){
	vetor[j+1] = vetor[j];
      }
 
      break;
    }
    
  }
  vetor[i-1] = novo;

  printf("\nimpressao do vetor de chaves primarias:\n");
  for(i=0; i< numberOfPKs; i++){ 
    printf("vetor.titulo = %s\n", vetor[i].titulo);
    printf("vetor.nrr = %s\n", vetor[i].nrr);
  }
  return 0;
}


/* salva todos os registros do nosso vetor de PKs no arquivo PK.dat*/
void salvarArquivoPK(tipo_registro_pk *vetor, FILE *arq_pk, int numberOfPKs)
{
  int i,j;
  
  fseek(arq_pk,0,SEEK_SET);
  
  for(i=0; i<numberOfPKs; i++)
    {
      for(j=0; j<TAM_TIT; j++)
	fprintf(arq_pk, "%c", vetor[i].titulo[j]);
      for(j=0; j<TAM_NRR; j++)
	fprintf(arq_pk, "%c", vetor[i].nrr[j]);     
      
    }
}


/* /\* Consulta nos registros do vetor de PKs, se o titulo passado como parametro existe nesse vetor, e portanto no arquivo PK.dat, caso exista a função retorna o NRR desse registro, caso titulo nao exista, então zero é retornado *\/ */
/* int consultarPK(pk *vetor, int *numberOfPKs, char *titulo) */
/* { */
/*   int i; */
/*   char tituloTemp[200]; */
  
/*   while(titulo[i]!= '\0') */
/*     tituloTemp[i] = titulo[i]; */
  
/*   while(i< 200) */
/*     tituloTemp[i] = ' '; */
  
/*   for(i=0; i<=numberOfPKs); i++){  */
/*   if(strcmp(vetor[i].titulo, tituloTemp)== 0) */
/*     return vetor.nrr; */
  
/* } */
/* return 0; */
/* } */




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
      for(j=0;j<MAX_TIT;j++) {
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
  return(strcmp( (char*)titulo_procurado, ((tipo_registro_pk*)vetor_de_registros)->titulo));
}

/* Funcao principal de consulta por chave primaria.
   Le o titulo procurado e verifica no arquivo de chaves primarias se ele
   esta la. Em caso positivo, chama uma funcao da biblioteca da base de dados
   que busca o registro e gera o HTML da consulta. */
void consulta_pk(int n_registros, tipo_registro_pk *vetor_de_registros, FILE *arq_base) {

  int NRR,teste;
  char titulo_procurado[MAX_TIT];
  tipo_registro_pk *elto_encontrado;
  /* tipo_registro_pk * vetor_de_registros = malloc(sizeof(tipo_registro_pk)*n_registros);*/
  if(n_registros==0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta pelo titulo no catalogo:\n");
  /* titulo_procurado eh lido pela mesma funcao de insercao de registro */
  Insere_titulo(titulo_procurado);

  /* Copiando os dados do arquivo de chaves primarias para o vetor. */
/*   fseek(arq_pk,0,SEEK_SET); */
/*   for(i=0;i<n_registros;i++) { */
/*     /\* Insercao do titulo caractere por caractere. *\/ */
/*     for(j=0;j<MAX_TIT;j++) { */
/*       vetor_de_registros[i].titulo[j]=fgetc(arq_pk); */
/*     } */
/*     /\* Insercao do NRR caractere por caractere. *\/ */
/*     for(j=0;j<TAM_NRR;j++) { */
/*       vetor_de_registros[i].nrr[j]=fgetc(arq_pk); */
/*     } */
/*   } */

  teste=strcmp(titulo_procurado,vetor_de_registros[0].titulo);
  printf("Teste == %d .",teste);

  /* Busca o titulo procurado no vetor de structs. */
  elto_encontrado=bsearch(titulo_procurado, vetor_de_registros, n_registros, sizeof(tipo_registro_pk), compara_bsearch);

  /* Caso o titulo nao esteja registrado, resposta==NULL. Retorna a funcao. */
  if(elto_encontrado==NULL) {
    printf("O titulo nao foi encontrado.\n\n");
  }
  /* Caso contrario, chama a funcao de busca na base de dados com o NRR. */
  else {
    NRR=atoi((*elto_encontrado).nrr);
    busca_registro(NRR, arq_base); /* funcao definida em base.c */
  }

  return;
}
