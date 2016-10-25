/********************************************//**
 ** @file FuncoesBasicas.c
 * @brief Contem todas as fun��es b�sicas.
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
 * @param nomeArq - Endere�o de mem�ria do nome do arquivo
 *
 * @return ERRO_ARQUIVO_INEXISTENTE - N�o existe
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
