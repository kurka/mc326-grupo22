/* Definicao das funcoes de manipulacao
   no arquivo de chaves secundarias. */

/*cria vetores de SKs, um para cada chave secundaria, assim como as suas respectivas listas invertidas*/
tipo_vetores_sk * criarVetorSK(int n_registros, tipo_arqs_li * arqs_li, FILE *arqBase);

/*insere um novo vetor de SKs, um para cada chave secundaria do novo registro, assim como as suas respectivas listas invertidas*/
tipo_vetores_sk * insereVetorSK(char *registro, tipo_vetores_sk *vetores_sk, tipo_arqs_li * arqs_li );


/* cria vetor sk e lista invertida*/	
tipo_dados_sk *cria_vetor_generico(char *registro, char *pk, tipo_dados_sk *generico, int *n_li_generica, FILE * arq_gen_li);


tipo_registro_sk *realoca_memoria_sk(tipo_registro_sk *vetor_SK_generico, int *limite); 


void consulta_sk_tit(tipo_vetores_sk *vetores_sk, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_tit_li, FILE *arq_base);
void consulta_sk_tip(tipo_vetores_sk *vetores_sk, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_tip_li, FILE *arq_base);
void consulta_sk_aut(tipo_vetores_sk *vetores_sk, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_aut_li, FILE *arq_base);
void consulta_sk_ano(tipo_vetores_sk *vetores_sk, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_ano_li, FILE *arq_base);

void acha_sk(char *palavra_procurada, int n_pk, FILE *arq_base, FILE *arq_gen_li, tipo_dados_sk * generico, tipo_registro_pk *vetor_pk);

/*funcao que le da entrada padrao e trata excecoes de entrada de busca*/
int le_sk(char* palavra_procurada, int max);

/* Funcoes Auxiliares */

/*funcao analoga a strcmp, mas insensivel a maiusculas/minusculas */
int strcmpinsensitive(char * a, char * b);
