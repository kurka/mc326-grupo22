/* Esta biblioteca realiza manipulações no arquivo de chaves primarias da
   base de dados, permitindo consultas, listagem e exibicao (em pagina HTML)
   dos registros contidos no banco de dados.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "base.h"
#include "pk.h"


/*sempre que o vetor que armazena as chaves primarias estiver cheio, 
  ele eh dobrado de tamanho (vetor dinamico dobravel)*/
void realoca_memoria(ap_tipo_registro_pk vetor_pk, int * limite){
  
  ap_tipo_registro_pk temp;

  limite[1]  = 2*(limite[1]);
  printf(">>>vetor (re)alocado com %d posicoes\n", (limite[1]));
  
  temp = realloc(vetor_pk, sizeof(tipo_registro_pk)*limite[1]);

  vetor_pk = temp;
}


/* le todos os dados do arquivo PK.dat e os adiciona em um vetor*/
void lerArquivoPK(FILE *arqPK, ap_tipo_registro_pk vetor, int * limite, int n_registros){
  int i, j;
  tipo_registro_pk novo;


  fseek(arqPK,0,SEEK_SET);
  
  for(i=0;i<n_registros;i++)
    {
      for(j=0; j<TAM_TIT; j++)
        fscanf(arqPK, "%c", &(novo.titulo[j]));
      fscanf(arqPK, "%d", &(novo.nrr));
      
      limite[0]++;

      /*insere cada elemento lido no arquivo pk.dat*/
      if(insere_pk(vetor, novo, limite)){
	printf("Erro na leitura de chaves primarias do arquivo pk.dat!\n");
	return;
      }
    }
}


/*(funcao auxiliar usada na funcao qsort)*/
int compara_qsort(const void * vetora, const void * vetorb) {
  return(strncmp( ((tipo_registro_pk *)vetora)->titulo, 
		  ((tipo_registro_pk *)vetorb)->titulo, TAM_TIT));
}

/*caso a lista em PK.dat nao estivesse criada, le os dados da base.dat 
  e cria os indices no arquivo.*/
void inserePKBase(FILE *arqBase, tipo_registro_pk *vetor ,int * limite, int n_registros){
  
  int i, j;
  tipo_registro_pk novo;
  
  for(i=0;i<n_registros;i++){
    /*encontra a posicao onde o titulo esta registrado*/
    fseek(arqBase,i*TAM_REGISTRO,SEEK_SET);     
    /*copia o titulo*/
    for(j=0; j<TAM_TIT; j++)
      fscanf(arqBase, "%c", &(novo.titulo[j]));

    limite[0]++;

    /*guarda o numero do registro*/
    novo.nrr = limite[0];   
    

    printf("\nimpressao do vetor de chaves primarias a ser inseridas:\n");
      printf("novo.titulo = ");
      for(j=0;j<TAM_TIT;j++)
	printf("%c", novo.titulo[j]);
      printf("novo.nrr = %d\n", novo.nrr);

    


    /*insere cada elemento lido no arquivo pk.dat*/
    if(insere_pk(vetor, novo, limite)){
      /*caso de erro*/
      printf("Erro na leitura de chaves primarias do arquivo base.dat!\n");
      return;
    }
  }  
  /*ordena o vetor em ordem alfabetica*/ 
  /*  qsort(vetor, numberOfPKs, sizeof(tipo_registro_pk), compara_qsort); */
  return;
} 


/*pega o ultimo titulo lido e registra ele como novo, 
para ser inserido no vetor de chaves primarias*/
int novopk(char *str_final, ap_tipo_registro_pk vetor, int * limite){

  int i;
  tipo_registro_pk novo;
 
  /*copia o ultimo titulo inserido*/
  for(i=0;i<TAM_TIT;i++)
    novo.titulo[i]=str_final[i];


  printf("str_final = %s\n\n\n", str_final);


  limite[0]++;
  /*imprime no vetor nrr o numero do seu registro*/
  novo.nrr = limite[0];
  
  
  if(insere_pk(vetor, novo, limite)){
    /*caso de erro*/
    limite[0]--;
    return 1;
  }
  

  return 0;
}

/* insere um novo registro no nosso vetor dinamico de PKs, essa inserção é ordenada e mantém a ordem alfabética do vetor */
int insere_pk(ap_tipo_registro_pk vetor_pk,tipo_registro_pk novo, int * limite){
  int i, j;
 
  printf(">>>insercao da chave primaria %d\n", limite[0]);
 

  /*verifica se ainda cabe dados no vetor (limite 0 contem 
    o numero de chaves primariase limite 1 o tamanho do vetor)*/
   if(limite[0] > limite[1])
     realoca_memoria(vetor_pk, limite);   
   
  if((limite[0])==1){
    printf("pelo menos eu entro aqui");
    vetor_pk[limite[0]-1]=novo;
    return 0;
  }

  for(i=0; i<limite[0]; i++){ 
    
    if(strncmp(novo.titulo, vetor_pk[i].titulo, TAM_TIT) == 0){
      printf("Erro! Titulo inserido já existente!\n");
      printf("Todos os titulos de obras devem ser diferentes! Repita a operação!\n\n");
      return 1;  
    }
    
    if(strncmp(novo.titulo, vetor_pk[i].titulo, TAM_TIT) < 0){
      /*desloca os elementos depois da posicao a ser inserida*/
      for(j=limite[0]-2; j>=i; j--){
	vetor_pk[j+1] = vetor_pk[j];
      }
      
      break;
    }
  }
  if(i==limite[0])
    i--;
  
  vetor_pk[i] = novo;    
  
  printf("\nimpressao do vetor de chaves primarias:\n");
  for(i=0; i< limite[0]; i++){ 
    printf("vetor.titulo = ");
    for(j=0;j<TAM_TIT;j++)
      printf("%c", vetor_pk[i].titulo[j]);
    printf("vetor.nrr = %d\n", vetor_pk[i].nrr);
  }
  
  return 0;
}


/* salva todos os registros do nosso vetor de PKs no arquivo PK.dat*/
void salvarArquivoPK(tipo_registro_pk *vetor, FILE *arq_pk, int limite_reg)
{
  int i,j;
  
  fseek(arq_pk,0,SEEK_SET);
  
  for(i=0; i<limite_reg; i++){
    for(j=0; j<TAM_TIT; j++)
      fprintf(arq_pk, "%c", vetor[i].titulo[j]);
    
    fprintf(arq_pk, "%d", vetor[i].nrr);     
  }
  
}



/* Funcao de listagem de registros. A partir do arquivo de chaves primarias,
 gera um arquivo em html com todos os titulos das obras. */
void lista_registros(int limite_reg, tipo_registro_pk *vetor_de_registros) {

  FILE *arq_html;
  int i,j;

  /* Caso nao haja registros, retorna a funcao. */
  if(limite_reg==0) {
    printf("Nao ha obras cadastradas.\n\n");
  }
  /* Caso haja, gera o arquivo de consulta em HTML */
  else {
    arq_html=fopen("tp2.html","w");
    /* Cabecalho do arquivo */
    fprintf(arq_html,"<html><head></head><body>\n<div align=\"center\">\n");
    fprintf(arq_html,"<br><b>Lista de obras cadastradas</b><br>");
    /* Para cada registro, insere o titulo caractere por caractere */
    for(i=0;i<limite_reg;i++) {
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
void consulta_pk(int limite_reg, tipo_registro_pk *vetor_de_registros, FILE *arq_base) {

  int NRR;
  char titulo_procurado[MAX_TIT];
  tipo_registro_pk *elto_encontrado;

  if(limite_reg==0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta pelo titulo no catalogo:\n");
  /* titulo_procurado eh lido pela mesma funcao de insercao de registro */
  Insere_titulo(titulo_procurado);

  /* Busca o titulo procurado no vetor de structs. */
  elto_encontrado=bsearch(titulo_procurado, vetor_de_registros, limite_reg, sizeof(tipo_registro_pk), compara_bsearch);

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
 
