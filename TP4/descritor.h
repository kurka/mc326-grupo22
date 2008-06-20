/* Funcoes de operacoes com descritor */

/* Verifica se ja existem os arquivos de descritores. */
int verificaDescritores();

/* Caso os arquivos nao existam, sao criados a partir da base de dados */
void criaDescritores();

/* Funcao principal de consulta por obras similares. Esta funcao invoca 
   as outras funcoes e organiza o funcionamento da pesquisa*/
void listaObrasSimilares();


/*** FUNCOES AUXILIARES (chamadas por funcoes internas) ***/

/* Recebe o descritor e retorna o numero de 1's 
   de seu correspondente binario */
int ContaUns(char descritor);

/* Verifica se a PK procurada existe nos registros;
   Se existe, calcula o seu descritor e encontra o nome do seu arquivo.*/
int verificaPKDescritores(estrutura_pk_imagem *entrada, int *descritor_entrada);

/* Retorna o numero de obras contidas no arquivo daquele descritor */
int contaObrasSimilares(int descritor);

/* Abre o arquivo de descritor correspondente ao valor de entrada e o 
   modo de abertura ("a","r","a+",etc) */
FILE *abreArquivoDescritor(int descritor, char *modo);

/* Funcao que le o titulo da entrada padrao */
void leTitulo(char *titulo);

/* Funcao que, a partir de um descritor, carrega todas as chaves dos 
   arquivos d-1, d e d+1 em um vetor obras_similares[]. */
void carregaObrasSimilares(int descritor, estrutura_pk_imagem_similaridade *obras_similares, char *path_obra_procurada, int *n);

/* Funcao auxiliar para a ordenacao usando o qsort */
int comparaQsortSimilaridade(const void *obra1 , const void *obra2);

/* Funcao que gera o arquivo html a partir das obras similares */
void geraHTMLSimilares(estrutura_pk_imagem_similaridade *obras_similares, int n_obras_a_listar);

