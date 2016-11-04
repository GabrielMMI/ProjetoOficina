/********************************************//**
 ** @file Win_Dlg_Inicial.c
 * @brief Implementa todas as funções de Win_Dlg_Inicial.h
 *
 *
 * @bug Nenhum problema conhecido!
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

#include "../include/Win_Dlg_Inicial.h"

/********************************************//**
 * \brief Funcao de controle da caixa de dialogo inicial
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuario
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/
LRESULT CALLBACK DlgIniProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND editNome, editEnder;
	Oficina ofic;
    FILE *oficinaInfo;

    switch (message){
        case WM_INITDIALOG:
            editNome = GetDlgItem(hwnd, OFIC_NOME);
			editEnder = GetDlgItem(hwnd, OFIC_ENDER);

			SendMessage(editNome, EM_SETLIMITTEXT, TAM_NOME, 0);
			SendMessage(editEnder, EM_SETLIMITTEXT, TAM_NOME, 0);
			return TRUE;
        break;
        case WM_COMMAND:

	        if(GetWindowTextLength(editNome) != 0 && GetWindowTextLength(editEnder) != 0){
	            EnableWindow(GetDlgItem(hwnd,ID_Entrar),TRUE);
	        }else{
	        	EnableWindow(GetDlgItem(hwnd,ID_Entrar),FALSE);
			}

			switch(wParam){

				case ID_Sair:
				    PostQuitMessage(0);
					break;

				case ID_Entrar:

					GetWindowText(editNome, ofic.nome, TAM_NOME);

					GetWindowText(editEnder, ofic.endereco, TAM_NOME);

		            oficinaInfo = fopen(ARQUIVO_DADOS_OFICINA, "w");

		            if(oficinaInfo != NULL){
		                fprintf(oficinaInfo, "%s\n",ofic.nome);
		                fprintf(oficinaInfo, "%s\n",ofic.endereco);

		                if(win_trataErros(hwnd, fechaArquivo(oficinaInfo)) == 0) EndDialog(hwnd, 0);
		            }else{
		                win_trataErros(hwnd, ERRO_ABRIR_ARQUIVO);
		            }
			}

			return TRUE;
		break;

        case WM_CLOSE:
            PostQuitMessage(0);
            return TRUE;
        break;
	}

	return FALSE;
}
