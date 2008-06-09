/*Constantes utilizadas durante a execucao do programa e struct	
que guarda titulo e numero de registro do arquivo de chaves primarias*/


#define TAM_REGISTRO 450
#define TAM_PK 208
#define INSERIR '1'
#define LISTAR '2'
#define CONSULTA_PK '3'
#define CONSULTA_SK_TIT '4'
#define CONSULTA_SK_TIP '5'
#define CONSULTA_SK_AUT '6'
#define CONSULTA_SK_ANO '7'
#define REMOVER '8'
#define SAIR '0'
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


/*estrutura com todos os dados necessarios para se manipular as sks de algum parametro*/
typedef struct 
{
  tipo_registro_sk *vetor_SK; 
  int n_sk;
  int tam_vetor;
  int limite_inf;
  int limite_sup;
  	
}tipo_dados_sk;



/*esta é uma estrutura com 4 apontadores que apontam para o inicio dos 4 vetores the SKs, 
  além de 4 campos inteiros que informam o tamanho destes vetores */
typedef struct 
{
  tipo_dados_sk *titulo; 
  tipo_dados_sk *tipo; 
  tipo_dados_sk *autor; 
  tipo_dados_sk *ano; 
  
	
}tipo_vetores_sk;


/*estrutura que guarda arquivos preenchidos com  chaves secundarias*/
typedef struct
{
  FILE * arq_sk_tit;
  FILE * arq_sk_tip;
  FILE * arq_sk_aut;
  FILE * arq_sk_ano;
}tipo_arqs_sk;



/*estrutura que guarda arquivos preenchidos com lista 
  invertida de registros de chaves secundarias*/
typedef struct
{
  FILE * arq_tit_li;
  FILE * arq_tip_li;
  FILE * arq_aut_li;
  FILE * arq_ano_li;
}tipo_arqs_li;
