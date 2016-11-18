/********************************************//**
 * @file Manutencao.h
 * @brief Contem os cabecalhos de todas as
 *        funcoes de operacoes com Manutencao, e
 *        a estrutura do tipo Manutencao e do tipo Data.
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
 * \brief Contem informacoes sobre uma data
 ***********************************************/
typedef struct Data{
	int dia, mes, ano;
}Data;

/********************************************//**
 * \brief Contem informacoes sobre uma manutencão
 ***********************************************/
typedef struct Manutencao{
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
