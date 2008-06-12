#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "defines.h"
#include "base.h"
#include "pk.h"
#include "sk.h"


/*! 
 * \brief Cria vetores de SKs, a partir da base, um para cada chave secundaria, 
 * assim como as suas respectivas listas invertidas
 */
tipo_vetores_sk * criarVetorSK(int n_registros, tipo_arqs_li * arqs_li, FILE *arqBase){
  int i, j;
  
  char registro[TAM_REGISTRO], pk[TAM_TIT+1];

  int n_titulos_li, n_autores_li, n_anos_li, n_tipos_li;

  tipo_vetores_sk *vetores_sk;
  
  /* Inicializa vetores_sk com memoria e valores iniciais*/
  vetores_sk = aloca_memoria_vetor(vetores_sk);
  
	
  n_titulos_li = 0;
  n_tipos_li = 0;
  n_autores_li = 0;
  n_anos_li = 0;

  fseek(arqBase,0,SEEK_SET);
  
  for(i=0; i<n_registros; i++)
    {
      
      fread(registro, sizeof(char)*TAM_REGISTRO, 1, arqBase);
      
      /* Guarda a chave primaria (titulo) */
      for(j=0; j<TAM_TIT; j++)
	pk[j] = registro[j];

      pk[TAM_TIT]='\0'; 

      
      /* Cria as chaves secundarias e listas invertidas, para cada campo */
      vetores_sk->titulo = cria_vetor_generico(registro, pk, vetores_sk->titulo, &n_titulos_li, arqs_li->arq_tit_li);   
      vetores_sk->tipo = cria_vetor_generico(registro, pk, vetores_sk->tipo, &n_tipos_li, arqs_li->arq_tip_li);      
      vetores_sk->autor = cria_vetor_generico(registro, pk, vetores_sk->autor, &n_autores_li, arqs_li->arq_aut_li);      
      vetores_sk->ano = cria_vetor_generico(registro, pk, vetores_sk->ano, &n_anos_li, arqs_li->arq_ano_li);      
    }
  
  /* Ordena registros de sk */
  qsort(vetores_sk->titulo->vetor_SK, vetores_sk->titulo->n_sk, sizeof(tipo_registro_sk), compara_qsort2); 
  qsort(vetores_sk->tipo->vetor_SK, vetores_sk->tipo->n_sk, sizeof(tipo_registro_sk), compara_qsort2); 
  qsort(vetores_sk->autor->vetor_SK, vetores_sk->autor->n_sk, sizeof(tipo_registro_sk), compara_qsort2); 
  qsort(vetores_sk->ano->vetor_SK, vetores_sk->ano->n_sk, sizeof(tipo_registro_sk), compara_qsort2); 
 

  return vetores_sk; 
}

/*! 
 * \brief Cria vetores de SKs, a partir de um arquivo ja existente com as chaves criadas
 */
tipo_vetores_sk *ler_arquivo_sk(tipo_arqs_sk * arqs_sk){ 
  
  tipo_vetores_sk *vetores_sk;

  /* Inicializa vetores_sk com memoria e valores iniciais*/
  vetores_sk = aloca_memoria_vetor(vetores_sk);

  /*faz a leitura das chaves de cada arquivo e guarda em seus respectivos campos*/
  vetores_sk->titulo = le_chaves_sk(vetores_sk->titulo, arqs_sk->arq_sk_tit);
  vetores_sk->tipo = le_chaves_sk(vetores_sk->tipo, arqs_sk->arq_sk_tip);
  vetores_sk->autor = le_chaves_sk(vetores_sk->autor, arqs_sk->arq_sk_aut);
  vetores_sk->ano = le_chaves_sk(vetores_sk->ano, arqs_sk->arq_sk_ano);

  return vetores_sk;
} 


/*! 
 * \brief Faz a leitura de cada arquivo, copiando as chaves secundarias para o vetor
 */
tipo_dados_sk *le_chaves_sk(tipo_dados_sk *generico, FILE * arq_generico){

  int i, n_sk;
  char temp[TAM_TIT];
  fseek(arq_generico,0,SEEK_SET);
  

  /*le primeiro o numero de chaves secundarias presentes no arquivo*/
  fscanf(arq_generico, "%8d", &n_sk);

  for(i=0; i<n_sk; i++){
    /* Verifica se precisa realocar o tamanho do vetor para inserir a nova SK */
    if(generico->n_sk == generico->tam_vetor)
      generico->vetor_SK = realoca_memoria_sk(generico->vetor_SK, &generico->tam_vetor); 
    
    
    /*le as chaves secundarias e seus apontadores*/
    fscanf(arq_generico, "%s", temp);   
    generico->vetor_SK[i].chave = (char *)malloc(sizeof(char)*((strlen(temp)+1))); 
    strcpy(generico->vetor_SK[i].chave, temp);  
    fscanf(arq_generico, "%8d", &generico->vetor_SK[i].endereco_li);
    generico->n_sk++;
 }
  
  return generico;
}


/*!
 * \brief Insere um novo vetor de SKs, um para cada chave secundaria nova do registro, 
 * assim como as suas respectivas listas invertidas
 */
tipo_vetores_sk * insereVetorSK(char *registro, tipo_vetores_sk *vetores_sk, tipo_arqs_li * arqs_li)
{
  int j;
  char pk[TAM_TIT+1];
  int n_titulos_li, n_autores_li, n_anos_li, n_tipos_li;
  

  n_titulos_li = ftell(arqs_li->arq_tit_li)/(TAM_TIT+8);
  n_tipos_li = ftell(arqs_li->arq_tip_li)/(TAM_TIT+8);
  n_autores_li = ftell(arqs_li->arq_aut_li)/(TAM_TIT+8);
  n_anos_li = ftell(arqs_li->arq_ano_li)/(TAM_TIT+8);
 

  /* Guarda a chave primaria (titulo) */
  for(j=0; j<TAM_TIT; j++)
    pk[j] = registro[j];
  
  pk[TAM_TIT]='\0';

      
  /* Adiciona as chaves secundarias e listas invertidas, para cada campo */
  vetores_sk->titulo = cria_vetor_generico(registro, pk, vetores_sk->titulo, &n_titulos_li, arqs_li->arq_tit_li);      
  vetores_sk->tipo = cria_vetor_generico(registro, pk, vetores_sk->tipo, &n_tipos_li, arqs_li->arq_tip_li);      
  vetores_sk->autor = cria_vetor_generico(registro, pk, vetores_sk->autor, &n_autores_li, arqs_li->arq_aut_li);      
  vetores_sk->ano = cria_vetor_generico(registro, pk, vetores_sk->ano, &n_anos_li, arqs_li->arq_ano_li);
  

  /* Ordena registros de sk */
  qsort(vetores_sk->titulo->vetor_SK, vetores_sk->titulo->n_sk, sizeof(tipo_registro_sk), compara_qsort2); 
  qsort(vetores_sk->tipo->vetor_SK, vetores_sk->tipo->n_sk, sizeof(tipo_registro_sk), compara_qsort2); 
  qsort(vetores_sk->autor->vetor_SK, vetores_sk->autor->n_sk, sizeof(tipo_registro_sk), compara_qsort2); 
  qsort(vetores_sk->ano->vetor_SK, vetores_sk->ano->n_sk, sizeof(tipo_registro_sk), compara_qsort2); 
  
  return vetores_sk;
}


/*! 
 * \brief Cria vetor sk e lista invertidas para diversos parametros
 */	
tipo_dados_sk *cria_vetor_generico(char *registro, char *pk, tipo_dados_sk *generico, int *n_li_generica, FILE * arq_gen_li){

  int j, k, l, prox;   
  char temp_sk[TAM_TIT];
  int novaSK, endereco_li;
  int n_sk = generico->n_sk;
  int n_li = *n_li_generica;
  int tam_vetor_sk = generico->tam_vetor; 
  
  /* Rotina que separa uma string composta em substrigs simples, que serão as SKs, e verifica se essa SK 
     já existe ou se deve ser inserida */
  k=0;
  for(j=generico->limite_inf; j<generico->limite_sup; j++){
    if(registro[j] == ' ' || j==generico->limite_sup-1){
      
      /* Se k==0 significa que estao sendo lidos os espacos no final do titulo*/
      if(k!=0){ 
	
	/* Excecao quando a palavra termina no ultimo caracter do campo */
	if(j == generico->limite_sup-1){
	  temp_sk[k] = registro[j];
	  k++;	      
	}
	
	/* Temos um nome simples (possivel SK) em temp_sk */
	temp_sk[k]='\0';
	
	/* novaSK (1 = true, 0 = false) */
	novaSK = 1;
	for(l=0; l<n_sk; l++){
	  if(strcmpinsensitive(generico->vetor_SK[l].chave, temp_sk) == 0)
	    novaSK = 0;
	}

	/* Caso a nova SK for valida, entao eh inserida */
	if(novaSK == 1){ 
	  
	  /* Verifica se precisa realocar o tamanho do vetor para inserir a nova SK */
	  if(n_sk == tam_vetor_sk)
	    generico->vetor_SK = realoca_memoria_sk(generico->vetor_SK, &tam_vetor_sk); 
	  
	  generico->vetor_SK[n_sk].chave = (char *)malloc(sizeof(char)*(k+1));
	  
	  strcpy(generico->vetor_SK[n_sk].chave, temp_sk);
	  n_sk++;
	  

	  /* Criacao da lista invertida */ 
	  generico->vetor_SK[n_sk-1].endereco_li = n_li;
	  prox = -1;
	  
	  fseek(arq_gen_li, (n_li)*(TAM_TIT+8),SEEK_SET);	  
	  fprintf(arq_gen_li, "%s", pk); 
	  fprintf(arq_gen_li, "%08d", prox);     	  
	  
	  n_li++;
	  
	}
	/* Caso a SK já existe, entao adiciona a chave primaria correspondente na lista invertida */
	else{
	  for(l=0; l<n_sk; l++){  
	    
	    if(strcmpinsensitive(generico->vetor_SK[l].chave, temp_sk) == 0){
	      
	      /* Encontramos a SK no vetor de SKs */
	      endereco_li = generico->vetor_SK[l].endereco_li;

	      fseek(arq_gen_li, ((endereco_li)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
	      fscanf(arq_gen_li, "%08d", &prox);

	      /* Percorre a lista invertida, para ele poder apontar para a nova entrada */
	      while(prox != -1){
		endereco_li = prox;
		fseek(arq_gen_li, ((prox)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
		fscanf(arq_gen_li, "%08d", &prox);
	      }
	      
	      /* Insercao na lista invertida */
	      fseek(arq_gen_li, ((endereco_li)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
	      fprintf(arq_gen_li, "%08d", n_li);     	  
	      fseek(arq_gen_li, ((n_li)*(TAM_TIT+8)), SEEK_SET);
	      fprintf(arq_gen_li, "%s", pk); 
	      fprintf(arq_gen_li, "%08d", prox);     	  
	      
	      n_li++;
	      
	      break;
	      
	    }
	  }  
	}  
	
      } 
      k = 0;
      
    }
    else{
      temp_sk[k] = registro[j];
      k++;
    }
  }

  /* Atualizacao dos parametros */
  generico->n_sk = n_sk;
  *n_li_generica = n_li;
  generico->tam_vetor = tam_vetor_sk;
  
/*   if(DEBUG){ */
/*     printf(" NUMERO %d\n", n_sk); */
/*     for(l=0; l< n_sk; l++) */
/*       { */
/* 	printf("%15s", generico->vetor_SK[l].chave); */
/* 	printf("   %d\n", generico->vetor_SK[l].endereco_li); */
/*       } */
/*   } */
  
  return generico;
}

/*!
 * \brief Aloca memoria inicial das estruturas de chaves secundarias
 */
tipo_vetores_sk *aloca_memoria_vetor(tipo_vetores_sk *vetores_sk){

  vetores_sk = (tipo_vetores_sk *)malloc(sizeof(tipo_vetores_sk));

  /* Alocacao de memoria para cada tipo de chave secundaria */
  vetores_sk->titulo = (tipo_dados_sk *)malloc(sizeof(tipo_dados_sk));
  vetores_sk->tipo = (tipo_dados_sk *)malloc(sizeof(tipo_dados_sk));
  vetores_sk->autor = (tipo_dados_sk *)malloc(sizeof(tipo_dados_sk));
  vetores_sk->ano = (tipo_dados_sk *)malloc(sizeof(tipo_dados_sk));
  
  /* Instanciacao dos atributos para cada tipo de SK */
  
  /* Numero de sks inicial*/
  vetores_sk->titulo->n_sk = 0;
  vetores_sk->tipo->n_sk = 0;
  vetores_sk->autor->n_sk = 0;
  vetores_sk->ano->n_sk = 0;
  

  /* Tamanho do vetor inicial*/
  vetores_sk->titulo->tam_vetor = MEM_INIT;
  vetores_sk->tipo->tam_vetor = MEM_INIT;
  vetores_sk->autor->tam_vetor = MEM_INIT;
  vetores_sk->ano->tam_vetor = MEM_INIT;

  /* Limites de leitura dentro dos campos de registro (com TAM_REG caracteres), 
     nos quais voce encontra os dados de cada registro de chave secundaria*/
  vetores_sk->titulo->limite_inf = 0;
  vetores_sk->titulo->limite_sup = MAX_TIT;
  vetores_sk->tipo->limite_inf = MAX_TIT;
  vetores_sk->tipo->limite_sup = MAX_TIP;
  vetores_sk->autor->limite_inf = MAX_TIP;
  vetores_sk->autor->limite_sup = MAX_AUT;
  vetores_sk->ano->limite_inf = MAX_AUT;
  vetores_sk->ano->limite_sup = MAX_ANO;

  /* Aloca/realoca o vetor (dobravel) de SKs (um para cada tipo) */
  vetores_sk->titulo->vetor_SK = realoca_memoria_sk(vetores_sk->titulo->vetor_SK, &vetores_sk->titulo->tam_vetor); 
  vetores_sk->tipo->vetor_SK = realoca_memoria_sk(vetores_sk->tipo->vetor_SK, &vetores_sk->tipo->tam_vetor);   
  vetores_sk->autor->vetor_SK = realoca_memoria_sk(vetores_sk->autor->vetor_SK, &vetores_sk->autor->tam_vetor); 
  vetores_sk->ano->vetor_SK = realoca_memoria_sk(vetores_sk->ano->vetor_SK, &vetores_sk->ano->tam_vetor); 

  return vetores_sk;
}


/*!
 * \brief Funcao de alocacao do vetor (dobravel) de SKs
 */
tipo_registro_sk *realoca_memoria_sk(tipo_registro_sk *vetor_SK_generico, int *limite){
  
  *limite = 2*(*limite);
 
  
  if(*limite==2*MEM_INIT){
    if(DEBUG)
      printf(">>>vetor de sk alocado com %d posicoes\n", (*limite) );
    vetor_SK_generico = (tipo_registro_sk *) malloc(sizeof(tipo_registro_sk)*(*limite));
  }

  else{
    if(DEBUG)
      printf(">>>vetor de sk realocado com %d posicoes\n", (*limite) );
    vetor_SK_generico = realloc(vetor_SK_generico, sizeof(tipo_registro_sk)*(*limite));
  }

  return vetor_SK_generico;
}

/*!
 * \brief Funcao de procura por chave no vetor de chaves secundarias
 */
void acha_sk(char *palavra_procurada, int n_pk, FILE *arq_base, FILE *arq_gen_li, tipo_dados_sk * generico, tipo_registro_pk *vetor_pk){
  
  int endereco_li, res;
  char pk[MAX_TIT];
  FILE *arq_html;
  tipo_registro_sk * elto_encontrado;


  /* Busca o titulo procurado no vetor de structs. */
  elto_encontrado=bsearch(palavra_procurada, generico->vetor_SK, generico->n_sk, sizeof(tipo_registro_sk), compara_bsearch2);  
 
 
  /* Caso o titulo nao esteja registrado, resposta==NULL. Retorna a funcao. */
  if(elto_encontrado==NULL) {
    printf("Nenhuma obra possui os termos procurados.\n\n");
  }
  /* Caso contrario, chama a funcao de busca na base de dados com o endereco_li. */
  else {
    

    /* ARQHTML eh aberto, para guardar os resultados da busca */
    arq_html=fopen(ARQHTML,"w");
    
    endereco_li=((*elto_encontrado).endereco_li);
    
    do{
      /* Desloca o cursor para o inicio do registro. */
      fseek(arq_gen_li, (endereco_li)*(TAM_TIT+8), SEEK_SET);
      fread(pk, sizeof(char)*TAM_TIT, 1, arq_gen_li);
      
      fseek(arq_gen_li, (endereco_li+1)*(TAM_TIT+8)-8, SEEK_SET);
      fscanf(arq_gen_li, "%08d", &endereco_li);
 
      res = acha_pk(vetor_pk, pk, n_pk, arq_base, arq_html);
    
    }
    while(endereco_li != -1);

    if(res){
      printf("Foram encontradas uma ou mais obras com os termos procurados. \n\n");
      printf("Para visualizar suas informações consulte\n"); 
      printf("sua pasta atual e abra o arquivo %s\n\n", ARQHTML);
    }
    else
      printf("Nenhuma obra possui os termos procurados.\n\n");

    fclose(arq_html);
    
  }
  return;
}


/*!
 * \brief Funcao que le da entrada padrao e trata excecoes de entrada de busca
 */
int le_sk(char* palavra_procurada, int max){

  int i, mod=0;
  char c;

  /* Remove espacos em branco do comeco */
  do{
    palavra_procurada[0] = getchar();
  } while(palavra_procurada[0] == ' ' || palavra_procurada[0] == '\n');
  
  for(i=1;i<max;i++){
    palavra_procurada[i]= getchar();
    if(palavra_procurada[i] == ' ' || palavra_procurada[i] == '\n'){
      c = palavra_procurada[i];
      palavra_procurada[i] = '\0';
      break;
    }
  }
  
  if(i == max){
    c = getchar();  
    palavra_procurada[i] = '\0';
  }
  
  /* Pega o "lixo" que o usuario digitar */
  while(c != '\n'){
    c=getchar();
    i++;
    mod = 1;
  }
  
  if(i>max){
    printf("Voce excedeu o tamanho maximo permitido para termo de pesquisa.\n");
    printf("Portanto, sua pesquisa nao foi concluida.\n");
    return 0;
  }
  
  if(mod)
    printf("Atencao! Apenas a primeira palavra digitada sera considerada na busca!\n");
  else
    printf("Titulo lido com sucesso!\n");
  return 1;
}

/*!
 * \brief Instancia a estrutura do tipo_dados_sk do campo titulo
 */
void consulta_sk_tit(tipo_dados_sk *titulo, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_tit_li, FILE *arq_base) {

  char titulo_procurado[TAM_TIT+1];

  if(n_pk == 0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta de titulo no catalogo:\n");
  /* titulo_procurado eh lido*/
  printf("Digite um termo (apenas uma palavra) a ser pesquisado (max 200 letras)\n\n");
  
  /* Le o tipo a ser buscado */
  if(le_sk(titulo_procurado, TAM_TIT))
    /* Procura se existe chave secundaria com o termo requisitado */
    acha_sk(titulo_procurado, n_pk, arq_base, arq_tit_li, titulo, vetor_pk);

  return;
}

/*!
 * \brief Instancia a estrutura do tipo_dados_sk do campo tipo
 */

void consulta_sk_tip(tipo_dados_sk * tipo, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_tip_li, FILE *arq_base) {

  char tipo_procurado[TAM_TIP+1];

  if(n_pk == 0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta de tipo catalogo:\n");
  /* tipo_procurado eh lido */
  printf("Digite um termo (apenas uma palavra) a ser pesquisado (max 100 letras)\n\n");

  /* Le o tipo a ser buscado */
  if(le_sk(tipo_procurado, TAM_TIP))
    /* Procura se existe chave secundaria com o termo requisitado */
    acha_sk(tipo_procurado, n_pk, arq_base, arq_tip_li, tipo, vetor_pk);

  return;
}


/*!
 * \brief Instancia a estrutura do tipo_dados_sk do campo autor
 */
void consulta_sk_aut(tipo_dados_sk * autor, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_aut_li, FILE *arq_base) {

  char autor_procurado[TAM_AUT+1];

  if(n_pk == 0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta de autor no catalogo:\n");
  /* autor_procurado eh lido*/
  printf("Digite um termo (apenas uma palavra) a ser pesquisado (max 125 letras)\n\n");
  
  /* Le o autor a ser buscado */
  if(le_sk(autor_procurado, TAM_AUT))
    /* Procura se existe chave secundaria com o termo requisitado */
    acha_sk(autor_procurado, n_pk, arq_base, arq_aut_li, autor, vetor_pk);

  return;
}


/*!
 * \brief Instancia a estrutura do tipo_dados_sk do campo ano
 */
void consulta_sk_ano(tipo_dados_sk * ano, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_ano_li, FILE *arq_base) {

  char ano_procurado[TAM_ANO+1];

  if(n_pk == 0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta de ano no catalogo:\n");
  /* ano_procurado eh lido */
  printf("Digite um ano a ser pesquisado (max 4 letras)\n\n");

  /* Le o ano a ser buscado */
  if(le_sk(ano_procurado, TAM_ANO))
    /* Procura se existe chave secundaria com o termo requisitado */
    acha_sk(ano_procurado, n_pk, arq_base, arq_ano_li, ano, vetor_pk);
  
  return;
}



/*!
 * \brief Salva em arquivo a lista com as chaves secundarias e seus apontadores para o arquivo de  lista invertida
 */
void salvar_arquivo_sk(tipo_vetores_sk *vetores_sk, tipo_arqs_sk *arqs_sk){ 
  
  salva_vetor_sk(vetores_sk->titulo, arqs_sk->arq_sk_tit);
  salva_vetor_sk(vetores_sk->tipo, arqs_sk->arq_sk_tip);
  salva_vetor_sk(vetores_sk->autor, arqs_sk->arq_sk_aut);
  salva_vetor_sk(vetores_sk->ano, arqs_sk->arq_sk_ano);
} 
  

/*!
 * \brief Salva um  vetor de chaves secundarias de um determinado tipo 
 */
void salva_vetor_sk(tipo_dados_sk *generico, FILE * arq_generico){
  int i;

  fseek(arq_generico,0,SEEK_SET);
  /*primeiro, imprime o numero de chaves secundarias no arquivo*/
  fprintf(arq_generico, "%08d", generico->n_sk);
  
  
  /*depois, imprime as chaves e seus apontadores, com um espaco entre els, para facilitar a leitura*/
  for(i=0;i<generico->n_sk;i++){
    fprintf(arq_generico, "%s", generico->vetor_SK[i].chave);
    fprintf(arq_generico, " ");
    fprintf(arq_generico, "%08d", generico->vetor_SK[i].endereco_li);
  }
  
}


/**************************************/
/*         Funcoes Auxiliares         */
/**************************************/

/*!
 * \brief Funcao analoga a strcmp, mas insensivel a maiusculas/minusculas
 */
int strcmpinsensitive(char * a, char * b){
  int i=0;
  while(a[i]!='\0'){
    if( tolower(a[i]) > tolower(b[i]) )
      return 1;
    if( tolower(a[i]) < tolower(b[i]) )
      return -1;
    
    i++;
  }

  /*se a string a for menor que b, retorna -1*/
  if(a[i]=='\0' && b[i]!=0)
    return -1;

  return 0;
}

/*!
 * \brief Funcao auxiliar usada na funcao qsort (para ordenar sks)
 */
int compara_qsort2(const void * vetora, const void * vetorb){
  return(strcmp( ((tipo_registro_sk *)vetora)->chave,
		  ((tipo_registro_sk *)vetorb)->chave));
}


/*!
 * \brief Funcao auxiliar usada na funcao bsearch (para encontrar sks)
 */
int compara_bsearch2(const void * titulo_procurado, const void * vetorb) {
  return(strcmpinsensitive( (char*)titulo_procurado,
			    ((tipo_registro_sk *)vetorb)->chave));
}
