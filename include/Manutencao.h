/********************************************//**
 * @file Manutencao.h
 * @brief Contem os cabeçalhos de todas as
 *        funcoes de operações com Manutenção, e
 *        a estrutura do tipo Manutenção e do tipo Data.
 * @bug Nao contem bugs conhecidos!
 *
 ***********************************************/
#ifndef MANUNTENCAO_H_SECURE
#define MANUNTENCAO_H_SECURE

#include "Win_FuncoesBasicas.h"
#include "Erros.h"
#include <time.h>

/********************************************//**
 * \brief Contem informações sobre uma data
 ***********************************************/
typedef struct data{
	int dia, mes, ano;
}Data;

/********************************************//**
 * \brief Contem informações sobre uma manutenção
 ***********************************************/
typedef struct manutencao{
	char placa[TAM_PLACA];
	char cpf[TAM_CPF];
	char descricao[TAM_DESCRICAO];
	float valorPecas;
	float valorObra;
	time_t data;
}Manutencao;

//----------------------------------------------------------------------//
//Manutencao
int incluiManutencao(Manutencao m);
int excluiManutencao(char *placa);
int buscaManutencao(char *placa, char *cpf, char *data, int *pos);
void obtemDataAtual(time_t *data);
//----------------------------------------------------------------------//
#endif
