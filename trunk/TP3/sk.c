#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "defines.h"
#include "base.h"
#include "pk.h"
#include "sk.h"


/*cria vetores de SKs, um para cada chave secundaria, assim como as suas respectivas listas invertidas*/
/* tipo_vetores_sk * criarVetorSK(FILE *arqBase, int n_registros) */
tipo_vetorzao * criarVetorSK(FILE *arqBase, int n_registros)
{
  int i, j, k, l;
  
  char registro[TAM_REGISTRO], temp_sk[TAM_TIT];

  tipo_vetorzao *vetorzao = (tipo_vetorzao *)malloc(sizeof(tipo_vetorzao));

  tipo_vetores_sk *vetores_sk = (tipo_vetores_sk *)malloc(sizeof(tipo_vetores_sk));
  tipo_vetores_li *vetores_li = (tipo_vetores_li *)malloc(sizeof(tipo_vetores_li));
  int novaSK, endereco_li;
  
  vetorzao->vetores_sk = vetores_sk;
  vetorzao->vetores_li = vetores_li;
  
  vetores_sk->n_titulos = 0;
  vetores_sk->n_autores = 0;
  vetores_sk->n_anos = 0;
  vetores_sk->n_tipos = 0;
  
  vetores_sk->vetor_SK_titulo = (tipo_registro_sk *)malloc(sizeof(tipo_registro_sk)*100);
  vetores_sk->vetor_SK_autor = (tipo_registro_sk *)malloc(sizeof(tipo_registro_sk)*100);
  vetores_sk->vetor_SK_ano = (tipo_registro_sk *)malloc(sizeof(tipo_registro_sk)*100);
  vetores_sk->vetor_SK_tipo = (tipo_registro_sk *)malloc(sizeof(tipo_registro_sk)*100);
	
  vetores_li->n_titulos = 0;
  vetores_li->n_autores = 0;
  vetores_li->n_anos = 0;
  vetores_li->n_tipos = 0;
  
  vetores_li->vetor_li_titulo = (tipo_registro_li *)malloc(sizeof(tipo_registro_li)*100);
  vetores_li->vetor_li_autor = (tipo_registro_li *)malloc(sizeof(tipo_registro_li)*100);
  vetores_li->vetor_li_ano = (tipo_registro_li *)malloc(sizeof(tipo_registro_li)*100);
  vetores_li->vetor_li_tipo = (tipo_registro_li *)malloc(sizeof(tipo_registro_li)*100);
  
  fseek(arqBase,0,SEEK_SET);
  
  for(i=0; i<n_registros; i++)
    {
      
      fread(registro, sizeof(char)*TAM_REGISTRO, 1, arqBase);
      
      
      /* criando vetor sk e lista invertida para titulo */	
      /*rotina que separa uma string composta em substrigs simples, que serão as SKs, e verifica se essa SK já existe ou se deve ser inserida	*/
      k=0;
      for(j=0; j<TAM_TIT; j++)
	{
	  /*printf("registro[j]=%c", registro[j]);*/
	  if(registro[j] == ' ')
	    {
	      /*se k=0 significa que estao sendo lidos os espacos no final do titulo*/
	      if(k!=0)  
		{ 
		  /*temos um nome simples(possivel SK) em temp_sk*/
		  temp_sk[k]='\0';
		  
		  
		  
		  /* novaSK(1 = true, 0 = false)*/
		  novaSK = 1;
		  for(l=0; l<vetores_sk->n_titulos; l++)
		    {
		      if(strcmpinsensitive(vetores_sk->vetor_SK_titulo[l].chave, temp_sk) == 0)
			novaSK = 0;
		    }
		  		  
		  if(novaSK == 1) /*se uma nova SK vai ser inserida*/
		    {
		      
		      vetores_sk->vetor_SK_titulo[vetores_sk->n_titulos].chave = (char *)malloc(sizeof(char)*(k+1));
		      
		      strcpy(vetores_sk->vetor_SK_titulo[vetores_sk->n_titulos].chave, temp_sk);
		      vetores_sk->n_titulos++;
		      
		      
		      /* criando a li */ 
		      vetores_sk->vetor_SK_titulo[vetores_sk->n_titulos-1].endereco_li = vetores_li->n_titulos;
		      vetores_li->vetor_li_titulo[vetores_li->n_titulos].chave = (char *)malloc(sizeof(char)*(TAM_TIT+1));
		      
		      
		      for(l=0; l<TAM_TIT; l++) /*copiando a chave*/
			{
			  vetores_li->vetor_li_titulo[vetores_li->n_titulos].chave[l] = registro[l];
			}	
		      vetores_li->vetor_li_titulo[vetores_li->n_titulos].chave[TAM_TIT] = '\0';
		      
		      
		      vetores_li->vetor_li_titulo[vetores_li->n_titulos].prox = -1;
		      vetores_li->n_titulos++;
		      
		    }
		  else /* a SK já existe, mas precisamos inserir a chave na lista invertida */
		    {
		      for(l=0; l<vetores_sk->n_titulos; l++) 
			{  
			  if(strcmpinsensitive(vetores_sk->vetor_SK_titulo[l].chave, temp_sk) == 0) 
			    /*encontramos a SK no vetor de SKs*/
 			    { 
			      
			      endereco_li = vetores_sk->vetor_SK_titulo[l].endereco_li;
			      
			      /* chegando no final da lista invertida, para ele poder apontar para a nova entrada*/
			      while(vetores_li->vetor_li_titulo[endereco_li].prox != -1) 
				{
				  endereco_li = vetores_li->vetor_li_titulo[endereco_li].prox;
				}
			      vetores_li->vetor_li_titulo[endereco_li].prox = vetores_li->n_titulos;
			      vetores_li->vetor_li_titulo[vetores_li->n_titulos].chave = (char *)malloc(sizeof(char)*(TAM_TIT+1));
			      
			      for(l=0; l<TAM_TIT; l++) /*copiando a chave*/
				{
				  vetores_li->vetor_li_titulo[vetores_li->n_titulos].chave[l] = registro[l];
				}	
			      vetores_li->vetor_li_titulo[vetores_li->n_titulos].chave[TAM_TIT] = '\0';
			      
			      vetores_li->vetor_li_titulo[vetores_li->n_titulos].prox = -1;
			      vetores_li->n_titulos++;
			      
			      break;
			      
			    }
 			}  
 		    }  
		  
		} 
	      k = 0;
	      
	    }
	  else
	    {
	      temp_sk[k] = registro[j];
	      k++;
	      
	      
	    }
	}
      
      
      
      
      
      
      
      
      /*criando vetor sk e lista invertida p/ tipo*/
      /*rotina que separa uma string composta em substrigs simples, que serão as SKs, 
	e verifica se essa SK já existe ou se deve ser inserida	*/
      k=0;
      for(j=MAX_TIT; j<MAX_TIP; j++)
	{
	  if(registro[j] == ' ')
	    {
	      
	      if(k!=0) /*temos um nome simples(possivel SK) em temp_sk*/
		{
		  temp_sk[k]='\0';
		  
		  
		  
		  /* novaSK(1 = true, 0 = false)*/
		  novaSK = 1;
		  
		  for(l=0; l<vetores_sk->n_tipos; l++)
		    {
		      if(strcmpinsensitive(vetores_sk->vetor_SK_tipo[l].chave, temp_sk) == 0)
			novaSK = 0;
		    }
		  
		  if(novaSK == 1) /*se uma nova SK vai ser inserida*/
		    {
		      
		      vetores_sk->vetor_SK_tipo[vetores_sk->n_tipos].chave = (char *)malloc(sizeof(char)*(k+1));
		      
		      strcpy(vetores_sk->vetor_SK_tipo[vetores_sk->n_tipos].chave, temp_sk);
		      vetores_sk->n_tipos++;
		      

		      /* criando a li */ 
		      vetores_sk->vetor_SK_tipo[vetores_sk->n_tipos-1].endereco_li = vetores_li->n_tipos;
		      vetores_li->vetor_li_tipo[vetores_li->n_tipos].chave = (char *)malloc(sizeof(char)*(TAM_TIP+1));
		      
		      
		      for(l=MAX_TIT; l<MAX_TIP; l++) /*copiando a chave*/
			{
			  vetores_li->vetor_li_tipo[vetores_li->n_tipos].chave[l-MAX_TIT] = registro[l];
			}	
		      vetores_li->vetor_li_tipo[vetores_li->n_tipos].chave[TAM_TIP] = '\0';
		      
		      
		      vetores_li->vetor_li_tipo[vetores_li->n_tipos].prox = -1;
		      vetores_li->n_tipos++;
		      
		    }

		  /* a SK já existe, mas precisamos inserir a chave na lista invertida */
		  else 
		    {
		      for(l=0; l<vetores_sk->n_tipos; l++) 
			{  
			  if(strcmpinsensitive(vetores_sk->vetor_SK_tipo[l].chave, temp_sk) == 0) 
			    /*encontramos a SK no vetor de SKs*/
 			    { 
			      
			      endereco_li = vetores_sk->vetor_SK_tipo[l].endereco_li;
			      
			      /* chegando no final da lista invertida, para ele poder apontar para a nova entrada*/
			      while(vetores_li->vetor_li_tipo[endereco_li].prox != -1) 
				{
				  endereco_li = vetores_li->vetor_li_tipo[endereco_li].prox;
				}
			      vetores_li->vetor_li_tipo[endereco_li].prox = vetores_li->n_tipos;
			      vetores_li->vetor_li_tipo[vetores_li->n_tipos].chave = (char *)malloc(sizeof(char)*(TAM_TIP+1));
			      
			      for(l=MAX_TIT; l<MAX_TIP; l++) /*copiando a chave*/
				{
				  vetores_li->vetor_li_tipo[vetores_li->n_tipos].chave[l-MAX_TIT] = registro[l];
				}	
			      vetores_li->vetor_li_tipo[vetores_li->n_tipos].chave[TAM_TIP] = '\0';
			      
			      vetores_li->vetor_li_tipo[vetores_li->n_tipos].prox = -1;
			      vetores_li->n_tipos++;
			      
			      break;
			      
			    }
			}
		    }
		  
		  
		  
		  k = 0;
		}
	    }
	  else
	    {
	      temp_sk[k] = registro[j];
	      k++;
	      
	      
	    }
	}
      
      
      /*criando vetor sk e lista invertida p/ autor*/
      /*rotina que separa uma string composta em substrigs simples, que serão as SKs, e verifica se essa SK já existe ou se deve ser inserida	*/
      k=0;
      for(j=MAX_TIP; j<MAX_AUT; j++)
	{
	  if(registro[j] == ' ')
	    {
	      
	      if(k!=0) /*temos um nome simples(possivel SK) em temp_sk*/
		{
		  temp_sk[k]='\0';
		  
		  
		  
		  /* novaSK(1 = true, 0 = false)*/
		  novaSK = 1;
		  
		  for(l=0; l<vetores_sk->n_autores; l++)
		    {
		      if(strcmpinsensitive(vetores_sk->vetor_SK_autor[l].chave, temp_sk) == 0)
			novaSK = 0;
		    }
		
  		  
		  if(novaSK == 1) /*se uma nova SK vai ser inserida*/
		    {
		      
		      vetores_sk->vetor_SK_autor[vetores_sk->n_autores].chave = (char *)malloc(sizeof(char)*(k+1));
		      
		      strcpy(vetores_sk->vetor_SK_autor[vetores_sk->n_autores].chave, temp_sk);
		      vetores_sk->n_autores++;
		      
		      
		      /* criando a li */ 
		      vetores_sk->vetor_SK_autor[vetores_sk->n_autores-1].endereco_li = vetores_li->n_autores;
		      vetores_li->vetor_li_autor[vetores_li->n_autores].chave = (char *)malloc(sizeof(char)*(TAM_AUT+1));
		      
		      
		      for(l=MAX_TIP; l<MAX_AUT; l++) /*copiando a chave*/
			{
			  vetores_li->vetor_li_autor[vetores_li->n_autores].chave[l-MAX_TIP] = registro[l];
			}	
		      vetores_li->vetor_li_autor[vetores_li->n_autores].chave[TAM_AUT] = '\0';
		      
		      
		      vetores_li->vetor_li_autor[vetores_li->n_autores].prox = -1;
		      vetores_li->n_autores++;
		       
		    }

		  /* a SK já existe, mas precisamos inserir a chave na lista invertida */
		  else 
		    {
		      for(l=0; l<vetores_sk->n_autores; l++) 
			{  
			  if(strcmpinsensitive(vetores_sk->vetor_SK_autor[l].chave, temp_sk) == 0)  
			    /*encontramos a SK no vetor de SKs*/
 			    { 
			      
			      endereco_li = vetores_sk->vetor_SK_autor[l].endereco_li;
			      
			      /* chegando no final da lista invertida, para ele poder apontar para a nova entrada*/
			      while(vetores_li->vetor_li_autor[endereco_li].prox != -1) 
				{
				  endereco_li = vetores_li->vetor_li_autor[endereco_li].prox;
				}
			      vetores_li->vetor_li_autor[endereco_li].prox = vetores_li->n_autores;
			      vetores_li->vetor_li_autor[vetores_li->n_autores].chave = (char *)malloc(sizeof(char)*(TAM_AUT+1));
			      
			      for(l=MAX_TIP; l<MAX_AUT; l++) /*copiando a chave*/
				{
				  vetores_li->vetor_li_autor[vetores_li->n_autores].chave[l-MAX_TIP] = registro[l];
				}	
			      vetores_li->vetor_li_autor[vetores_li->n_autores].chave[TAM_AUT] = '\0';
			      
			      vetores_li->vetor_li_autor[vetores_li->n_autores].prox = -1;
			      vetores_li->n_autores++;
			      
			      break;
			      
			    }
			}
		    }
		  
		  k = 0;
		}
	    }
	  else
	    {
	      temp_sk[k] = registro[j];
	      k++;
	      
	      
	    }
	}
      
      /*criando vetor sk e lista invertida p/ ano*/
      /*rotina que separa uma string composta em substrigs simples, que serão as SKs, e verifica se essa SK já existe ou se deve ser inserida	*/
      k=0;
      for(j=MAX_AUT; j<MAX_ANO; j++)
	{
	  if(registro[j] == ' ')
	    {
	      
	      if(k!=0) /*temos um nome simples(possivel SK) em temp_sk*/
		{
		  temp_sk[k]='\0';
		  
		  
		  
		  /* novaSK(1 = true, 0 = false)*/
		  novaSK = 1;
		  
		  for(l=0; l<vetores_sk->n_anos; l++)
		    {
		      if(strcmpinsensitive(vetores_sk->vetor_SK_ano[l].chave, temp_sk) == 0)
			novaSK = 0;
		    }
		  
		  if(novaSK == 1) /*se uma nova SK vai ser inserida*/
		    {
		      
		      vetores_sk->vetor_SK_ano[vetores_sk->n_anos].chave = (char *)malloc(sizeof(char)*(k+1));
		      
		      strcpy(vetores_sk->vetor_SK_ano[vetores_sk->n_anos].chave, temp_sk);
		      vetores_sk->n_anos++;
		      

		      /* criando a li */ 
		      vetores_sk->vetor_SK_ano[vetores_sk->n_anos-1].endereco_li = vetores_li->n_anos;
		      vetores_li->vetor_li_ano[vetores_li->n_anos].chave = (char *)malloc(sizeof(char)*(TAM_ANO+1));
		      
		      
		      for(l=MAX_AUT; l<MAX_ANO; l++) /*copiando a chave*/
			{
			  vetores_li->vetor_li_ano[vetores_li->n_anos].chave[l-MAX_AUT] = registro[l];
			}	
		      vetores_li->vetor_li_ano[vetores_li->n_anos].chave[TAM_ANO] = '\0';
		      
		      
		      vetores_li->vetor_li_ano[vetores_li->n_anos].prox = -1;
		      vetores_li->n_anos++;
		    }


		  /* a SK já existe, mas precisamos inserir a chave na lista invertida */
		  else 
		    {
		      for(l=0; l<vetores_sk->n_anos; l++) 
			{  
			  if(strcmpinsensitive(vetores_sk->vetor_SK_ano[l].chave, temp_sk) == 0) 
			    /*encontramos a SK no vetor de SKs*/
 			    { 
			      
			      endereco_li = vetores_sk->vetor_SK_ano[l].endereco_li;
			      
			      /* chegando no final da lista invertida, para ele poder apontar para a nova entrada*/
			      while(vetores_li->vetor_li_ano[endereco_li].prox != -1) 
				{
				  endereco_li = vetores_li->vetor_li_ano[endereco_li].prox;
				}
			      vetores_li->vetor_li_ano[endereco_li].prox = vetores_li->n_anos;
			      vetores_li->vetor_li_ano[vetores_li->n_anos].chave = (char *)malloc(sizeof(char)*(TAM_ANO+1));
			      
			      for(l=MAX_AUT; l<MAX_ANO; l++) /*copiando a chave*/
				{
				  vetores_li->vetor_li_ano[vetores_li->n_anos].chave[l-MAX_AUT] = registro[l];
				}	
			      vetores_li->vetor_li_ano[vetores_li->n_anos].chave[TAM_ANO] = '\0';
			      
			      vetores_li->vetor_li_ano[vetores_li->n_anos].prox = -1;
			      vetores_li->n_anos++;
			      
			      break;
			      
			    }
			}
		    }
		  

		  k = 0;
		}
	    }
	  else
	    {
	      temp_sk[k] = registro[j];
	      k++;
	    }
	}   
    }
  
  
  if(DEBUG){
    printf("\n NUMERO %d", vetores_li->n_titulos);	
    for(l=0; l< vetores_li->n_titulos; l++)
      {
	printf("l = %d", l);
	printf("%-50s", vetores_li->vetor_li_titulo[l].chave);
	printf("%d\n", vetores_li->vetor_li_titulo[l].prox);	
      }
  }
  

  /*  return vetores_sk;*/
  salvaArquivosLi(vetores_li);
  
  return vetorzao;
}



/**
    \brief salva todos os registros da lista invertida de chaves secundarias nos arquivos *li.dat
*/
void salvaArquivosLi(tipo_vetores_li * vetores_li)
{

  FILE * arq_tit_li;
  int i;

  arq_tit_li = fopen("titulos_li.dat", "w+");  


  
  fseek(arq_tit_li,0,SEEK_SET);
  
  for(i=0; i<vetores_li->n_titulos; i++){
    fprintf(arq_tit_li, "%s", vetores_li->vetor_li_titulo[i].chave); 
    fprintf(arq_tit_li, "%08d", vetores_li->vetor_li_titulo[i].prox);     
  }
  fclose(arq_tit_li); 
}


/* /\** */
/*    \brief funcao auxiliar usada na funcao bsearch */
/* *\/ */
/* int compara_bsearch(const void * titulo_procurado, const void * vetor_de_registros) { */
/*   return(strcmpinsensitive( (char*)titulo_procurado,  */
/* 		  ((tipo_registro_sk*)vetores_sk->vetor_de_registros_sk)->chave)); */
/* } */


void consulta_sk(tipo_vetores_sk * vetores_sk, tipo_vetores_li * vetores_li, FILE *arq_base, tipo_registro_pk * vetor_pk, int n_pk) {

  int endereco_li, i;
  char titulo_procurado[MAX_TIT];
  tipo_registro_sk * elto_encontrado;


  if(n_pk == 0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta por chave secundaria no catalogo:\n");
  /* titulo_procurado eh lido*/
  printf("Digite a chave secundaria a ser pesquisada\n\n");
  scanf("%s", titulo_procurado);
  

  /* Busca o titulo procurado no vetor de structs. */
  /*   elto_encontrado=bsearch(titulo_procurado, vetores_sk->vetor_SK_titulo, limite_reg, sizeof(tipo_registro_sk), compara_bsearch); */

  elto_encontrado = NULL;

  for(i=0; i<vetores_sk->n_titulos; i++)
    {
      if(strcmpinsensitive(vetores_sk->vetor_SK_titulo[i].chave, titulo_procurado) == 0){
	elto_encontrado = &(vetores_sk->vetor_SK_titulo[i]);
	break;
      }
    }
  
  /* Caso o titulo nao esteja registrado, resposta==NULL. Retorna a funcao. */
  if(elto_encontrado==NULL) {
    printf("O titulo nao foi encontrado.\n\n");
  }
  /* Caso contrario, chama a funcao de busca na base de dados com o endereco_li. */
  else {

    endereco_li=((*elto_encontrado).endereco_li);
    
    acha_pk(vetores_li->vetor_li_titulo[endereco_li].chave, vetor_pk, arq_base, n_pk);
		      
/*     /\* chegando no final da lista invertida, para ele poder apontar para a nova entrada*\/ */
/*     while(vetores_li->vetor_li_titulo[endereco_li].prox != -1)  */
/*       { */
/* 	strcpy(vetores_li->vetor_li_ano[endereco_li].chave, titulo_procurado); */
/*       } */
/*     vetores_li->vetor_li_ano[endereco_li].prox = vetores_li->n_anos; */
  }

  return;
}


/**************************************/
/*         Funcoes Auxiliares         */
/**************************************/

/**
   \brief funcao analoga a strcmp, mas insensivel a maiusculas/minusculas
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
  return 0;
}
