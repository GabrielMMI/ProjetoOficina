/********************************************//**
 ** @file Arvore_Prop.c
 * @brief Contém as operacoes de uma arvore binária de proprietários!
 * @bug Nao contem bugs conhecidos!
 *
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

 #include "../include/Arvore_Prop.h"

/********************************************//**
 * \brief Inicializa uma arvore com um n鉶 nulo
 *
 *
 * \return NULL
 *
 ***********************************************/

Arvore* inicializaArvoreProp(){
    return NULL;
}

/********************************************//**
 * \brief Criar um n贸 de uma arvore
 *
 * \param dado - Os dados de um proprietario
 *
 * \return lista - Endere莽o de memoria da arvore criada
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
    return arvore;
}

/********************************************//**
 * \brief Insere um n贸 em uma arvore
 *
 * \param arvore - Arvore na qual o n贸 ser谩 inserido
 * \param dado - Os dados de um proprietario
 *
 * \return arvore - Endere鏾 de mem髍ia da nova arvore
 *
 ***********************************************/

Arvore* inserirNaArvoreProp(Arvore *arvore,Proprietario dado){
    Arvore *arvoreAux;
    arvoreAux = criaNoProp(dado);
    if(arvore==NULL){
    	arvore=arvoreAux;
	}else if(stricmp(dado.nome,arvore->dado.nome)<0){
		arvore->esquerda=inserirNaArvoreProp(arvore->esquerda,dado);
	}else if(stricmp(dado.nome,arvore->dado.nome)>=0){
		arvore->direita=inserirNaArvoreProp(arvore->direita,dado);
	}
	return arvore;
}

/********************************************//**
 * \brief Libera a mem贸ria alocada de todos os elementos da arvore
 *
 * \param arvore - A arvore que ser谩 liberada da mem贸ria
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
