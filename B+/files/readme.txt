cada arquivo nessa pasta corresponde a uma pagina da arvore B+, gerada pelo programa..
o arquivo 0 corresponde a raiz.

Cada arquivo, é composto por vários números que possuem a seguinte disposição:

posicao (nome do arquivo)
tipo (1 se for folha, 2 se não for)
n_elementos
chave0 chave1 chave2 ... chaveN
apontador0 apontador1 apontador2 apontador3 ...apontadorN+1 (se nao for folha)
prox_esq (se for folha)
prox_dir (se for folha)
