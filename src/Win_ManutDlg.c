/********************************************//**
 ** @file Win_ManutDlg.c
 * @brief Contem as funções de controle da tabPage Manutenção.
 * @bug Nao contem bugs conhecidos!
 *
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/
#include "../include/Win_Functions.h"
#include<time.h>

/********************************************//**
 * \brief Le os dados do formulario de manutenção
 *
 * \param hwnd HWND
 * \return Manutencao*
 *
 ***********************************************/
Manutencao *leDadosManutForm(HWND hwnd){
    Manutencao *aux;
    aux = (Manutencao *)malloc(sizeof(Manutencao));
    char *pecas, *obra;

    pecas = (char *)malloc(GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_PECAS_MANUT))*sizeof(char));
    obra = (char *)malloc(GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_OBRA_MANUT))*sizeof(char));

    GetDlgItemText(hwnd, ID_EDIT_PLACA_MANUT, aux->placa, TAM_NOME);
    GetDlgItemText(hwnd, ID_EDIT_CPF_MANUT, aux->cpf, TAM_CPF);
    GetDlgItemText(hwnd, ID_EDIT_PECAS_MANUT, pecas, 10);
    GetDlgItemText(hwnd, ID_EDIT_ESTADO_PROP, obra, 10);
    GetDlgItemText(hwnd, ID_EDIT_DESCRICAO_PROP, aux->descricao, TAM_DESCRICAO);

    aux->valorPecas = atoi(pecas);
    aux->valorObra = atoi(obra);

    free(pecas);
    free(obra);

    return aux;
}


/********************************************//**
 * \brief Converte um struct do tipo SYSTEMTIME em
 *        um time_t
 * \param st SYSTEMTIME
 * \return time_t
 *
 ***********************************************/
time_t convertTime(SYSTEMTIME st){
    struct tm time_m;

    time_m.tm_sec = (int)st.wSecond;
	time_m.tm_min = (int)st.wMinute;
	time_m.tm_hour = (int)st.wHour;
	time_m.tm_mday = (int)st.wDay;
	time_m.tm_mon = (int)st.wMonth - 1;
	time_m.tm_year = (int)st.wYear - 1900;
    time_m.tm_wday = (int)st.wDayOfWeek;
    time_m.tm_isdst = -1;

    if((time_t)mktime(&time_m) == (time_t)-1){

    return mktime(&time_m);
    }else{
	return 1;
    }
}

/********************************************//**
 * \brief Atualiza a lista de manutenções de acordo
 *        com a data inicial e a data final
 * \param hwndList HWND
 * \param timeI time_t
 * \param timeF time_t
 * \return void
 *
 ***********************************************/
void atualizaListaManut(HWND hwndList, time_t timeI, time_t timeF){

    LVITEM lvItem;
    int cont = 0;
    SendMessage(hwndList,LVM_DELETEALLITEMS,0,0);
    Manutencao aux;
    char data[TAM_DATA];
    FILE *arq;
    time_t auxTime;
    struct tm *dataS;

                    dataS = localtime(&timeI);

                    sprintf(data, "%02d/%02d/%02d", dataS->tm_mday, dataS->tm_mon+1, dataS->tm_year+1900);

                    MessageBox(hwndList, data, data, MB_OK);

                    dataS = localtime(&timeF);
                    sprintf(data, "%d/%d/%d", dataS->tm_mday, dataS->tm_mon+1, dataS->tm_year+1900);

                    MessageBox(hwndList, data, data, MB_OK);


    if(existeArquivo(ARQUIVO_DADOS_MANUTENCAO)){
        arq = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
        if(arq != NULL){
            while(fread(&aux, sizeof(Manutencao), 1, arq) == 1){
                if(aux.data >= timeI && aux.data <= timeF){
                    lvItem.mask=LVIF_TEXT;   // Text Style
                    lvItem.cchTextMax = TAM_NOME;
                    lvItem.iItem=cont;          // choose item
                    lvItem.iSubItem=0;       // Put in first coluom
                    lvItem.pszText=aux.placa; // Text to display (can be from a char variable) (Items)

                    SendMessage(hwndList,LVM_INSERTITEM,cont,(LPARAM)&lvItem); // Send info to the Listview

                    lvItem.iSubItem = 1;       // Put in first coluom
                    lvItem.pszText = aux.cpf; // Text to display (can be from a char variable) (Items)

                    SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem); // Send info to the Listview

                    lvItem.iSubItem = 2;       // Put in first coluom
                    auxTime = aux.data;
                    dataS = localtime(&auxTime);
                    sprintf(data, "%d/%d/%d", dataS->tm_mday, dataS->tm_mon, dataS->tm_year);
                    lvItem.pszText = data; // Text to display (can be from a char variable) (Items)

                    SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem); // Send info to the Listview

                    cont++;
                }
            }
            fclose(arq);
        }else{
        win_trataErros(hwndList, ERRO_ABRIR_ARQUIVO);
        }
    }

}

/********************************************//**
 * \brief Nomeia as colunas da lista de Manutenções
 *
 * \param hwndList HWND
 * \return void
 *
 ***********************************************/
void inicializaListManut(HWND hwndList){
    LVCOLUMN lvCol;

    lvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
    lvCol.cx=28;
    lvCol.pszText="Placa";
    lvCol.cx=120;
    SendMessage(hwndList ,LVM_INSERTCOLUMN, 0, (LPARAM)&lvCol);

    lvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
    lvCol.cx=28;
    lvCol.pszText="CPF";
    lvCol.cx=120;
    SendMessage(hwndList ,LVM_INSERTCOLUMN, 1, (LPARAM)&lvCol);

    lvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
    lvCol.cx=28;
    lvCol.pszText="Data";
    lvCol.cx=103;
    SendMessage(hwndList ,LVM_INSERTCOLUMN, 2, (LPARAM)&lvCol);
}

/********************************************//**
 * \brief Função de controle da janela "Excluir Manutenção"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrão Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formExcluirManut(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Manutencao auxEnvio;
    static HINSTANCE g_inst;
    int iSelect;
    time_t dataI, dataF;
    LV_ITEM lvItem;
    COPYDATASTRUCT CDS;
    HWND formAlterar;
    static HWND hwndList;
    SYSTEMTIME dateT;

    switch(msg) {
        case WM_INITDIALOG:
            hwndList = GetDlgItem(hwnd, ID_MANUT_LIST);
            inicializaListManut(hwndList);

            return TRUE;
        break;

        case WM_COMMAND:

            iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);
            switch(LOWORD(wp)){
                case ID_MANUT_BOTAO_EXCLUIR:

                    DateTime_GetRange(GetDlgItem(hwnd, ID_MANUT_DATA_INICIO), &dateT);
                    dataI = convertTime(dateT);
                    DateTime_GetRange(GetDlgItem(hwnd, ID_MANUT_DATA_FIM), &dateT);
                    dataF = convertTime(dateT);
                    atualizaListaManut(hwndList, dataI, dataF);

                    if(iSelect == -1){
                        MessageBox(hwnd,"Nenhum proprietario selecionado!",
                        "Erro!",MB_OK|MB_ICONINFORMATION);
                    }else{/*
                        formAlterar = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_ALTERAR_FORM), hwnd, formAlterarPropBox);

                        lvItem.mask=LVIF_TEXT;
                        lvItem.iSubItem=1;
                        lvItem.cchTextMax=TAM_CPF;
                        lvItem.iItem=iSelect;

                        SendMessage(GetDlgItem(hwnd, ID_PROP_ALTERAR_LIST),LVM_GETITEMTEXT, iSelect, (LPARAM)&lvItem);
                        pegaProprietario(lvItem.pszText, &auxEnvio);

                        CDS.dwData = 0;
                        CDS.cbData = sizeof(Proprietario);
                        CDS.lpData = &auxEnvio;

                        SendMessage(formAlterar, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
                        SetDlgItemText(hwnd, ID_PROP_ALTERAR_BUSCA_EDIT, "");*/
                    }
                break;

                case ID_PROP_ALTERAR_ATUALIZAR_BOTAO:
                        SetDlgItemText(hwnd, ID_PROP_ALTERAR_BUSCA_EDIT, "");
                break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}


/********************************************//**
 * \brief Função de controle do janela "Adicionar Manutenção"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrão Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formAddManut(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    Manutencao *aux;
    int erro;
    char cpf[TAM_CPF], placa[TAM_PLACA];

    switch(msg) {
        case WM_INITDIALOG:

        SendMessage(GetDlgItem(hwnd, ID_EDIT_PLACA_MANUT), EM_LIMITTEXT, TAM_PLACA-1, 0);
        SendMessage(GetDlgItem(hwnd, ID_EDIT_CPF_MANUT), EM_LIMITTEXT, TAM_CPF-1, 0);
        SendMessage(GetDlgItem(hwnd, ID_EDIT_DESCRICAO_MANUT), EM_LIMITTEXT, TAM_DESCRICAO-1, 0);

        EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_MANUT), FALSE);
        break;

        case WM_COMMAND:

            GetDlgItemText(hwnd, ID_EDIT_CPF_MANUT, cpf, TAM_CPF);
            GetDlgItemText(hwnd, ID_EDIT_PLACA_MANUT, placa, TAM_PLACA);

            if( GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_PECAS_MANUT)) > 0 &&
                validaCPF(cpf) == CPF_VALIDO && validaPlaca(placa) == PLACA_VALIDA &&
                GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_OBRA_MANUT)) > 0 &&
                GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_DESCRICAO_MANUT)) > 0){
                EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_MANUT), TRUE);
            }else{
                SetDlgItemText(hwnd, ID_MANUT_ADD_LOG, "");
                EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_MANUT), FALSE);
            }

            if(validaCPF(cpf) != CPF_VALIDO && strlen(cpf) == TAM_CPF-1) SetDlgItemText(hwnd, ID_MANUT_ADD_LOG, "O CPF inserido é inválido!");
            if(validaPlaca(placa) != PLACA_VALIDA && strlen(placa) == TAM_PLACA-1) SetDlgItemText(hwnd, ID_MANUT_ADD_LOG, "A placa inserida é inválida!");


            switch(wp){
            case ID_BOTAO_ACAO_MANUT:
                aux = leDadosManutForm(hwnd);

                erro = incluiManutencao(*aux);
                free(aux);
                if(win_trataErros(hwnd, erro) == 0) EndDialog(hwnd, 0);
            break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Função de controle da tabPage "Manutenção"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrão Windows para janelas
 *
 ***********************************************/

BOOL CALLBACK tabManutPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND formManutDlg, *formAux;
    static HINSTANCE g_inst;

    switch(msg) {

    case WM_COMMAND:

        formAux = guardaPegaHandle(NULL, 1);
        if(formAux != NULL) EndDialog(*formAux, 0);

        switch (wp) {
        case ID_BOTAO_ADD_MANUT:
            formManutDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_MANUT_ADD_FORM), GetParent(hwnd), formAddManut);
            break;

        case ID_BOTAO_EXCLUIR_MANUT:
            formManutDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_MANUT_EXCLUIR), GetParent(hwnd), NULL);
            break;
        }

        guardaPegaHandle(&formManutDlg, 0);
        return TRUE;
        break;
    }

    return FALSE;
}
