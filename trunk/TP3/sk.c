#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "defines.h"
#include "base.h"
#include "sk.h"

/*cria vetores de SKs, um para cada chave secundaria, assim como as suas respectivas listas invertidas*/
tipo_vetores_sk * criarVetorSK(FILE *arqBase, int n_registros)
{
  int i, j, k, l;
  
  char registro[TAM_REGISTRO], temp_sk[TAM_TIT];
  tipo_vetores_sk *vetores_sk = (tipo_vetores_sk *)malloc(sizeof(tipo_vetores_sk));
  tipo_vetores_li *vetores_li = (tipo_vetores_li *)malloc(sizeof(tipo_vetores_li));
  int novaSK;
  
  
  
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
	  if(registro[j] == ' ')
	    {
	      
	      if(k!=0) /*temos um nome simples(possivel SK) em temp_sk*/
		{
		  temp_sk[k]='\0';
		  
		  
		  
		  /* novaSK(1 = true, 0 = false)*/
		  novaSK = 1;
		  for(l=0; l<vetores_sk->n_titulos; l++)
		    {
		      if(strcmp(vetores_sk->vetor_SK_titulo[l].chave, temp_sk) == 0)
			novaSK = 0;
		    }
		  
		  if(novaSK == 1) /*se uma nova SK vai ser inserida*/
		    {
		      
		      vetores_sk->vetor_SK_titulo[vetores_sk->n_titulos].chave = (char *)malloc(sizeof(char)*(k+1));
		      
		      strcpy(vetores_sk->vetor_SK_titulo[vetores_sk->n_titulos].chave, temp_sk);
		      vetores_sk->n_titulos++;
		      
		      
		      /* criando a li */  /* legal */
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
		  else /* a SK já existe, mas precisamos inserir a chave na lista invertida */ /* Roda mas não foi testado*/
		    {
		      for(l=0; l<vetores_sk->n_titulos; l++)
			{
			  if(strcmp(vetores_sk->vetor_SK_titulo[l].chave, temp_sk) == 0) /* encontramos a SK no vetor de SKs */
			    {
			      int endereco_li = vetores_sk->vetor_SK_titulo[l].endereco_li;
			      
			      while(vetores_li->vetor_li_titulo[endereco_li].prox!= -1) /* chegando no final da lista invertida, para ele poder apontar para a nova entrada*/
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
      
      
      
      
      
      
      
      
      /*criando vetor sk e lista invertida p/ autor*/
      
      /*rotina que separa uma string composta em substrigs simples, que serão as SKs, e verifica se essa SK já existe ou se deve ser inserida	*/
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
		      if(strcmp(vetores_sk->vetor_SK_tipo[l].chave, temp_sk) == 0)
			novaSK = 0;
		    }
		  
		  if(novaSK == 1) /*se uma nova SK vai ser inserida*/
		    {
		      
		      vetores_sk->vetor_SK_tipo[vetores_sk->n_tipos].chave = (char *)malloc(sizeof(char)*(k+1));
		      
		      strcpy(vetores_sk->vetor_SK_tipo[vetores_sk->n_tipos].chave, temp_sk);
		      vetores_sk->n_tipos++;
		      
		      
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
		      if(strcmp(vetores_sk->vetor_SK_autor[l].chave, temp_sk) == 0)
			novaSK = 0;
		    }
		  
		  if(novaSK == 1) /*se uma nova SK vai ser inserida*/
		    {
		      
		      vetores_sk->vetor_SK_autor[vetores_sk->n_autores].chave = (char *)malloc(sizeof(char)*(k+1));
		      
		      strcpy(vetores_sk->vetor_SK_autor[vetores_sk->n_autores].chave, temp_sk);
		      vetores_sk->n_autores++;
		      
		      
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
      
      /*criando vetor sk e lista invertida p/ tipo*/
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
		      if(strcmp(vetores_sk->vetor_SK_ano[l].chave, temp_sk) == 0)
			novaSK = 0;
		    }
		  
		  if(novaSK == 1) /*se uma nova SK vai ser inserida*/
		    {
		      
		      vetores_sk->vetor_SK_ano[vetores_sk->n_anos].chave = (char *)malloc(sizeof(char)*(k+1));
		      
		      strcpy(vetores_sk->vetor_SK_ano[vetores_sk->n_anos].chave, temp_sk);
		      vetores_sk->n_anos++;
		      
		      
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
  
  
  
  /*printf("\n NUMERO %d", vetores_li->n_titulos);	
    for(l=0; l< vetores_li->n_titulos; l++)
    {
    printf("%s", vetores_li->vetor_li_titulo[l].chave);	
    }
    
    int x;
    scanf("%d", &x);
  */
  return vetores_sk;
  
}





/* Estrutura do arquivo de chaves secundarias:
   [SK][Numero de PKs associadas][Chaves associadas (multiplo de 200)]
   Exemplo:
   Registros: "a ultima ceia","a santa ceia"

   a 2 a ultima ceia             a santa ceia               
   ultima 1 a ultima ceia        
   ceia 2 a ultima ceia          a santa ceia               
   santa 1 a santa ceia          
*/


/*
  1 Ao iniciar o programa, verifica se existe um arquivo de chaves secundarias
  1.1 Existe sk.dat
  1.2 Nao existe sk.dat
  1.2.1 Se existe base.dat => gera um sk.dat
 */


/*
  Busca por indice secundario (recebe uma string e procura no arquivo de SK's ) 
 */


/*
  Remocao de registro -> avail list dos indices secundarios
  Insercao de registro -> insere novas chaves secundarias do novo registro
 */


void consulta_sk() {
  return;
}
