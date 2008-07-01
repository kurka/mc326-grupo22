/*implementacao de funcoes de insercao em arvore B+*/

/*faz a insercao de chave na arvore*/
void insere(int *prox_chave, int *nrr);

/*procura recursivamente pela folha onde se deve inserir a chave. Na volta da recursao, insere nos niveis superiores*/
void acha_folha_ins(int chave[2], int pagina, int retorno[3], int *prox_chave);

/*insre elemento na folha correta*/
void insere_folha(tipoNo *no, int chave[2], int retorno[3], int *prox_chave);

/*insere elemento em noh da arvore*/  
void insere_arvore(tipoNo *no, int dados[3], int *prox_chave);
