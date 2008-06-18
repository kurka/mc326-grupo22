/* Esta funcao verifica se ja existem arquivos com os descritores. Retorna 
   OK(0) se ja existem, ou ERRO(-1) caso contrario */
int verificaDescritores();

/* Cria os arquivos dos descritores a partir dos registros ja existentes na base. */
void criaDescritores(ap_tipo_registro_pk vetor_registros , int n_registros , estrutura_descritores_pks vetores_descritores_pks, int *limite_descritores);

/* Carrega as PKs dos arquivos de descritores para os vetores correspondentes*/
void carregaDescritores(estrutura_descritores_pks vetores_descritores_pks, int *limite_descritores);

/* Insere a PK fornecida no arquivo e no vetor correspondentes ao seu descritor */
void insereDescritor(char *titulo , int NRR , estrutura_descritores_pks vetores_descritores_pks, int *limite_descritores);


/* Funcao auxiliar que recebe o descritor e retorna o numero de 1's de seu correspondente binario */
int ContaUns(char descritor);

/* Funcao de inicializacao dos valores para o limite[] dos descritores */
void inicia_limite_descritores(int *limite_descritores);
