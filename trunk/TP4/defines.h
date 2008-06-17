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


/*nomes dos arquivos criados pelo programa*/
#define ARQBASE "base22.dat"
#define ARQPK "pk.dat"
#define ARQAVAIL "avail_head.dat"
#define ARQSK_TIT "sk_titulos.dat"
#define ARQSK_TIP "sk_tipos.dat"
#define ARQSK_AUT "sk_autores.dat"
#define ARQSK_ANO "sk_anos.dat"
#define ARQLI_TIT "li_titulos.dat"
#define ARQLI_TIP "li_tipos.dat"
#define ARQLI_AUT "li_autores.dat"
#define ARQLI_ANO "li_anos.dat"
#define ARQHTML "tp4.html"
#define ARQDSC0 "pks_dsc0.dat"
#define ARQDSC1 "pks_dsc1.dat"
#define ARQDSC2 "pks_dsc2.dat"
#define ARQDSC3 "pks_dsc3.dat"
#define ARQDSC4 "pks_dsc4.dat"
#define ARQDSC5 "pks_dsc5.dat"
#define ARQDSC6 "pks_dsc6.dat"
#define ARQDSC7 "pks_dsc7.dat"
#define ARQDSC8 "pks_dsc8.dat"
#define DIRIMG "./img/"


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


/* estrutura de armazenamento das Pks de cada um
   dos descritores*/
typedef struct {
  ap_tipo_registro_pk vetor_pks_dsc0;
  ap_tipo_registro_pk vetor_pks_dsc1;
  ap_tipo_registro_pk vetor_pks_dsc2;
  ap_tipo_registro_pk vetor_pks_dsc3;
  ap_tipo_registro_pk vetor_pks_dsc4;
  ap_tipo_registro_pk vetor_pks_dsc5;
  ap_tipo_registro_pk vetor_pks_dsc6;
  ap_tipo_registro_pk vetor_pks_dsc7;
  ap_tipo_registro_pk vetor_pks_dsc8;
} estrutura_descritores_pks;
