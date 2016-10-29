#ifndef H_DLG_VEIC_SECURE
#define H_DLG_VEIC_SECURE

#include "Win_Funcoes_Basicas.h"

Veiculo *leDadosVeicForm(HWND hwnd);

void atualizaListaVeic(HWND hwndList, char *placa);
void inicializaListVeic(HWND hwndList);

void inicializaFormVeic(HWND hwnd);
void validaLiberaFormVeic(HWND hwnd);
void preencheFormVeic(HWND hwndForm, Veiculo *veic);

BOOL CALLBACK formAddVeic(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formAlterarVeic(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formAlterarVeicBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formExcluirVeic(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formExcluirVeicBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK tabVeicPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

#endif // H_DLG_VEIC_SECURE
