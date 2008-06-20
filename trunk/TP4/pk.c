



/* Esta biblioteca realiza manipulações no arquivo de chaves primarias da
   base de dados, permitindo consultas, listagem e exibicao (em pagina HTML)
   dos registros contidos no banco de dados. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "defines.h"
#include "base.h"
#include "pk.h"
#include "fopen.h"




/*!
 * \brief Caso a lista em PK.dat nao estivesse criada, le os dados da base.dat
 * e cria os indices no arquivo.
 */
void inserePKBase(FILE *arqBase, int * limite, int n_registros){
  
  int i, j, tamanho;
  tipo_registro_pk novo;
  tamanho = *limite;


  for(i=0;i<n_registros;i++){
    /* Encontra a posicao onde o titulo esta registrado */
    fseek(arqBase,i*TAM_REGISTRO,SEEK_SET);
    /* Copia o titulo */
    for(j=0; j<TAM_TIT; j++)
      fscanf(arqBase, "%c", &(novo.titulo[j]));
    
    tamanho++;
    
    /* Guarda o numero do registro */
    novo.nrr = tamanho;
    
    
    insere_pk_arquivo(novo);
  } 
  *limite = tamanho;
}


/*!
 * \brief Remove as chaves primarias do vetor_registros
 */
ap_tipo_registro_pk limpa_pk(FILE *arq_base, ap_tipo_registro_pk vetor_pk, int *limite,int cabeca_avail){
  
  int *avail;
  int i, tam = 1;
  
  /* Cria vetor onde serao armazenadas as nrrs dos
    indices dos elementos da avail_list */
  avail = (int *) malloc(sizeof(int)*tam);
  avail[0] = cabeca_avail;
    
  /* A cada novo elemento encontrado, realoca o vetor e o adiciona a lista */
  while(cabeca_avail != -1){
    /* Le o proximo elemento no arquivo base.dat */
    fseek(arq_base, (cabeca_avail-1)*TAM_REGISTRO, SEEK_SET);
    fscanf(arq_base, "%05d", &cabeca_avail);
    
    tam++;
    avail = realloc(avail, sizeof(int)*(tam));
    avail[tam-1]=cabeca_avail;
  } 
  
  /* Remove os elementos encontrados */
  for(i=0;i<tam-1;i++)
    vetor_pk = remove_pk(vetor_pk, limite, avail[i]);
  
  
  return vetor_pk;
}


/*!
 * \brief Insere o ultimo titulo lido no vetor de chaves primarias
 */
void novopk(char *str_final, int nrr){
  
  int i;
  tipo_registro_pk novo;
 
  /* Copia o ultimo titulo inserido */
  for(i=0;i<TAM_TIT;i++)
    novo.titulo[i]=str_final[i];

  /* Guarda no campo nrr o numero do seu registro */
  novo.nrr = nrr;
  
  insere_pk_arquivo(novo);
  
}



/*! 
 * \brief Insere um novo registro no arquivo de PKs 
 */
void insere_pk_arquivo(tipo_registro_pk novo){
 
  FILE* arq_pk;
  int n_pk, i;
  char *arquivo;
  char titulo[TAM_TIT+1];
 
  for(i=0; i<TAM_TIT; i++)
    titulo[i] =  novo.titulo[i];
  titulo[TAM_TIT] = '\0';
  
  /*calcula o hash e abre o arquivo correspondente */
  arquivo = calculaHash(titulo, ARQPK);


  arq_pk = fopen(arquivo, "r+");
 
  /* Se o arquivo nao existe */
  if(!arq_pk){
    if(DEBUG)
      printf(">>>Criando arquivo %s\n", arquivo);
    arq_pk = fopen(arquivo, "w+");

    fseek(arq_pk, 0, SEEK_SET);

   /*  for(i=0; i<TAM_TIT; i++) */
    /*       fprintf(arq_pk, "%c", novo.titulo[i]); */
    fprintf(arq_pk, "%s", titulo);
    fprintf(arq_pk, "%08d", novo.nrr);      
  }      
  /*se o arquivo existe*/  
  else
    if(arq_pk){
      fseek(arq_pk, 0, SEEK_END);
      n_pk = ftell(arq_pk)/TAM_PK;
      
            
      fseek(arq_pk, TAM_PK*n_pk, SEEK_SET);
/*       for(i=0; i<TAM_TIT; i++) */
/* 	fprintf(arq_pk, "%c", novo.titulo[i]); */
      fprintf(arq_pk, "%s", titulo);   
      fprintf(arq_pk, "%08d", novo.nrr);      
      
    }
  free(arquivo);
  fclose(arq_pk);  
}


/*! 
 * \brief Remove a chave primaria que acabou de ser removida da base
 */
ap_tipo_registro_pk remove_pk(ap_tipo_registro_pk vetor_pk, int * limite, int cabeca_avail){

  int i;

  /* Procura a pk com a chave que foi removida */
  for(i=0;i<limite[0];i++){
    if(vetor_pk[i].nrr == cabeca_avail){
      limite[0]--;
      break;
    }
  }
  
  /* Desloca as pks seguintes */
  for(;i<limite[0];i++)
    vetor_pk[i]=vetor_pk[i+1];

  return vetor_pk;
}
  

/*! 
 *\brief Funcao de listagem de registros. A partir do arquivo de chaves primarias,
gera um arquivo em html com todos os titulos das obras. 
*/
void lista_registros(int limite_reg){

  FILE *arq_html;
  int i,j,k, tam;
  char arquivo[TAM_NOME_ARQ];
  FILE * teste;
  tipo_registro_pk * pks;

  /* Caso nao haja registros, retorna a funcao. */
  if(limite_reg==0) {
    printf("Nao ha obras cadastradas.\n\n");
  }
  /* Caso haja, gera o arquivo de consulta em HTML */
  else {
    arq_html=fopen(ARQHTML,"w");
    /* Cabecalho do arquivo */
    fprintf(arq_html,"<html><head></head><body>\n<div align=\"center\">\n");
    fprintf(arq_html,"<br><b>Lista de obras cadastradas</b><br>");
    /* Para cada registro, insere o titulo caractere por caractere */
    fprintf(arq_html,"<br>");
    for(k=0; k<NUM_HASH; k++){
      sprintf(arquivo, "%s%d.dat", ARQPK, k);
      teste = fopen(arquivo,"r");
      if(teste){
	fseek(teste, 0, SEEK_END);
	tam = ftell(teste)/TAM_PK;
	/*cria lista ligada das pks do arquivo*/
	pks = (tipo_registro_pk *) malloc(sizeof(tipo_registro_pk)*tam); 
	pks = lerArquivoPK(teste, pks, tam);
	for(i=0; i<tam; i++){
	  fprintf(arq_html,"<br>");
	  for(j=0;j<TAM_TIT;j++) {
	    fprintf(arq_html,"%c",pks[i].titulo[j]);
	  }
	}
	free(pks);
      }
    }
    fprintf(arq_html,"<br></div></body></html>");        
    fclose(arq_html);
    printf("Listagem efetuada com sucesso. Para visualiza-la, consulte\n");
    printf("sua pasta atual e abra o arquivo %s\n\n", ARQHTML);
  }

  return;
}

/*!
 * \brief Funcao para leitura de chave primaria a ser procurada na base
 */
void consulta_pk(int limite_reg, FILE *arq_base) {

  char titulo_procurado[MAX_TIT+1];
  char * arquivo;
  FILE *arq_html, *arq_pk;
  int tam;
  tipo_registro_pk * pks;



  if(limite_reg==0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta pelo titulo no catalogo:\n");
  /* titulo_procurado eh lido pela mesma funcao de insercao de registro */
  Insere_titulo(titulo_procurado);


  titulo_procurado[MAX_TIT] = '\0';
  
  /*calcula o hash e abre o arquivo correspondente */
  arquivo = calculaHash(titulo_procurado, ARQPK);

  if(DEBUG)
    printf(">>>Buscando chave primaria no arquivo %s\n", arquivo);

  arq_pk = fopen(arquivo, "r");
  if(arq_pk){
    fseek(arq_pk, 0, SEEK_END);
    tam = ftell(arq_pk)/TAM_PK;
    pks = (tipo_registro_pk *) malloc(sizeof(tipo_registro_pk)*tam); 
    pks = lerArquivoPK(arq_pk, pks, tam);
    
    
    /* Como a chave primaria eh unica, arq_html eh criado em modo "w" */
    arq_html=fopen(ARQHTML,"w");
    
    if(acha_pk(pks, titulo_procurado, tam, arq_base, arq_html)){
      printf("Obra encontrada. Para visualizar suas informações consulte\n");
      printf("sua pasta atual e abra o arquivo %s\n\n", ARQHTML); 
    }
    else{
      printf("O titulo nao foi encontrado.\n\n");
    }

    free(pks);
    
    fclose(arq_html);
  }
  else{
    printf("O titulo nao foi encontrado.\n\n");
  }
 
}


/*!
 * \brief Verifica chave primaria a ser procurada na base
 * (retorna 1 caso encontre e 0 caso nao encontre)
 */
int acha_pk(ap_tipo_registro_pk vetor_de_registros, char titulo_procurado[MAX_TIT+1], int limite_reg, FILE * arq_base, FILE *arq_html){
  ap_tipo_registro_pk elto_encontrado;
  int NRR;
  /* Busca o titulo procurado no vetor de structs. */
  elto_encontrado=bsearch(titulo_procurado, vetor_de_registros, limite_reg, sizeof(tipo_registro_pk), compara_bsearch);
  /* Caso o titulo nao esteja registrado, resposta==NULL. Retorna a funcao. */
  if(elto_encontrado==NULL) {
    return 0;
  }
  /* Caso contrario, chama a funcao de busca na base de dados com o NRR. */
  else {
    NRR=((*elto_encontrado).nrr);
    busca_registro(NRR, arq_base, arq_html); /* funcao definida em base.c */
  }

  return 1;
}


/*!
 * \brief Le todos os dados do arquivo PK.dat e os adiciona em um vetor
 */
ap_tipo_registro_pk lerArquivoPK(FILE *arqPK, ap_tipo_registro_pk vetor, int n_registros){

  int i, j;
  tipo_registro_pk novo;

  fseek(arqPK,0,SEEK_SET);
  for(i=0;i<n_registros;i++){
    for(j=0; j<TAM_TIT; j++){
      fscanf(arqPK, "%c", &(novo.titulo[j]));
    }
       
    fscanf(arqPK, "%d", &(novo.nrr));
   
    
    /* Insere cada elemento lido no arquivo pk.dat */
    vetor = insere_pk(vetor, novo, i); 
  }

  return vetor;
}


/*! 
 * \brief Insere um novo registro no vetor dinamico de PKs, essa insercao eh 
 * ordenada e mantem a ordem alfabetica do vetor 
 */
ap_tipo_registro_pk insere_pk(ap_tipo_registro_pk vetor_pk,tipo_registro_pk novo, int limite){
 
  vetor_pk[limite] = novo;  
  
  /* Ordena o vetor em ordem alfabetica */
  qsort(vetor_pk, limite, sizeof(tipo_registro_pk), compara_qsort); 

  return vetor_pk;
  
}

/**************************************/
/*         Funcoes Auxiliares         */
/**************************************/


/*!
 * \brief Funcao auxiliar usada na funcao qsort
 */
int compara_qsort(const void * vetora, const void * vetorb) {
  return(strncmp( ((tipo_registro_pk *)vetora)->titulo,
		  ((tipo_registro_pk *)vetorb)->titulo, TAM_TIT));
}

/*!
 * \brief Funcao analoga a strncmp, mas insensivel a maiusculas/minusculas
 */
int strncmpinsensitive(char * a, char * b, int size){
  int i;
  for(i=0; i<size;i++){
    if( tolower(a[i]) > tolower(b[i]) )
      return 1;
    if( tolower(a[i]) < tolower(b[i]) )
      return -1;
  }
  return 0;
}


/*!
 * \brief Funcao auxiliar usada na funcao bsearch
 */
int compara_bsearch(const void * titulo_procurado, const void * vetor_de_registros) {
  return(strncmpinsensitive( (char*)titulo_procurado, 
			     ((tipo_registro_pk*)vetor_de_registros)->titulo,TAM_TIT));
} 
