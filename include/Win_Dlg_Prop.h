#ifndef H_DLG_PROP_SECURE
#define H_DLG_PROP_SECURE

#include "Win_Funcoes_Basicas.h"

Proprietario *leDadosPropForm(HWND hwnd);

void inicializaListProp(HWND hwndList);
void atualizaListaProp(HWND hwndList, char *cpf, char *nome);

void validaLiberaFormProp(HWND hwnd);
void inicializaFormProp(HWND hwnd);
void preencheFormProp(HWND hwndForm, Proprietario *prop);

BOOL CALLBACK formAddProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formAlterarProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formAlterarPropBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formExcluirProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formExcluirPropBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK tabPropPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

#endif // H_DLG_PROP_SECURE
