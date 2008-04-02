/* Nesta biblioteca estao definidas as funcoes de insercao no
   vetor principal, de acordo com as especificacoes. */

#include <stdio.h>

#define ERRO -1
#define ERRO2 -2
#define OK 0
#define MAX_TIT 200
#define MAX_TIP 300
#define MAX_AUT 400
#define MAX_ANO 404
#define MAX_VAL 413
#define MAX_IMG 420



/*Funcao que le da entrada padrao (teclado) e verifica 
  coerencia do titulo da obra.*/
void Insere_titulo(char *str_final) {
  int i,resposta;
  char c;
  
  do {
    
    /* 'resposta' eh a variavel de controle de validade da sequencia 
       de caracteres. Caso o procedimento encontre algum problema, 'resposta' 
       recebe ERRO, e reinicia-se a execucao*/
    resposta=OK;
    
    printf("Digite o titulo da obra (no maximo 200 caracteres).\n");
    c=getchar();
    
    /* Eliminacao de espacos antes dos caracteres */
    while(c==' ') {
      c=getchar();
    }
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') {
      resposta=ERRO;
    }
    
    i=0;
    
    /* Caracteres a serem inseridos */
    while(c!='\n' && resposta == OK) {
      str_final[i]=c;
      i++;
      c=getchar();
      
      /* CASO DE ERRO */
      /* Caso a entrada seja maior que o tamanho limite*/
      if((i>=MAX_TIT) && (c!='\n')) {
        /*continua a receber a entrada ate o usuario apertar "enter" */
        while(c!='\n') {
	  
	  /*aceita que o usuario digite 
	    espacos depois que terminar a digitacao*/    
	  if(c!=' ')
	    resposta=ERRO;
	  
	  c=getchar();

        }
	
	if(resposta==ERRO){
	  printf("ERRO: Tamanho de titulo excedido!\n");	
	  break;
	}
      }    
    }
    
    if(resposta==OK){
      /*preenche o resto do vetor com espacos*/
      for(;i<MAX_TIT;i++)
	str_final[i]=' ';
    }
    
  } while(resposta==ERRO);
  
  printf("Titulo inserido com sucesso.\n");
  return;
  
}


/*Funcao que le da entrada padrao (teclado) e verifica
  coerencia do tipo da obra.*/
void Insere_tipo(char *str_final) {
  
  int i,resposta;
  char c;
  
  do {
    
    resposta=OK;
    
    printf("Digite o tipo da obra (maximo 100 caracteres).\n");
    c=getchar();
    
    /* Eliminacao de espacos antes dos caracteres */
    while(c==' ') {
      c=getchar();
    }
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') {
      resposta=ERRO;
    }
  
    /*O registro inicia no final do registro anterior*/
    i=MAX_TIT;
    
    /* Caracteres a serem inseridos */
    while(c!='\n' && resposta == OK) {
      str_final[i]=c;
      i++;
      c=getchar();
      
      /* Caso a entrada seja maior que o tamanho limite*/
      if((i>=MAX_TIP)&&(c!='\n')) {
        /*continua a receber a entrada ate o usuario apertar "enter" */
        while(c!='\n') {

	  /*aceita que o usuario digite 
	    espacos depois que terminar a digitacao*/    
	  if(c!=' ')
	    resposta=ERRO;

	  c=getchar();
        }
	
	if(resposta==ERRO){
	  printf("ERRO: Tamanho de tipo excedido!\n");	
	  break;
	}
      }
    }

    if(resposta==OK){
      /*preenche o resto do vetor com espacos*/
      for(;i<MAX_TIP;i++)
	str_final[i]=' ';
    }

  } while(resposta==ERRO);
  
  printf("Tipo inserido com sucesso.\n");
  return;
  
}


/*Funcao que le da entrada padrao (teclado) e verifica
  coerencia do nome do autor da obra.*/
void Insere_autor(char *str_final) {

  int i,resposta;
  char c;
  
  do {
    
    resposta=OK;
    
    printf("Digite o nome do autor da obra (maximo 100 caracteres).\n");
    c=getchar();
    
    /* Eliminacao de espacos antes dos caracteres */
    while(c==' ') {
      c=getchar();
    }
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') {
      resposta=ERRO;
    }
  
    /*O registro inicia no final do registro anterior*/
    i=MAX_TIP;
    
    /* Caracteres a serem inseridos */
    while(c!='\n' && resposta == OK) {
      str_final[i]=c;
      i++;
      c=getchar();
      
      
      /* Caso a entrada seja maior que o tamanho limite*/
      if((i>=MAX_AUT)&&(c!='\n')) {
        /*continua a receber a entrada ate o usuario apertar "enter" */
        while(c!='\n') {
	  /*aceita que o usuario digite 
	    espacos depois que terminar a digitacao*/    
	  if(c!=' ')
	    resposta=ERRO;
	  
	  c=getchar();
	}
	
	if(resposta==ERRO){
	  printf("ERRO: Nome do autor maior que o permitido!\n");	
	  break;
	}
      }     
    }

    if(resposta==OK){
      /*preenche o resto do vetor com espacos*/
      for(;i<MAX_AUT;i++)
	str_final[i]=' ';
    }
    
  } while(resposta==ERRO);
  
  printf("Autor inserido com sucesso.\n");
  return;
  
}

/*Funcao que le da entrada padrao (teclado) e verifica
  coerencia do ano da obra.*/
void Insere_ano(char *str_final) {

  int i,resposta;
  char c;
  
  do {
    
    resposta=OK;
    
    printf("Digite o ano da obra (com quatro algarismos).\n");
    c=getchar();
    
    /* Eliminacao de espacos antes dos caracteres */
    while(c==' ') {
      c=getchar();
    }
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') {
      resposta=ERRO;
    }
  
    /*O registro inicia no final do registro anterior*/
    i=MAX_AUT;
    
    /* Caracteres a serem inseridos */
    while(c!='\n' && resposta!=ERRO) {
      
      /*Confere se o usuario digita algum caracter diferente de numeros
	(valores extraidos da tabela ascii)*/
      if (c < 48 || c > 57){
	resposta=ERRO2;
      }
      else{
	str_final[i]=c;
	i++;
      }
      c=getchar();
      
      /* Caso a entrada seja maior que o tamanho limite*/
      if((i>=MAX_ANO)&&(c!='\n')) {
        /*continua a receber a entrada ate o usuario apertar "enter" */
        while(c!='\n') {

	  /*aceita que o usuario digite 
	    espacos depois que terminar a digitacao*/    
	  if(c!=' ')
	    resposta=ERRO;
	  
	  c=getchar();
        }
	
	if(resposta==ERRO){
	  printf("ERRO: Ano invalido!\n");	
	  break;
	}
      }     
    }

    /*Caso tenha encontrado algum caracter diferente de numero.*/
    if(resposta==ERRO2)
      printf("ERRO: O ano deve conter apenas numeros\n");    
    
    if(resposta==OK){
      /*Confere se o ano foi preenchido ate o final*/
      if(i < MAX_ANO){
	printf("ERRO: Dados incompletos\n");
	resposta=ERRO;
      }
    }
    
  } while(resposta!=OK);
  
  printf("Ano inserido com sucesso.\n");
  return;
  
}

/*Funcao que le da entrada padrao (teclado) e verifica
  coerencia do valor da obra.*/
void Insere_valor(char *str_final) {

  int i,j,k,resposta;
  char c, valor[9];
  
  do {
    resposta=OK;
    
    printf("Digite o valor da obra (maximo 9 digitos).\n");
    c=getchar();
    
    /* Eliminacao de espacos antes dos caracteres */
    while(c==' ') {
      c=getchar();
    }
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') {
      resposta=ERRO;
    }
  
 
    /*O registro inicia no final do registro anterior*/
    i=MAX_ANO;
    j=0;
    /* Caracteres a serem inseridos */
    while(c!='\n' && resposta != ERRO) {
      
      /*Confere se o usuario digita algum caracter diferente de numeros
	(valores extraidos da tabela ascii)*/
      if (c < 48 || c > 57){
	resposta=ERRO2;
      }
      else{
	valor[j]=c;
	i++;
	j++;
      }
      c=getchar();
      
      /* Caso a entrada seja maior que o tamanho limite*/
      if((i>=MAX_VAL)&&(c!='\n')) {
        /*continua a receber a entrada ate o usuario apertar "enter" */
        while(c!='\n') {

	  /*aceita que o usuario digite 
	    espacos depois que terminar a digitacao*/    
	  if(c!=' ')
	    resposta=ERRO;

	  c=getchar();
	}
	
	if(resposta==ERRO){
	  printf("ERRO: Valor excedeu tamanho maximo!\n");	
	  break;
	}
      }
    }

    /*Caso tenha encontrado algum caracter diferente de numero.*/
    if(resposta==ERRO2)
      printf("ERRO: O valor deve conter apenas numeros\n");
    
    
    if(resposta==OK){
      /*preenche o vetor com 0*/ 
      for(k=MAX_ANO;k<MAX_VAL;k++)
	str_final[k]='0';
      /*copia o valor lido para o final do vetor*/
      i=MAX_VAL-1;
      for(k=j-1;k>=0;k--){
	str_final[i]=valor[k];
	i--;
      }
    }
    
  } while(resposta!=OK);
  
  printf("Valor inserido com sucesso.\n");
  return;
  
}

/*Funcao que le da entrada padrao (teclado) e verifica
  coerencia do identificador da obra.*/
void Insere_imagem(char *str_final) {

  int i, j, resposta;
  char c, formato[3];
  
  do {
    resposta=OK;
    
    printf("Digite o nome identificador da obra (quatro digitos + extensao: [png, jpg, gif])\n");
    c=getchar();
    
    /* Eliminacao de espacos antes dos caracteres */
    while(c==' ') {
      c=getchar();
    }
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') {
      resposta=ERRO;
    }
    
    /*O registro inicia no final do registro anterior*/
    i=MAX_VAL;
    j=0;
    /* Caracteres a serem inseridos */
    
    while(c!='\n' && resposta == OK) {
      
      /*Confere se o usuario digita algum caracter diferente de numeros
	antes da extensao (valores extraidos da tabela ascii)*/
      if (i < MAX_IMG-3 && (c < 48 || c > 57)){
	resposta=ERRO2;
      }
      /*Guarda o formato da figura no string "formato"*/
      if (i > MAX_IMG-4 && i < MAX_IMG){
	formato[j] = c;
	j++;
      }
      
      str_final[i]=c;
      i++;
      c=getchar();
      
      /*Confere se a extensao do arquivo eh valida*/
      if(i == MAX_IMG)
	if(!((formato[0]=='p'&&formato[1]=='n'&&formato[2]=='g') ||
	     (formato[0]=='j'&&formato[1]=='p'&&formato[2]=='g') ||
	     (formato[0]=='g'&&formato[1]=='i'&&formato[2]=='f'))){
	  printf("ERRO: extensao invalida!\n");
	  resposta=ERRO;
	  break;
	}

      /* Caso a entrada seja maior que o tamanho limite*/
      if((i>=MAX_IMG)&&(c!='\n')) {
        /*continua a receber a entrada ate o usuario apertar "enter" */
        while(c!='\n') {
	  /*aceita que o usuario digite 
	    espacos depois que terminar a digitacao*/    
	  if(c!=' ')
	    resposta=ERRO;
	  
	  c=getchar();
	}
	
	if(resposta==ERRO){
	  printf("ERRO: Identificador excedeu tamanho maximo!\n");	
	  break;
	}
      }
    }

    /*Caso tenha encontrado algum caracter diferente de numero.*/
    if(resposta==ERRO2)
      printf("ERRO: o identificador deve conter apenas digitos e uma extensao valida.\n");
    
    if(resposta==OK){
      /*Confere se o identificador foi preenchido ate o final*/
      if(i < MAX_IMG){
	printf("ERRO: dados incompletos\n");
	resposta = ERRO;
      }
    }
  } while(resposta==ERRO);
  
  printf("Identificador inserido com sucesso.\n");
  return;
}

