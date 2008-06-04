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
tipo_vetores_sk * criarVetorSK(int n_registros, tipo_arqs_li * arqs_li, FILE *arqBase)
{
  int i, j;
  
  char registro[TAM_REGISTRO], pk[TAM_TIT+1];

  tipo_vetores_sk *vetores_sk = (tipo_vetores_sk *)malloc(sizeof(tipo_vetores_sk));

  int n_titulos_li, n_autores_li, n_anos_li, n_tipos_li;
  
  vetores_sk->n_titulos = 0;
  vetores_sk->n_autores = 0;
  vetores_sk->n_anos = 0;
  vetores_sk->n_tipos = 0;
  
  vetores_sk->vetor_SK_titulo = (tipo_registro_sk *)malloc(sizeof(tipo_registro_sk)*100);
  vetores_sk->vetor_SK_autor = (tipo_registro_sk *)malloc(sizeof(tipo_registro_sk)*100);
  vetores_sk->vetor_SK_ano = (tipo_registro_sk *)malloc(sizeof(tipo_registro_sk)*100);
  vetores_sk->vetor_SK_tipo = (tipo_registro_sk *)malloc(sizeof(tipo_registro_sk)*100);
	

  arqs_li->arq_tit_li = fopen("li_titulos.dat", "w+");  
  arqs_li->arq_tip_li = fopen("li_tipos.dat", "w+");  
  arqs_li->arq_aut_li = fopen("li_autores.dat", "w+");  
  arqs_li->arq_ano_li = fopen("li_anos.dat", "w+");  
  
  
  n_titulos_li = 0;
  n_tipos_li = 0;
  n_autores_li = 0;
  n_anos_li = 0;

  fseek(arqBase,0,SEEK_SET);
  
  for(i=0; i<n_registros; i++)
    {
      
      fread(registro, sizeof(char)*TAM_REGISTRO, 1, arqBase);
      
      /*guarda a chave primaria (titulo)*/
      for(j=0; j<TAM_TIT; j++)
	pk[j] = registro[j];

      pk[TAM_TIT]='\0'; 

      
      /*cria as chaves secundarias e listas invertidas, para cada campo*/      
      cria_vetor_titulo(registro, pk, &n_titulos_li, vetores_sk, arqs_li->arq_tit_li);
      cria_vetor_tipo(registro, pk, &n_tipos_li, vetores_sk, arqs_li->arq_tip_li);
      cria_vetor_autor(registro, pk, &n_autores_li, vetores_sk, arqs_li->arq_aut_li);
      cria_vetor_ano(registro, pk, &n_anos_li, vetores_sk, arqs_li->arq_ano_li);
      
    }
  
  
/*   if(DEBUG){ */
/*     printf("\n NUMERO %d", n_titulos); */
/*     for(l=0; l< n_titulos; l++) */
/*       { */
/* 	printf("l = %d", l); */
/* 	printf("%-50s", vetores_li->vetor_li_titulo[l].chave); */
/* 	printf("%d\n", vetores_li->vetor_li_titulo[l].prox); */
/*       } */
/*   } */


  return vetores_sk;
}


/*insere um novo vetor de SKs, um para cada chave secundaria nova do registro, assim como as suas respectivas listas invertidas*/
tipo_vetores_sk * insereVetorSK(char *registro, tipo_vetores_sk *vetores_sk, tipo_arqs_li * arqs_li)
{
  int j;
  char pk[TAM_TIT+1];
  int n_titulos_li, n_autores_li, n_anos_li, n_tipos_li;
  

  vetores_sk->n_titulos = 0;
  vetores_sk->n_autores = 0;
  vetores_sk->n_anos = 0;
  vetores_sk->n_tipos = 0;
  
  /*  //dar realloc (depois que concertar a alocacao do vetor)*/
  
  /*  vetores_sk->vetor_SK_titulo = (tipo_registro_sk *) malloc(sizeof(tipo_registro_sk)*100);
      vetores_sk->vetor_SK_autor = (tipo_registro_sk *)malloc(sizeof(tipo_registro_sk)*100);
      vetores_sk->vetor_SK_ano = (tipo_registro_sk *)malloc(sizeof(tipo_registro_sk)*100);
      vetores_sk->vetor_SK_tipo = (tipo_registro_sk *)malloc(sizeof(tipo_registro_sk)*100); */
	
  n_titulos_li = ftell(arqs_li->arq_tit_li)/(TAM_TIT+8);
  n_tipos_li = ftell(arqs_li->arq_tip_li)/(TAM_TIT+8);
  n_autores_li = ftell(arqs_li->arq_aut_li)/(TAM_TIT+8);
  n_anos_li = ftell(arqs_li->arq_ano_li)/(TAM_TIT+8);
 

  /*guarda a chave primaria (titulo)*/
  for(j=0; j<TAM_TIT; j++)
    pk[j] = registro[j];
  
  pk[TAM_TIT]='\0'; 

      
  /*adiciona as chaves secundarias e listas invertidas, para cada campo*/      
  cria_vetor_titulo(registro, pk, &n_titulos_li, vetores_sk, arqs_li->arq_tit_li);
  cria_vetor_tipo(registro, pk, &n_tipos_li, vetores_sk, arqs_li->arq_tip_li);
  cria_vetor_autor(registro, pk, &n_autores_li, vetores_sk, arqs_li->arq_aut_li);
  cria_vetor_ano(registro, pk, &n_anos_li, vetores_sk, arqs_li->arq_ano_li);
  
  return vetores_sk;
}


/* cria vetor sk e lista invertida para titulo */	
void cria_vetor_titulo(char registro[TAM_REGISTRO], char pk[TAM_TIT+1], int * n_titulos_li, tipo_vetores_sk *vetores_sk, FILE * arq_tit_li){
 

  int j, k, l, prox;   
  char temp_sk[TAM_TIT];
  int novaSK, endereco_li;
  
  int n_titulos = * n_titulos_li;

  /*rotina que separa uma string composta em substrigs simples, que serão as SKs, e verifica se essa SK 
    já existe ou se deve ser inserida	*/
  k=0;
  for(j=0; j<MAX_TIT; j++)
    {
      /*printf("registro[j]=%c", registro[j]);*/
      if(registro[j] == ' ' || j==MAX_TIT-1)
	{
	  
	  /*se k=0 significa que estao sendo lidos os espacos no final do titulo*/
	  if(k!=0)  
	    { 

	      /*excecao quando a palavra termina no ultimo caracter do campo*/
	      if(j == MAX_TIT-1){
		temp_sk[k] = registro[j];
		k++;	      
	      }


	      /*temos um nome simples(possivel SK) em temp_sk*/
	      temp_sk[k]='\0';
	      
	      /* novaSK(1 = true, 0 = false)*/
	      novaSK = 1;
	      for(l=0; l<vetores_sk->n_titulos; l++)
		{
		  if(strcmpinsensitive(vetores_sk->vetor_SK_titulo[l].chave, temp_sk) == 0)
		    if(strcmpinsensitive(temp_sk, vetores_sk->vetor_SK_titulo[l].chave) == 0)
		      novaSK = 0;
		}
	      
	      if(novaSK == 1) /*se uma nova SK vai ser inserida*/
		{
		  vetores_sk->vetor_SK_titulo[vetores_sk->n_titulos].chave = (char *)malloc(sizeof(char)*(k+1));
		  
		  strcpy(vetores_sk->vetor_SK_titulo[vetores_sk->n_titulos].chave, temp_sk);
		  vetores_sk->n_titulos++;
		  
		  
		  /* criando a li */ 
		  vetores_sk->vetor_SK_titulo[vetores_sk->n_titulos-1].endereco_li = n_titulos;
		  prox = -1;
		  
		  fseek(arq_tit_li, (n_titulos)*(TAM_TIT+8),SEEK_SET);	  
		  fprintf(arq_tit_li, "%s", pk); 
		  fprintf(arq_tit_li, "%08d", prox);     	  
		  
		  n_titulos++;
		  
		}
	      else /* a SK já existe, mas precisamos inserir a chave na lista invertida */
		{
		  for(l=0; l<vetores_sk->n_titulos; l++) 
		    {  
		      if(strcmpinsensitive(vetores_sk->vetor_SK_titulo[l].chave, temp_sk) == 0) 
			/*encontramos a SK no vetor de SKs*/
			{ 
			  
			  endereco_li = vetores_sk->vetor_SK_titulo[l].endereco_li;
			  

			  fseek(arq_tit_li, ((endereco_li)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
			  fscanf(arq_tit_li, "%08d", &prox);
			  /* chegando no final da lista invertida, para ele poder apontar para a nova entrada*/
			  while(prox != -1) 
			    {
			      endereco_li = prox;
			      fseek(arq_tit_li, ((prox)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
			      fscanf(arq_tit_li, "%08d", &prox);
			    }


			  fseek(arq_tit_li, ((endereco_li)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
			  fprintf(arq_tit_li, "%08d", n_titulos);     	  


			  fseek(arq_tit_li, ((n_titulos)*(TAM_TIT+8)), SEEK_SET);
			  fprintf(arq_tit_li, "%s", pk); 
			  fprintf(arq_tit_li, "%08d", prox);     	  
		
			  n_titulos++;
			  
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
  
  *n_titulos_li = n_titulos;
}


/* cria vetor sk e lista invertida para tipo */	
void cria_vetor_tipo(char registro[TAM_REGISTRO], char pk[TAM_TIT+1], int *n_tipos_li, tipo_vetores_sk *vetores_sk, FILE * arq_tip_li){
 

  int j, k, l, prox;   
  char temp_sk[TAM_TIT];
  int novaSK, endereco_li;
  
  int n_tipos = * n_tipos_li;

  /*rotina que separa uma string composta em substrigs simples, que serão as SKs, 
    e verifica se essa SK já existe ou se deve ser inserida	*/
  k=0;
  for(j=MAX_TIT; j<MAX_TIP; j++)
    {
      if(registro[j] == ' ' || j == MAX_TIP-1)
	{
	  
	  if(k!=0) /*temos um nome simples(possivel SK) em temp_sk*/
	    {

	      /*excecao quando a palavra termina no ultimo caracter do campo*/
	      if(j == MAX_TIP-1){
		temp_sk[k] = registro[j];
		k++;	      
	      }
	  
	      temp_sk[k]='\0';
	      
	      /* novaSK(1 = true, 0 = false)*/
	      novaSK = 1;
	      
	      for(l=0; l<vetores_sk->n_tipos; l++)
		{
		  if(strcmpinsensitive(vetores_sk->vetor_SK_tipo[l].chave, temp_sk) == 0)
		    if(strcmpinsensitive(temp_sk, vetores_sk->vetor_SK_tipo[l].chave) == 0)
		      novaSK = 0;
		}
	      
	      if(novaSK == 1) /*se uma nova SK vai ser inserida*/
		{
		  vetores_sk->vetor_SK_tipo[vetores_sk->n_tipos].chave = (char *)malloc(sizeof(char)*(k+1));
		  
		  strcpy(vetores_sk->vetor_SK_tipo[vetores_sk->n_tipos].chave, temp_sk);
		  vetores_sk->n_tipos++;
	

		  /* criando a li */ 
		  vetores_sk->vetor_SK_tipo[vetores_sk->n_tipos-1].endereco_li = n_tipos;
		  prox = -1;

		  fseek(arq_tip_li, (n_tipos)*(TAM_TIT+8),SEEK_SET);
		  fprintf(arq_tip_li, "%s", pk); 
		  fprintf(arq_tip_li, "%08d", prox);     	  
		  
		  n_tipos++;
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
			  

			  fseek(arq_tip_li, ((endereco_li)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
			  fscanf(arq_tip_li, "%08d", &prox);
			  /* chegando no final da lista invertida, para ele poder apontar para a nova entrada*/
			  while(prox != -1) 
			    {
			      endereco_li = prox;
			      fseek(arq_tip_li, ((prox)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
			      fscanf(arq_tip_li, "%08d", &prox);
			    }


			  fseek(arq_tip_li, ((endereco_li)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
			  fprintf(arq_tip_li, "%08d", n_tipos);     	  
			  

			  fseek(arq_tip_li, ((n_tipos)*(TAM_TIT+8)), SEEK_SET);
			  fprintf(arq_tip_li, "%s", pk); 
			  fprintf(arq_tip_li, "%08d", prox);     	  
		
			  n_tipos++;
			  
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
  *n_tipos_li = n_tipos;
}



/* cria vetor sk e lista invertida para autor */	
void cria_vetor_autor(char registro[TAM_REGISTRO], char pk[TAM_TIT+1], int *n_autores_li, tipo_vetores_sk *vetores_sk, FILE *arq_aut_li){
 
  int j, k, l, prox;   
  char temp_sk[TAM_TIT];
  int novaSK, endereco_li;
  
  int n_autores = * n_autores_li;

  /*rotina que separa uma string composta em substrigs simples, que serão as SKs, 
    e verifica se essa SK já existe ou se deve ser inserida	*/
  k=0;
  for(j=MAX_TIP; j<MAX_AUT; j++)
    {
      if(registro[j] == ' ' || j == MAX_AUT-1)
	{
	  if(k!=0) /*temos um nome simples(possivel SK) em temp_sk*/
	    {

	      /*excecao quando a palavra termina no ultimo caracter do campo*/
	      if(j == MAX_AUT-1){
		temp_sk[k] = registro[j];
		k++;	      
	      }
	      
	      temp_sk[k]='\0';
	      
	      /* novaSK(1 = true, 0 = false)*/
	      novaSK = 1;
	      
	      for(l=0; l<vetores_sk->n_autores; l++)
		{
		  if(strcmpinsensitive(vetores_sk->vetor_SK_autor[l].chave, temp_sk) == 0)
		    if(strcmpinsensitive(temp_sk, vetores_sk->vetor_SK_autor[l].chave) == 0)
		      novaSK = 0;
		}
	      
	      if(novaSK == 1) /*se uma nova SK vai ser inserida*/
		{
		  vetores_sk->vetor_SK_autor[vetores_sk->n_autores].chave = (char *)malloc(sizeof(char)*(k+1));
		  
		  strcpy(vetores_sk->vetor_SK_autor[vetores_sk->n_autores].chave, temp_sk);
		  vetores_sk->n_autores++;
		  

		  /* criando a li */ 
		  vetores_sk->vetor_SK_autor[vetores_sk->n_autores-1].endereco_li = n_autores;
		  prox = -1;

		  fseek(arq_aut_li, (n_autores)*(TAM_TIT+8),SEEK_SET);
		  fprintf(arq_aut_li, "%s", pk); 
		  fprintf(arq_aut_li, "%08d", prox);     	  
		  
		  n_autores++;
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
			  
			  fseek(arq_aut_li, ((endereco_li)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
			  fscanf(arq_aut_li, "%08d", &prox);
			  /* chegando no final da lista invertida, para ele poder apontar para a nova entrada*/
			  while(prox != -1) 
			    {
			      endereco_li = prox;
			      fseek(arq_aut_li, ((prox)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
			      fscanf(arq_aut_li, "%08d", &prox);
			    }


			  fseek(arq_aut_li, ((endereco_li)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
			  fprintf(arq_aut_li, "%08d", n_autores);     	  


			  fseek(arq_aut_li, ((n_autores)*(TAM_TIT+8)), SEEK_SET);
			  fprintf(arq_aut_li, "%s", pk); 
			  fprintf(arq_aut_li, "%08d", prox);     	  
		
			  n_autores++;
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
  *n_autores_li = n_autores;
}

/* cria vetor sk e lista invertida para ano */	
void cria_vetor_ano(char registro[TAM_REGISTRO], char pk[TAM_TIT+1], int *n_anos_li, tipo_vetores_sk *vetores_sk, FILE *arq_ano_li){
 

  int j, k, l, prox;   
  char temp_sk[TAM_TIT];
  int novaSK, endereco_li;
  
  int n_anos = * n_anos_li;


   
  /*criando vetor sk e lista invertida p/ ano*/
  /*rotina que separa uma string composta em substrigs simples, que serão as SKs, 
    e verifica se essa SK já existe ou se deve ser inserida */
  k=0;
  for(j=MAX_AUT; j<MAX_ANO; j++)
    {
      if(registro[j] == ' ' || j == MAX_ANO-1)
	{
	  if(k!=0) /*temos um nome simples(possivel SK) em temp_sk*/
	    {

	      /*excecao quando a palavra termina no ultimo caracter do campo*/
	      if(j == MAX_ANO-1){
		temp_sk[k] = registro[j];
		k++;	      
	      }
	      
	      
	      temp_sk[k]='\0';
	      
	      /* novaSK(1 = true, 0 = false)*/
	      novaSK = 1;
	      
	      for(l=0; l<vetores_sk->n_anos; l++)
		{
		  if(strcmpinsensitive(vetores_sk->vetor_SK_ano[l].chave, temp_sk) == 0)
		    if(strcmpinsensitive(temp_sk, vetores_sk->vetor_SK_ano[l].chave) == 0)
		      novaSK = 0;
		}
	      
	      if(novaSK == 1) /*se uma nova SK vai ser inserida*/
		{
		  vetores_sk->vetor_SK_ano[vetores_sk->n_anos].chave = (char *)malloc(sizeof(char)*(k+1));
		  
		  strcpy(vetores_sk->vetor_SK_ano[vetores_sk->n_anos].chave, temp_sk);
		  vetores_sk->n_anos++;
		  

		  /* criando a li */ 
		  vetores_sk->vetor_SK_ano[vetores_sk->n_anos-1].endereco_li = n_anos;
		  prox = -1;

		  fseek(arq_ano_li, (n_anos)*(TAM_TIT+8),SEEK_SET);
		  fprintf(arq_ano_li, "%s", pk); 
		  fprintf(arq_ano_li, "%08d", prox);     	  
		  
		  n_anos++;
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
			  
			  fseek(arq_ano_li, ((endereco_li)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
			  fscanf(arq_ano_li, "%08d", &prox);
			  /* chegando no final da lista invertida, para ele poder apontar para a nova entrada*/
			  while(prox != -1) 
			    {
			      endereco_li = prox;
			      fseek(arq_ano_li, ((prox)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
			      fscanf(arq_ano_li, "%08d", &prox);
			    }


			  fseek(arq_ano_li, ((endereco_li)*(TAM_TIT+8))+TAM_TIT, SEEK_SET);
			  fprintf(arq_ano_li, "%08d", n_anos);     	  


			  fseek(arq_ano_li, ((n_anos)*(TAM_TIT+8)), SEEK_SET);
			  fprintf(arq_ano_li, "%s", pk); 
			  fprintf(arq_ano_li, "%08d", prox);     	  
		
			  n_anos++;
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
  *n_anos_li = n_anos;
}


/* /\** */
/*    \brief funcao auxiliar usada na funcao bsearch */
/* *\/ */
/* int compara_bsearch(const void * titulo_procurado, const void * vetor_de_registros) { */
/*   return(strcmpinsensitive( (char*)titulo_procurado,  */
/* 		  ((tipo_registro_sk*)vetores_sk->vetor_de_registros_sk)->chave)); */
/* } */

void consulta_sk_tit(tipo_vetores_sk * vetores_sk, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_tit_li, FILE *arq_base) {

  int endereco_li, i, res;
  char titulo_procurado[MAX_TIT+1];
  char pk[MAX_TIT];
  FILE *arq_html;
  tipo_registro_sk * elto_encontrado;


  if(n_pk == 0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta de titulo no catalogo:\n");
  /* titulo_procurado eh lido*/
  printf("Digite um termo (apenas uma palavra) a ser pesquisado (max 200 letras)\n\n");
  scanf(" %s", titulo_procurado);
  getchar();
  

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
    printf("Nenhuma obra possui os termos procurados.\n\n");
  }
  /* Caso contrario, chama a funcao de busca na base de dados com o endereco_li. */
  else {

    /*tp3.html eh aberto, para guardar os resultados da busca*/
    arq_html=fopen("tp3.html","w");  
   
    endereco_li=((*elto_encontrado).endereco_li); 
    
    do{
      /* Desloca o cursor para o inicio do registro. */
      fseek(arq_tit_li, (endereco_li)*(TAM_TIT+8), SEEK_SET);
      fread(pk, sizeof(char)*TAM_TIT, 1, arq_tit_li);
      
      fseek(arq_tit_li, (endereco_li+1)*(TAM_TIT+8)-8, SEEK_SET);
      fscanf(arq_tit_li, "%08d", &endereco_li);
 
      res= acha_pk(vetor_pk, pk, n_pk, arq_base, arq_html);
      
    }
    while(endereco_li != -1);

    if(res){
      printf("Foram encontradas uma ou mais obras com os termos procurados. \n");
      printf("Para visualizar suas informações consulte sua pasta atual e abra o arquivo tp3.html\n\n"); 
    }
    else
      printf("Nenhuma obra possui os termos procurados.\n\n");


    fclose(arq_html);
    
  }

  return;
}




void consulta_sk_tip(tipo_vetores_sk * vetores_sk, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_tip_li, FILE *arq_base) {

  int endereco_li, i, res;
  char tipo_procurado[MAX_TIT+1];
  char pk[MAX_TIT];
  FILE *arq_html;
  tipo_registro_sk * elto_encontrado;


  if(n_pk == 0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta de tipo catalogo:\n");
  /* titulo_procurado eh lido*/
  printf("Digite um termo (apenas uma palavra) a ser pesquisado (max 100 letras)\n\n");
  scanf(" %s", tipo_procurado);
  getchar();
  
  
  /* Busca o tipo procurado no vetor de structs. */
  /*   elto_encontrado=bsearch(titulo_procurado, vetores_sk->vetor_SK_titulo, limite_reg, sizeof(tipo_registro_sk), compara_bsearch); */
  
  elto_encontrado = NULL;
  
  for(i=0; i<vetores_sk->n_tipos; i++)
    {
      if(strcmpinsensitive(vetores_sk->vetor_SK_tipo[i].chave, tipo_procurado) == 0){
	elto_encontrado = &(vetores_sk->vetor_SK_tipo[i]);
	break;
      }
    }
  
  /* Caso o tipo nao esteja registrado, resposta==NULL. Retorna a funcao. */
  if(elto_encontrado==NULL) {
    printf("Nenhuma obra possui os termos procurados.\n\n");
  }
  /* Caso contrario, chama a funcao de busca na base de dados com o endereco_li. */
  else {

    /*tp3.html eh aberto, para guardar os resultados da busca*/
    arq_html=fopen("tp3.html","w");  
   
    endereco_li=((*elto_encontrado).endereco_li); 
    
    do{
      /* Desloca o cursor para o inicio do registro. */
      fseek(arq_tip_li, (endereco_li)*(TAM_TIT+8), SEEK_SET);
      fread(pk, sizeof(char)*TAM_TIT, 1, arq_tip_li);
      
      fseek(arq_tip_li, (endereco_li+1)*(TAM_TIT+8)-8, SEEK_SET);
      fscanf(arq_tip_li, "%08d", &endereco_li);
 
      res= acha_pk(vetor_pk, pk, n_pk, arq_base, arq_html);
      
    }
    while(endereco_li != -1);
    
    if(res){
      printf("Foram encontradas uma ou mais obras com os termos procurados. \n");
      printf("Para visualizar suas informações consulte sua pasta atual e abra o arquivo tp3.html\n\n"); 
    }
    else
      printf("Nenhuma obra possui os termos procurados.\n\n");
    
    
    fclose(arq_html);
    
  }

  return;
}



void consulta_sk_aut(tipo_vetores_sk * vetores_sk, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_aut_li, FILE *arq_base) {

  int endereco_li, i, res;
  char autor_procurado[MAX_TIT+1];
  char pk[MAX_TIT];
  FILE *arq_html;
  tipo_registro_sk * elto_encontrado;


  if(n_pk == 0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta de autor no catalogo:\n");
  /* titulo_procurado eh lido*/
  printf("Digite um termo (apenas uma palavra) a ser pesquisado (max 125 letras)\n\n");
  scanf(" %s", autor_procurado);
  getchar();
  

  /* Busca o autor procurado no vetor de structs. */
  /*   elto_encontrado=bsearch(titulo_procurado, vetores_sk->vetor_SK_titulo, limite_reg, sizeof(tipo_registro_sk), compara_bsearch); */

  elto_encontrado = NULL;

  for(i=0; i<vetores_sk->n_autores; i++)
    {
      if(strcmpinsensitive(vetores_sk->vetor_SK_autor[i].chave, autor_procurado) == 0){
	elto_encontrado = &(vetores_sk->vetor_SK_autor[i]);
	break;
      }
    }
  
  /* Caso o autor nao esteja registrado, resposta==NULL. Retorna a funcao. */
  if(elto_encontrado==NULL) {
    printf("Nenhuma obra possui os termos procurados.\n\n");
  }
  /* Caso contrario, chama a funcao de busca na base de dados com o endereco_li. */
  else {

    /*tp3.html eh aberto, para guardar os resultados da busca*/
    arq_html=fopen("tp3.html","w");  
   
    endereco_li=((*elto_encontrado).endereco_li); 
    
    do{
      /* Desloca o cursor para o inicio do registro. */
      fseek(arq_aut_li, (endereco_li)*(TAM_TIT+8), SEEK_SET);
      fread(pk, sizeof(char)*TAM_TIT, 1, arq_aut_li);
      
      fseek(arq_aut_li, (endereco_li+1)*(TAM_TIT+8)-8, SEEK_SET);
      fscanf(arq_aut_li, "%08d", &endereco_li);
 
      res= acha_pk(vetor_pk, pk, n_pk, arq_base, arq_html);
      
    }
    while(endereco_li != -1);
    
    if(res){
      printf("Foram encontradas uma ou mais obras com os termos procurados. \n");
      printf("Para visualizar suas informações consulte sua pasta atual e abra o arquivo tp3.html\n\n"); 
    }
    else
      printf("Nenhuma obra possui os termos procurados.\n\n");


    fclose(arq_html);
    
  }

  return;
}



void consulta_sk_ano(tipo_vetores_sk * vetores_sk, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_ano_li, FILE *arq_base) {

  int endereco_li, i, res;
  char ano_procurado[MAX_TIT+1];
  char pk[MAX_TIT];
  FILE *arq_html;
  tipo_registro_sk * elto_encontrado;


  if(n_pk == 0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("Consulta de ano no catalogo:\n");
  /* ano_procurado eh lido*/
  printf("Digite um ano a ser pesquisado (max 4 letras)\n\n");
  scanf(" %s", ano_procurado);
  getchar();
  

  /* Busca o ano procurado no vetor de structs. */
  /*   elto_encontrado=bsearch(titulo_procurado, vetores_sk->vetor_SK_titulo, limite_reg, sizeof(tipo_registro_sk), compara_bsearch); */

  elto_encontrado = NULL;

  for(i=0; i<vetores_sk->n_anos; i++)
    {
      if(strcmpinsensitive(vetores_sk->vetor_SK_ano[i].chave, ano_procurado) == 0){
	elto_encontrado = &(vetores_sk->vetor_SK_ano[i]);
	break;
      }
    }
  
  /* Caso o ano nao esteja registrado, resposta==NULL. Retorna a funcao. */
  if(elto_encontrado==NULL) {
    printf("Nenhuma obra possui os termos procurados.\n\n");
  }
  /* Caso contrario, chama a funcao de busca na base de dados com o endereco_li. */
  else {

    /*tp3.html eh aberto, para guardar os resultados da busca*/
    arq_html=fopen("tp3.html","w");  
   
    endereco_li=((*elto_encontrado).endereco_li); 
    
    do{
      /* Desloca o cursor para o inicio do registro. */
      fseek(arq_ano_li, (endereco_li)*(TAM_TIT+8), SEEK_SET);
      fread(pk, sizeof(char)*TAM_TIT, 1, arq_ano_li);
      
      fseek(arq_ano_li, (endereco_li+1)*(TAM_TIT+8)-8, SEEK_SET);
      fscanf(arq_ano_li, "%08d", &endereco_li);
 
      res= acha_pk(vetor_pk, pk, n_pk, arq_base, arq_html);
      
    }
    while(endereco_li != -1);

    if(res){
      printf("Foram encontradas uma ou mais obras com os termos procurados. \n");
      printf("Para visualizar suas informações consulte sua pasta atual e abra o arquivo tp3.html\n\n"); 
    }
    else
      printf("Nenhuma obra possui os termos procurados.\n\n");

    
    fclose(arq_html);
    
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
