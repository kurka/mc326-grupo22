/* Funcoes de operacoes a serem realizadas nos arquivos 
   referentes a chaves primarias */

/*sempre que o vetor que armazena as chaves primarias estiver cheio, 
  ele eh dobrado de tamanho (vetor dinamico dobravel)*/
ap_tipo_registro_pk realoca_memoria(ap_tipo_registro_pk vetor_pk, int * limite);

/* le todos os dados do arquivo PK.dat e os adiciona em um vetor, mantendo a ordem de registros, que é alfabética */
void lerArquivoPK(FILE *arq_pk, ap_tipo_registro_pk vetor, int * limite, int n_registros);

/*caso a lista em PK.dat nao estivesse criada, le os dados da base.dat 
  e cria os indices no arquivo.*/
void inserePKBase(FILE *arqBase, ap_tipo_registro_pk vetor, int * limite, int n_registros);

/*pega o ultimo titulo lido e registra ele como novo,para ser inserido no vetor de chaves primarias*/
int novopk(char *str_final, ap_tipo_registro_pk vetor, int * limite);

/* insere um novo registro no nosos vetor dinamico de PKs, essa inserção é ordenada e mantém a ordem alfabética do vetor */
ap_tipo_registro_pk insere_pk(ap_tipo_registro_pk vetor_pk, tipo_registro_pk novo, int * limite);

/* salva todos os registros do nosso vetor de PKs no arquivo PK.dat*/
void salvarArquivoPK(ap_tipo_registro_pk vetor, FILE *arq_pk, int limite_reg);


/* Consulta por chave primaria */
void consulta_pk(int limite_reg, ap_tipo_registro_pk vetor_de_registros, FILE *arqBase);

/* Lista todas as chaves primarias presentes*/
void lista_registros( int limite_reg,  ap_tipo_registro_pk vetor_de_registros);




