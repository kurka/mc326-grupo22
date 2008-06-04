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
  tipo_vetores_li *vetores_li = (tipo_vetores_li *)malloc(sizeof(tipo_vetores_li));
  
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
      
      /*guarda a chave primaria (titulo)*/
      for(j=0; j<TAM_TIT; j++)
	pk[j] = registro[j];

      pk[TAM_TIT]='\0'; 

      
      /*cria as chaves secundarias e listas invertidas, para cada campo*/      
      cria_vetor_titulo(registro, pk, vetores_sk, vetores_li);
      cria_vetor_tipo(registro, pk, vetores_sk, vetores_li);
      cria_vetor_autor(registro, pk, vetores_sk, vetores_li);
      cria_vetor_ano(registro, pk, vetores_sk, vetores_li);
      
    }
  
  
/*   if(DEBUG){ */
/*     printf("\n NUMERO %d", vetores_li->n_titulos); */
/*     for(l=0; l< vetores_li->n_titulos; l++) */
/*       { */
/* 	printf("l = %d", l); */
/* 	printf("%-50s", vetores_li->vetor_li_titulo[l].chave); */
/* 	printf("%d\n", vetores_li->vetor_li_titulo[l].prox); */
/*       } */
/*   } */
  
  /*salva em arquivo as listas invertidas de chaves secundarias*/
  salvaArquivosLi(vetores_li, arqs_li);

  /*libera a memoria alocada*/
  free(vetores_li->vetor_li_titulo);
  free(vetores_li->vetor_li_autor);
  free(vetores_li->vetor_li_ano);
  free(vetores_li->vetor_li_tipo);
  free(vetores_li);  

  return vetores_sk;
}


/* cria vetor sk e lista invertida para titulo */	
void cria_vetor_titulo(char registro[TAM_REGISTRO], char pk[TAM_TIT+1], tipo_vetores_sk *vetores_sk, tipo_vetores_li *vetores_li){
 

  int j, k, l;   
  char temp_sk[TAM_TIT];
  int novaSK, endereco_li;
  
  /*rotina que separa uma string composta em substrigs simples, que serão as SKs, e verifica se essa SK 
    já existe ou se deve ser inserida	*/
  k=0;
  for(j=0; j<MAX_TIT; j++)
    {
      /*printf("registro[j]=%c", registro[j]);*/
      if(registro[j] == ' ' || j==MAX_TIT-1)
	{
	  /*excecao quando a palavra termina no ultimo caracter do campo*/
	  if(j == MAX_TIT-1){
	    temp_sk[k] = registro[j];
	    k++;	      
	  }
	  
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
		    if(strcmpinsensitive(temp_sk, vetores_sk->vetor_SK_titulo[l].chave) == 0)
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
		  
		  /*copiando a chave*/
		  strcpy(vetores_li->vetor_li_titulo[vetores_li->n_titulos].chave,  pk); 
		  
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
			  
			  /*copiando a chave*/
			  strcpy(vetores_li->vetor_li_titulo[vetores_li->n_titulos].chave,  pk); 		      
			  
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
  
}



/* cria vetor sk e lista invertida para tipo */	
void cria_vetor_tipo(char registro[TAM_REGISTRO], char pk[TAM_TIT+1], tipo_vetores_sk *vetores_sk, tipo_vetores_li *vetores_li){
 

  int j, k, l;   
  char temp_sk[TAM_TIT];
  int novaSK, endereco_li;

  /*rotina que separa uma string composta em substrigs simples, que serão as SKs, 
    e verifica se essa SK já existe ou se deve ser inserida	*/
  k=0;
  for(j=MAX_TIT; j<MAX_TIP; j++)
    {
      if(registro[j] == ' ' || j == MAX_TIP-1)
	{
	  
	  /*excecao quando a palavra termina no ultimo caracter do campo*/
	  if(j == MAX_TIP-1){
	    temp_sk[k] = registro[j];
	    k++;	      
	  }
	  
	  if(k!=0) /*temos um nome simples(possivel SK) em temp_sk*/
	    {
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
		  vetores_sk->vetor_SK_tipo[vetores_sk->n_tipos-1].endereco_li = vetores_li->n_tipos;
		  vetores_li->vetor_li_tipo[vetores_li->n_tipos].chave = (char *)malloc(sizeof(char)*(TAM_TIT+1));
		  
		  /*copiando a chave*/
		  strcpy(vetores_li->vetor_li_tipo[vetores_li->n_tipos].chave,  pk); 
		  
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
			  vetores_li->vetor_li_tipo[vetores_li->n_tipos].chave = (char *)malloc(sizeof(char)*(TAM_TIT+1));
			  
			  /*copiando a chave*/
			  strcpy(vetores_li->vetor_li_tipo[vetores_li->n_tipos].chave,  pk); 
			  
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
}



/* cria vetor sk e lista invertida para autor */	
void cria_vetor_autor(char registro[TAM_REGISTRO], char pk[TAM_TIT+1], tipo_vetores_sk *vetores_sk, tipo_vetores_li *vetores_li){
 

  int j, k, l;   
  char temp_sk[TAM_TIT];
  int novaSK, endereco_li;
 
  /*rotina que separa uma string composta em substrigs simples, que serão as SKs, 
    e verifica se essa SK já existe ou se deve ser inserida	*/
  k=0;
  for(j=MAX_TIP; j<MAX_AUT; j++)
    {
      if(registro[j] == ' ' || j == MAX_AUT-1)
	{
	  /*excecao quando a palavra termina no ultimo caracter do campo*/
	  if(j == MAX_AUT-1){
	    temp_sk[k] = registro[j];
	    k++;	      
	  }
	  
	  if(k!=0) /*temos um nome simples(possivel SK) em temp_sk*/
	    {
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
		  vetores_sk->vetor_SK_autor[vetores_sk->n_autores-1].endereco_li = vetores_li->n_autores;
		  vetores_li->vetor_li_autor[vetores_li->n_autores].chave = (char *)malloc(sizeof(char)*(TAM_TIT+1));
		  
		  /*copiando a chave*/
		  strcpy(vetores_li->vetor_li_autor[vetores_li->n_autores].chave, pk);
		  
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
			  vetores_li->vetor_li_autor[vetores_li->n_autores].chave = (char *)malloc(sizeof(char)*(TAM_TIT+1));
			  
			  /*copiando a chave*/
			  strcpy(vetores_li->vetor_li_autor[vetores_li->n_autores].chave, pk);
			  
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
}


/* cria vetor sk e lista invertida para ano */	
void cria_vetor_ano(char registro[TAM_REGISTRO], char pk[TAM_TIT+1], tipo_vetores_sk *vetores_sk, tipo_vetores_li *vetores_li){
 

  int j, k, l;   
  char temp_sk[TAM_TIT];
  int novaSK, endereco_li;

   
  /*criando vetor sk e lista invertida p/ ano*/
  /*rotina que separa uma string composta em substrigs simples, que serão as SKs, 
    e verifica se essa SK já existe ou se deve ser inserida */
  k=0;
  for(j=MAX_AUT; j<MAX_ANO; j++)
    {
      if(registro[j] == ' ' || j == MAX_ANO-1)
	{
	  /*excecao quando a palavra termina no ultimo caracter do campo*/
	  if(j == MAX_ANO-1){
	    temp_sk[k] = registro[j];
	    k++;	      
	  }
	  
	  if(k!=0) /*temos um nome simples(possivel SK) em temp_sk*/
	    {
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
		  vetores_sk->vetor_SK_ano[vetores_sk->n_anos-1].endereco_li = vetores_li->n_anos;
		  vetores_li->vetor_li_ano[vetores_li->n_anos].chave = (char *)malloc(sizeof(char)*(TAM_TIT+1));
		  
		  
		  /*copiando a chave*/
		  strcpy( vetores_li->vetor_li_ano[vetores_li->n_anos].chave,  pk);  
		  
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
			  vetores_li->vetor_li_ano[vetores_li->n_anos].chave = (char *)malloc(sizeof(char)*(TAM_TIT+1));
			  
			  /*copiando a chave*/
			  strcpy( vetores_li->vetor_li_ano[vetores_li->n_anos].chave,  pk);  
			  
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


/**
    \brief salva todos os registros da lista invertida de chaves secundarias nos arquivos *li.dat
*/
void salvaArquivosLi(tipo_vetores_li * vetores_li, tipo_arqs_li * arqs_li)
{
  int i;

  arqs_li->arq_tit_li = fopen("li_titulos.dat", "w+");  
  arqs_li->arq_tip_li = fopen("li_tipos.dat", "w+");  
  arqs_li->arq_aut_li = fopen("li_autores.dat", "w+");  
  arqs_li->arq_ano_li = fopen("li_anos.dat", "w+");  


  /*salva arquivos lista invertida de chaves secundarias relacionadas a titulos*/  
  fseek(arqs_li->arq_tit_li,0,SEEK_SET);
  
  for(i=0; i<vetores_li->n_titulos; i++){
    fprintf(arqs_li->arq_tit_li, "%s", vetores_li->vetor_li_titulo[i].chave); 
    fprintf(arqs_li->arq_tit_li, "%08d", vetores_li->vetor_li_titulo[i].prox);     
  }


  /*salva arquivos lista invertida de chaves secundarias relacionadas a tipos*/  
  fseek(arqs_li->arq_tip_li,0,SEEK_SET);
  
  for(i=0; i<vetores_li->n_tipos; i++){
    fprintf(arqs_li->arq_tip_li, "%s", vetores_li->vetor_li_tipo[i].chave); 
    fprintf(arqs_li->arq_tip_li, "%08d", vetores_li->vetor_li_tipo[i].prox);     
  }


  /*salva arquivos lista invertida de chaves secundarias relacionadas a autores*/  
  fseek(arqs_li->arq_aut_li,0,SEEK_SET);
  
  for(i=0; i<vetores_li->n_autores; i++){
    fprintf(arqs_li->arq_aut_li, "%s", vetores_li->vetor_li_autor[i].chave); 
    fprintf(arqs_li->arq_aut_li, "%08d", vetores_li->vetor_li_autor[i].prox);     
  }


  /*salva arquivos lista invertida de chaves secundarias relacionadas a anos*/  
  fseek(arqs_li->arq_ano_li,0,SEEK_SET);
  
  for(i=0; i<vetores_li->n_anos; i++){
    fprintf(arqs_li->arq_ano_li, "%s", vetores_li->vetor_li_ano[i].chave); 
    fprintf(arqs_li->arq_ano_li, "%08d", vetores_li->vetor_li_ano[i].prox);     
  }
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
