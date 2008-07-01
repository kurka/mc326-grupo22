/*funcoes de manipulacao em arvores B+*/

/*imprime no arquivo informacoes sobre o no*/
void fecha_no(tipoNo *arvore);

/*cria uma nova raiz, no caso da arvore subir de nivel*/
tipoNo *cria_raiz(int numero);

/*carrega conteudo de um no na memoria*/
tipoNo *abre_no(int numero, int tipo);


/*faz a insercao de chave na arvore*/
void insere(int *prox_chave, int *nrr);

/*procura recursivamente pela folha onde se deve inserir a chave. Na volta da recursao, insere nos niveis superiores*/
void acha_folha(int chave[2], int pagina, int retorno[3], int *prox_chave);

/*insre elemento na folha correta*/
void insere_folha(tipoNo *no, int chave[2], int retorno[3], int *prox_chave);

/*insere elemento em noh da arvore*/  
void insere_arvore(tipoNo *no, int dados[3], int *prox_chave);

/*lista as chaves e os respectivos nrrs armazenados na arvore*/
void lista_elementos();
