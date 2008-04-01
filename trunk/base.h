/* Funcoes de operacoes a serem realizadas na base de dados
   (baseXX.dat) e funcoes auxiliares */

/* Funcao de insercao na base */
char * Insere_base(FILE *arq_base);

void busca_registro(int NRR);

/* ********************************* */
/* Funcoes de tratamento de entradas */
/* ********************************* */
/* Funcao que le da entrada padrao (teclado) e verifica coerencia do titulo da obra */
void Insere_titulo(char *str_final);
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

/* Funcao que ignora espacos antes do comeco da entrada */
char come_espaco(char c);
/* Funcao que recebe caracteres alem do esperado pelo campo */
int come_excesso(char c);
