/*implementacao de funcoes de remocao em arvore B+*/

/*rotirna de remocao de no em uma arvore B+*/
void remove(&ultima_chave, &nrr);

/*procura recursivamente pela folha onde se deve remover a chave. 
  Na volta da recursao, se necessario, faz merge dos nos superiores*/
int acha_folha_rem(int chave, int pagina, int parentesco[3], int *prox_chave);

/*remove elemento na folha da arvore*/
int remove_folha(tipoNo *no, int chave, int parentesco[3], int *prox_chave);

/*remove elemento em no da arvore*/
int remove_arvore(tipoNo *no, int pos_chave, int parentesco[3], int *prox_chave);
