/********************************************//**
 ** @file main.c
 * @brief Inicializa a janela inicial e cria os diretórios necessários.
 * @bug Nao contem bugs conhecidos!
 *
 * @author Matheus Bispo
 *
 ***********************************************/

#include "../include/Proprietario.h"
#include "../include/Manutencao.h"
#include "../include/Veiculo.h"
#include "../include/Win_Functions.h"
#include <dirent.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    InitCommonControls();
    FILE *dbprop, *dbveic, *dbmanut;
    mkdir("database");
    dbprop = fopen(ARQUIVO_DADOS_PROPRIETARIO, "ab");
    dbveic = fopen(ARQUIVO_DADOS_VEICULO, "ab");
    dbmanut = fopen(ARQUIVO_DADOS_MANUTENCAO, "ab");
    if( dbprop != NULL && dbveic != NULL && dbmanut != NULL){
        fclose(dbprop);
        fclose(dbveic);
        fclose(dbmanut);
        DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgIniProc);
        return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC)DlgMainProc);
    }else{
        return 1;
    }
}


