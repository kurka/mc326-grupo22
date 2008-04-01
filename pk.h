/* Funcoes de operacoes a serem realizadas nos arquivos 
   referentes a chaves primarias */

/*#include "defines.h"*/
/* le todos os dados do arquivo PK.dat e os adiciona em um vetor, mantendo a ordem de registros, que é alfabética */
ap_tipo_registro_pk lerArquivoPK(FILE *arq_pk, int numberOfPKs);

/*pega o ultimo titulo lido e registra ele como novo,para ser inserido no vetor de chaves primarias*/
tipo_registro_pk novopk(char *str_final, int numberOfPKs);

/* insere um novo registro no nosos vetor dinamico de PKs, essa inserção é ordenada e mantém a ordem alfabética do vetor */
int inserirPK(tipo_registro_pk *vetor, tipo_registro_pk novo, int numberOfPKs);

/* salva todos os registros do nosso vetor de PKs no arquivo PK.dat*/
void salvarArquivoPK(tipo_registro_pk *vetor, FILE *arq_pk, int numberOfPKs);


/* Consulta por chave primaria */
void consulta_pk(int n_registros, ap_tipo_registro_pk vetor_de_registros);

/* Lista todas as chaves primarias presentes*/
void lista_registros( int n_registros,  ap_tipo_registro_pk vetor_de_registros);


/* /\*\/\* Consulta nos registros do vetor de PKs, se o titulo passado como parametro existe nesse vetor, e portanto no arquivo PK.dat, caso exista a função retorna o NRR desse registro, caso titulo nao exista, então zero é retornado *\/ */
/* int consultarPK(pk *vetor, int *numberOfPKs, char *titulo); *\/ */
