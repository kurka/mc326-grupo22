
/* Constantes numericas */
#define CHAVES 4
#define OK 0
#define ERRO -1
#define ERRO2 -2
#define DEBUG 0/*if(DEBUG) imprime etapas e outras infos uteis para o programador ou usuario avancado*/ 


/* Definicao de strings, nomes de arquivos, etc */
#define MODOA "a"
#define MODOR "r"
#define MODOW "w"

/* Definicao de tipos */
typedef struct {
  int a;
  int b;
} tipoParDeInt;


typedef struct{
  int tipo; /*(1 se for folha, 0 se nao for folha)*/
  int n_pagina;
  int chaves[CHAVES]; /*depois isso vai virar um union..*/
  int apontadores[CHAVES+1];
  int prox_dir;
  int prox_esq;
} tipoNo
