#ifndef H_ARVORE_SECURE
#define H_ARVORE_SECURE

/********************************************//**
 * @file Arvore_Prop.h
 * @brief Contem os cabecalhos de todas as
 *        funcoes de operacoes com Arvore dos proprietários, e
 *        a estrutura do tipo Arvore
 * @bug Nao contem bugs conhecidos!
 *
 *@author Matheus Bispo
 *@author Gabriel Messias
 ***********************************************/

#include "Proprietario.h"
/********************************************//**
 * \brief Contem as variáveis necessárias para
 *        criar um no do tipo proprietário em uma
 *        arvore binária.
 ***********************************************/
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
