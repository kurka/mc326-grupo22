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

  int i, retorno, pos_chave, temp=0;
  char linha_com[TAM_LINHA_COM];
  
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
      if(chave <= no->chaves[i])
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
    
    
    retorno = acha_folha_rem(chave, no->apontadores[i], parentesco, prox_chave);
    

    /* Em caso de merge remove na arvore delimitador antigo */  
    if(retorno == REM_PAI){ 
      /* pos_folha guarda a posicao da chave (delimitador) a ser removida */
      if(i == no->n_elementos)
	pos_chave = i-1;
      else
	pos_chave = i;
      
      retorno = remove_arvore(no, pos_chave, parentesco, prox_chave); 
    } 
  }
  if(no->tipo == REMOVER)
    temp = no->posicao;
  fecha_no(no);
  
  if(temp){
    /* Apaga noh */
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
  tipoNo *nova, *pai;
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
	  if(pai->chaves[i] < no->chaves[0] && pai->chaves[i] > nova->chaves[0])
	    break;
	}

	/* Insere a ultima chave da esquerda como primeiro elemento do no atual, evitando underflow */
	chave_viz[0] = nova->chaves[nova->n_elementos-1];
	chave_viz[1] = nova->nrr[nova->n_elementos-1];
	
	remove_folha(nova, chave_viz[0], parentesco, prox_chave); 
	insere_folha(no, chave_viz, parentesco, prox_chave);

	/* O novo delimitador corresponde ao primeiro elemento da arvore */
	pai->chaves[i] = no->chaves[0];
	


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
	  if(pai->chaves[i] > no->chaves[no->n_elementos-1] && pai->chaves[i] < nova->chaves[0])
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
	  printf(">>>Rotacao com a esquerda, da folha %d com a folha %d. N_elementos = %d\n\n", no->posicao, nova->posicao, no->n_elementos);

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
      
      no->prox_esq = nova->prox_esq;
      
      /* Troca posicao dos arquivos, pra apontador da esquerda sempre conter o no */
      temp = no->posicao;
      no->posicao = nova->posicao;
      nova->posicao = temp;
      

/*      nova->n_elementos = 0; */
/*       nova->prox_esq = NADA; */
/*       nova->prox_dir = NADA; */
      
      if(DEBUG)
	printf(">>>Merge com a esquerda, da folha %d com a folha %d (que foi apagada). N_elementos = %d\n\n", no->posicao, nova->posicao, no->n_elementos);
      fecha_no(nova);

      /* Apaga folha */
      sprintf(linha_com, "%s%s%d", RM, DIRETORIO, temp);
      system(linha_com);

      /* O delimitador do pai deve ser removido */
      return REM_PAI;
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
         
      if(DEBUG)
	printf(">>>Merge com a direita, da folha %d com a folha %d (que foi apagada). N_elementos = %d\n\n", no->posicao, nova->posicao, no->n_elementos);

      temp = nova->posicao;
      fecha_no(nova);

      /* Apaga folha */
      sprintf(linha_com, "%s%s%d", RM, DIRETORIO, temp);
      system(linha_com);
      
      /* O delimitador do pai deve ser removido */
      return REM_PAI;
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
  
  no->n_elementos--;  
  
    


  /* Remocao simples */ 
  if(no->n_elementos >= CHAVES/2 || no->posicao == 0){
   
    /* Caso a raiz tenha ficado vazia, desce um nivel a arvore */
    if(no->n_elementos == 0){


      nova = abre_no(no->apontadores[0], FOLHA);
      
      no->posicao = nova->posicao;
      no->tipo = REMOVER;
      nova->posicao = ROOT;

      if(DEBUG)
	printf(">>>Diminuindo um nivel a altura da arvore: troca folha %d por %d. N_elementos = %d\n\n", nova->posicao, ROOT, nova->n_elementos);      

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
      nova = abre_no(no->prox_esq, NO);
      
      /* Confere se o noh da esquerda pode "emprestar" sua chave */ 
      if(nova->n_elementos > CHAVES/2){
	
	/* Insere o delimitador no noh da direita e o ultimo da esquerda vira delimitador */
	pai = abre_no(parentesco[2], NO);
	
	for(i=0; i<pai->n_elementos; i++){
	  if(pai->chaves[i] < no->chaves[0] && pai->chaves[i] > nova->chaves[nova->n_elementos-1])
	    break;
	}


	/* nova_chave possui a chave do antigo delimitador com novos apontadores */
	nova_chave[0] = pai->chaves[i];
	nova_chave[1] = nova->apontadores[nova->n_elementos];
	nova_chave[2] = no->apontadores[0];

	/* O novo delimitador corresponde ao ultimo elemento do no da esquerda */
	pai->chaves[i] = nova->chaves[nova->n_elementos-1];

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
      nova = abre_no(no->prox_dir, NO);
      
      /* Confere se o noh da direita pode "emprestar" sua chave */ 
      if(nova->n_elementos > CHAVES/2){

	
	/* Insere o delimitador no noh da esquerda e o ultimo da direita vira delimitador */
	pai = abre_no(parentesco[2], NO);
	
	for(i=0; i<pai->n_elementos; i++){
	  if(pai->chaves[i] > no->chaves[no->n_elementos-1] && pai->chaves[i] < nova->chaves[0])
	    break;
	}

	/* nova_chave possui a chave do antigo delimitador com novos apontadores */
	nova_chave[0] = pai->chaves[i];
	nova_chave[1] = nova->apontadores[0];
	nova_chave[2] = no->apontadores[no->n_elementos];

	/* O novo delimitador corresponde ao primeiro elemento do no da direita */
	pai->chaves[i] = nova->chaves[0];

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
      nova = abre_no(no->prox_esq, NO);
      
      if(nova->n_elementos <= CHAVES/2){
	/* Copia chaves para noh da direita */
	for(i=0; i<nova->n_elementos; i++){
	  nova_chave[0] = nova->chaves[i];
	  nova_chave[1] = nova->apontadores[i];
	  nova_chave[2] = nova->apontadores[i+1];
	  insere_folha(no, nova_chave, parentesco, prox_chave);
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
      
      /* O delimitador do pai deve ser removido */
      return REM_PAI;
    }
    
    /* Merge com a direita */
    /* Confere se o noh da direita eh "filho" do mesmo pai */
    if(parentesco[1] != NADA){
      nova = abre_no(no->prox_dir, NO);
      
      if(nova->n_elementos <= CHAVES/2){
	/* Copia chaves para noh da esquerda */
	for(i=0; i<nova->n_elementos; i++){
	  nova_chave[0] = nova->chaves[i];
	  nova_chave[1] = nova->apontadores[i];
	  nova_chave[2] = nova->apontadores[i+1];
	  insere_folha(no, nova_chave, parentesco, prox_chave);
	}
      }
      
      temp = nova->posicao;
      fecha_no(nova);

      /* Apaga noh */
      sprintf(linha_com, "%s%s%d", RM, DIRETORIO, temp);
      system(linha_com);

      /* O delimitador do pai deve ser removido */
      return REM_PAI;
    }
  }
  return ERRO; 
} 
