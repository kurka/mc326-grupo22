/* Definicao das funcoes de manipulacao
   no arquivo de chaves secundarias. */

/*cria vetores de SKs, um para cada chave secundaria, assim como as suas respectivas listas invertidas*/
tipo_vetores_sk * criarVetorSK(int n_registros, tipo_arqs_li * arqs_li, FILE *arqBase);


/* cria vetor sk e lista invertida para titulo */	
void cria_vetor_titulo(char registro[TAM_REGISTRO], char pk[TAM_TIT+1], int *n_titulos_li, tipo_vetores_sk *vetores_sk, FILE *arq_tit_li);
/* cria vetor sk e lista invertida para tipo */	
void cria_vetor_tipo(char registro[TAM_REGISTRO], char pk[TAM_TIT+1], int *n_tipos_li, tipo_vetores_sk *vetores_sk, FILE *arq_tip_li);
/* cria vetor sk e lista invertida para autor */	
void cria_vetor_autor(char registro[TAM_REGISTRO], char pk[TAM_TIT+1], int *n_autores_li, tipo_vetores_sk *vetores_sk, FILE *arq_aut_li);
/* cria vetor sk e lista invertida para ano */	
void cria_vetor_ano(char registro[TAM_REGISTRO], char pk[TAM_TIT+1], int *n_anos_li, tipo_vetores_sk *vetores_sk, FILE *arq_ano_li);


void consulta_sk_tit(tipo_vetores_sk *vetores_sk, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_tit_li, FILE *arq_base);
void consulta_sk_tip(tipo_vetores_sk *vetores_sk, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_tip_li, FILE *arq_base);
void consulta_sk_aut(tipo_vetores_sk *vetores_sk, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_aut_li, FILE *arq_base);
void consulta_sk_ano(tipo_vetores_sk *vetores_sk, tipo_registro_pk *vetor_pk, int n_pk, FILE *arq_ano_li, FILE *arq_base);

/* Funcoes Auxiliares */

/*funcao analoga a strcmp, mas insensivel a maiusculas/minusculas */
int strcmpinsensitive(char * a, char * b);
