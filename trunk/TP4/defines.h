/*Constantes utilizadas durante a execucao do programa e struct	
que guarda titulo e numero de registro do arquivo de chaves primarias*/


#define TAM_REGISTRO 450
#define TAM_PK 208
#define TAM_LI 208
#define INSERIR '1'
#define LISTAR '2'
#define CONSULTA_PK '3'
#define CONSULTA_SK_TIT '4'
#define CONSULTA_SK_TIP '5'
#define CONSULTA_SK_AUT '6'
#define CONSULTA_SK_ANO '7'
#define CONSULTA_DSC '8'
#define REMOVER '9'
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
#define DEBUG 0/*if(DEBUG) imprime etapas e outras infos uteis para o programador ou usuario avancado*/ 
#define TAM_NRR_CHAR 5
#define DSC0 0
#define DSC1 1
#define DSC2 2
#define DSC3 3
#define DSC4 4
#define DSC5 5
#define DSC6 6
#define DSC7 7
#define DSC8 8
#define TAM_HEXA 2
#define TAM_BIN 8
#define TAM_DIR 6
#define N_MAX_REG 5
#define NUM_HASH 4
#define TAM_NOME_ARQ 200
#define MIN_OBRAS 1


/*nomes dos arquivos criados pelo programa*/
#define ARQBASE "files/base22.dat"
#define ARQPK "files/pk"
#define ARQAVAIL "files/avail_head.dat"
#define ARQSK_TIT "files/sk_titulos"
#define ARQSK_TIP "files/sk_tipos"
#define ARQSK_AUT "files/sk_autores"
#define ARQSK_ANO "files/sk_anos"
#define ARQLI_TIT "files/li_titulos"
#define ARQLI_TIP "files/li_tipos"
#define ARQLI_AUT "files/li_autores"
#define ARQLI_ANO "files/li_anos"
#define ARQHTML "files/tp4.html"
#define ARQDSC0 "files/pks_dsc0.dat"
#define ARQDSC1 "files/pks_dsc1.dat"
#define ARQDSC2 "files/pks_dsc2.dat"
#define ARQDSC3 "files/pks_dsc3.dat"
#define ARQDSC4 "files/pks_dsc4.dat"
#define ARQDSC5 "files/pks_dsc5.dat"
#define ARQDSC6 "files/pks_dsc6.dat"
#define ARQDSC7 "files/pks_dsc7.dat"
#define ARQDSC8 "files/pks_dsc8.dat"
#define DIRIMG "./img/"
#define MODOA "a"
#define MODOR "r"
#define MODOW "w"


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


typedef struct {
  char titulo[TAM_TIT+1];
  char path[TAM_DIR+TAM_IMG+1];
} estrutura_pk_imagem;

typedef struct {
  char titulo[TAM_TIT];
  char path[TAM_DIR+TAM_IMG+1];
  float similaridade;
} estrutura_pk_imagem_similaridade;
