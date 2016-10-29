/********************************************//**
 * @file Proprietario.h
 * @brief Contem os cabeçalhos de todas as
 *        funcoes de operações com Proprietario, e
 *        a estrutura do tipo Proprietario e do tipo Endereço.
 * @bug Nao contem bugs conhecidos!
 *
 ***********************************************/

#ifndef PROPRIETARIO_H_SECURE
#define PROPRIETARIO_H_SECURE

#include "Win_FuncoesBasicas.h"
#include <stdio.h>
#include <stdlib.h>

/********************************************//**
 * \brief Guarda um endereço
 ***********************************************/
typedef struct endereco{
	char descricao[TAM_DESCRICAO];/**< A descrição do endereço*/
	char cidade[TAM_CIDADE];/**< A cidade do endereço */
	char estado[TAM_ESTADO];/**< O estado do endereço */
}Endereco;

/********************************************//**
 * \brief Guarda um endereço
 ***********************************************/
typedef struct telefone{
	char ddd[TAM_DDD];/**< A descrição do endereço*/
	char telefone[TAM_TEL];/**< A cidade do endereço */
}Telefone;

/********************************************//**
 * \brief Guarda as informações de
 *        um proprietário
 ***********************************************/
typedef struct proprietario{
	char nome[TAM_NOME];/**< Nome do proprietario */
	char cpf[TAM_CPF];/**< CPF do proprietario */
	Endereco endereco;/**< Endereço do proprietario */
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

//----------------------------------------------------------------------//
#endif
