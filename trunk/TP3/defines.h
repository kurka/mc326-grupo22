/*Constantes utilizadas durante a execucao do programa e struct	
que guarda titulo e numero de registro do arquivo de chaves primarias*/


#define TAM_REGISTRO 450
#define TAM_PK 208
#define INSERIR '1'
#define LISTAR '2'
#define CONSULTA_PK '3'
#define CONSULTA_SK '4'
#define REMOVER '5'
#define SAIR '6'
#define OK 0
#define ERRO -1
#define ERRO2 -2
#define TAM_TIT 200
#define MAX_TIT 200
#define TAM_TIP 100
#define MAX_TIP 300
#define TAM_AUT 125
#define MAX_AUT 425
#define TAM_ANO 4
#define MAX_ANO 429
#define TAM_VAL 12
#define MAX_VAL 441
#define TAM_IMG 9
#define MAX_IMG 450
#define TAM_FORM 3
#define MEM_INIT 10
#define DEBUG 0 /*if(DEBUG) imprime etapas e outras infos uteis para o programador ou usuario avancado*/ 
#define TAM_NRR_CHAR 5

typedef struct {
  char titulo[TAM_TIT];
  int nrr;
}tipo_registro_pk;

typedef tipo_registro_pk * ap_tipo_registro_pk;


typedef struct
{
  char *chave;
  int endereco_li; /*endereço na lista invertida*/
}tipo_registro_sk;


/*esta é uma estrutura com 4 apontadores que apontam para o inicio dos 4 vetores the SKs, além de 4 campos inteiros que informam o tamanho destes vetores */
typedef struct 
{
  tipo_registro_sk *vetor_SK_titulo; int n_titulos;
  tipo_registro_sk *vetor_SK_autor; int n_autores;
  tipo_registro_sk *vetor_SK_ano; int n_anos;
  tipo_registro_sk *vetor_SK_tipo; int n_tipos;
	
}tipo_vetores_sk;


/*estrutura que representa um registro da lista invertida*/
typedef struct
{
   char *chave;
   int prox;	
}tipo_registro_li;

/*estrutura com 4 apontadores para o inicio de cada uma das 4 listas invertidas(titulo, tipo, autor, ano), e com 4 inteiros que informam o tamanho dessas listas*/
typedef struct 
{
  tipo_registro_li *vetor_li_titulo; int n_titulos;
  tipo_registro_li *vetor_li_autor; int n_autores;
  tipo_registro_li *vetor_li_ano; int n_anos;
  tipo_registro_li *vetor_li_tipo; int n_tipos;
	
}tipo_vetores_li;


