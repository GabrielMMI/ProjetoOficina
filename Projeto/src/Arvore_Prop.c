/********************************************//**
 ** @file Main.c
 * @brief Inicializa a janela inicial e cria os diretórios necessários.
 * @bug Nao contem bugs conhecidos!
 *
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

 #include "../include/ListaEncadeada.h"

/********************************************//**
 * \brief Inicializa uma arvore com um nó nulo
 *
 * \param void
 *
 * \return NULL
 *
 ***********************************************/

Arvore* inicializaArvoreProp(){
    return NULL;
}

/********************************************//**
 * \brief Criar um nó de uma arvore
 *
 * \param dado - Os dados de um proprietario
 *
 * \return lista - Endereço de memoria da arvore criada
 *
 ***********************************************/

Arvore* criaNoProp(Proprietario dado){
    Arvore *arvore;
    
    arvore=(Arvore*)malloc(sizeof(Arvore));
    
    if(arvore!=NULL){
        arvore->dado = dado;
        arvore->esquerda=NULL;
        arvore->direita=NULL;
    }
    return lista;
}

/********************************************//**
 * \brief Insere um nó em uma arvore
 *
 * \param arvore - Arvore na qual o nó será inserido
 * \param dado - Os dados de um proprietario
 *
 * \return arvore - Endere�o de mem�ria da nova arvore
 *
 ***********************************************/

Arvore* inserirNaArvoreProp(Arvore *arvore,Proprietario dado){
    Arvore *arvoreAux;
    arvoreAux=criaNo(dado);
    if(arvore==NULL){
    	arvore=arvoreAux;
	}else if(stricmp(dado.nome,arvore->dado.nome)<0){
		arvore->esqueda=inserirNaArvoreProp(arvore->esquerda,dado);
	}else if(stricmp(dado.nome,arvore->dado.nome)>=0){
		arvore->direita=inserirNaArvoreProp(arvore->direita,dado);
	}
	return arvore;
}

/********************************************//**
 * \brief Libera a memória alocada de todos os elementos da arvore
 *
 * \param arvore - A arvore que será liberada da memória
 *
 * \return void
 *
 ***********************************************/

void liberaArvoreProp(Arvore *arvore){
	if(arvore==NULL){
		return;
	}
    if(arvore->esquerda!=NULL){
   		liberaArvoreProp(arvore->esquerda);
    }
	if(arvore->direita!=NULL){
    	liberaArvoreProp(arvore->direita);
	}
	free(arvore);
}
