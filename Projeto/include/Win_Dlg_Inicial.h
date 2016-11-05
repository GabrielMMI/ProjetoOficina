/********************************************//**
 * @file Win_Dlg_Inicial.h
 * @brief Contem os cabeçalhos de todas as
 *        funcoes existentes no Dialog inicial
 * @bug Nao contem bugs conhecidos!
 *
 *@author Matheus Bispo
 *@author Gabriel Messias
 ***********************************************/

#ifndef H_DLG_INI_SECURE
#define H_DLG_INI_SECURE

#include "Win_Funcoes_Basicas.h"
#include "Win_Dlg_main.h"


//Dialog Inicial
Oficina *leDadosOficForm(HWND hwnd);
void validaLiberaFormOfic(HWND hwnd);
LRESULT CALLBACK DlgIniProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif
