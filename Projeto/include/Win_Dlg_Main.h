/********************************************//**
 * @file Win_Dlg_Main.h
 * @brief Contem todas as fun��es relacionadas ao
 *		  Dialog inicial
 *
 * @bug Nao contem bugs conhecidos!
 *
 *@author Matheus Bispo
 *@author Gabriel Messias
 ***********************************************/

#ifndef WINFUNCTIONS_H_SECURE
#define WINFUNCTIONS_H_SECURE

#include "Win_Funcoes_Basicas.h"
#include "Win_Dlg_Prop.h"
#include "Win_Dlg_Veic.h"
#include "Win_Dlg_Manut.h"

/********************************************//**
 * \brief Contem os dados da oficina
 ***********************************************/
typedef struct oficina{
	char nome[TAM_NOME];/**< Nome da oficina */
	Endereco endereco;/**< Endere�o da oficina */
}Oficina;


//--------------------------------------------------------------------------------------
//Dialog Principal
LRESULT CALLBACK DlgMainProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK mostraDadosProp(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK mostraDadosVeic(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK mostraDadosManut(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

BOOL CALLBACK tabPropPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK tabVeicPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK tabManutPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

#endif
