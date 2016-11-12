/********************************************//**
 * @file Win_Dlg_Prop.h
 * @brief Contem os cabe�alhos de todas as
 *        funcoes existentes na tab de Propriet�rios
 * @bug Nao contem bugs conhecidos!
 *
 *@author Matheus Bispo
 *@author Gabriel Messias
 ***********************************************/

#ifndef H_DLG_PROP_SECURE
#define H_DLG_PROP_SECURE

#include "Win_Funcoes_Basicas.h"
#include "Win_Dlg_Veic.h"
#include "Proprietario.h"
#include "Arvore_Prop.h"


Proprietario *leDadosPropForm(HWND hwnd);

void inicializaListProp(HWND hwndList);
void atualizaListaProp(HWND hwndList, char *cpf, char *nome);
void atualizaListaVeicProp(HWND hwndList, char *placa);

void atualizaListaArvProp(Arvore *a, HWND list);

void validaLiberaFormProp(HWND hwnd);
void inicializaFormProp(HWND hwnd);
void preencheFormProp(HWND hwndForm, Proprietario *prop);

BOOL CALLBACK formPesquisarPropBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formPesquisarProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formAddProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formAlterarProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formAlterarPropBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formExcluirProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formExcluirPropBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK formMostraVeicProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK tabPropPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

#endif // H_DLG_PROP_SECURE
