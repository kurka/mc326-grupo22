/* Definicao das funcoes de manipulacao das chaves secundarias */

/* Cria os registros de SKs, um para cada chave secundaria, assim como as suas respectivas listas invertidas */
void criaRegistrosSK(int n_registros, FILE *arqBase);


/* Cria vetores de SKs, a partir de um arquivo ja existente com as chaves criadas*/
tipo_vetores_sk *ler_arquivo_sk(tipo_arqs_sk *arqs_sk);
  
/* Faz a leitura de cada arquivo, copiando as chaves secundarias para um vetor*/
tipo_registro_sk *le_chaves_sk(FILE *arq_generico, int *n_sks);

/* Insere um novo vetor de SKs, um para cada chave secundaria do novo registro, assim como as suas 
   respectivas listas invertidas*/
void insereVetorSK(char *registro);

/* Cria vetor sk e lista invertida*/	
void cria_vetor_generico(char *registro, char *pk, int limite[2], char *prefixo_sk, char *prefixo_li);

/* Aloca memoria inicial das estruturas de chaves secundarias */
tipo_registro_sk *aloca_memoria_vetor(tipo_registro_sk *vetor_sk, int tam);

/* Funcao de alocacao do vetor (dobravel) de SKs */
tipo_registro_sk *realoca_memoria_sk(tipo_registro_sk *vetor_SK_generico, int *limite); 

/*Realiza a busca por chaves secundarias*/
void abre_arqs_busca(char * palavra_procurada, char * pre_li, char * pre_sk, FILE * arq_base);

/* Estas funcoes "instanciam" os tipos das chaves secundarias (titulo, tipo, autor ou ano) */
void consulta_sk_tit(int n_pk, FILE *arq_base);
void consulta_sk_tip(int n_pk, FILE *arq_base);
void consulta_sk_aut(int n_pk, FILE *arq_base);
void consulta_sk_ano(int n_pk, FILE *arq_base);

/* Procura por uma chave no vetor de chaves secundarias */
void acha_sk(char *palavra_procurada, int n_pk, int n_sk, FILE *arq_base, FILE *arq_gen_li, tipo_registro_sk *vetor_sk, tipo_registro_pk *vetor_pk);

/* Funcao que le da entrada padrao e trata excecoes de entrada de busca */
int le_sk(char* palavra_procurada, int max);


/* Funcoes Auxiliares */

/* Funcao analoga a strcmp, mas insensivel a maiusculas/minusculas */
int strcmpinsensitive(char * a, char * b);
/* Funcao auxiliar usada na funcao qsort (para ordenar sks) */
int compara_qsort2(const void * vetora, const void * vetorb);
/* Funcao auxiliar usada na funcao bsearch (para encontrar sks) */
int compara_bsearch2(const void * titulo_procurado, const void * vetor_de_registros);
