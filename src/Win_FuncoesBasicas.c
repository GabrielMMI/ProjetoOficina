/********************************************//**
 ** @file FuncoesBasicas.c
 * @brief Contem todas as funções básicas.
 *
 ***********************************************/


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include "../include/Erros.h"

/********************************************//**
 * @brief Verificar se um arquivo existe
 *
 * @param nomeArq - Endereço de memória do nome do arquivo
 *
 * @return ERRO_ARQUIVO_INEXISTENTE - Não existe
 * @return ARQUIVO_EXISTENTE - Existe
 *
 ***********************************************/
int existeArquivo(char *nomeArq)
{
	FILE *arq;
	int flag;
	arq = fopen(nomeArq, "r");
	if (arq==NULL){
		flag = ERRO_ARQUIVO_INEXISTENTE;
	} else {
		flag = ARQUIVO_EXISTENTE;
		fclose(arq);
	}
	return flag;
}


/********************************************//**
 * \brief Armazena ou recupera o ultimo handle armazenado
 *
 * \param handle HWND*
 * \param tipo int
 * \return HWND*
 *
 ***********************************************/
HWND *guardaPegaHandle(HWND *handle, int tipo){
    static HWND *hwnd;

    if(tipo == 0) hwnd = handle;

    return hwnd;
}

/********************************************//**
 * \brief fecha e verifica o fechamento de uma stream de arquivo
 *
 * \param arq - Ponteiro do tipo FILE
 * 
 * \return FECHA_ARQUIVO_SUCESSO - Sucesso ao fechar arquivo
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar arquivo
 *
 ***********************************************/
int fechaArquivo(FILE *arq){
	int flag = FECHA_ARQUIVO_ERRO;

    if(fclose(arq) != EOF) flag = FECHA_ARQUIVO_SUCESSO;

    return flag;
}

