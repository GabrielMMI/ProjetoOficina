/********************************************//**
 * @file WinFunctions.h
 * @brief Contem todas as funções relacionadas com a programação
 *        da GUI em Win32.
 *
 * @bug Nao contem bugs conhecidos!
 * @author Matheus Bispo
 ***********************************************/

#ifndef WINFUNCTIONS_H_SECURE
#define WINFUNCTIONS_H_SECURE

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <commctrl.h>
#include "../res/resource.h"
#include "Manutencao.h"
#include "Proprietario.h"
#include "Veiculo.h"
#include "Win_FuncoesBasicas.h"
#include "Defines.h"
#include "Erros.h"


/********************************************//**
 * \brief Contem os dados da oficina
 ***********************************************/
typedef struct oficina{
	char nome[TAM_NOME];/**< Nome da oficina */
	char endereco[TAM_NOME];/**< Endereço resumido da oficina */
}Oficina;

//Dialog Inicial
LRESULT CALLBACK DlgIniProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgMainProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//Dialog Proprietario
BOOL CALLBACK tabPropPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

//Dialog Veiculo
BOOL CALLBACK tabVeicPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

//Dialog Manutenção
BOOL CALLBACK tabManutPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

#endif
