/********************************************//**
 * @file Proprietario.h
 * @brief Contem os cabecalhos de todas as
 *        funcoes de operacoes com Proprietario, e
 *        a estrutura do tipo Proprietario e do tipo Endereco.
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
 * \brief Guarda um endereco
 ***********************************************/
typedef struct Endereco
{
    char descricao[TAM_DESCRICAO];/**< A descricão do endereco*/
    char cidade[TAM_CIDADE];/**< A cidade do endereco */
    char estado[TAM_ESTADO];/**< O estado do endereco */
} Endereco;

/********************************************//**
 * \brief Guarda um telefone
 ***********************************************/
typedef struct Telefone
{
    char ddd[TAM_DDD];/**< O DDD do telefone*/
    char telefone[TAM_TEL];/**< O número do telefone */
} Telefone;

/********************************************//**
 * \brief Guarda as informacoes de
 *        um proprietário
 ***********************************************/
typedef struct Proprietario
{
    char nome[TAM_NOME];/**< Nome do proprietario */
    char cpf[TAM_CPF];/**< CPF do proprietario */
    Endereco endereco;/**< Endereco do proprietario */
    Telefone telefone;/**< Telefone do proprietario */
} Proprietario;


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
