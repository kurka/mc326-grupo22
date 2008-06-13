/* Funcoes usadas na abertura de arquivos */

/* Confere se existe e abre ou cria arquivo base22.dat */
FILE * abre_base22(FILE *arq_base, int *n_registros);

/* Confere se existe e abre ou cria arquivo pk.dat */
FILE * abre_pk(FILE *arq_pk, int *pk);

/* Confere se existe e abre ou cria arquivo cabeca_avail_base.dat */
FILE * abre_avail(FILE *arq_cabeca_avail_base, int *cabeca_avail_base);

/* Abre ou cria arquivos de chaves secundarias*/
void abre_sk(tipo_arqs_sk *arq_sk, tipo_arqs_li *arqs_li, int *sk);

/* Para nao voltar abruptamente para o menu, pede para o usuario digitar algo para prosseguir */
void espera();

/* Desaloca memoria alocada nas estruturas durante a execucao */
void liberamemoria(tipo_registro_pk *vetor_registros, tipo_arqs_sk *arqs_sk, tipo_arqs_li *arqs_li, tipo_vetores_sk *vetores_sk);
