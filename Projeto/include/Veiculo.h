/********************************************//**
 * @file Veiculo.h
 *
 * @brief Contem os cabecalhos de todas as
 *        funcoes de operacoes com Veiculo, e
 *        a estrutura do tipo Veiculo.
 * @bug Nao contem bugs conhecidos!
 *
 *@author Matheus Bispo
 *@author Gabriel Messias
 ***********************************************/
#ifndef VEICULO_H_SECURE
#define VEICULO_H_SECURE

#include "Win_Funcoes_Basicas.h"
#include "Manutencao.h"
#include "Defines.h"
#include "Erros.h"
#include <ctype.h>

/********************************************//**
 * \brief Contem as informacoes de um veiculo
 ***********************************************/
typedef struct Veiculo
{
    char placa[TAM_PLACA];
    char modelo[TAM_MODELO];
    char fabricante[TAM_FABRICANTE];
    char chassi[TAM_CHASSI];
    char ano[TAM_ANO];
} Veiculo;

//----------------------------------------------------------------------//
//Veiculo
int incluiVeiculo(Veiculo v);
int alteraVeiculo(Veiculo vNovo, char *placa);
int excluiVeiculo(char *placa);

int validaPlaca(char *placa);
int verificaChassiRepetido(char *chassi);

int buscaVeiculo(char *placa, int *pos);
int pegaVeiculo(char *placa,Veiculo *v);
Veiculo *carregaVeiculos();
int obtemQuantVeicArquivo();
//----------------------------------------------------------------------//
#endif
