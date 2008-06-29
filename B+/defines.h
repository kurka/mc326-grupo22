/* Constantes numericas */
#define CHAVES 2
#define OK 0
#define ERRO -1
#define ERRO2 -2
#define DEBUG 0/*if(DEBUG) imprime etapas e outras infos uteis para o programador ou usuario avancado*/ 


/* Definicao de strings, nomes de arquivos, etc */
#define ROOT 0
#define INSERE '1'
#define CONSULTA '2'
#define REMOVE '3'
#define SAIR '0'
#define TAM_NOME_ARQ 16
#define DIRETORIO "files/"

/* Definicao de tipos */
typedef struct{
  int a;
  int b;
} tipoParDeInt;


/*vamos definir que ir a esquerda de um elemento de um nó implica valores menores ou iguais a ele, e a direita maiores*/
typedef struct{
  int posicao;
  int tipo; /*(1 se for folha, 0 se nao for folha)*/
  int n_elementos;
  int chaves[CHAVES+1];/*armazena um a mais, para split*/
  int apontadores[CHAVES+2];
  int prox_dir;
  int prox_esq;
} tipoNo;
