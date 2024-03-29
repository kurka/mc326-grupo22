/* Funcoes de operacoes a referentes a chaves primarias */

/* Sempre que o vetor que armazena as chaves primarias estiver cheio, 
  ele eh dobrado de tamanho (vetor dinamico dobravel) */
ap_tipo_registro_pk realoca_memoria(ap_tipo_registro_pk vetor_pk, int * limite);

/* Le todos os dados do arquivo pk.dat e os adiciona em um vetor, mantendo a ordem de registros, que eh alfabetica */
ap_tipo_registro_pk lerArquivoPK(FILE *arq_pk, ap_tipo_registro_pk vetor, int * limite, int n_registros);

/* Caso a lista em pk.dat nao estivesse criada, le os dados da base.dat 
  e cria os indices no arquivo */
ap_tipo_registro_pk inserePKBase(FILE *arqBase, ap_tipo_registro_pk vetor, int * limite, int n_registros);

/* Remove chaves primarias no vetor_registros que na verdade sao 
   elementos de avail_list */
ap_tipo_registro_pk limpa_pk(FILE *arq_base, ap_tipo_registro_pk vetor_pk, int *limite,int cabeca_avail);

/* Pega o ultimo titulo lido e registra ele como novo, para ser inserido no vetor de chaves primarias */
ap_tipo_registro_pk novopk(char *str_final, ap_tipo_registro_pk vetor, int * limite, int nrr);

/* Insere um novo registro no vetor dinamico de PKs. Essa insercao eh ordenada e mantem a ordem alfabetica do vetor */
ap_tipo_registro_pk insere_pk(ap_tipo_registro_pk vetor_pk, tipo_registro_pk novo, int * limite);

/* Remove a chave primaria que acabou de ser removida da base22.dat */
ap_tipo_registro_pk  remove_pk(ap_tipo_registro_pk vetor_pk, int * limite, int cabeca_avail);

/* Salva todos os registros do nosso vetor de PKs no arquivo PK.dat */
void salvarArquivoPK(ap_tipo_registro_pk vetor, FILE *arq_pk, int limite_reg);

/* Faz a leitura de uma chave primaria que sera buscada na base */
void consulta_pk(int limite_reg, ap_tipo_registro_pk vetor_de_registros, FILE *arqBase);

/* Busca no arquivo da base a chave primaria procurada */
int acha_pk(ap_tipo_registro_pk vetor_de_registros, char titulo_procurado[MAX_TIT], int limite_reg, FILE * arq_base, FILE *arq_html);

/* Lista todas as chaves primarias presentes */
void lista_registros( int limite_reg,  ap_tipo_registro_pk vetor_de_registros);


/*** Funcoes Auxiliares ***/

/* Funcao auxiliar usada na funcao qsort */
int compara_qsort(const void * vetora, const void * vetorb);

/* Funcao analoga a strncmp, mas insensivel a maiusculas/minusculas */
int strncmpinsensitive(char * a, char * b, int size);

/* Funcao auxiliar usada na funcao bsearch */
int compara_bsearch(const void * titulo_procurado, const void * vetor_de_registros);


