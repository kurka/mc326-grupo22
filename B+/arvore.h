/*funcoes de manipulacao em arvores B+*/

/*imprime no arquivo informacoes sobre o no*/
void fecha_no(tipoNo *arvore);

/*abre ou cria arquivo com os registros da raiz da arvore*/
void abre_raiz();

/*carrega conteudo de uma folha na memoria*/
tipoNo *abre_folha(int numero);

/*faz a insercao de chave na arvore*/
void insere(int *prox_chave);

/*procura recursivamente pela folha onde se deve inserir a chave. Na volta da recursao, insere nos niveis superiores*/
void acha_folha(int chave, int pagina, int retorno[3], int *prox_chave);

/*insre elemento na folha correta*/
void insere_folha(tipoNo *no, int chave, int retorno[3], int *prox_chave);

/*insere elemento em noh da arvore*/  
void insere_arvore(tipoNo *no, int dados[3], int *prox_chave);
