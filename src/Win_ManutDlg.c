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
    GetDlgItemText(hwnd, ID_EDIT_OBRA_MANUT, obra, 10);
    GetDlgItemText(hwnd, ID_EDIT_DESCRICAO_MANUT, aux->descricao, TAM_DESCRICAO);

    aux->valorPecas = atof(pecas);
    aux->valorObra = atof(obra);

    free(pecas);
    free(obra);

    return aux;
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
void atualizaListaManut(HWND hwndList, Data dataI, Data dataF){

    LVITEM lvItem;
    int cont = 0;
    Manutencao aux;
    char data[TAM_DATA];
    FILE *arq;

    SendMessage(hwndList,LVM_DELETEALLITEMS,0,0);

    if(existeArquivo(ARQUIVO_DADOS_MANUTENCAO)){
        arq = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
        if(arq != NULL){
            while(fread(&aux, sizeof(Manutencao), 1, arq) == 1){
                if(comparaData(aux.data, dataI) >= 0 && comparaData(aux.data, dataF) <= 0 && comparaData(dataI, dataF) <= 0){
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
                    sprintf(data, "%d/%d/%d", aux.data.dia, aux.data.mes, aux.data.ano);
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
 * \brief Função de controle do Dialogo "Excluir Proprietario"
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
BOOL CALLBACK formExcluirManutBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Manutencao *auxAntigo;
    int erro;
    PCOPYDATASTRUCT pcds;
    char valor[10];

    switch(msg) {
        break;

        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lp;
			if(pcds->dwData == 0){
				    auxAntigo = (Veiculo *)(pcds->lpData);
                    SetDlgItemText(hwnd, ID_EDIT_PLACA_MANUT, auxAntigo->placa);
                    SetDlgItemText(hwnd, ID_EDIT_CPF_MANUT, auxAntigo->cpf);
                    sprintf(valor, "%.2f", auxAntigo->valorPecas);
                    SetDlgItemText(hwnd, ID_EDIT_PECAS_MANUT, valor);
                    sprintf(valor, "%.2f", auxAntigo->valorObra);
                    SetDlgItemText(hwnd, ID_EDIT_OBRA_MANUT, valor);
                    SetDlgItemText(hwnd, ID_EDIT_DESCRICAO_MANUT, auxAntigo->descricao);
			}
        return TRUE;
        break;

        case WM_COMMAND:

            switch(wp){
            case ID_BOTAO_ACAO_MANUT:
                    erro = excluiManutencao(auxAntigo->placa);
                    free(auxAntigo);
                    win_trataErros(hwnd, erro);
                    SendMessage(guardaPegaHandle(NULL, 1), WM_COMMAND, 3, NULL);
                    EndDialog(hwnd, 0);
            break;

            case ID_BOTAO_CANCELAR_MANUT:
                EndDialog(hwnd, 0);
            break;
            }

        return TRUE;
        break;
    }
    return FALSE;
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
    int iSelect;
    static Data dataI, dataF;
    HWND formExcluir;
    static HWND hwndList;
    SYSTEMTIME dateT;
    char data[TAM_DATA];
    static Manutencao auxEnvio;
    LVITEM lvItem;
    COPYDATASTRUCT CDS;

    switch(msg) {
        case WM_INITDIALOG:
            hwndList = GetDlgItem(hwnd, ID_MANUT_LIST);
            inicializaListManut(hwndList);

            GetLocalTime(&dateT);
            DateTime_SetRange(GetDlgItem(hwnd, ID_MANUT_DATA_INICIO), GDTR_MAX, &dateT);
            DateTime_SetRange(GetDlgItem(hwnd, ID_MANUT_DATA_FIM), GDTR_MIN, &dateT);

            DateTime_GetSystemtime(GetDlgItem(hwnd, ID_MANUT_DATA_INICIO), &dateT);
            dataI = convertTime(dateT);
            DateTime_GetSystemtime(GetDlgItem(hwnd, ID_MANUT_DATA_FIM), &dateT);
            dataF = convertTime(dateT);
            atualizaListaManut(hwndList, dataI, dataF);

            return TRUE;
        break;

        case WM_NOTIFY:

            switch(((LPNMHDR)lp)->code){

                case DTN_DATETIMECHANGE:{
                    DateTime_GetSystemtime(GetDlgItem(hwnd, ID_MANUT_DATA_INICIO), &dateT);
                    dataI = convertTime(dateT);
                    DateTime_GetSystemtime(GetDlgItem(hwnd, ID_MANUT_DATA_FIM), &dateT);
                    dataF = convertTime(dateT);
                    atualizaListaManut(hwndList, dataI, dataF);
                }
                break;

            break;
            }

        break;

        case WM_COMMAND:

            iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);

            switch(LOWORD(wp)){
                case 3:
                    atualizaListaManut(hwndList, dataI, dataF);
                break;
                case ID_MANUT_BOTAO_EXCLUIR:
                    guardaPegaHandle(hwnd, 0);
                    if(iSelect == -1){
                        MessageBox(hwnd,"Nenhum proprietario selecionado!",
                        "Erro!",MB_OK|MB_ICONINFORMATION);
                    }else{
                        formExcluir = CreateDialog(NULL, MAKEINTRESOURCE(IDD_MANUT_EXCLUIR_FORM), hwnd, formExcluirManutBox);

                        ListView_GetItemText(GetDlgItem(hwnd, ID_MANUT_LIST), iSelect, 0, auxEnvio.placa, TAM_PLACA);

                        ListView_GetItemText(GetDlgItem(hwnd, ID_MANUT_LIST), iSelect, 1, auxEnvio.cpf, TAM_CPF);

                        ListView_GetItemText(GetDlgItem(hwnd, ID_MANUT_LIST), iSelect, 2, data, TAM_DATA);

                        sscanf(data, "%d/%d/%d", &(auxEnvio.data.dia), &(auxEnvio.data.mes), &(auxEnvio.data.ano));

                        pegaManutencao(auxEnvio.placa, auxEnvio.cpf, auxEnvio.data, &auxEnvio);

                        CDS.dwData = 0;
                        CDS.cbData = sizeof(Manutencao);
                        CDS.lpData = &auxEnvio;

                        SendMessage(formExcluir, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
                    }
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
    SYSTEMTIME data;

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

                GetLocalTime(&data);
                aux->data = convertTime(data);

                erro = incluiManutencao(*aux);
                free(aux);
                win_trataErros(hwnd, erro);
                if(erro == MANUT_INSERIR_SUCESSO) EndDialog(hwnd, 0);
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
            formManutDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_MANUT_EXCLUIR), GetParent(hwnd), formExcluirManut);
            break;
        }

        guardaPegaHandle(&formManutDlg, 0);
        return TRUE;
        break;
    }

    return FALSE;
}
