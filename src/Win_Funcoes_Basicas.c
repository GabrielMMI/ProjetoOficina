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
#include "../include/Win_Funcoes_Basicas.h"

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
HWND *guardaPegaHandle(HWND *handle, int tipo)
{
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
int fechaArquivo(FILE *arq)
{
	int flag = FECHA_ARQUIVO_ERRO;

    if(fclose(arq) != EOF) flag = FECHA_ARQUIVO_SUCESSO;

    return flag;
}

void formataCPF(HWND hwndEdit)
{
    int tam = Edit_GetTextLength(hwndEdit);
    static int cont = 0;
    switch(tam){
        case 0:
            cont = 0;
        break;

        case 4:
            if(cont < 1){
                Edit_SetSel(hwndEdit, 3, 3);
                Edit_ReplaceSel(hwndEdit, ".");
                Edit_SetSel(hwndEdit, 6, 6);
                cont++;
            }else{
                Edit_SetSel(hwndEdit, 3, 4);
                Edit_ReplaceSel(hwndEdit, "");
                cont--;
            }
        break;

        case 8:
            if(cont < 2){
                Edit_SetSel(hwndEdit, 7, 7);
                Edit_ReplaceSel(hwndEdit, ".");
                Edit_SetSel(hwndEdit, 10, 10);
                cont++;
            }else{
                Edit_SetSel(hwndEdit, 7, 8);
                Edit_ReplaceSel(hwndEdit, "");
                cont--;
            }
        break;

        case 12:
            if(cont < 3){
                Edit_SetSel(hwndEdit, 11, 11);
                Edit_ReplaceSel(hwndEdit, "-");
                Edit_SetSel(hwndEdit, 13, 13);
                cont++;
            }else{
                Edit_SetSel(hwndEdit, 11, 12);
                Edit_ReplaceSel(hwndEdit, "");
                cont--;
            }
        break;
    }
}

void formataTel(HWND hwndEdit)
{
    int tam = Edit_GetTextLength(hwndEdit);
    static int cont;

    if(tam == 0){
        cont = 0;
    }

    if(tam == 5){
        if(cont < 1){
            Edit_SetSel(hwndEdit, 4, 4);
            Edit_ReplaceSel(hwndEdit, "-");
            Edit_SetSel(hwndEdit, 7, 7);
            cont++;
        }else{
            Edit_SetSel(hwndEdit, 4, 5);
            Edit_ReplaceSel(hwndEdit, "");
            cont--;
        }
    }
}

void formataPlaca(HWND hwndEdit)
{
    int tam = Edit_GetTextLength(hwndEdit);
    static int cont;

    if(tam == 0){
        cont = 0;
    }

    if(tam == 4){
        if(cont < 1){
            Edit_SetSel(hwndEdit, 3, 3);
            Edit_ReplaceSel(hwndEdit, "-");
            Edit_SetSel(hwndEdit, 8, 8);
            cont++;
        }else{
            Edit_SetSel(hwndEdit, 3, 4);
            Edit_ReplaceSel(hwndEdit, "");
            cont--;
        }
    }
}

BOOL isFloat(char *str)
{
    float f;
    int aux;

    for(aux = 0; aux < strlen(str); aux++){
        if(!isdigit(str[aux]) && str[aux] != '.') return FALSE;
    }

    if(sscanf(str, "%f", &f) != 1)
        return FALSE;
    return TRUE;
}

void editTextFloat(HWND hDlg, int ctrlID)
{
    HWND hEdit    = GetDlgItem(hDlg, ctrlID);
    int len    = GetWindowTextLength(hEdit)+1;
    char str[len];

    Edit_GetText(hEdit, str, len);

    if(!isFloat(str) && len != 1)
    {
        Edit_SetSel(hEdit, 0, len-1);
        Edit_ReplaceSel(hEdit, "");
        Edit_SetSel(hEdit, 0, 0);
        MessageBeep(MB_CUR_MAX);

    }
}

void formataFloat(HWND hwndEdit)
{
    int tam = Edit_GetTextLength(hwndEdit);
    static int cont;

    if(tam == 0){
        cont = 0;
    }

    if(tam == 2){
        if(cont < 1){
            Edit_SetSel(hwndEdit, 0, 0);
            Edit_ReplaceSel(hwndEdit, ".");
            Edit_SetSel(hwndEdit, 3, 3);
            cont++;
        }else{
            Edit_SetSel(hwndEdit, 0, 1);
            Edit_ReplaceSel(hwndEdit, "");
            cont--;
        }
    }
}
