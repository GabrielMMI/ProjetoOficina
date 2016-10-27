/********************************************//**
 ** @file Win_VeicDlg.c
 * @brief Contem as funções de controle da tabPage Veiculo.
 * @bug Nao contem bugs conhecidos!
 *
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

#include "../include/Win_Functions.h"

/********************************************//**
 * \brief Le os dados do formulario e retorna um
 *        ponteiro do tipo Veiculo
 * \param hwnd HWND
 * \return Veiculo*
 *
 ***********************************************/
Veiculo *leDadosVeicForm(HWND hwnd){
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
 * \brief Atualiza uma lista de veiculos de
 *        acordo com um determinado filtro
 * \param hwndList HWND
 * \param filtro char*
 * \return void
 *
 ***********************************************/
void atualizaListaVeic(HWND hwndList, char *filtro){

    LVITEM lvItem;
    int cont = 0;
    SendMessage(hwndList,LVM_DELETEALLITEMS,0,0);
    Veiculo aux;
    FILE *arq;

    if(strlen(filtro) != 0){
        if(existeArquivo(ARQUIVO_DADOS_VEICULO)){
            arq = fopen(ARQUIVO_DADOS_VEICULO, "rb");
            if(arq != NULL){
                while(fread(&aux, sizeof(Veiculo), 1, arq) == 1){
                    if(strnicmp(aux.placa, filtro, strlen(filtro)) == 0){
                        lvItem.mask=LVIF_TEXT;   // Text Style
                        lvItem.cchTextMax = TAM_MODELO;
                        lvItem.iItem=cont;          // choose item
                        lvItem.iSubItem=0;       // Put in first coluom
                        lvItem.pszText=aux.modelo; // Text to display (can be from a char variable) (Items)

                        SendMessage(hwndList,LVM_INSERTITEM,cont,(LPARAM)&lvItem); // Send info to the Listview

                        lvItem.iSubItem = 1;       // Put in first coluom
                        lvItem.pszText = aux.placa; // Text to display (can be from a char variable) (Items)

                        SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem); // Send info to the Listview

                        lvItem.iSubItem = 2;           // Put in first coluom
                        lvItem.pszText = aux.chassi; // Text to display (can be from a char variable) (Items)

                        SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem); // Send info to the Listview

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
 * \brief Função de controle do janela "Adicionar Veiculo"
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
BOOL CALLBACK formAddVeic(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    char placa[TAM_PLACA];
    int erro;
    static Veiculo *veic;

    switch(msg) {
        case WM_INITDIALOG:
        SendMessage(GetDlgItem(hwnd, ID_EDIT_PLACA_VEIC), EM_LIMITTEXT, TAM_PLACA-1, 0);
        SendMessage(GetDlgItem(hwnd, ID_EDIT_MODELO_VEIC), EM_LIMITTEXT, TAM_MODELO-1, 0);
        SendMessage(GetDlgItem(hwnd, ID_EDIT_FAB_VEIC), EM_LIMITTEXT, TAM_FABRICANTE-1, 0);
        SendMessage(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC), EM_LIMITTEXT, TAM_CHASSI-1, 0);
        SendMessage(GetDlgItem(hwnd, ID_EDIT_ANO_VEIC), EM_LIMITTEXT, TAM_ANO-1, 0);

        EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), FALSE);
        return TRUE;
        break;

        case WM_COMMAND:
            GetDlgItemText(hwnd, ID_EDIT_PLACA_VEIC, placa, TAM_PLACA);

            if( GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_MODELO_VEIC)) > 0 &&
                validaPlaca(placa) == PLACA_VALIDA &&
                GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_FAB_VEIC)) > 0 &&
                GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_ANO_VEIC)) == TAM_ANO -1 &&
                GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC)) == TAM_CHASSI-1){
                EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_VEIC), TRUE);
            }else{
                SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "");
                EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_VEIC), FALSE);
            }

            if(validaPlaca(placa) == PLACA_INVALIDA && strlen(placa) == TAM_PLACA-1) SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "A placa inserida a invalida!");
            if(GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC)) < TAM_CHASSI-1 && GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC)) > 0) SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "O chassi inserido e invalido!");

            switch(wp){
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
 * \brief Nomeia as colunas da lista de Veículos
 *
 * \param hwndList HWND
 * \return void
 *
 ***********************************************/
void inicializaListVeic(HWND hwndList){
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
 * \brief Função de controle do Dialogo "Alterar Proprietario"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formAlterarVeicBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Veiculo *auxAntigo;
    int erro;
    PCOPYDATASTRUCT pcds;

    switch(msg) {
        case WM_INITDIALOG:
            SendMessage(GetDlgItem(hwnd, ID_EDIT_PLACA_VEIC), EM_LIMITTEXT, TAM_PLACA-1, 0);
            SendMessage(GetDlgItem(hwnd, ID_EDIT_MODELO_VEIC), EM_LIMITTEXT, TAM_MODELO-1, 0);
            SendMessage(GetDlgItem(hwnd, ID_EDIT_FAB_VEIC), EM_LIMITTEXT, TAM_FABRICANTE-1, 0);
            SendMessage(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC), EM_LIMITTEXT, TAM_CHASSI-1, 0);
            SendMessage(GetDlgItem(hwnd, ID_EDIT_ANO_VEIC), EM_LIMITTEXT, TAM_ANO-1, 0);
        break;

        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lp;
			if(pcds->dwData == 0){
				    auxAntigo = (Veiculo *)(pcds->lpData);
                    SetDlgItemText(hwnd, ID_EDIT_PLACA_VEIC, auxAntigo->placa);
                    SetDlgItemText(hwnd, ID_EDIT_MODELO_VEIC, auxAntigo->modelo);
                    SetDlgItemText(hwnd, ID_EDIT_FAB_VEIC, auxAntigo->fabricante);
                    SetDlgItemText(hwnd, ID_EDIT_CHASSI_VEIC, auxAntigo->chassi);
                    SetDlgItemText(hwnd, ID_EDIT_ANO_VEIC, auxAntigo->ano);
			}
        return TRUE;
        break;

        case WM_COMMAND:

            switch(wp){
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
 * \brief Função de controle do janela "Alterar Veiculo"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formAlterarVeic(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    char placa[TAM_PLACA];
    static HWND hwndList, hwndProprio;
    int iSelect;
    static HINSTANCE g_inst;
    HWND formAlterar;
    static Veiculo *auxEnvio;
    COPYDATASTRUCT CDS;

    switch(msg) {
        case WM_INITDIALOG:
        hwndList = GetDlgItem(hwnd, ID_VEIC_ALTERAR_LIST);
        SendMessage(GetDlgItem(hwnd, ID_VEIC_ALTERAR_BUSCA_EDIT), EM_LIMITTEXT, TAM_PLACA-1, 0);

        inicializaListVeic(hwndList);
        return TRUE;
        break;

        case WM_COMMAND:
                iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);

                if(HIWORD(wp) == EN_CHANGE){

                    GetDlgItemText(hwnd, ID_VEIC_ALTERAR_BUSCA_EDIT, placa, TAM_PLACA);
                    atualizaListaVeic(hwndList, placa);

                }
                switch(LOWORD(wp)){
                    case ID_VEIC_ALTERAR_BOTAO:
                        if(iSelect == -1){
                            MessageBox(hwnd,"Nenhum veiculo selecionado!",
                            "Erro!",MB_OK|MB_ICONERROR);
                        }else{
                            formAlterar = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_ALTERAR_FORM), hwnd, (DLGPROC)formAlterarVeicBox);

                            ListView_GetItemText(hwndList, iSelect, 1, placa, TAM_PLACA);

                            auxEnvio = (Veiculo *)malloc(sizeof(Veiculo));
                            pegaVeiculo(placa, auxEnvio);

                            CDS.dwData = 0;
                            CDS.cbData = sizeof(Veiculo);
                            CDS.lpData = auxEnvio;

                            SendMessage(formAlterar, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
                            SetDlgItemText(hwnd, ID_VEIC_ALTERAR_BUSCA_EDIT, "");
                            hwndProprio = hwnd;
                            guardaPegaHandle(&hwndProprio, 0);
                        }
                    break;

                    case ID_VEIC_ALTERAR_ATUALIZAR_BOTAO:
                            SetDlgItemText(hwnd, ID_VEIC_ALTERAR_BUSCA_EDIT, "");
                    break;

                }
            return TRUE;
            break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Função de controle do Dialogo "Excluir Proprietario"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formExcluirVeicBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Veiculo *auxAntigo;
    int erro;
    PCOPYDATASTRUCT pcds;

    switch(msg) {
        break;

        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lp;
			if(pcds->dwData == 0){
				    auxAntigo = (Veiculo *)(pcds->lpData);
                    SetDlgItemText(hwnd, ID_EDIT_PLACA_VEIC, auxAntigo->placa);
                    SetDlgItemText(hwnd, ID_EDIT_MODELO_VEIC, auxAntigo->modelo);
                    SetDlgItemText(hwnd, ID_EDIT_FAB_VEIC, auxAntigo->fabricante);
                    SetDlgItemText(hwnd, ID_EDIT_CHASSI_VEIC, auxAntigo->chassi);
                    SetDlgItemText(hwnd, ID_EDIT_ANO_VEIC, auxAntigo->ano);
			}
        return TRUE;
        break;

        case WM_COMMAND:

            switch(wp){
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
 * \brief Função de controle do janela "Excluir Veiculo"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formExcluirVeic(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    char placa[TAM_PLACA];
    static HWND hwndList, hwndProprio;
    int iSelect;
    static HINSTANCE g_inst;
    HWND formAlterar;
    Veiculo *auxEnvio;
    COPYDATASTRUCT CDS;

    switch(msg) {
        case WM_INITDIALOG:
        hwndList = GetDlgItem(hwnd, ID_VEIC_EXCLUIR_LIST);
        SendMessage(GetDlgItem(hwnd, ID_VEIC_EXCLUIR_BUSCA_EDIT), EM_LIMITTEXT, TAM_PLACA-1, 0);

        inicializaListVeic(hwndList);
        return TRUE;
        break;

        case WM_COMMAND:
                iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);
                if(HIWORD(wp) == EN_CHANGE){

                    GetDlgItemText(hwnd, ID_VEIC_EXCLUIR_BUSCA_EDIT, placa, TAM_PLACA);
                    atualizaListaVeic(hwndList, placa);

                }
                switch(LOWORD(wp)){
                    case ID_VEIC_EXCLUIR_BOTAO:
                        if(iSelect == -1){
                            MessageBox(hwnd,"Nenhum veiculo selecionado!",
                            "Erro!",MB_OK|MB_ICONERROR);
                        }else{
                            formAlterar = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_EXCLUIR_FORM), hwnd, (DLGPROC)formExcluirVeicBox);

                            ListView_GetItemText(hwndList, iSelect, 1, placa, TAM_PLACA);

                            auxEnvio = (Veiculo *)malloc(sizeof(Veiculo));
                            pegaVeiculo(placa, auxEnvio);

                            CDS.dwData = 0;
                            CDS.cbData = sizeof(Veiculo);
                            CDS.lpData = auxEnvio;

                            SendMessage(formAlterar, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
                            SetDlgItemText(hwnd, ID_VEIC_EXCLUIR_BUSCA_EDIT, "");
                            hwndProprio = hwnd;
                            guardaPegaHandle(&hwndProprio, 0);
                        }
                    break;

                    case ID_VEIC_EXCLUIR_ATUALIZAR_BOTAO:
                            SetDlgItemText(hwnd, ID_VEIC_EXCLUIR_BUSCA_EDIT, "");
                    break;

                }
            return TRUE;
            break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Função de controle da tabPage "Veículo"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/

BOOL CALLBACK tabVeicPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND formVeicDlg, *formAux;
    static HINSTANCE g_inst;

    switch(msg) {

    case WM_COMMAND:

        formAux = guardaPegaHandle(NULL, 1);
        if(formAux != NULL) EndDialog(*formAux, 0);

        switch (wp) {
        case ID_BOTAO_ADD_VEIC:
            formVeicDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_ADD_FORM), GetParent(hwnd), (DLGPROC)formAddVeic);
            break;

        case ID_BOTAO_ALTERAR_VEIC:
            formVeicDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_ALTERAR), GetParent(hwnd), (DLGPROC)formAlterarVeic);
            break;

        case ID_BOTAO_EXCLUIR_VEIC:
            formVeicDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_EXCLUIR), GetParent(hwnd), (DLGPROC)formExcluirVeic);
            break;
        }

        guardaPegaHandle(&formVeicDlg, 0);
        return TRUE;
        break;
    }

    return FALSE;
}
