/********************************************//**
 ** @file Win_Dlg_Veic.c
 * @brief Contem as funcoes de controle da tabPage Veiculo.
 * @bug Nao contem bugs conhecidos!
 *
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

#include "../include/Win_Dlg_Veic.h"
#include "../include/Win_Dlg_Manut.h"
#include "../include/Win_Dlg_Prop.h"

/********************************************//**
 * \brief Le os dados do formulario de veiculo
 *
 * \param hwnd 				- Manipulador da janela
 * \return Manutencao * 	- Endereco de memoria do tipo Veiculo contendo os dados lidos de um formulario
 *
 ***********************************************/
Veiculo *leDadosVeicForm(HWND hwnd)
{
    Veiculo *aux;
    aux = (Veiculo *)malloc(sizeof(Veiculo));

    GetDlgItemText(hwnd, ID_EDIT_MODELO_VEIC, aux->modelo, TAM_MODELO);
    GetDlgItemText(hwnd, ID_EDIT_FAB_VEIC, aux->fabricante, TAM_FABRICANTE);
    GetDlgItemText(hwnd, ID_EDIT_CHASSI_VEIC, aux->chassi, TAM_CHASSI);
    GetDlgItemText(hwnd, ID_EDIT_ANO_VEIC, aux->ano, TAM_ANO);
    GetDlgItemText(hwnd, ID_EDIT_PLACA_VEIC, aux->placa, TAM_PLACA);

    return aux;
}

/********************************************//**
 * \brief Atualiza a lista de manutencoes de acordo
 *        com a placa
 *
 * \param hwndList - Manipulador do ListControl
 * \param placa - A placa de um veiculo que esta na manutencao
 *
 * \return void
 *
 ***********************************************/
void atualizaListaManutVeic(HWND hwndList, char *placa)
{
    LVITEM lvItem;
    int cont = 0;
    Manutencao aux;
    char data[TAM_DATA];
    FILE *arq;

    SendMessage(hwndList,LVM_DELETEALLITEMS,0,0);
    if(existeArquivo(ARQUIVO_DADOS_MANUTENCAO) && strlen(placa) > 0){
        arq = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
        if(arq != NULL){
            while(fread(&aux, sizeof(Manutencao), 1, arq) == 1){
                if(strnicmp(aux.placa,placa,strlen(placa))==0){
                    lvItem.mask=LVIF_TEXT;
                    lvItem.cchTextMax = TAM_NOME;
                    lvItem.iItem=cont;
                    lvItem.iSubItem=0;
                    lvItem.pszText=aux.placa;

                    SendMessage(hwndList,LVM_INSERTITEM,cont,(LPARAM)&lvItem);
                    lvItem.iSubItem = 1;
                    lvItem.pszText = aux.cpf;

                    SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);
                    lvItem.iSubItem = 2;
                    sprintf(data, "%02d/%02d/%d", aux.data.dia, aux.data.mes, aux.data.ano);
                    lvItem.pszText = data;

                    SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);

                    cont++;
                }
            }

            if(win_trataErros(hwndList,fechaArquivo(arq)) != 0) return;
        }else{
            if(win_trataErros(hwndList, ERRO_ABRIR_ARQUIVO) != 0) return;
        }
    }
}

/********************************************//**
 * \brief Atualiza a lista de proprietarios de acordo
 *        com a placa
 *
 * \param hwndList - Manipulador do ListControl
 * \param placa - A placa de um veiculo que esta na manutencao
 *
 * \return void
 *
 ***********************************************/
void atualizaListaPropVeic(HWND hwndList, char *placa)
{
    LVITEM lvItem;
    int cont = 0, qtManut, cont2;
    Manutencao aux, *manutAux;
    Proprietario propAux;
    char telefone[TAM_TEL+TAM_DDD];
    FILE *arq;
    LVFINDINFO info;

    SendMessage(hwndList,LVM_DELETEALLITEMS,0,0);

    if(existeArquivo(ARQUIVO_DADOS_MANUTENCAO) && strlen(placa) > 0){
        arq = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
        if(arq != NULL){
            while(fread(&aux, sizeof(Manutencao), 1, arq) == 1){
                if(strnicmp(aux.placa,placa,strlen(placa))==0){
                	pegaProprietario(aux.cpf, &propAux);

					info.flags = LVFI_STRING;
		            info.psz = propAux.nome;

                	if(ListView_FindItem(hwndList, -1, &info) == -1){

		                lvItem.mask=LVIF_TEXT;
		                lvItem.cchTextMax = TAM_NOME;
		                lvItem.iItem=cont;
		                lvItem.iSubItem=0;
		                lvItem.pszText=propAux.nome;

		                SendMessage(hwndList,LVM_INSERTITEM,cont,(LPARAM)&lvItem);
		                lvItem.iSubItem = 1;
		                lvItem.pszText = propAux.cpf;

		                SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);
		                lvItem.iSubItem = 2;
		                sprintf(telefone, "(%s)%s", propAux.telefone.ddd, propAux.telefone.telefone);
		                lvItem.pszText = telefone;

		                SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);

		                cont++;
	            	}
                }
            }

            if(win_trataErros(hwndList,fechaArquivo(arq)) != 0) return;
        }else{
            if(win_trataErros(hwndList, ERRO_ABRIR_ARQUIVO) != 0) return;
        }
    }
}


/********************************************//**
 * \brief Atualiza uma lista de veiculos de
 *        acordo com uma placa
 * \param hwndList 	- Manipulador de uma ListView Control
 * \param placa  	- Placa que ser� utilizada como filtro na pesquisa
 * \return void
 *
 ***********************************************/
void atualizaListaVeic(HWND hwndList, char *placa)
{

    LVITEM lvItem;
    int cont = 0;
    Veiculo aux;
    FILE *arq;
    SendMessage(hwndList,LVM_DELETEALLITEMS,0,0);

    if(strlen(placa) != 0){
        if(existeArquivo(ARQUIVO_DADOS_VEICULO)){
            arq = fopen(ARQUIVO_DADOS_VEICULO, "rb");
            if(arq != NULL){
                while(fread(&aux, sizeof(Veiculo), 1, arq) == 1){
                    if(strnicmp(aux.placa, placa, strlen(placa)) == 0){
                        lvItem.mask=LVIF_TEXT;
                        lvItem.cchTextMax = TAM_MODELO;
                        lvItem.iItem=cont;
                        lvItem.iSubItem=0;
                        lvItem.pszText=aux.modelo;

                        SendMessage(hwndList,LVM_INSERTITEM,cont,(LPARAM)&lvItem);

                        lvItem.iSubItem = 1;
                        lvItem.pszText = aux.placa;

                        SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);

                        lvItem.iSubItem = 2;
                        lvItem.pszText = aux.chassi;

                        SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);

                        cont++;
                    }
                }
                if(win_trataErros(hwndList, fechaArquivo(arq)) == 1) return;
            }else{
                if(win_trataErros(hwndList, ERRO_ABRIR_ARQUIVO) == 1) return;
            }
        }
    }
}

/********************************************//**
 * \brief Inicializa um formul�rio de Veiculo
 *
 * \param hwnd - Manipulador de uma ListView Control
 * \return void
 *
 ***********************************************/
void inicializaFormVeic(HWND hwnd){
    SendMessage(GetDlgItem(hwnd, ID_EDIT_PLACA_VEIC), EM_LIMITTEXT, TAM_PLACA-1, 0);
    SendMessage(GetDlgItem(hwnd, ID_EDIT_MODELO_VEIC), EM_LIMITTEXT, TAM_MODELO-1, 0);
    SendMessage(GetDlgItem(hwnd, ID_EDIT_FAB_VEIC), EM_LIMITTEXT, TAM_FABRICANTE-1, 0);
    SendMessage(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC), EM_LIMITTEXT, TAM_CHASSI-1, 0);
    SendMessage(GetDlgItem(hwnd, ID_EDIT_ANO_VEIC), EM_LIMITTEXT, TAM_ANO-1, 0);

    EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), FALSE);
}

/********************************************//**
 * \brief le valida e libera o botao de acao de um veiculo
 *
 * \param hwnd 				- Manipulador da janela
 * \return void
 *
 ***********************************************/
void validaLiberaFormVeic(HWND hwnd){
    char placa[TAM_PLACA];
    HWND editPlaca;

    GetDlgItemText(hwnd, ID_EDIT_PLACA_VEIC, placa, TAM_PLACA);
    formataPlaca(GetDlgItem(hwnd, ID_EDIT_PLACA_VEIC));

    if( GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_MODELO_VEIC)) > 0 &&
        validaPlaca(placa) == PLACA_VALIDA &&
        GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_FAB_VEIC)) > 0 &&
        GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_ANO_VEIC)) == TAM_ANO -1 &&
        GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC)) == TAM_CHASSI-1){
        SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "");
        EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_VEIC), TRUE);
    }else{
        SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "");
        EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_VEIC), FALSE);
    }

    if(validaPlaca(placa) == PLACA_INVALIDA && strlen(placa) == TAM_PLACA-1) SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "A placa inserida a invalida!");
    if(GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC)) < TAM_CHASSI-1 && GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC)) > 0) SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "O chassi inserido e invalido!");

}

/********************************************//**
 * \brief Preenche um formulario de Veiculo
 *
 * \param hwnd	- Manipulador da janela
 * \param veic		- Endereco de memoria de uma struct do tipo Veiculo
 *
 * \return void
 *
 ***********************************************/
void preencheFormVeic(HWND hwnd, Veiculo *veic){
    SetDlgItemText(hwnd, ID_EDIT_PLACA_VEIC, veic->placa);
    SetDlgItemText(hwnd, ID_EDIT_MODELO_VEIC, veic->modelo);
    SetDlgItemText(hwnd, ID_EDIT_FAB_VEIC, veic->fabricante);
    SetDlgItemText(hwnd, ID_EDIT_CHASSI_VEIC, veic->chassi);
    SetDlgItemText(hwnd, ID_EDIT_ANO_VEIC, veic->ano);
}

/********************************************//**
 * \brief Funcao de controle do janela "Pesquisar Veiculos"
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
BOOL CALLBACK formDadosVeicBox(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    static Veiculo *auxAntigo;
    int erro;
    PCOPYDATASTRUCT pcds;

    switch(message) {
        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lParam;
			if(pcds->dwData == 0){
				auxAntigo = (Veiculo *)(pcds->lpData);
                preencheFormVeic(hwnd, auxAntigo);
            }
        return TRUE;
        break;

        case WM_CLOSE:
            EndDialog(hwnd, 0);
            return TRUE;
        break;
    }

    return FALSE;
}

/********************************************//**
 * \brief Funcao de controle do janela "Adicionar Veiculo"
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
BOOL CALLBACK formAddVeic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int erro;
    static Veiculo *veic;

    switch(message) {
        case WM_INITDIALOG:
            inicializaFormVeic(hwnd);
        return TRUE;
        break;

        case WM_COMMAND:

            validaLiberaFormVeic(hwnd);

            switch(wParam){
            case ID_BOTAO_ACAO_VEIC:
                    veic = leDadosVeicForm(hwnd);

                    erro = incluiVeiculo(*veic);

                    win_trataErros(hwnd, erro);

                    if(erro == VEIC_INSERIR_SUCESSO) EndDialog(hwnd, 0);

            break;
            }

            return TRUE;
            break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Nomeia as colunas da lista de Ve�culos
 *
 * \param hwndList HWND
 * \return void
 *
 ***********************************************/
void inicializaListVeic(HWND hwndList)
{
	ListView_SetExtendedListViewStyle(hwndList, LVS_REPORT | LVS_EX_FULLROWSELECT);
    LVCOLUMN lvCol;

    lvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
    lvCol.cchTextMax = TAM_MODELO;
    lvCol.pszText="Modelo        ";
    SendMessage(hwndList ,LVM_INSERTCOLUMN, 0, (LPARAM)&lvCol);

    lvCol.pszText="Placa               ";
    lvCol.cchTextMax = TAM_PLACA;
    SendMessage(hwndList ,LVM_INSERTCOLUMN, 1, (LPARAM)&lvCol);

    lvCol.pszText="Chassi";
    lvCol.cchTextMax = TAM_CHASSI;
    SendMessage(hwndList ,LVM_INSERTCOLUMN, 2, (LPARAM)&lvCol);

    ListView_SetColumnWidth(hwndList, 0, LVSCW_AUTOSIZE_USEHEADER);
    ListView_SetColumnWidth(hwndList, 1, LVSCW_AUTOSIZE_USEHEADER);
    ListView_SetColumnWidth(hwndList, 2, LVSCW_AUTOSIZE_USEHEADER);
}

/********************************************//**
 * \brief Funcao de controle do Dialogo "Alterar Veiculo"
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
BOOL CALLBACK formAlterarVeicBox(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static Veiculo *auxAntigo;
    int erro;
    PCOPYDATASTRUCT pcds;

    switch(message) {
        case WM_INITDIALOG:
            inicializaFormVeic(hwnd);
        break;

        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lParam;
			if(pcds->dwData == 0){
				    auxAntigo = (Veiculo *)(pcds->lpData);

                    preencheFormVeic(hwnd, auxAntigo);
			}
        return TRUE;
        break;

        case WM_COMMAND:

            switch(wParam){
            case ID_BOTAO_ACAO_VEIC:
                    auxAntigo = leDadosVeicForm(hwnd);
                    erro = alteraVeiculo(*auxAntigo, auxAntigo->placa);
                    free(auxAntigo);
                    win_trataErros(hwnd, erro);
                    EndDialog(hwnd, 0);
            break;

            case ID_BOTAO_CANCELAR_VEIC:
                EndDialog(hwnd, 0);
            break;
            }

        return TRUE;
        break;
    }
    return FALSE;
}


/********************************************//**
 * \brief Funcao de controle do janela "Alterar Veiculo"
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
BOOL CALLBACK formAlterarVeic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    char placa[TAM_PLACA];
    static HWND hwndList;
    int iSelect;
    static HINSTANCE g_inst;
    HWND formAlterar;
    static Veiculo *auxEnvio;
    COPYDATASTRUCT CDS;

    switch(message) {
        case WM_INITDIALOG:
        hwndList = GetDlgItem(hwnd, ID_VEIC_LIST);
        Edit_LimitText(GetDlgItem(hwnd, ID_VEIC_EDIT_BUSCA_PLACA), TAM_PLACA-1);

        inicializaListVeic(hwndList);
        return TRUE;
        break;

        case WM_COMMAND:
                formataPlaca(GetDlgItem(hwnd, ID_VEIC_EDIT_BUSCA_PLACA));

                iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);

                if(HIWORD(wParam) == EN_CHANGE){

                    GetDlgItemText(hwnd, ID_VEIC_EDIT_BUSCA_PLACA, placa, TAM_PLACA);
                    atualizaListaVeic(hwndList, placa);

                }

                switch(LOWORD(wParam)){
                    case ID_BOTAO_ALTERAR_VEIC:
						if(iSelect == -1){
							MessageBox(hwnd, "Nenhum veiculo foi selecionado!", "Erro", MB_OK|MB_ICONINFORMATION);
						}else{

	                        formAlterar = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_ALTERAR_FORM), hwnd, (DLGPROC)formAlterarVeicBox);

	                        ListView_GetItemText(hwndList, iSelect, 1, placa, TAM_PLACA);

	                        auxEnvio = (Veiculo *)malloc(sizeof(Veiculo));
	                        pegaVeiculo(placa, auxEnvio);

	                        CDS.dwData = 0;
	                        CDS.cbData = sizeof(Veiculo);
	                        CDS.lpData = auxEnvio;

	                        SendMessage(formAlterar, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
	                        SetDlgItemText(hwnd, ID_VEIC_EDIT_BUSCA_PLACA, "");
                   		}
                    break;
                }
            return TRUE;
            break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Funcao de controle do Dialogo "Excluir Veiculo"
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
BOOL CALLBACK formExcluirVeicBox(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static Veiculo *auxAntigo;
    int erro;
    PCOPYDATASTRUCT pcds;

    switch(message) {
        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lParam;
			if(pcds->dwData == 0){
				auxAntigo = (Veiculo *)(pcds->lpData);
                preencheFormVeic(hwnd, auxAntigo);
            }
        return TRUE;
        break;

        case WM_COMMAND:

            switch(wParam){
            case ID_BOTAO_ACAO_VEIC:
                    erro = excluiVeiculo(auxAntigo->placa);
                    free(auxAntigo);
                    win_trataErros(hwnd, erro);
                    EndDialog(hwnd, 0);
            break;

            case ID_BOTAO_CANCELAR_VEIC:
                EndDialog(hwnd, 0);
            break;
            }

        return TRUE;
        break;
    }
    return FALSE;
}


/********************************************//**
 * \brief Funcao de controle do janela "Excluir Veiculo"
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
BOOL CALLBACK formExcluirVeic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    char placa[TAM_PLACA];
    static HWND hwndList;
    int iSelect;
    static HINSTANCE g_inst;
    HWND formAlterar;
    Veiculo *auxEnvio;
    COPYDATASTRUCT CDS;

    switch(message) {
        case WM_INITDIALOG:
        hwndList = GetDlgItem(hwnd, ID_VEIC_LIST);
        SendMessage(GetDlgItem(hwnd, ID_VEIC_EDIT_BUSCA_PLACA), EM_LIMITTEXT, TAM_PLACA-1, 0);

        inicializaListVeic(hwndList);
        return TRUE;
        break;

        case WM_COMMAND:
                formataPlaca(GetDlgItem(hwnd, ID_VEIC_EDIT_BUSCA_PLACA));

                iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);

                if(HIWORD(wParam) == EN_CHANGE){

                    GetDlgItemText(hwnd, ID_VEIC_EDIT_BUSCA_PLACA, placa, TAM_PLACA);
                    atualizaListaVeic(hwndList, placa);

                }

                switch(LOWORD(wParam)){
                    case ID_VEIC_EXCLUIR_BOTAO:
                	if(iSelect == -1){
                    	MessageBox(hwnd, "Nenhum veiculo foi selecionado!", "Erro", MB_OK|MB_ICONINFORMATION);
                	}else{
                        formAlterar = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_EXCLUIR_FORM), hwnd, (DLGPROC)formExcluirVeicBox);

                        ListView_GetItemText(hwndList, iSelect, 1, placa, TAM_PLACA);

                        auxEnvio = (Veiculo *)malloc(sizeof(Veiculo));
                        pegaVeiculo(placa, auxEnvio);

                        CDS.dwData = 0;
                        CDS.cbData = sizeof(Veiculo);
                        CDS.lpData = auxEnvio;

                        SendMessage(formAlterar, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
                        SetDlgItemText(hwnd, ID_VEIC_EDIT_BUSCA_PLACA, "");
                    }
                    break;
                }
            return TRUE;
            break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Funcao de controle do janela "Propriet�rios e manutencoes de um Veiculo"
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
BOOL CALLBACK formMostrarPropManut(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    char placa[TAM_PLACA],dataAux[10],cpf[TAM_CPF];
    Data data;
    static HWND hwndListProp,hwndListManut;
    int iSelectProp,iSelectManut;
    static HINSTANCE g_inst;
    HWND formAlterarProp,formAlterarManut;
    Manutencao *manutAux;
    Proprietario *propAux;
    COPYDATASTRUCT CDS;

    switch(message) {
        case WM_INITDIALOG:
        hwndListProp = GetDlgItem(hwnd, ID_VEIC_PROP_LIST);
        hwndListManut = GetDlgItem(hwnd, ID_VEIC_MANUT_LIST);
        SendMessage(GetDlgItem(hwnd, ID_VEIC_EDIT_BUSCA_PLACA), EM_LIMITTEXT, TAM_PLACA-1, 0);

        inicializaListProp(hwndListProp);
        inicializaListManut(hwndListManut);
        return TRUE;
        break;
        case WM_COMMAND:

                iSelectProp = ListView_GetNextItem(hwndListProp, -1,LVNI_SELECTED | LVNI_FOCUSED);
                iSelectManut = ListView_GetNextItem(hwndListManut, -1,LVNI_SELECTED | LVNI_FOCUSED);

                if(HIWORD(wParam) == EN_CHANGE){

                	formataPlaca(GetDlgItem(hwnd, ID_VEIC_EDIT_BUSCA_PLACA));
                    GetDlgItemText(hwnd, ID_VEIC_EDIT_BUSCA_PLACA, placa, TAM_PLACA);
                    atualizaListaManutVeic(hwndListManut,placa);
                    atualizaListaPropVeic(hwndListProp,placa);
                }

                switch(LOWORD(wParam)){
                    case ID_VEIC_VER_PROP_BOTAO:
                		if(iSelectProp == -1){
                    		MessageBox(hwnd, "Nenhum proprietario foi selecionado!", "Erro", MB_OK|MB_ICONINFORMATION);
                		}else{
	                        formAlterarProp = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_PESQUISAR_FORM), hwnd, (DLGPROC)formPesquisarPropBox);

	                        propAux = (Proprietario *)malloc(sizeof(Proprietario));

	                        ListView_GetItemText(hwndListProp, iSelectProp, 1, cpf, TAM_CPF);
	                        pegaProprietario(cpf,propAux);

	                        CDS.dwData = 0;
	                        CDS.cbData = sizeof(Proprietario);
	                        CDS.lpData = propAux;
	                        SendMessage(formAlterarProp, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
	                        iSelectProp = -1;
                    	}
                    break;

                    case ID_VEIC_VER_MANUT_BOTAO:
                    	if(iSelectManut == -1){
                    		MessageBox(hwnd, "Nenhuma manutencao foi selecionada!", "Erro", MB_OK|MB_ICONINFORMATION);
                		}else{
	                        formAlterarManut = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_MANUT_DADOS_FORM), hwnd, (DLGPROC)formDadosManutBox);

	                        manutAux = (Manutencao *)malloc(sizeof(Manutencao));

	                        ListView_GetItemText(hwndListManut, iSelectManut, 0, placa, TAM_PLACA);
	                        ListView_GetItemText(hwndListManut, iSelectManut, 1, cpf, TAM_CPF);
	                        ListView_GetItemText(hwndListManut, iSelectManut, 2, dataAux, TAM_DATA);

	                        converteStringData(dataAux,&data);

	                        pegaManutencao(placa,cpf,data,manutAux);
	                        CDS.dwData = 0;
	                        CDS.cbData = sizeof(Manutencao);
	                        CDS.lpData = manutAux;

	                        SendMessage(formAlterarManut, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
	                        iSelectManut = -1;
                    	}
                        break;

                    case ID_VEIC_LIMPAR_BOTAO:
                    	SetDlgItemText(hwnd, ID_VEIC_EDIT_BUSCA_PLACA, "");
                    	break;
                }
            return TRUE;
            break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Funcao de controle da tabPage "Ve�culo"
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
BOOL CALLBACK tabVeicPage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND formVeicDlg, *formAux;
    static HINSTANCE g_inst;

    switch(message) {

    case WM_COMMAND:

        formAux = guardaPegaHandle(NULL, 1);
        if(formAux != NULL) EndDialog(*formAux, 0);

        switch (wParam) {
        case ID_BOTAO_ADD_VEIC:
            formVeicDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_ADD_FORM), GetParent(hwnd), (DLGPROC)formAddVeic);
            break;

        case ID_BOTAO_ALTERAR_VEIC:
            formVeicDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_ALTERAR), GetParent(hwnd), (DLGPROC)formAlterarVeic);
            break;

        case ID_BOTAO_EXCLUIR_VEIC:
            formVeicDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_EXCLUIR), GetParent(hwnd), (DLGPROC)formExcluirVeic);
            break;

        case ID_BOTAO_PROP_MANUT_VEIC:
        	formVeicDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_APRESENTA_MANUT_PROP), GetParent(hwnd), (DLGPROC)formMostrarPropManut);
        	break;
        }

        guardaPegaHandle(&formVeicDlg, 0);
        return TRUE;
        break;
    }

    return FALSE;
}
