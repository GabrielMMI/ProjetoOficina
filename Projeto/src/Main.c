/********************************************//**
 ** @file Main.c
 * @brief Inicializa a janela inicial e cria os diretórios necessários.
 * @bug Nao contem bugs conhecidos!
 *
 ***********************************************/

#include "../include/Win_Dlg_Inicial.h"

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    InitCommonControls();

    int flag = 0;

    flag = configuraAmbiente();

    if(flag == FECHA_ARQUIVO_SUCESSO){
        DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgIniProc);
        return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC)DlgMainProc);
    }else{
        return flag;
    }
}
