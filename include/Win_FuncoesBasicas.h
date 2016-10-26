/********************************************//**
 * @file FuncoesBasicas.h
 * @brief Contem os cabeçalhos de todas as
 *        funcoes basicas de leitura
 *        e de arquivos.
 * @bug Nao contem bugs conhecidos!
 *
 ***********************************************/

#ifndef FBASICAS_H_SECURE
#define FBASICAS_H_SECURE

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include"Defines.h"
#include <windows.h>

//----------------------------------------------------------------------//
//funcoes basicas

int abreArquivo(char *nomeArq, char *tipoAbertura, FILE* arq);
int existeArquivo(char *nomeArq);
HWND *guardaPegaHandle(HWND *handle, int tipo);
int fechaArquivo(FILE *arq);
//----------------------------------------------------------------------//

#endif
