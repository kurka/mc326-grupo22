/* Constantes numericas */
#define CHAVES 4 /*numero de chaves por noh*/
#define OK -1 /* retornos das funcoes de insercao e remocao*/
#define ERRO -2
#define REM_PAI 1
#define NADA -1 /*quando apontador para folha nao existe*/
#define DEBUG 0/*if(DEBUG) imprime etapas e outras infos uteis para o programador ou usuario avancado*/ 


/* Definicao de strings, nomes de arquivos, etc */
#define ROOT 0
#define FOLHA 1 /*tipos de nohs*/
#define NO 0
#define INSERE 1  /*opcoes do menu*/
#define CONSULTA 2
#define LISTAR 3
#define REMOVE 4
#define SAIR 0
#define TAM_NOME_ARQ 16
#define VETOR 1000
#define DIRETORIO "files/"
#define DADOS "dados.dat"

/*vamos definir que ir a esquerda de um elemento de um nó implica valores menores ou iguais a ele, e a direita maiores*/
typedef struct{
  int posicao;
  int tipo; /*(FOLHA se for folha, NO se nao for folha)*/
  int n_elementos;
  int chaves[CHAVES+1];/*armazena um a mais, para split*/
  int nrr[CHAVES+1];
  int apontadores[CHAVES+2];
  int prox_dir;
  int prox_esq;
} tipoNo;
