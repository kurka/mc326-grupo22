#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "defines.h"
#include "base.h"
#include "pk.h"
#include "sk.h"
#include "fopen.h"


/*! 
 * \brief Cria os registros de SKs, a partir da base, um para cada chave secundaria, 
 * assim como as suas respectivas listas invertidas
 */
void criaRegistrosSK(int n_registros, FILE *arqBase){
  int i, j;
  
  char registro[TAM_REGISTRO], pk[TAM_TIT+1];

  int limites_tit[2],limites_tip[2],limites_aut[2], limites_ano[2];


  limites_tit[0]= 0;
  limites_tit[1]= MAX_TIT;
  limites_tip[0]= MAX_TIT;
  limites_tip[1]= MAX_TIP;
  limites_aut[0]= MAX_TIP;
  limites_aut[1]= MAX_AUT;
  limites_ano[0]= MAX_AUT;
  limites_ano[1]= MAX_ANO;

  fseek(arqBase,0,SEEK_SET);
  
  for(i=0; i<n_registros; i++)
    {
      
      fread(registro, sizeof(char)*TAM_REGISTRO, 1, arqBase);
      
      /* Guarda a chave primaria (titulo) */
      for(j=0; j<TAM_TIT; j++)
	pk[j] = registro[j];

      pk[TAM_TIT]='\0'; 


      /* Cria as chaves secundarias e listas invertidas, para cada campo */
      cria_vetor_generico(registro, pk, limites_tit, ARQSK_TIT, ARQLI_TIT);   
      cria_vetor_generico(registro, pk, limites_tip, ARQSK_TIP, ARQLI_TIP);  
      cria_vetor_generico(registro, pk, limites_aut, ARQSK_AUT, ARQLI_AUT);  
      cria_vetor_generico(registro, pk, limites_ano, ARQSK_ANO, ARQLI_ANO);   
    }
  
}

/* /\*! */
/*  * \brief Cria vetores de SKs, a partir de um arquivo ja existente com as chaves criadas */
/*  *\/ */
/* tipo_vetores_sk *ler_arquivo_sk(tipo_arqs_sk * arqs_sk, int tam){ */
  
/*   tipo_registro_sk *vetor_sk; */

/*   /\* Inicializa vetores_sk com memoria e valores iniciais*\/ */
/*   vetores_sk = aloca_memoria_vetor(vetores_sk); */

/*   /\*faz a leitura das chaves de cada arquivo e guarda em seus respectivos campo*\/ */
/*   vetor_sk = le_chaves_sk(vetor_sk, arqs_sk->arq_sk_tit); */
 

/*   return vetor; */
/* } */


/*! 
 * \brief Faz a leitura de um arquivo de chaves secundarias, copiando as chaves secundarias para um vetor
 */
tipo_registro_sk *le_chaves_sk(FILE *arq_generico, int *n_sks){

  int i, n_sk, size;
  char temp[TAM_TIT];
  tipo_registro_sk *vetor_sk;

  fseek(arq_generico,0,SEEK_END);
  size = ftell(arq_generico);
  
  if(size){
    fseek(arq_generico,0,SEEK_SET);
    /*le primeiro o numero de chaves secundarias presentes no arquivo*/
    fscanf(arq_generico, "%8d", &n_sk);
  
  
    vetor_sk = aloca_memoria_vetor(vetor_sk, n_sk);
    
    for(i=0; i<n_sk; i++){
      
      /*le as chaves secundarias e seus apontadores*/
      fscanf(arq_generico, "%s", temp);   
      vetor_sk[i].chave = (char *)malloc(sizeof(char)*((strlen(temp)+1))); 
      strcpy(vetor_sk[i].chave, temp);  
      fscanf(arq_generico, "%8d", &vetor_sk[i].endereco_li);
     /*  generico->n_sk++; */
    }
  }
  else
    if(!size){
      n_sk = 0;
      vetor_sk = NULL;
    }

  
  *n_sks = n_sk;
  
  return vetor_sk;
}


/*!
 * \brief Insere um novo vetor de SKs, um para cada chave secundaria nova do registro,
 * assim como as suas respectivas listas invertidas
 */
void insereVetorSK(char *registro)
{
  int j;
  char pk[TAM_TIT+1];
  int limites_tit[2],limites_tip[2],limites_aut[2], limites_ano[2];


  limites_tit[0]= 0;
  limites_tit[1]= MAX_TIT;
  limites_tip[0]= MAX_TIT;
  limites_tip[1]= MAX_TIP;
  limites_aut[0]= MAX_TIP;
  limites_aut[1]= MAX_AUT;
  limites_ano[0]= MAX_AUT;
  limites_ano[1]= MAX_ANO;
 

  /* Guarda a chave primaria (titulo) */
  for(j=0; j<TAM_TIT; j++)
    pk[j] = registro[j];
  
  pk[TAM_TIT]='\0';

      
  /* Adiciona as chaves secundarias e listas invertidas, para cada campo */
  cria_vetor_generico(registro, pk, limites_tit, ARQSK_TIT, ARQLI_TIT);   
  cria_vetor_generico(registro, pk, limites_tip, ARQSK_TIP, ARQLI_TIP);  
  cria_vetor_generico(registro, pk, limites_aut, ARQSK_AUT, ARQLI_AUT);  
  cria_vetor_generico(registro, pk, limites_ano, ARQSK_ANO, ARQLI_ANO);     
 } 


/*! 
 * \brief Cria vetor sk e lista invertidas para diversos parametros
 */	
void cria_vetor_generico(char *registro, char *pk, int limite[2], char *prefixo_sk, char *prefixo_li){

  int j, k, l, prox;   
  char temp_sk[TAM_TIT];
  char *arquivo;
  int novaSK, endereco_li;
  int n_li, n_sk, pos;
  FILE *arq_sk, *arq_li;
  tipo_registro_sk *vetor_sk;
  
  
  /* Rotina que separa uma string composta em substrigs simples, que serão as SKs, e verifica se essa SK 
     já existe ou se deve ser inserida */
  k=0;
  for(j=limite[0]; j<limite[1]; j++){
    if(registro[j] == ' ' || j==limite[1]-1){
      
      /* Se k==0 significa que estao sendo lidos os espacos no final do titulo*/
      if(k!=0){ 
	
	/* Excecao quando a palavra termina no ultimo caracter do campo */
	if(j == limite[1]-1){
	  temp_sk[k] = registro[j];
	  k++;	      
	}
	
	/* Temos um nome simples (possivel SK) em temp_sk */
	temp_sk[k]='\0';
	

	/*calcula o hash e abre o arquivo correspondente */
	arquivo = calculaHash(temp_sk, prefixo_sk);
	arq_sk = fopen(arquivo, "r+");
	if(!arq_sk){
	  if(DEBUG)
	    printf(">>>Criando arquivo %s\n", arquivo);
	  arq_sk = fopen(arquivo, "w+");
	}

	/*carrega os vetores dinamicamente*/	
	vetor_sk = le_chaves_sk(arq_sk, &n_sk);

	/*abre arquivo correspondente de lista invertida*/
	arquivo = calculaHash(temp_sk, prefixo_li);
	arq_li = fopen(arquivo, "r+");
	if(!arq_li){
	  if(DEBUG)
	    printf(">>>Criando arquivo %s\n", arquivo);
	  arq_li = fopen(arquivo, "w+");
	}

	/*calcula o numero de chaves no arquivo*/
	fseek(arq_li,0,SEEK_END);
	n_li = ftell(arq_li)/(TAM_LI);

	/* novaSK (1 = true, 0 = false) */
	novaSK = 1;
	for(l=0; l<n_sk; l++){
	  if(strcmpinsensitive(vetor_sk[l].chave, temp_sk) == 0)
	    novaSK = 0;
	}

	/* Caso a nova SK for valida, entao eh inserida */
	if(novaSK == 1){ 

	  /*guarda o novo numero de sks no arquivo*/
	  fseek(arq_sk, 0,SEEK_SET);
	  fprintf(arq_sk, "%08d", n_sk+1);

	  /*a chave vai ser inserida no final do arquivo*/
	  fseek(arq_sk,0,SEEK_END);
	  pos = ftell(arq_sk);	  

	  fseek(arq_sk, pos, SEEK_SET);
	  fprintf(arq_sk, "%s ", temp_sk);
	  fprintf(arq_sk, "%08d", n_li);
	    
	  
	  prox = -1;
	  
	  fseek(arq_li, (n_li)*(TAM_TIT+8),SEEK_SET);	  
	  fprintf(arq_li, "%s", pk); 
	  fprintf(arq_li, "%08d", prox);     	  
	  
	}
	/* Caso a SK já existe, entao adiciona a chave primaria correspondente na lista invertida */
	else{
	  for(l=0; l<n_sk; l++){  
	    
	    if(strcmpinsensitive(vetor_sk[l].chave, temp_sk) == 0){
	      
	      /* Encontramos a SK no vetor de SKs */
	      endereco_li = vetor_sk[l].endereco_li;
	      
	      fseek(arq_li, ((endereco_li)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
	      fscanf(arq_li, "%08d", &prox);

	      /* Percorre a lista invertida, para ele poder apontar para a nova entrada */
	      while(prox != -1){
		endereco_li = prox;
		fseek(arq_li, ((prox)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
		fscanf(arq_li, "%08d", &prox);
	      }
	      
	      /* Insercao na lista invertida */
	      fseek(arq_li, ((endereco_li)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
	      fprintf(arq_li, "%08d", n_li);     	  
	      fseek(arq_li, ((n_li)*(TAM_TIT+8)), SEEK_SET);
	      fprintf(arq_li, "%s", pk); 
	      fprintf(arq_li, "%08d", prox);     	  
	      
	      break;
	      
	    }
	  }  
	}  
	fclose(arq_sk);
	fclose(arq_li);	
      } 
      k = 0;
      
    }
    else{
      temp_sk[k] = registro[j];
      k++;
    }
  }

  /*desaloca vetor criado*/
  for(j=0; j<n_sk; j++)
    free(vetor_sk[j].chave);

  if(n_sk)
    free(vetor_sk);

}

/*!
 *
 *\brief Abre ou cria arquivo que sera usado 
 */


/*!
 * \brief Aloca memoria inicial das estruturas de chaves secundarias
 */
tipo_registro_sk *aloca_memoria_vetor(tipo_registro_sk *vetor_sk, int tam){

  
  vetor_sk = (tipo_registro_sk *) malloc(sizeof(tipo_registro_sk)*(tam));
 
  return vetor_sk;
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
void acha_sk(char *palavra_procurada, int n_pk, int n_sk, FILE *arq_base, FILE *arq_gen_li, tipo_registro_sk *vetor_sk, tipo_registro_pk *vetor_pk){
  
  int endereco_li, res;
  char pk[MAX_TIT];
  FILE *arq_html;
  tipo_registro_sk * elto_encontrado;


  /* Busca o titulo procurado no vetor de structs. */
  elto_encontrado=bsearch(palavra_procurada, vetor_sk, n_sk, sizeof(tipo_registro_sk), compara_bsearch2);  
 
 
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
void consulta_sk_tit(int n_pk, FILE *arq_base) {

  char titulo_procurado[TAM_TIT+1];
  char * arquivo;
  int n_sk, tam_pks;
  FILE *arq_li, *arq_sk, *arq_pk;
  tipo_registro_pk * pks;
  tipo_registro_sk * sks;


  if(n_pk == 0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta de titulo no catalogo:\n");
  /* titulo_procurado eh lido*/
  printf("Digite um termo (apenas uma palavra) a ser pesquisado (max 200 letras)\n\n");
  
  /* Le o tipo a ser buscado */
  if(le_sk(titulo_procurado, TAM_TIT)){
    
    

    /*calcula hash e abre arquivo li*/
    arquivo = calculaHash(titulo_procurado, ARQLI_TIT);   
    arq_li = fopen(arquivo, "r+");

    /*abre arquivo de sks e carrega suas chaves em vetor dinamico*/
    arquivo = calculaHash(titulo_procurado, ARQSK_TIT);   
    if(DEBUG)
      printf(">>>Buscando chave no arquivo %s\n", arquivo);
    
    arq_sk = fopen(arquivo, "r+");
    if(!arq_sk)
      arq_sk = fopen(arquivo, "w+");

    sks = le_chaves_sk(arq_sk, &n_sk);
    /*ordena vetor, para fazer bsearch*/
    qsort(sks, n_sk, sizeof(tipo_registro_sk), compara_qsort2); 

    /*abre arquivo de pks e carrega as suas chaves primarias*/
    arquivo = calculaHash(titulo_procurado, ARQPK);   
    arq_pk = fopen(arquivo, "a+");
 
    fseek(arq_pk, 0, SEEK_END);
    tam_pks = ftell(arq_pk)/TAM_PK;
    
    pks = (tipo_registro_pk *) malloc(sizeof(tipo_registro_pk)*tam_pks);
    pks = lerArquivoPK(arq_pk, pks, tam_pks);


    /* Procura se existe chave secundaria com o termo requisitado */
    acha_sk(titulo_procurado, tam_pks, n_sk, arq_base, arq_li, sks, pks);
  }

    free(sks);
    free(pks);
  return;
}

/* /\*! */
/*  * \brief Instancia a estrutura do tipo_dados_sk do campo tipo */
/*  *\/ */

/* void consulta_sk_tip(tipo_dados_sk * tipo, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_tip_li, FILE *arq_base) { */

/*   char tipo_procurado[TAM_TIP+1]; */

/*   if(n_pk == 0) { */
/*     printf("Nao ha obras registradas no catalogo.\n\n"); */
/*     return; */
/*   } */

/*   printf("Consulta de tipo catalogo:\n"); */
/*   /\* tipo_procurado eh lido *\/ */
/*   printf("Digite um termo (apenas uma palavra) a ser pesquisado (max 100 letras)\n\n"); */

/*   /\* Le o tipo a ser buscado *\/ */
/*   if(le_sk(tipo_procurado, TAM_TIP)) */
/*     /\* Procura se existe chave secundaria com o termo requisitado *\/ */
/*     acha_sk(tipo_procurado, n_pk, arq_base, arq_tip_li, tipo, vetor_pk); */

/*   return; */
/* } */


/* /\*! */
/*  * \brief Instancia a estrutura do tipo_dados_sk do campo autor */
/*  *\/ */
/* void consulta_sk_aut(tipo_dados_sk * autor, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_aut_li, FILE *arq_base) { */

/*   char autor_procurado[TAM_AUT+1]; */

/*   if(n_pk == 0) { */
/*     printf("Nao ha obras registradas no catalogo.\n\n"); */
/*     return; */
/*   } */

/*   printf("Consulta de autor no catalogo:\n"); */
/*   /\* autor_procurado eh lido*\/ */
/*   printf("Digite um termo (apenas uma palavra) a ser pesquisado (max 125 letras)\n\n"); */
  
/*   /\* Le o autor a ser buscado *\/ */
/*   if(le_sk(autor_procurado, TAM_AUT)) */
/*     /\* Procura se existe chave secundaria com o termo requisitado *\/ */
/*     acha_sk(autor_procurado, n_pk, arq_base, arq_aut_li, autor, vetor_pk); */

/*   return; */
/* } */


/* /\*! */
/*  * \brief Instancia a estrutura do tipo_dados_sk do campo ano */
/*  *\/ */
/* void consulta_sk_ano(tipo_dados_sk * ano, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_ano_li, FILE *arq_base) { */

/*   char ano_procurado[TAM_ANO+1]; */

/*   if(n_pk == 0) { */
/*     printf("Nao ha obras registradas no catalogo.\n\n"); */
/*     return; */
/*   } */

/*   printf("Consulta de ano no catalogo:\n"); */
/*   /\* ano_procurado eh lido *\/ */
/*   printf("Digite um ano a ser pesquisado (max 4 letras)\n\n"); */

/*   /\* Le o ano a ser buscado *\/ */
/*   if(le_sk(ano_procurado, TAM_ANO)) */
/*     /\* Procura se existe chave secundaria com o termo requisitado *\/ */
/*     acha_sk(ano_procurado, n_pk, arq_base, arq_ano_li, ano, vetor_pk); */
  
/*   return; */
/* } */

/*!
 * \brief Instancia a estrutura do tipo_dados_sk do 'campo' descritor
 */
void consulta_sk_dsc(tipo_dados_sk * descritor, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_dsc_li, FILE *arq_base) {

  /* char descritor_procurado; */

  if(n_pk == 0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta de registro por descritor da imagem.\n");
  printf("Digite um valor de classificacao de descritor (de 0 a 8).\n\n");

  /* descritor_procurado eh lido */
  /* // DAVID: descritor deve ser um numero, de 0 a 8 (chamar funcao que faz isso) */


  return;
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
