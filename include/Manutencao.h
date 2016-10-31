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

#include "Win_Funcoes_Basicas.h"
#include "Defines.h"
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
	Data data;
}Manutencao;

//----------------------------------------------------------------------//
//Manutencao
int incluiManutencao(Manutencao m);
int excluiManutencao(char *placa,char *cpf, Data data);
int buscaManutencao(char *placa, char *cpf, Data data, int *pos);
int pegaManutencao(char *placa, char *cpf, Data data, Manutencao *manut);
int buscaManutencaoCPF(char *cpf, int *pos);
Manutencao *carregaManutencoesCPF(char *cpf, int *qtManutCPF);
void obtemDataAtual(Data *data);
int comparaData(Data data1, Data data2);
Data convertTime(SYSTEMTIME st);
Manutencao *carregaManutencoes();
int obtemQuantManutArquivo();
int converteDataString(char* stringData, Data data);
int pegaManutencaoPlacDat(char *placa, Data data, Manutencao *manut);
int buscaManutencaoPlacDat(char *placa,Data data, int *pos);
int converteStringData(char *stringData, Data *data);
//----------------------------------------------------------------------//
#endif
