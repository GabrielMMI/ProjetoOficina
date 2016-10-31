/********************************************//**
 * @file Proprietario.h
 * @brief Contem os cabe�alhos de todas as
 *        funcoes de opera��es com Proprietario, e
 *        a estrutura do tipo Proprietario e do tipo Endere�o.
 * @bug Nao contem bugs conhecidos!
 *
 ***********************************************/

#ifndef PROPRIETARIO_H_SECURE
#define PROPRIETARIO_H_SECURE

#include "Win_Funcoes_Basicas.h"
#include "Defines.h"
#include <stdio.h>
#include <stdlib.h>

/********************************************//**
 * \brief Guarda um endere�o
 ***********************************************/
typedef struct endereco{
	char descricao[TAM_DESCRICAO];/**< A descri��o do endere�o*/
	char cidade[TAM_CIDADE];/**< A cidade do endere�o */
	char estado[TAM_ESTADO];/**< O estado do endere�o */
}Endereco;

/********************************************//**
 * \brief Guarda um endere�o
 ***********************************************/
typedef struct telefone{
	char ddd[TAM_DDD];/**< A descri��o do endere�o*/
	char telefone[TAM_TEL];/**< A cidade do endere�o */
}Telefone;

/********************************************//**
 * \brief Guarda as informa��es de
 *        um propriet�rio
 ***********************************************/
typedef struct proprietario{
	char nome[TAM_NOME];/**< Nome do proprietario */
	char cpf[TAM_CPF];/**< CPF do proprietario */
	Endereco endereco;/**< Endere�o do proprietario */
	Telefone telefone;/**< Telefone do proprietario */
}Proprietario;

//----------------------------------------------------------------------//
//Proprietario
int incluiProprietario(Proprietario p);
int buscaProprietario(char *cpf, int *pos);
int alteraProprietario(Proprietario novoP, char *cpf);
int excluiProprietario(char *cpf);
Proprietario *pesquisaProprietario(char *nome);
int pegaProprietario(char *cpf, Proprietario *pAux);
int validaCPF(char *cpf);
int validaTelefone(char *tel);
Proprietario *carregaProprietarios();
int obtemQuantPropArquivo();
//----------------------------------------------------------------------//
#endif
