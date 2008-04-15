/* Estrutura do arquivo de chaves secundarias:
   [SK][Numero de PKs associadas][Chaves associadas (multiplo de 200)]
   Exemplo:
   Registros: "a ultima ceia","a santa ceia"

   a 2 a ultima ceia             a santa ceia               
   ultima 1 a ultima ceia        
   ceia 2 a ultima ceia          a santa ceia               
   santa 1 a santa ceia          
*/


/*
  1 Ao iniciar o programa, verifica se existe um arquivo de chaves secundarias
  1.1 Existe sk.dat
  1.2 Nao existe sk.dat
  1.2.1 Se existe base.dat => gera um sk.dat
 */


/*
  Busca por indice secundario (recebe uma string e procura no arquivo de SK's ) 
 */


/*
  Remocao de registro -> avail list dos indices secundarios
  Insercao de registro -> insere novas chaves secundarias do novo registro
 */
