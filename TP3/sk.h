/* Definicao das funcoes de manipulacao das chaves secundarias */

/* Cria vetores de SKs, um para cada chave secundaria, assim como as suas respectivas listas invertidas */
tipo_vetores_sk * criarVetorSK(int n_registros, tipo_arqs_li * arqs_li, FILE *arqBase);

/* Insere um novo vetor de SKs, um para cada chave secundaria do novo registro, assim como as suas 
   respectivas listas invertidas*/
tipo_vetores_sk * insereVetorSK(char *registro, tipo_vetores_sk *vetores_sk, tipo_arqs_li * arqs_li );


/* Cria vetor sk e lista invertida*/	
tipo_dados_sk *cria_vetor_generico(char *registro, char *pk, tipo_dados_sk *generico, int *n_li_generica, FILE * arq_gen_li);

/* Funcao de alocacao do vetor (dobravel) de SKs */
tipo_registro_sk *realoca_memoria_sk(tipo_registro_sk *vetor_SK_generico, int *limite); 

/* Estas funcoes "instanciam" os tipos das chaves secundarias (titulo, tipo, autor ou ano) */
void consulta_sk_tit(tipo_dados_sk *titulo, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_tit_li, FILE *arq_base);
void consulta_sk_tip(tipo_dados_sk *tipo, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_tip_li, FILE *arq_base);
void consulta_sk_aut(tipo_dados_sk *autor, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_aut_li, FILE *arq_base);
void consulta_sk_ano(tipo_dados_sk *ano, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_ano_li, FILE *arq_base);

/* Procura por uma chave no vetor de chaves secundarias */
void acha_sk(char *palavra_procurada, int n_pk, FILE *arq_base, FILE *arq_gen_li, tipo_dados_sk * generico, tipo_registro_pk *vetor_pk);

/* Funcao que le da entrada padrao e trata excecoes de entrada de busca */
int le_sk(char* palavra_procurada, int max);

/* Salva em arquivo a lista com as chaves secundarias e seus apontadores para o arquivo de  lista invertida*/
void salvarArquivoSK(tipo_vetores_sk *vetores_sk, tipo_arqs_sk *arqs_sk);

/* Salva um  vetor de chaves secundarias de um determinado tipo */
void salvaVetorSK(tipo_dados_sk *generico, FILE * arq_generico);



/* Funcoes Auxiliares */

/* Funcao analoga a strcmp, mas insensivel a maiusculas/minusculas */
int strcmpinsensitive(char * a, char * b);
/* Funcao auxiliar usada na funcao qsort (para ordenar sks) */
int compara_qsort2(const void * vetora, const void * vetorb);
/* Funcao auxiliar usada na funcao bsearch (para encontrar sks) */
int compara_bsearch2(const void * titulo_procurado, const void * vetor_de_registros);
