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
 * \brief Le os dados do formulario de oficina
 *
 * \param hwnd 				- Manipulador da janela
 * \return Manutencao * 	- Endereço de memória do tipo Proprietario contendo os dados lidos de um formulario
 *
 ***********************************************/
Oficina *leDadosOficForm(HWND hwnd)
{
    Oficina *aux;
    aux = (Oficina *)malloc(sizeof(Oficina));

    GetDlgItemText(hwnd, ID_EDIT_NOME_OFIC, aux->nome, TAM_NOME);
    GetDlgItemText(hwnd, ID_EDIT_CIDADE_OFIC, aux->endereco.cidade, TAM_CIDADE);
    GetDlgItemText(hwnd, ID_EDIT_ESTADO_OFIC, aux->endereco.estado, TAM_ESTADO);
    GetDlgItemText(hwnd, ID_EDIT_DESCRICAO_OFIC, aux->endereco.descricao, TAM_DESCRICAO);

    return aux;
}

/********************************************//**
 * \brief le valida e libera o botão de ação de entrar
 *
 * \param hwnd 				- Manipulador da janela
 * \return void
 *
 ***********************************************/
void validaLiberaFormOfic(HWND hwnd)
{
    int aux;

    if( Edit_GetTextLength(GetDlgItem(hwnd, ID_EDIT_NOME_OFIC)) > 0 &&
        Edit_GetTextLength(GetDlgItem(hwnd, ID_EDIT_CIDADE_OFIC)) > 0 &&
        Edit_GetTextLength(GetDlgItem(hwnd, ID_EDIT_DESCRICAO_OFIC)) > 0){
        Button_Enable(GetDlgItem(hwnd, ID_ENTRAR), TRUE);
    }else{
        Button_Enable(GetDlgItem(hwnd, ID_ENTRAR), FALSE);
    }

}


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
    static HWND hwndCombo;
	Oficina *ofic;
    FILE *oficinaInfo;

    switch (message){
        case WM_INITDIALOG:
        	Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_NOME_OFIC), TAM_NOME-1);
        	Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_CIDADE_OFIC), TAM_CIDADE-1);
        	Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_DESCRICAO_OFIC), TAM_DESCRICAO-1);
        	
        	hwndCombo = GetDlgItem(hwnd, ID_EDIT_ESTADO_OFIC);
        	
        	ComboBox_AddString(hwndCombo, "AC"); ComboBox_AddString(hwndCombo, "AL"); ComboBox_AddString(hwndCombo, "AP");
	        ComboBox_AddString(hwndCombo, "AM"); ComboBox_AddString(hwndCombo, "BA"); ComboBox_AddString(hwndCombo, "CE");
	        ComboBox_AddString(hwndCombo, "DF"); ComboBox_AddString(hwndCombo, "ES"); ComboBox_AddString(hwndCombo, "GO");
	        ComboBox_AddString(hwndCombo, "MA"); ComboBox_AddString(hwndCombo, "MT"); ComboBox_AddString(hwndCombo, "MS");
	        ComboBox_AddString(hwndCombo, "MG"); ComboBox_AddString(hwndCombo, "PA"); ComboBox_AddString(hwndCombo, "PB");
	        ComboBox_AddString(hwndCombo, "PR"); ComboBox_AddString(hwndCombo, "PE"); ComboBox_AddString(hwndCombo, "PI");
	        ComboBox_AddString(hwndCombo, "RJ"); ComboBox_AddString(hwndCombo, "RN"); ComboBox_AddString(hwndCombo, "RS");
	        ComboBox_AddString(hwndCombo, "RO"); ComboBox_AddString(hwndCombo, "RR"); ComboBox_AddString(hwndCombo, "SC");
	        ComboBox_AddString(hwndCombo, "SP"); ComboBox_AddString(hwndCombo, "SE"); ComboBox_AddString(hwndCombo, "TO");

        	ComboBox_SetCurSel(hwndCombo, 0);
        	
			return TRUE;
        break;
        
        case WM_COMMAND:

	        validaLiberaFormOfic(hwnd);

			switch(wParam){

				case ID_SAIR:
				    PostQuitMessage(0);
					break;

				case ID_ENTRAR:
					ofic = leDadosOficForm(hwnd);

		            oficinaInfo = fopen(ARQUIVO_DADOS_OFICINA, "wb");

		            if(oficinaInfo != NULL){
		            	if(fwrite(ofic, sizeof(Oficina), 1, oficinaInfo) != 1){
		            		MessageBox(hwnd, "Erro ao gerar dados de oficina!", "Erro!", MB_ICONERROR);
		            		if(win_trataErros(hwnd, fechaArquivo(oficinaInfo)) == 0) PostQuitMessage(0);
						}
						
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
