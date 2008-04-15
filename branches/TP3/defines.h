/*Constantes utilizadas durante a execucao do programa e struct	
que guarda titulo e numero de registro do arquivo de chaves primarias*/


#define TAM_REGISTRO 450
#define INSERIR '1'
#define LISTAR '2'
#define CONSULTA '3'
#define SAIR '4'
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
#define MEM_INIT 1



typedef struct {
  char titulo[TAM_TIT];
  int nrr;
}tipo_registro_pk;

typedef tipo_registro_pk * ap_tipo_registro_pk;
