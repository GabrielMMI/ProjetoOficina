/********************************************//**
 * @file Manutencao.h
 * @brief Contem os cabe�alhos de todas as
 *        funcoes de opera��es com Manuten��o, e
 *        a estrutura do tipo Manuten��o e do tipo Data.
 * @bug Nao contem bugs conhecidos!
 *
 *@author Matheus Bispo
 *@author Gabriel Messias
 ***********************************************/
#ifndef MANUTENCAO_H_SECURE
#define MANUTENCAO_H_SECURE

#include "Win_Funcoes_Basicas.h"
#include "Proprietario.h"
#include "Veiculo.h"
#include "Defines.h"
#include "Erros.h"
#include <time.h>

/********************************************//**
 * \brief Contem informa��es sobre uma data
 ***********************************************/
typedef struct data{
	int dia, mes, ano;
}Data;

/********************************************//**
 * \brief Contem informa��es sobre uma manuten��o
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

Manutencao * carregaManutencoesCPF(char *cpf, int *qtManutCPF);
Manutencao * carregaManutencoes();
int obtemQuantManutArquivo();

int pegaManutencaoPlacDat(char *placa, Data data, Manutencao *manut);
int buscaManutencaoPlacDat(char *placa,Data data, int *pos);
int buscaManutencaoPlaca(char *placa, int *pos);
int buscaManutencaoCPF(char *cpf, int *pos);

int converteDataString(char* stringData, Data data);
int converteStringData(char *stringData, Data *data);
void obtemDataAtual(Data *data);
int comparaData(Data data1, Data data2);
Data convertTime(SYSTEMTIME st);

//----------------------------------------------------------------------//
#endif
