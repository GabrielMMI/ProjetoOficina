#ifndef H_ARVORE_SECURE
#define H_ARVORE_SECURE

/********************************************//**
 * @file ListaEncadeada.h
 * @brief Contem os cabe�alhos de todas as
 *        funcoes de opera��es com Arvore dos proprietarios, e
 *        a estrutura do tipo ArvoreProp
 * @bug Nao contem bugs conhecidos!
 *
 *@author Matheus Bispo
 *@author Gabriel Messias
 ***********************************************/

#include "Proprietario.h"

 typedef struct Arvore{
     Proprietario dado;
     struct Arvore *esquerda;
     struct Arvore *direita;
 }Arvore;

Arvore* inicializaArvoreProp();
Arvore* criaNoProp(Proprietario dado);
Arvore* inserirNaArvoreProp(Arvore *arvore,Proprietario dado);
void liberaArvoreProp(Arvore *arvore);

#endif
