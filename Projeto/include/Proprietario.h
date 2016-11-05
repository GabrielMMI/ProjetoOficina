/********************************************//**
 * @file Proprietario.h
 * @brief Contem os cabeçalhos de todas as
 *        funcoes de operações com Proprietario, e
 *        a estrutura do tipo Proprietario e do tipo Endereço.
 * @bug Nao contem bugs conhecidos!
 *
 *@author Matheus Bispo
 *@author Gabriel Messias
 ***********************************************/

#ifndef PROPRIETARIO_H_SECURE
#define PROPRIETARIO_H_SECURE

#include "Win_Funcoes_Basicas.h"
#include "Manutencao.h"
#include "Defines.h"
#include "Erros.h"
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
 * \brief Guarda um telefone
 ***********************************************/
typedef struct telefone{
	char ddd[TAM_DDD];/**< O DDD do telefone*/
	char telefone[TAM_TEL];/**< O número do telefone */
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
int alteraProprietario(Proprietario novoP, char *cpf);
int excluiProprietario(char *cpf);

int buscaProprietario(char *cpf, int *pos);
int pegaProprietario(char *cpf, Proprietario *pAux);
Proprietario *carregaProprietarios();
int obtemQuantPropArquivo();

int validaDDD(char *ddd);
int validaCPF(char *cpf);
int validaTelefone(char *tel);

//----------------------------------------------------------------------//
#endif
