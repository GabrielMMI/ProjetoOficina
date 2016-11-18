/********************************************//**
 * @file Win_Dlg_Veic.h
 * @brief Contem os cabecalhos de todas as
 *        funcoes existentes na tab de Veiculos
 * @bug Nao contem bugs conhecidos!
 *
 *@author Matheus Bispo
 *@author Gabriel Messias
 ***********************************************/

#ifndef H_DLG_VEIC_SECURE
#define H_DLG_VEIC_SECURE

#include "Win_Funcoes_Basicas.h"
#include "Veiculo.h"

Veiculo *leDadosVeicForm(HWND hwnd);

void atualizaListaManutVeic(HWND hwndList, char *placa);
void atualizaListaPropVeic(HWND hwndList, char *placa);
void atualizaListaVeic(HWND hwndList, char *placa);
void inicializaListVeic(HWND hwndList);

void inicializaFormVeic(HWND hwnd);
void validaLiberaFormVeic(HWND hwnd);
void preencheFormVeic(HWND hwndForm, Veiculo *veic);

BOOL CALLBACK formDadosVeicBox(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK formAddVeic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK formAlterarVeic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK formAlterarVeicBox(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK formExcluirVeic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK formExcluirVeicBox(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK formMostrarPropManut(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK tabVeicPage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // H_DLG_VEIC_SECURE
