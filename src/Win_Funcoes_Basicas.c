/********************************************//**
 ** @file Win_Funcoes_Basicas.c
 * @brief Contem as funções básicas utilizadas no programa.
 * @bug Nao contem bugs conhecidos!
 *
 * @author Matheus Bispo
 * @author Gabriel Messias
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
 * \param handle - um endereço de memória de um handle
 * \param tipo   - 1 :: Caso queria guardar
 *				 - 2 :: Caso queira recuperar
 * \return HWND* - Endereço de memória de um handle
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

/********************************************//**
 * \brief formata um CPF em um EditControl em tempo real
 *
 * \param hwndEdit - O handle de um EditControl
 *
 * \return FECHA_ARQUIVO_SUCESSO - Sucesso ao fechar arquivo
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar arquivo
 *
 ***********************************************/
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

/********************************************//**
 * \brief formata um telefone em um EditControl em tempo real
 *
 * \param hwndEdit - O handle de um EditControl
 *
 * \return FECHA_ARQUIVO_SUCESSO - Sucesso ao fechar arquivo
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar arquivo
 *
 ***********************************************/
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

/********************************************//**
 * \brief formata uma placa em um EditControl em tempo real
 *
 * \param hwndEdit - O handle de um EditControl
 *
 * \return FECHA_ARQUIVO_SUCESSO - Sucesso ao fechar arquivo
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar arquivo
 *
 ***********************************************/
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

/********************************************//**
 * \brief Verifica se uma string pode ser transformada em um float
 *
 * \param str 	- O endereço de memória de uma string
 *
 * \return TRUE 	- Pode ser transformada em float
 * \return FALSE 	- Não pode ser transformada em float
 *
 ***********************************************/
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

/********************************************//**
 * \brief Configura um EditControl de tal modo que ele só aceite número inteiros ou float
 *
 * \param hDlg 		- O handle do dialogo onde se encontra o EditCOntrol
 * \param ctrlID 	- O ID do EditControl
 *
 * \return void
 *
 ***********************************************/
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

/********************************************//**
 * \brief Pesquisa a ocorrência de uma substring em um string, sem case sensitive
 *
 * \param str 		- O endereço de memória de uma string
 * \param strSearch	- O endereço de memória de uma string
 *
 * \return void
 *
 ***********************************************/
char *stristr (char *str, char *strSearch) {
    char *sors, *subs, *res = NULL;
    if ((sors = strdup (str)) != NULL) {
        if ((subs = strdup (strSearch)) != NULL) {
            res = strstr (strlwr (sors), strlwr (subs));
            if (res != NULL)
                res = str + (res - sors);
            free (subs);
        }
        free (sors);
    }
    return res;
}
