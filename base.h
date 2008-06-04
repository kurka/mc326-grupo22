/* Funcoes de operacoes a serem realizadas na base de dados
   (baseXX.dat) e funcoes auxiliares */

/* Funcao de insercao na base */
void Insere_base(FILE *arq_base, char * str_final, ap_tipo_registro_pk vetor, int n_registros);

void busca_registro(int NRR, FILE *arq_base, FILE *arq_html);

/* ********************************* */
/* Funcoes de tratamento de entradas */
/* ********************************* */
/* Funcao que le da entrada padrao (teclado) e verifica coerencia do titulo da obra */
void Insere_titulo(char *str_final, ap_tipo_registro_pk vetor, int n_registros);
/* Funcao que le da entrada padrao (teclado) e verifica coerencia do tipo da obra */
void Insere_tipo(char *str_final);
/* Funcao que le da entrada padrao (teclado) e verifica coerencia do autor da obra */
void Insere_autor(char *str_final);
/* Funcao que le da entrada padrao (teclado) e verifica coerencia do ano da obra */
void Insere_ano(char *str_final);
/* Funcao que le da entrada padrao (teclado) e verifica coerencia do valor da obra */
void Insere_valor(char *str_final);
/* Funcao que le da entrada padrao (teclado) e verifica coerencia do identificador da obra */
void Insere_imagem(char *str_final);

/* Funcao que verifica onde o novo registro deve ser inserido e o insere*/
int escreve_base(FILE * arq_base, FILE* arq_avail,  char *str_final, int *cabeca_avail);

/* Funcao de remocao de registro da base de dados */
void remove_registro (int n_registros, ap_tipo_registro_pk vetor_registros, FILE * arq_base, FILE * arq_cabeca_avail_base, int *avail_base);

/* Funcao que ignora espacos antes do comeco da entrada */
char come_espaco(char c);
/* Funcao que recebe caracteres alem do esperado pelo campo */
int come_excesso(char c);
/*funcao que verifica se titulo ja foi inserido anteriormente (case insensitive)*/
int checa_redundancia_tit(char * str_final, ap_tipo_registro_pk vetor, int n_registros);
