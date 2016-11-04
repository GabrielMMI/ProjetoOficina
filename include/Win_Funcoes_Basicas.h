/********************************************//**
 * @file Win_Funcoes_Basicas.h
 * @brief Contem os cabeçalhos de todas as
 *        funcoes basicas de leitura
 *        e de arquivos.
 * @bug Nao contem bugs conhecidos!
 *
 *@author Matheus Bispo
 *@author Gabriel Messias
 ***********************************************/

#ifndef FBASICAS_H_SECURE
#define FBASICAS_H_SECURE

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <commctrl.h>
#include "../res/resource.h"
#include "Defines.h"
#include "Erros.h"
#include <ctype.h>

//----------------------------------------------------------------------//
//funcoes basicas

int configuraAmbiente();

int abreArquivo(char *nomeArq, char *tipoAbertura, FILE* arq);
int existeArquivo(char *nomeArq);
int fechaArquivo(FILE *arq);

HWND *guardaPegaHandle(HWND *handle, int tipo);

void editTextFloat(HWND hDlg, int ctrlID);
BOOL isFloat(char *str);

void formataCPF(HWND hwndEdit);
void formataTel(HWND hwndEdit);
void formataPlaca(HWND hwndEdit);
char *stristr (char *str, char *strSearch);
//----------------------------------------------------------------------//

#endif
