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

#include "Win_Funcoes_Basicas.h"

/********************************************//**
 * \brief Contem os dados da oficina
 ***********************************************/
typedef struct oficina{
	char nome[TAM_NOME];/**< Nome da oficina */
	char endereco[TAM_NOME];/**< Endereço resumido da oficina */
}Oficina;

LRESULT CALLBACK DlgMainProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK tabPropPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK tabVeicPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK tabManutPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

#endif
