/*funcoes de manipulacao em arvores B+*/

/*imprime no arquivo informacoes sobre o no*/
void fecha_no(tipoNo *arvore);

/*cria uma nova raiz, no caso da arvore subir de nivel*/
tipoNo *cria_raiz(int numero);

/*carrega conteudo de um no na memoria*/
tipoNo *abre_no(int numero, int tipo);


/*lista as chaves e os respectivos nrrs armazenados na arvore*/
void lista_elementos();

/* Para nao voltar abruptamente para o menu, pede para o usuario digitar algo para prosseguir */
void espera();
