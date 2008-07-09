/* Implementacao de funcoes de remocao em arvore B+ */

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<malloc.h>
#include "defines.h"
#include "remocao.h"
#include "leitura.h"
#include "insercao.h"


/*!
 * \brief Rotina de remocao de no em uma arvore B+
 */
void remover(int *ultima_chave){

  int chave, resposta;
  int parentesco[3] = {NADA, NADA, NADA};
 
  /* Le chave a ser removida */
  printf("Digite a chave a ser removida\n"); 
  scanf("%d", &chave);

  /* Acha a folha onde acontecera a remocao */
  resposta = acha_folha_rem(chave, ROOT, parentesco, ultima_chave);

    
 
}


/*!
 * \brief Procura recursivamente pela folha onde se deve remover a chave.
 * Na volta da recursao, se necessario, faz merge dos nos superiores
 */
int acha_folha_rem(int chave, int pagina, int parentesco[3], int *prox_chave){ 
  
  tipoNo *no;
  int i, retorno, pos_chave, ap, temp=0;
  char linha_com[TAM_LINHA_COM];
  int parentesco_pai[3];

  parentesco_pai[0] = parentesco[0];
  parentesco_pai[1] = parentesco[1];
  parentesco_pai[2] = parentesco[2];

  /* Abre arquivo e o le */
  no = abre_no(pagina, FOLHA);
  
  /* Se eh uma folha, remove a chave desejada */
  if(no->tipo == FOLHA){ 
    retorno = remove_folha(no, chave, parentesco, prox_chave); 
    if(retorno != ERRO)
      printf("Chave removida com sucesso!\n\n");  
  } 
  else{ 
    /* Acha proxima folha */ 
    for(i=0; i<no->n_elementos; i++){
      if(chave < no->chaves[i])
	break;
    }

    /* parentesco[0] e [1] possuem o endereco dos irmaos da esquerda e da direita da folha em que a chave sera removida */
    /* parentesco[2] possui o endereco do pai dos irmaos */
    parentesco[2] = no->posicao;

    /* Se a folha corresponde ao primeiro apontador do noh, ela nao tem irmao a esquerda */
    if(i==0)
      parentesco[0] = NADA; 
    else
      parentesco[0] = no->apontadores[i-1];
   
    /* Se a folha corresponde ao ultimo apontador do noh, ela nao tem irmao a direita */
    if(i == no->n_elementos)
      parentesco[1] = NADA;
    else
      parentesco[1] = no->apontadores[i+1];
    
    ap = no->apontadores[i];
    /*fecha no, caso seu delimitador seja alterado, dentro da recursao*/    
    fecha_no(no);
   
    retorno = acha_folha_rem(chave, ap, parentesco, prox_chave);
    
    /*reabre no*/
    no = abre_no(pagina, FOLHA);
    
    /* Em caso de merge remove na arvore delimitador antigo */  
    if(retorno == REM_PAI_DIR || retorno == REM_PAI_ESQ){ 
   
      if(DEBUG)
	printf(">>>i = %d\n", i);
      /* pos_folha guarda a posicao da chave (delimitador) a ser removida */
      if(retorno == REM_PAI_DIR)
	pos_chave = i;
      if(retorno == REM_PAI_ESQ)
	pos_chave = i-1;
      
      retorno = remove_arvore(no, pos_chave, parentesco_pai, prox_chave); 
 
      if(no->tipo == REMOVER){
	temp = no->posicao;
      }

    } 
  }
 

  fecha_no(no);
  
  if(temp){
    /* Apaga noh, caso a raiz mude */
    sprintf(linha_com, "%s%s%d", RM, DIRETORIO, temp);
    system(linha_com);  
  }
  
  return retorno;
}


/*!
 * \brief Remove elemento na folha da arvore
 */
int remove_folha(tipoNo *no, int chave, int parentesco[3], int *prox_chave){

  int i, j, temp, chave_viz[2];
  tipoNo *nova, *nova2, *pai;
  char linha_com[TAM_LINHA_COM];

  /* Remove elemento da folha */
     
  for(i=0; i<no->n_elementos; i++){
    if(chave == no->chaves[i]){
      break;
    }
  }
  
  if(i==no->n_elementos){
    printf("Erro! A chave nao foi encontrada! Por favor, tente de novo!\n\n\n");
    return ERRO;
  }
    
  for(j=i; j<no->n_elementos; j++){
    no->chaves[j] = no->chaves[j+1];
    no->nrr[j] = no->nrr[j+1];
  }
  
  no->n_elementos--;  
  
    


  /* Remocao simples */ 
  if(no->n_elementos >= CHAVES/2 || no->posicao == 0){
    
 
    if(DEBUG)
      printf(">>>Remocao simples, na folha %d. N_elementos = %d\n\n", no->posicao, no->n_elementos);
    
   /* Remocao ocorreu com sucesso e nada deve ser feito */
    return OK;
  }
  
  /* Verifica se deu underflow */
  if(no->n_elementos < CHAVES/2){
    
    /*ROTACAO*/
    
    /* Rotacao com a esquerda */
    /* Confere se a folha da esquerda eh "filha" do mesmo pai */
    if(parentesco[0] != NADA){
      nova = abre_no(no->prox_esq, FOLHA);
      
      /* Confere se a folha da esquerda pode "emprestar" sua chave */ 
      if(nova->n_elementos > CHAVES/2){
	
	pai = abre_no(parentesco[2], FOLHA);
	for(i=0; i<pai->n_elementos; i++){
	  if(pai->chaves[i] <= no->chaves[0] && pai->chaves[i] >= nova->chaves[0])
	    break;
	}

	/* Insere a ultima chave da esquerda como primeiro elemento do no atual, evitando underflow */
	chave_viz[0] = nova->chaves[nova->n_elementos-1];
	chave_viz[1] = nova->nrr[nova->n_elementos-1];

	/* O novo delimitador corresponde ao primeiro elemento da arvore */
	pai->chaves[i] = nova->chaves[nova->n_elementos-1];
	
	remove_folha(nova, chave_viz[0], parentesco, prox_chave); 
	insere_folha(no, chave_viz, parentesco, prox_chave);


	if(DEBUG)
	  printf(">>novo delimitador, folha %d, posicao %d, valor %d", pai->posicao, i, pai->chaves[i]);	


	if(DEBUG)
	  printf(">>>Rotacao com a esquerda, da folha %d com a folha %d. N_elementos = %d\n\n", no->posicao, nova->posicao, no->n_elementos);

	fecha_no(pai);  
	fecha_no(nova);
	return OK;
      }
      
      fecha_no(nova);     
    }
    
    /* Rotacao com a direita */
    /* Confere se a folha da direita eh "filha" do mesmo pai */
    if(parentesco[1] != NADA){
      nova = abre_no(no->prox_dir, FOLHA);
      
      /* Confere se a folha da direita pode "emprestar" sua chave */ 
      if(nova->n_elementos > CHAVES/2){
		
	pai = abre_no(parentesco[2], FOLHA);
	for(i=0; i<pai->n_elementos; i++){
	  if(pai->chaves[i] >= no->chaves[no->n_elementos-1] && pai->chaves[i] <= nova->chaves[0])
	    break;
	}


	/* Insere a primeira chave da direita como ultimo elemento do no atual, evitando underflow */
	chave_viz[0] = nova->chaves[0];
	chave_viz[1] = nova->nrr[0];

	
	remove_folha(nova, chave_viz[0], parentesco, prox_chave); 
	insere_folha(no, chave_viz, parentesco, prox_chave);
	
	/* O novo delimitador corresponde ao primeiro elemento da folha da direita */
	pai->chaves[i] = nova->chaves[0];

	if(DEBUG)
	  printf(">>>novo delimitador, folha %d, posicao %d, valor %d, n_elementos = %d\n", pai->posicao, i, pai->chaves[i], pai->n_elementos);

	if(DEBUG)
	  printf(">>>Rotacao com a direita, da folha %d com a folha %d. N_elementos = %d\n\n", no->posicao, nova->posicao, no->n_elementos);

	fecha_no(pai);  
	fecha_no(nova);
      	return OK;
      }

      fecha_no(nova);     
    }
    
    
    /* MERGE */
    
    /* Merge com a esquerda */
    /* Confere se a folha da esquerda eh "filha" do mesmo pai */
    if(parentesco[0] != NADA){
      nova = abre_no(no->prox_esq, FOLHA);
      
      if(nova->n_elementos <= CHAVES/2){
	/* Copia chaves para folha da direita */
	for(i=0; i<nova->n_elementos; i++){
	  chave_viz[0] = nova->chaves[i];
	  chave_viz[1] = nova->nrr[i];
	  insere_folha(no, chave_viz, parentesco, prox_chave);
	}
      }
      
      
      /* Troca posicao dos arquivos, pra apontador da esquerda sempre conter o no */
      temp = no->posicao;
      no->posicao = nova->posicao;
      nova->posicao = temp;
      
      no->prox_esq = nova->prox_esq;
      nova2 = abre_no(no->prox_esq, FOLHA);
      nova2->prox_dir = no->posicao;
      fecha_no(nova2);

      nova2 = abre_no(no->prox_dir, FOLHA);
      nova2->prox_esq = no->posicao;
      fecha_no(nova2);

      
      if(DEBUG)
	printf(">>>Merge com a esquerda, da folha %d com a folha %d (que foi apagada). N_elementos = %d\n\n", no->posicao, nova->posicao, no->n_elementos);
      fecha_no(nova);

      /* Apaga folha */
      sprintf(linha_com, "%s%s%d", RM, DIRETORIO, temp);
      system(linha_com);

      /* O delimitador do pai deve ser removido */
      return REM_PAI_ESQ;
    }
    
    /* Merge com a direita */
    /* Confere se a folha da direita eh "filha" do mesmo pai */
    if(parentesco[1] != NADA){
      nova = abre_no(no->prox_dir, FOLHA);
      
      if(nova->n_elementos <= CHAVES/2){
	/* Copia chaves para folha da esquerda */
	for(i=0; i<nova->n_elementos; i++){
	  chave_viz[0] = nova->chaves[i];
	  chave_viz[1] = nova->nrr[i];
	  insere_folha(no, chave_viz, parentesco, prox_chave);
	}
      }
      
      no->prox_dir = nova->prox_dir;
      nova2 = abre_no(no->prox_dir, FOLHA);
      nova2->prox_esq = no->posicao;
      fecha_no(nova2);
         
      if(DEBUG)
	printf(">>>Merge com a direita, da folha %d com a folha %d (que foi apagada). N_elementos = %d\n\n", no->posicao, nova->posicao, no->n_elementos);

      temp = nova->posicao;
      fecha_no(nova);

      /* Apaga folha */
      sprintf(linha_com, "%s%s%d", RM, DIRETORIO, temp);
      system(linha_com);
      
      /* O delimitador do pai deve ser removido */
      return REM_PAI_DIR;
    }
  }
  return ERRO;
} 
  
  

/*!
 * \brief Remove elemento em no da arvore
 */
int remove_arvore(tipoNo *no, int pos_chave, int parentesco[3], int *prox_chave){

  int i, temp, nova_chave[3];
  tipoNo *nova, *pai;
  char linha_com[TAM_LINHA_COM];

  /* Remove elemento do noh */
     
  for(i=pos_chave; i<no->n_elementos; i++){
    no->chaves[i] = no->chaves[i+1];
    no->apontadores[i+1] = no->apontadores[i+2];
  }
  
  no->n_elementos = no->n_elementos - 1;  
  
    


  /* Remocao simples */ 
  if(no->n_elementos >= CHAVES/2 || no->posicao == 0){
   

    if(DEBUG)
      printf(">>>no->n_elementos =  %d\n", no->n_elementos);
    /* Caso a raiz tenha ficado vazia, desce um nivel a arvore */
    if(no->n_elementos == 0){


      nova = abre_no(no->apontadores[0], FOLHA);
      
      no->posicao = nova->posicao;
      no->tipo = REMOVER;
      nova->posicao = ROOT;

      if(DEBUG)
	printf(">>>Diminuindo um nivel a altura da arvore: troca folha %d por %d. N_elementos = %d\n\n", no->posicao, ROOT, nova->n_elementos);      

      fecha_no(nova);  
    }
  

 
    /* Remocao ocorreu com sucesso e nada deve ser feito */
    return OK;
  }
  
  /* Verifica se deu underflow */
  if(no->n_elementos < CHAVES/2){
    
    /* ROTACAO */
    
    /* Rotacao com a esquerda */
    /* Confere se o noh da esquerda eh "filho" do mesmo pai */
    if(parentesco[0] != NADA){
      nova = abre_no(parentesco[0], NO);
      
      /* Confere se o noh da esquerda pode "emprestar" sua chave */ 
      if(nova->n_elementos > CHAVES/2){
	
	/* Insere o delimitador no noh da direita e o ultimo da esquerda vira delimitador */
	pai = abre_no(parentesco[2], NO);
	
	for(i=0; i<pai->n_elementos; i++){
	  if(pai->chaves[i] <= no->chaves[0] && pai->chaves[i] >= nova->chaves[nova->n_elementos-1])
	    break;
	}


	/* nova_chave possui a chave do antigo delimitador com novos apontadores */
	nova_chave[0] = pai->chaves[i];
	nova_chave[1] = nova->apontadores[nova->n_elementos];
	nova_chave[2] = no->apontadores[0];

	/* O novo delimitador corresponde ao ultimo elemento do no da esquerda */
	pai->chaves[i] = nova->chaves[nova->n_elementos-1];

	if(DEBUG)
	  printf(">>novo delimitador, folha %d, posicao %d, valor %d", pai->posicao, i, pai->chaves[i]);

	remove_arvore(nova, nova->n_elementos-1, parentesco, prox_chave); 
	insere_arvore(no, nova_chave, prox_chave);

	fecha_no(pai); 
	fecha_no(nova);
	return OK; 
      }

      fecha_no(nova);
    }
    
    /* Rotacao com a direita */
    /* Confere se o noh da direita eh "filho" do mesmo pai */
    if(parentesco[1] != NADA){
      nova = abre_no(parentesco[1], NO);
      
      /* Confere se o noh da direita pode "emprestar" sua chave */ 
      if(nova->n_elementos > CHAVES/2){

	
	/* Insere o delimitador no noh da esquerda e o ultimo da direita vira delimitador */
	pai = abre_no(parentesco[2], NO);
	
	for(i=0; i<pai->n_elementos; i++){
	  if(pai->chaves[i] >= no->chaves[no->n_elementos-1] && pai->chaves[i] <= nova->chaves[0])
	    break;
	}

	/* nova_chave possui a chave do antigo delimitador com novos apontadores */
	nova_chave[0] = pai->chaves[i];
	nova_chave[1] = nova->apontadores[0];
	nova_chave[2] = no->apontadores[no->n_elementos];

	/* O novo delimitador corresponde ao primeiro elemento do no da direita */
	pai->chaves[i] = nova->chaves[0];

	if(DEBUG)
	  printf(">>novo delimitador, folha %d, posicao %d, valor %d", pai->posicao, i, pai->chaves[i]);

	remove_arvore(nova, 0, parentesco, prox_chave); 
	insere_arvore(no, nova_chave, prox_chave);
	
	fecha_no(pai);
	fecha_no(nova);
   	return OK;
      }
      
      fecha_no(nova);
    }
    
    
    /* MERGE */
    
    /* Merge com a esquerda */
    /* Confere se o noh da esquerda eh "filho" do mesmo pai */
    if(parentesco[0] != NADA){
      nova = abre_no(parentesco[0], NO);
      


      if(nova->n_elementos <= CHAVES/2){


	pai = abre_no(parentesco[2], NO);
	
	for(i=0; i<pai->n_elementos; i++){
	  if(pai->chaves[i] <= no->chaves[no->n_elementos-1] && pai->chaves[i] >= nova->chaves[0])
	    break;
	}
	no->chaves[no->n_elementos] = pai->chaves[i];
	no->n_elementos++;
	
	/* Copia chaves para noh da direita*/
	for(i=0; i<nova->n_elementos; i++){
	  no->chaves[no->n_elementos] = nova->chaves[i];
	  no->apontadores[no->n_elementos] = nova->apontadores[i];
	  no->apontadores[no->n_elementos+1] = nova->apontadores[i+1];
	  no->n_elementos++;
	 /*  insere_folha(no, nova_chave, parentesco, prox_chave); */
	}

      }
      
      /* Faz com que o noh da esquerda seja a valido */
      temp = no->posicao;
      no->posicao = nova->posicao;
      nova->posicao = temp;
      
      fecha_no(nova);

      /* Apaga noh */
      sprintf(linha_com, "%s%s%d", RM, DIRETORIO, temp);
      system(linha_com);
      
      if(DEBUG)
	printf(">>>merge com a esquerda\n");
      /* O delimitador do pai deve ser removido */
      return REM_PAI_ESQ;
    }
    
    /* Merge com a direita */
    /* Confere se o noh da direita eh "filho" do mesmo pai */
    if(parentesco[1] != NADA){
      nova = abre_no(parentesco[1], NO);
      
      if(nova->n_elementos <= CHAVES/2){


	pai = abre_no(parentesco[2], NO);
	
	for(i=0; i<pai->n_elementos; i++){
	  if(pai->chaves[i] >= no->chaves[no->n_elementos-1] && pai->chaves[i] <= nova->chaves[0])
	    break;
	}
	no->chaves[no->n_elementos] = pai->chaves[i];
	no->n_elementos++;
	
	/* Copia chaves para noh da esquerda */
	for(i=0; i<nova->n_elementos; i++){
	  no->chaves[no->n_elementos] = nova->chaves[i];
	  no->apontadores[no->n_elementos] = nova->apontadores[i];
	  no->apontadores[no->n_elementos+1] = nova->apontadores[i+1];
	  no->n_elementos++;
	 /*  insere_folha(no, nova_chave, parentesco, prox_chave); */
	}

	fecha_no(pai);
      }
      
      temp = nova->posicao;
      fecha_no(nova);

      /* Apaga noh */
      sprintf(linha_com, "%s%s%d", RM, DIRETORIO, temp);
      system(linha_com);

      if(DEBUG)
	printf(">>>merge com a direita\n");
      /* O delimitador do pai deve ser removido */
      return REM_PAI_DIR;
    }
  }
  if(DEBUG)
    printf(">>>ERRO!\n");
  return ERRO; 
} 
