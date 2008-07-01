cada arquivo nessa pasta corresponde a uma pagina da arvore B+, gerada pelo programa..
o arquivo 0 corresponde a raiz.

Cada arquivo, é composto por vários números que possuem uma das duas disposições, dependendo de seu tipo (folha ou nao):


Caso 1 - Folha
posicao (nome do arquivo)
1 (tipo) 
n_elementos
chave0 chave1 chave2 ... chaveN
nrr0   nrr1   nrr2   ... nrrN
prox_esq
prox_dir

Caso 2 - No (que nao seja folha)
posicao (nome do arquivo)
1 (tipo) 
n_elementos
chave0 chave1 chave2 ... chaveN
apontador0 apontador1 apontador2 apontador3 ...apontadorN+1 

