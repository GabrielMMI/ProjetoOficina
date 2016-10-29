#include "Win_Funcoes_Basicas.h"

Manutencao *leDadosManutForm(HWND hwnd);

void atualizaListaManut(HWND hwndList, Data dataI, Data dataF);
void inicializaListManut(HWND hwndList);

void validaLiberaFormManut(HWND hwnd);
void inicializaFormManut(HWND hwnd);
void preencheFormManut(HWND hwndForm, Manutencao *manut);

BOOL CALLBACK formPesquisarManut(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formDadosManutBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formAddManut(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK tabManutPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
