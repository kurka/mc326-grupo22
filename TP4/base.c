/* Nesta biblioteca estao definidas as funcoes de operacao na
   base de dados (baseXX.dat) e algumas funcoes auxiliares. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "defines.h"
#include "base.h"
#include "pk.h"

/*! 
 * \brief Funcao da insercao propriamente dita (insercao no arquivo) 
 */
void Insere_base(FILE *arq_base, char * str_final){
  
  /* Chamadas das funcoes de organizacao do vetor a ser inserido */
  Insere_titulo(str_final);
  Insere_tipo(str_final);
  Insere_autor(str_final);
  Insere_ano(str_final);
  Insere_valor(str_final);
  Insere_imagem(str_final);

}

/*! 
 * \brief Funcao que verifica onde o novo registro deve ser inserido e o insere
 */
int escreve_base(FILE * arq_base, FILE* arq_avail, char *str_final, int *NRR_cabeca){

  int NRR_nova_cabeca;
  int nrr = *NRR_cabeca;
  /* Caso o arquivo exista, ha 2 possibilidades:
     1-) A cabeca da avail nele contida eh -1. Neste caso, o registro eh inserido no final da base;
     2-) A cabeca aponta p/ algum registro. Nesse caso, o novo registro eh inserido no lugar desta cabeca,
     e a cabeca eh atualizada. */
  
  /* Possibilidade 1*/
  if(nrr == -1){

    if(DEBUG)
      printf(">>>guardando registro no final do arquivo base.dat\n");
    /* Insercao no fim do arquivo */
    fseek(arq_base,0,SEEK_END);
    fprintf(arq_base,"%s",str_final);

    fseek(arq_base,0,SEEK_END);
    nrr = ftell(arq_base)/TAM_REGISTRO;
  }   
  /* Possibilidade 2 */
  else{
    if(DEBUG)
      printf(">>>guardando registro em avail list do arquivo base.dat\n");

    /* Procedimento para atualizacao da cabeca */
    fseek(arq_base,(nrr-1)*TAM_REGISTRO,SEEK_SET);
    /* Leitura da nova cabeca */
    fscanf(arq_base, "%05d", &NRR_nova_cabeca); 

     
    /* Escrita da nova cabeca no arquivo */
    fseek(arq_avail,0,SEEK_SET);     
    fprintf(arq_avail,"%05d",NRR_nova_cabeca);

    /* Insercao no lugar do registro apontado pela cabeca da avail */
    fseek(arq_base,(nrr-1)*TAM_REGISTRO,SEEK_SET);
    fprintf(arq_base,"%s",str_final);
  }
  *NRR_cabeca = NRR_nova_cabeca;  
  printf("Obra adicionada com sucesso.\n\n\n");
  return nrr;
}
  

/*!
 * \brief Funcao que le da entrada padrao (teclado) e verifica coerencia do titulo da obra.
 */
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
    c = come_espaco(c);
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') {
      resposta=ERRO;
    }
    
    i=0;
    
    /* Caracteres a serem inseridos */
    while(c!='\n' && resposta == OK) {
      str_final[i]=c;
      i++;
      /* Remove os espacos entre palavras */
      if(c==' ') {
	c=come_espaco(c);
      }
      else{
	c=getchar();
      }

      /* CASO DE ERRO */
      /* Caso a entrada seja maior que o tamanho limite */
      if((i>=MAX_TIT) && (c!='\n')) {
	resposta = come_excesso(c);
	
	if(resposta==ERRO) {
	  printf("ERRO: Tamanho de titulo excedido!\n");
	}
	break;	
      }
    }
    
    if(resposta==OK){
      /* Preenche o resto do vetor com espacos */
      for(;i<MAX_TIT;i++) {
	str_final[i]=' ';
      }
    }

 /*    resposta = checa_redundancia_tit(str_final, vetor, n_registros); */

  } while(resposta==ERRO);
  

  printf("Titulo lido com sucesso!\n");

  return;
  
}

/*!
 * \brief Funcao que le da entrada padrao (teclado) e verifica coerencia do tipo da obra.
 */
void Insere_tipo(char *str_final) {
  
  int i,resposta;
  char c;
  
  do {
    
    resposta=OK;
    
    printf("Digite o tipo da obra (maximo 100 caracteres).\n");
    c=getchar();
    
    /* Eliminacao de espacos antes dos caracteres */
    c = come_espaco(c);
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') {
      resposta=ERRO;
    }
  
    /* O registro inicia no final do registro anterior (i=200) */
    i=MAX_TIT;
    
    /* Caracteres a serem inseridos */
    while(c!='\n' && resposta == OK) {

      str_final[i]=c;
      i++;
      /* Remove os espacos entre palavras */
      if(c==' ') {
	c=come_espaco(c);
      }
      else{
	c=getchar();
      }

      /* Caso a entrada seja maior que o tamanho limite */
      if((i>=MAX_TIP)&&(c!='\n')) {
	resposta = come_excesso(c);
	
	if(resposta==ERRO)
	  printf("ERRO: Tamanho de tipo excedido!\n");	

	break;
      }
      
    }

    if(resposta==OK){
      /* Preenche o resto do vetor com espacos */
      for(;i<MAX_TIP;i++)
	str_final[i]=' ';
    }

  } while(resposta==ERRO);
  
  printf("Tipo inserido com sucesso.\n");
  return;
  
}


/*!
 * \brief Funcao que le da entrada padrao (teclado) e verifica coerencia do nome do autor da obra.
 */
void Insere_autor(char *str_final) {

  int i,resposta;
  char c;
  
  do {
    
    resposta=OK;
    
    printf("Digite o nome do autor da obra (maximo 125 caracteres).\n");
    c=getchar();
    
    /* Eliminacao de espacos antes dos caracteres */
    c = come_espaco(c);
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') {
      resposta=ERRO;
    }
  
    /* O registro inicia no final do registro anterior */
    i=MAX_TIP;
    
    /* Caracteres a serem inseridos */
    while(c!='\n' && resposta == OK) {
      
      str_final[i]=c;
      i++;
      /* Remove os espacos entre palavras */
      if(c==' ') {
	c=come_espaco(c);
      }
      else{
	c=getchar();
      }
      
      /* Caso a entrada seja maior que o tamanho limite */
      if((i>=MAX_AUT)&&(c!='\n')) {
	resposta = come_excesso(c);
	
	if(resposta==ERRO)
	  printf("ERRO: Nome do autor maior que o permitido!\n");	

	break;
      }     

    }

    if(resposta==OK){
      /* Preenche o resto do vetor com espacos */
      for(;i<MAX_AUT;i++)
	str_final[i]=' ';
    }
    
  } while(resposta==ERRO);
  
  printf("Autor inserido com sucesso.\n");
  return;
  
}

/*!
 * \brief Funcao que le da entrada padrao (teclado) e verifica coerencia do ano da obra.
 */
void Insere_ano(char *str_final) {

  int i,resposta;
  char c;
  
  do {
    
    resposta=OK;
    
    printf("Digite o ano da obra (com quatro algarismos).\n");
    c=getchar();
    
    /* Eliminacao de espacos antes dos caracteres */
    c = come_espaco(c);
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') {
      resposta=ERRO;
    }
  
    /* O registro inicia no final do registro anterior */
    i=MAX_AUT;
    
    /* Caracteres a serem inseridos */
    while(c!='\n' && resposta!=ERRO) {
      
      /* Confere se o usuario digita algum caracter diferente de numeros
	(valores extraidos da tabela ascii) */
      if (c < '0' || c > '9'){
	resposta=ERRO2;
      }
      else{
	str_final[i]=c;
	i++;
      }
      c=getchar();
      
      /* Caso a entrada seja maior que o tamanho limite */
      if((i>=MAX_ANO)&&(c!='\n')) {
	resposta = come_excesso(c);
	
	if(resposta==ERRO)
	  printf("ERRO: Ano invalido!\n");	
 
	break;
      }
      
    }

    /* Caso tenha encontrado algum caracter diferente de numero. */
    if(resposta==ERRO2)
      printf("ERRO: O ano deve conter apenas numeros\n");    
    
    if(resposta==OK){
      /* Confere se o ano foi preenchido ate o final */
      if(i < MAX_ANO){
	printf("ERRO: Dados incompletos\n");
	resposta=ERRO;
      }
    }
    
  } while(resposta!=OK);
  
  printf("Ano inserido com sucesso.\n");
  return;
  
}

/*!
 * \brief Funcao que le da entrada padrao (teclado) e verifica coerencia do valor da obra.
 */
void Insere_valor(char *str_final) {

  int i,j,k,resposta;
  char c, valor[TAM_VAL];
  
  do {
    resposta=OK;
    
    printf("Digite o valor da obra (maximo 12 digitos).\n");
    c=getchar();
    
    /* Eliminacao de espacos antes dos caracteres */
    c = come_espaco(c);
    
    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') {
      resposta=ERRO;
    }
  
 
    /* O registro inicia no final do registro anterior */
    i=MAX_ANO;
    j=0;
    /* Caracteres a serem inseridos */
    while(c!='\n' && resposta != ERRO) {
      
      /* Confere se o usuario digita algum caracter diferente de numeros
	(valores extraidos da tabela ascii) */
      if (c < '0' || c > '9'){
	resposta=ERRO2;
      }
      else{
	valor[j]=c;
	i++;
	j++;
      }
      c=getchar();
      
      /* Caso a entrada seja maior que o tamanho limite */
      if((i>=MAX_VAL)&&(c!='\n')) {
	resposta = come_excesso(c);
	
	if(resposta==ERRO)
	  printf("ERRO: Valor excedeu tamanho maximo!\n");	

	break;
      }
      
    }
    
    /* Caso tenha encontrado algum caracter diferente de numero. */
    if(resposta==ERRO2)
      printf("ERRO: O valor deve conter apenas numeros\n");
    
    
    if(resposta==OK){
      /* Preenche o vetor com 0 */ 
      for(k=MAX_ANO;k<MAX_VAL;k++)
	str_final[k]='0';
      /* Copia o valor lido para o final do vetor */
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

/*!
 * \brief Funcao que le da entrada padrao (teclado) e verifica coerencia do identificador da obra.
 */
void Insere_imagem(char *str_final) {

  int i, j, resposta;
  char c, formato[TAM_FORM];
  
  do {
    resposta=OK;
    
    printf("Digite o nome identificador da obra (seis digitos + extensao: [png, jpg, gif])\n");
    c=getchar();
    


    /* Eliminacao de espacos antes dos caracteres */
    c = come_espaco(c);

    /* Caso o primeiro caractere seja um 'Enter' */
    if(c=='\n') {
      resposta=ERRO;
    }
    
    /* O registro inicia no final do registro anterior */
    i=MAX_VAL;
    j=0;
    /* Caracteres a serem inseridos */
    
    while(c!='\n' && resposta!=ERRO) {
      
      /* Confere se o usuario digita algum caracter diferente de numeros
	antes da extensao (valores extraidos da tabela ascii) */
      if (i < MAX_IMG-TAM_FORM && (c < '0' || c > '9')){
	resposta=ERRO2;
      }
      /* Guarda o formato da figura no string "formato" */
      if (i > MAX_IMG-TAM_FORM-1 && i < MAX_IMG){
	formato[j] = c;
	j++;
      }
      
      str_final[i]=c;
      i++;
      c=getchar();
      
      /* Confere se a extensao do arquivo eh valida */
      if(i == MAX_IMG)
	if(!((formato[0]=='p'&&formato[1]=='n'&&formato[2]=='g') ||
	     (formato[0]=='j'&&formato[1]=='p'&&formato[2]=='g') ||
	     (formato[0]=='g'&&formato[1]=='i'&&formato[2]=='f'))){
	  printf("ERRO: extensao invalida!\n");
	  resposta=ERRO;
	}

      /* Caso a entrada seja maior que o tamanho limite */
      if((i>=MAX_IMG)&&(c!='\n')) {
	resposta = come_excesso(c);
       
	if(resposta==ERRO)
	  printf("ERRO: Identificador excedeu tamanho maximo!\n");	
	
	break;
      }
    }

    /* Caso tenha encontrado algum caracter diferente de numero. */
    if(resposta==ERRO2)
      printf("ERRO: o identificador deve conter apenas digitos e uma extensao valida.\n");
    
    if(resposta==OK){
      /* Confere se o identificador foi preenchido ate o final */
      if(i < MAX_IMG){
	printf("ERRO: dados incompletos\n");
	resposta = ERRO;
      }
    }
  } while(resposta!=OK);
  
  printf("Identificador inserido com sucesso.\n");
  return;
}


/*!
 * \brief Funcao que acessa a base diretamente a partir do NRR e gera o html.
 */
void busca_registro(int NRR, FILE * arq_base, FILE * arq_html) {

  int i;
  char identificador[TAM_IMG];


  /* Desloca o cursor para o inicio do registro. */
  fseek(arq_base,(NRR-1)*TAM_REGISTRO,SEEK_SET);


  /* Geracao do arquivo de consulta em HTML: */

  /* Cabecalho do arquivo */
  fprintf(arq_html,"<html><head></head><body>\n<div align=\"center\"><br>\n");

  /* Titulo */
  fprintf(arq_html,"\n<br><br><b>Titulo: </b>");
  for(i=0;i<TAM_TIT;i++) {
    fprintf(arq_html,"%c",fgetc(arq_base));
  }

  /* Tipo */
  fprintf(arq_html,"\n<br><br><b>Tipo: </b>");
  for(i=0;i<TAM_TIP;i++) {
    fprintf(arq_html,"%c",fgetc(arq_base));
  }

  /* Autor */
  fprintf(arq_html,"\n<br><b><br>Autor: </b>");
  for(i=0;i<TAM_AUT;i++) {
    fprintf(arq_html,"%c",fgetc(arq_base));
  }

  /* Ano */
  fprintf(arq_html,"\n<br><br><b>Ano: </b>");
  for(i=0;i<TAM_ANO;i++) {
    fprintf(arq_html,"%c",fgetc(arq_base));
  }

  /* Valor */
  fprintf(arq_html,"\n<br><br><b>Valor: </b>");
  for(i=0;i<TAM_VAL;i++) {
    fprintf(arq_html,"%c",fgetc(arq_base));
  }

  /* Identificador */
  fprintf(arq_html,"\n<br><br><b>Codigo identificador da obra: </b>");
  for(i=0;i<TAM_IMG;i++) {
    identificador[i]=fgetc(arq_base);
    fprintf(arq_html,"%c",identificador[i]);
  }

  /* Imagem */
  fprintf(arq_html,"\n<br><br><p><img src=\"img/");
  for(i=0;i<TAM_IMG;i++) {
    fprintf(arq_html,"%c",identificador[i]);
    if (i==5) {
      fprintf(arq_html,".");
    }
  }
  fprintf(arq_html,"\"></p><hr>");


  /* Fim do html */
  fprintf(arq_html,"<br></div></body></html>");

  return;
}

/*! 
 * \brief Funcao de remocao de registro - avail list da base de dados 
 */
void remove_registro (int n_registros, ap_tipo_registro_pk vetor_registros, FILE * arq_base, FILE * arq_cabeca_avail_base, int *cabeca_avail_base_original) {

  int NRR_a_remover, NRR_cabeca_antiga, cabeca_avail_base;
  char titulo_a_remover[MAX_TIT];
  ap_tipo_registro_pk elto_encontrado;

  cabeca_avail_base = *cabeca_avail_base_original;

   if(n_registros == 0) {
    printf("Nao ha obras registradas no catalogo.\n\n");
    return;
  }

  printf("ATENCAO! Remocao de obra do catalogo\n\n");
  /* titulo_a_remover eh lido pela mesma funcao de insercao de registro */
  Insere_titulo(titulo_a_remover);

  /* Busca o titulo procurado no vetor de structs. */
  elto_encontrado = bsearch(titulo_a_remover, vetor_registros, n_registros, sizeof(tipo_registro_pk), compara_bsearch);
  
  /* Caso o titulo nao esteja registrado, resposta==NULL. Retorna a funcao. */
  if(elto_encontrado==NULL) {
    printf("\nO titulo nao foi encontrado! Tente novamente!\n\n");
  }

  /* Caso contrario, a partir do NRR, faz o procedimento de remocao do registro: */
  else {

    NRR_a_remover=((*elto_encontrado).nrr);

    if(DEBUG)
      printf(">>>NRR a remover: %d\n", NRR_a_remover);

      
      /* Caso a avail list seja vazia, nao ha nenhum registro apagado */
    if (cabeca_avail_base == -1) {
 
      fseek(arq_cabeca_avail_base,0,SEEK_SET);     
      fprintf(arq_cabeca_avail_base, "%05d", NRR_a_remover);
      
      /* Atribui-se o final da lista '-1' no comeco do registro que deseja-se remover */
      fseek(arq_base, (NRR_a_remover-1)*TAM_REGISTRO, SEEK_SET);
      fprintf(arq_base, "%05d",-1);
    }
    

    /* Caso ja exista registros removidos (arq existe) */
    else {

      if(DEBUG)
	printf("\n>>>O arquivo cabeca avail ja existia. Atualizando a lista... \n\n");
      
      /* Leitura do NRR da cabeca da lista a partir do arquivo que ja existia */
      NRR_cabeca_antiga = cabeca_avail_base;
      
      /* Atualizacao da cabeca: cabeca=NRR_a_remover */
      fseek(arq_cabeca_avail_base,0,SEEK_SET);
      fprintf(arq_cabeca_avail_base, "%05d", NRR_a_remover);
      /* Adiciona o endereco da antiga cabeca no inicio do registro a ser removido */
      fseek(arq_base, (NRR_a_remover -1)*TAM_REGISTRO, SEEK_SET);
      fprintf(arq_base,"%05d",NRR_cabeca_antiga);
      
      if(DEBUG){
	printf(">>>Nova cabeca da Avail List: %d\n", NRR_a_remover);
	printf(">>>Antiga cabeca (segundo elemento): %d\n\n", NRR_cabeca_antiga);
	  }
    }
    
    printf("Obra removida com sucesso.\n\n"); 
  }
  
  *cabeca_avail_base_original = NRR_a_remover;

  return;
}


/**************************************/
/*         Funcoes Auxiliares         */
/**************************************/

/*! 
 * \brief Funcao aux que ignora espacos antes do comeco da entrada
 */
char come_espaco(char c){
  /* sobrescreve o valor de "c" ate achar algum valor diferente de espaco */
  while(c==' ') {
    c=getchar();
  }
  
  return(c);
}

/*! 
 * \brief Funcao aux que recebe caracteres alem do esperado pelo campo
 */
int come_excesso(char c){
  char resposta = OK;
  /* Continua a receber a entrada ate o usuario apertar "enter" */
  while(c!='\n') {
    /* Aceita que o usuario digite
      espacos depois que terminar a digitacao */
    if(c!=' ')
      resposta=ERRO;
    c=getchar();
  }
  return(resposta);
}

/*! 
 * \brief Funcao aux que verifica se titulo ja foi inserido anteriormente (case insensitive)
 */
int checa_redundancia_tit(char * str_final, ap_tipo_registro_pk vetor, int n_registros){
  
  int i, j;
  
  for(i=0; i<n_registros; i++){ 
    for(j=0; j<TAM_TIT; j++){ 

      if(tolower(str_final[j]) != tolower(vetor[i].titulo[j]))
	break;

      if(j == TAM_TIT-1){
	printf("Erro! Titulo inserido já existente!\n");
	printf("Todos os titulos de obras devem ser diferentes! Repita a operação!\n\n");
	return ERRO;
      }

    }
  }
 
  return OK;     
}
