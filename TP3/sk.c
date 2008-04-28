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
	int novaSK;
	
	vetores_sk->n_titulos = 0;
	vetores_sk->n_autores = 0;
	vetores_sk->n_anos = 0;
	vetores_sk->n_tipos = 0;
	
	vetores_sk->vetor_SK_titulo = (tipo_vetores_sk *)malloc(sizeof(tipo_vetores_sk)*100);
	vetores_sk->vetor_SK_autor = (tipo_vetores_sk *)malloc(sizeof(tipo_vetores_sk)*100);
	vetores_sk->vetor_SK_ano = (tipo_vetores_sk *)malloc(sizeof(tipo_vetores_sk)*100);
	vetores_sk->vetor_SK_tipo = (tipo_vetores_sk *)malloc(sizeof(tipo_vetores_sk)*100);
	
		
	
	for(i=0; i<n_registros; i++)
	{
		fread(arqBase, sizeof(TAM_registro), 1, registro);
    	
		criando vetor sk e lista invertida p/ titulo
	  	
			
		//rotina que separa uma string composta em substrigs simples, que serão as SKs, e verifica se essa SK já existe ou se deve ser inserida	
		k=0;
		for(j=0; j<TAM_TIT; j++)
		{
		    if(registro[j] == 0)
		    {
		        if(k!=0) //temos um nome simples(possivel SK) em temp_sk
				{
					temp_sk[k]='\0';
					k=0;
					
					// novaSK(1 = true, 0 = false)
					novaSK = 1
					for(l=0; l<vetores_sk->n_titulos; l++)
					{
						if(strcmp(vetores_sk->vetor_SK_titulo[i], temp_sk) == 0)
							novaSK = 0;
					}
				    
					if(novaSK == 1) //se uma nova SK foi encontrada
					{
					  	strcpy(vetores_sk->vetor_SK_titulo[vetores_sk->n_titulos], temp_sk);
						vetores_sk->n_titulo++;
					}
					
				}
		    }
			else
			{
				temp_sk[k] = registro[j];
				k++
			}
 		}
				
			
			
	    //criando vetor sk e lista invertida p/ autor
		
	    //criando vetor sk e lista invertida p/ ano
		
	    //criando vetor sk e lista invertida p/ tipo
	}
	
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
