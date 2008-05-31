/* Definicao das funcoes de manipulacao
   no arquivo de chaves secundarias. */

/*cria vetores de SKs, um para cada chave secundaria, assim como as suas respectivas listas invertidas*/
/* tipo_vetores_sk * criarVetorSK(FILE *arqBase, int n_registros); */

tipo_vetorzao * criarVetorSK(FILE *arqBase, int n_registros);

void consulta_sk(tipo_vetores_sk * vetores_sk, tipo_vetores_li * vetores_li, FILE *arq_base, tipo_registro_pk * vetor_pk, int n_pk);


/* Funcoes Auxiliares */

/*funcao analoga a strcmp, mas insensivel a maiusculas/minusculas */
int strcmpinsensitive(char * a, char * b);
