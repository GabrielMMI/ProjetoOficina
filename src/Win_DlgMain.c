/********************************************//**
 ** @file Win_DlgMain.c
 * @brief Contem a fun��o de controle da janela Principal.
 * @bug Nao contem bugs conhecidos!
 *
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

#include "../include/Win_Functions.h"

/********************************************//**
 * \brief Fun��o de controle da janela "Cr�ditos"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usu�rio
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informa��es adicionais sobre o comando ou n�o
 * \return Padr�o Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK creditosProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
//"jack-in-the-box.avi"
    switch(msg) {
        case WM_INITDIALOG:
            Animate_Open(GetDlgItem(hwnd, ID_GIF_CREDITOS), "res/matheus.avi");
            Animate_Play(GetDlgItem(hwnd, ID_GIF_CREDITOS), 0, -1, -1);

            Animate_Open(GetDlgItem(hwnd, ID_GIF_CREDITOS_2), "res/matheus.avi");
            Animate_Play(GetDlgItem(hwnd, ID_GIF_CREDITOS_2), 0, -1, -1);
            return TRUE;
        break;

        case WM_COMMAND:
        return TRUE;
        break;

        case WM_CLOSE:
            EndDialog(hwnd, 0);
        break;
    }
    return FALSE;
}


/********************************************//**
 * \brief Fun��o de controle da janela Principal
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usu�rio
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informa��es adicionais sobre o comando ou n�o
 * \return Padr�o Windows para janelas
 *
 ***********************************************/
LRESULT CALLBACK DlgMainProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE g_inst;
	static HWND hTab, tabProp, tabVeic, tabManut;
	TCITEM itemProp, itemVeic, itemManu;
	HFONT hFont;
	LRESULT count;
	FILE *oficinaInfo;
	static Oficina ofic;
	int sel;

    switch (message){

        case WM_INITDIALOG:

            tabProp = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_TABPROP), hwnd, tabPropPage);
            tabManut = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_TABMANUN), hwnd, tabManutPage);
            tabVeic = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_TABVEIC), hwnd, tabVeicPage);

            ShowWindow(tabProp, (sel == 0) ? SW_SHOW : SW_HIDE);
            ShowWindow(tabVeic, (sel == 1) ? SW_SHOW : SW_HIDE);
            ShowWindow(tabManut, (sel == 2) ? SW_SHOW : SW_HIDE);

            hFont = CreateFont (20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Microsoft Sans Serif");

            SendDlgItemMessage(hwnd, OFICIAL_NOME, WM_SETFONT, (WPARAM) (hFont), TRUE);

            SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(ICON_PROJETO)));

            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(ICON_PROJETO)));

            if(existeArquivo(ARQUIVO_DADOS_OFICINA)){
                oficinaInfo = fopen(ARQUIVO_DADOS_OFICINA, "r");
                if(oficinaInfo != NULL){
                    fgets(ofic.nome, TAM_NOME, oficinaInfo);
                    fgets(ofic.endereco, TAM_NOME, oficinaInfo);

                    fclose(oficinaInfo);

                    remove(ARQUIVO_DADOS_OFICINA);

                    SetDlgItemText(hwnd, OFICIAL_NOME, ofic.nome);
                    SetDlgItemText(hwnd, OFICIAL_ENDERECO, ofic.endereco);
                }else{
                    win_trataErros(hwnd, ERRO_ABRIR_ARQUIVO);
                }
            }

            hTab = GetDlgItem(hwnd, HTAB);

            itemProp.mask = TCIF_TEXT;
            itemProp.pszText = "Propriet�rios";

            count = SendMessage(hTab, TCM_GETITEMCOUNT, 0, 0);
            SendMessage(hTab, TCM_INSERTITEM, count,
                (LPARAM) (LPTCITEM) &itemProp);

            itemVeic.mask = TCIF_TEXT;
            itemVeic.pszText = "Veiculos";

            count = SendMessage(hTab, TCM_GETITEMCOUNT, 0, 0);
            SendMessage(hTab, TCM_INSERTITEM, count,
                (LPARAM) (LPTCITEM) &itemVeic);

            itemManu.mask = TCIF_TEXT;
            itemManu.pszText = "Manuten��o";

            count = SendMessage(hTab, TCM_GETITEMCOUNT, 0, 0);
            SendMessage(hTab, TCM_INSERTITEM, count,
                (LPARAM) (LPTCITEM) &itemManu);

            return TRUE;
        break;

        case WM_COMMAND:

            switch(LOWORD(wParam)){
                case ID_CREDITOS_BOTAO:
                    DialogBox(g_inst, MAKEINTRESOURCE(IDD_CREDITOS), hwnd, creditosProc);
                break;

            }

		break;

		case WM_NOTIFY: {
            switch (((LPNMHDR)lParam)->code) {
            case TCN_SELCHANGE:
                sel = TabCtrl_GetCurSel(hTab);
                ShowWindow(tabProp, (sel == 0) ? SW_SHOW : SW_HIDE);
                ShowWindow(tabVeic, (sel == 1) ? SW_SHOW : SW_HIDE);
                ShowWindow(tabManut, (sel == 2) ? SW_SHOW : SW_HIDE);
                break;
            }
        return TRUE;
            break;
        }

        case WM_CLOSE:
            PostQuitMessage(0);
        break;
    }

	return FALSE;
}


