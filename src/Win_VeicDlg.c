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
                fclose(arq);
            }else{
            win_trataErros(hwndList, ERRO_ABRIR_ARQUIVO);
            }
        }
    }
}

/********************************************//**
 * \brief Função de controle do janela "Pega CPF"
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
BOOL CALLBACK veic_pegaCpfProc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp){
    static char cpf[TAM_CPF];
    int pos;
    HWND *hwndAux;
    COPYDATASTRUCT pcds;

    switch(message){
        case WM_INITDIALOG:

            SendMessage(GetDlgItem(hwnd, ID_PEGACPF_CAMPO), EM_SETLIMITTEXT, TAM_CPF-1, 0);
            return TRUE;
            break;

        case WM_COMMAND:
            GetDlgItemText(hwnd, ID_PEGACPF_CAMPO, cpf, TAM_CPF);
            if(validaCPF(cpf) != CPF_VALIDO && strlen(cpf) == TAM_CPF-1){
                SetDlgItemText(hwnd, ID_PEGACPF_LOG, "O CPF inserido é inválido!");
            }else if(validaCPF(cpf) == CPF_VALIDO){
                SetDlgItemText(hwnd, ID_PEGACPF_LOG, "");
                EnableWindow(GetDlgItem(hwnd, ID_PEGACPF_OK), TRUE);
            }

            switch(wp){
                case ID_PEGACPF_OK:
                hwndAux = guardaPegaHandle(NULL, 1);
                if(buscaProprietario(cpf, &pos) == PROP_BUSCA_SUCESSO && pos != -1){
                     pcds.dwData = 1;
                     pcds.cbData = sizeof(cpf);
                     pcds.lpData = (LPSTR)cpf;

                     SendMessage(*hwndAux, WM_COPYDATA,(WPARAM)hwnd, (LPARAM)&pcds);
                     EndDialog(hwnd, 0);

                }else{
                    win_trataErros(hwnd,PROP_BUSCA_INEXISTENTE);
                };

                break;
                case ID_PEGACPF_CANCEL:
                    EndDialog(hwnd, 0);
                    break;
                }
            return TRUE;
            break;
    }

    return FALSE;
}

/********************************************//**
 * \brief Nomeia as colunas da lista de Proprietários
 *        de cada veículo
 * \param hwndList HWND
 * \return void
 *
 ***********************************************/
void inicializaListPropVeic(HWND hwndList){
    LVCOLUMN lvCol;

    lvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
    lvCol.pszText="Proprietário        ";
    SendMessage(hwndList ,LVM_INSERTCOLUMN, 0, (LPARAM)&lvCol);

    lvCol.pszText="CPF                 ";
    lvCol.cchTextMax = TAM_CPF;
    SendMessage(hwndList ,LVM_INSERTCOLUMN, 1, (LPARAM)&lvCol);

    lvCol.pszText="Telefone";
    lvCol.cchTextMax = TAM_TEL;
    SendMessage(hwndList ,LVM_INSERTCOLUMN, 2, (LPARAM)&lvCol);

    ListView_SetColumnWidth(hwndList, 0, LVSCW_AUTOSIZE_USEHEADER);
    ListView_SetColumnWidth(hwndList, 1, LVSCW_AUTOSIZE_USEHEADER);
    ListView_SetColumnWidth(hwndList, 2, LVSCW_AUTOSIZE_USEHEADER);
}

/********************************************//**
 * \brief Verifica se já existe algum proprietário
 *        com o mesmo cpf na lista
 *
 * \param hwndList HWND
 * \param cpf char*
 * \return  1 - Caso exista
 *          0 - Caso não exista
 ***********************************************/
int existeNaListaProp(HWND hwndList, char *cpf){
    int cont = ListView_GetItemCount(hwndList), aux, flag = 0;
    char cpfTeste[TAM_CPF];

    for(aux = 0; aux < cont; aux++){
        ListView_GetItemText(hwndList, aux, 1, cpfTeste, TAM_CPF);

        if(stricmp(cpfTeste, cpf)==0)
            flag = 1;
    }

    return flag;
}

/********************************************//**
 * \brief Função de controle do janela "Adicionar Veiculo"
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
BOOL CALLBACK formAddVeic(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    char placa[TAM_PLACA];
    LPSTR cpf;
    static HWND hwndList;
    COPYDATASTRUCT *pcds;
    Proprietario prop;
    Veiculo veic;
    LVITEM lvItem;
    int cont = ListView_GetItemCount(hwndList), aux, flag = 0, erro;

    switch(msg) {
        case WM_INITDIALOG:
        hwndList = GetDlgItem(hwnd, ID_LIST_PROP_VEIC);
        SendMessage(GetDlgItem(hwnd, ID_EDIT_PLACA_VEIC), EM_LIMITTEXT, TAM_PLACA-1, 0);
        SendMessage(GetDlgItem(hwnd, ID_EDIT_MODELO_VEIC), EM_LIMITTEXT, TAM_MODELO-1, 0);
        SendMessage(GetDlgItem(hwnd, ID_EDIT_FAB_VEIC), EM_LIMITTEXT, TAM_FABRICANTE-1, 0);
        SendMessage(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC), EM_LIMITTEXT, TAM_CHASSI-1, 0);
        SendMessage(GetDlgItem(hwnd, ID_EDIT_ANO_VEIC), EM_LIMITTEXT, TAM_ANO-1, 0);

        inicializaListPropVeic(hwndList);
        EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), FALSE);
        return TRUE;
        break;

        case WM_COMMAND:
            cont = ListView_GetItemCount(hwndList);
            GetDlgItemText(hwnd, ID_EDIT_PLACA_VEIC, placa, TAM_PLACA);

            if( GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_MODELO_VEIC)) > 0 &&
                validaPlaca(placa) == PLACA_VALIDA &&
                GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_FAB_VEIC)) > 0 &&
                GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_ANO_VEIC)) == TAM_ANO -1 &&
                GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC)) == TAM_CHASSI-1 &&
                ListView_GetItemCount(hwndList) > 0){
                EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_VEIC), TRUE);
            }else{
                SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "");
                EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_VEIC), FALSE);
            }

            if(validaPlaca(placa) == PLACA_INVALIDA && strlen(placa) == TAM_PLACA-1) SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "A placa inserida é inválida!");
            if(GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC)) < TAM_CHASSI-1 && GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_CHASSI_VEIC)) > 0) SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "O chassi inserido é inválido!");

            switch(wp){
            case ID_VEIC_BOTAO_ADD_PROP:

                CreateDialog(NULL, MAKEINTRESOURCE(IDD_PEGACPF_VEIC), hwnd, veic_pegaCpfProc);

            break;

            case ID_VEIC_BOTAO_REMOVE_PROP:
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CONFIRM_REMOVE_PROP), TRUE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CANCELA_REMOVE_PROP), TRUE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_TODOS_PROP), TRUE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_ADD_PROP), FALSE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_PROP), FALSE);

                SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "Selecione o proprietario que deseja remover!");

            break;

            case ID_VEIC_BOTAO_CANCELA_REMOVE_PROP:
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CONFIRM_REMOVE_PROP), FALSE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CANCELA_REMOVE_PROP), FALSE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_TODOS_PROP),FALSE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_ADD_PROP), TRUE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_PROP), TRUE);

                SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "");

            break;

            case ID_VEIC_BOTAO_CONFIRM_REMOVE_PROP:
                flag = 0;
                cont = ListView_GetItemCount(hwndList);
                for(aux = 0; aux < cont; aux++){
                    if(ListView_GetItemState(hwndList, aux, LVNI_SELECTED || LVNI_FOCUSED)){
                        ListView_DeleteItem(hwndList, aux);
                        flag = 1;
                        break;
                    }
                }

                if(flag == 1){
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CONFIRM_REMOVE_PROP), FALSE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CANCELA_REMOVE_PROP), FALSE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_TODOS_PROP), FALSE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_ADD_PROP), TRUE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_PROP), TRUE);

                    SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "");
                }

            break;

            case ID_VEIC_BOTAO_REMOVE_TODOS_PROP:
                flag = 0;
                cont = ListView_GetItemCount(hwndList);
                ListView_DeleteAllItems(hwndList);
                flag = 1;

                if(flag == 1){
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CONFIRM_REMOVE_PROP), FALSE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CANCELA_REMOVE_PROP), FALSE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_TODOS_PROP), FALSE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_ADD_PROP), TRUE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_PROP), TRUE);

                    SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "");
                }

            break;

            case ID_BOTAO_ACAO_VEIC:
                    cont = ListView_GetItemCount(hwndList);
                    GetDlgItemText(hwnd, ID_EDIT_PLACA_VEIC, veic.placa, TAM_PLACA);
                    GetDlgItemText(hwnd, ID_EDIT_MODELO_VEIC, veic.modelo, TAM_MODELO);
                    GetDlgItemText(hwnd, ID_EDIT_FAB_VEIC, veic.fabricante, TAM_FABRICANTE);
                    GetDlgItemText(hwnd, ID_EDIT_CHASSI_VEIC, veic.chassi, TAM_CHASSI);
                    GetDlgItemText(hwnd, ID_EDIT_ANO_VEIC, veic.ano, TAM_ANO);
                    for(aux = 0; aux < cont; aux++)
                        ListView_GetItemText(hwndList, aux, 1, veic.proprietarios[aux], TAM_CPF);

                    veic.qtProprietario = cont;

                    erro = incluiVeiculo(veic);

                    cont = 0;
                    win_trataErros(hwnd, erro);

                    if(erro == VEIC_INSERIR_SUCESSO) EndDialog(hwnd, 0);

            break;
            }

            return TRUE;
            break;

            case WM_COPYDATA:
                hwndList = GetDlgItem(hwnd, ID_LIST_PROP_VEIC);
                pcds = (COPYDATASTRUCT*)lp;
                if(pcds->dwData == 1){
                    cpf = pcds->lpData;
                    if(!existeNaListaProp(hwndList, cpf)){
                        if(pegaProprietario(cpf, &prop) == PROP_PEGAPROP_SUCESSO){
                            lvItem.mask=LVIF_TEXT;
                            lvItem.cchTextMax = TAM_NOME;
                            lvItem.iItem=cont;
                            lvItem.iSubItem=0;
                            lvItem.pszText=prop.nome;

                            SendMessage(hwndList,LVM_INSERTITEM,cont,(LPARAM)&lvItem);

                            lvItem.cchTextMax = TAM_CPF;
                            lvItem.iSubItem=1;
                            lvItem.pszText=prop.cpf;
                            SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);

                            lvItem.cchTextMax = TAM_TEL;
                            lvItem.iSubItem=2;
                            lvItem.pszText=prop.telefone;
                            SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);
                            ListView_Update(hwndList, LVNI_ALL);
                        }
                    }
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
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrão Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formAlterarVeicBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Veiculo *auxAntigo;
    Proprietario pAux;
    LPSTR cpf;
    char cpf2[TAM_CPF];
    int erro, aux, flag, cont;
    PCOPYDATASTRUCT pcds;
    static HWND hwndList, auxHnwd;
    LVITEM lvItem;

    switch(msg) {
        case WM_INITDIALOG:
            hwndList = GetDlgItem(hwnd, ID_LIST_PROP_VEIC);
            inicializaListPropVeic(hwndList);
        return TRUE;
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
                    for(aux = 0; aux < auxAntigo->qtProprietario; aux++){
                        pegaProprietario(auxAntigo->proprietarios[aux], &pAux);
                        lvItem.mask=LVIF_TEXT;   // Text Style
                        lvItem.cchTextMax = TAM_NOME;
                        lvItem.iItem=aux;          // choose item
                        lvItem.iSubItem=0;       // Put in first coluom
                        lvItem.pszText=pAux.nome; // Text to display (can be from a char variable) (Items)

                        SendMessage(hwndList,LVM_INSERTITEM,aux,(LPARAM)&lvItem);

                        lvItem.cchTextMax = TAM_CPF;
                        lvItem.iSubItem = 1;
                        lvItem.pszText = pAux.cpf;

                        SendMessage(hwndList,LVM_SETITEM,aux,(LPARAM)&lvItem);

                        lvItem.cchTextMax = TAM_TEL;
                        lvItem.iSubItem = 2;
                        lvItem.pszText = pAux.telefone;

                        SendMessage(hwndList,LVM_SETITEM,aux,(LPARAM)&lvItem);
                    }
			}

            if((pcds->dwData) == 1){
                    cpf = pcds->lpData;
                    cont = ListView_GetItemCount(hwndList);
                    if(!existeNaListaProp(hwndList, cpf)){
                        if(pegaProprietario(cpf, &pAux) == PROP_PEGAPROP_SUCESSO){
                            lvItem.mask=LVIF_TEXT;
                            lvItem.cchTextMax = TAM_NOME;
                            lvItem.iItem=cont;
                            lvItem.iSubItem=0;
                            lvItem.pszText=pAux.nome;

                            SendMessage(hwndList,LVM_INSERTITEM,cont,(LPARAM)&lvItem);

                            lvItem.cchTextMax = TAM_CPF;
                            lvItem.iSubItem=1;
                            lvItem.pszText=pAux.cpf;
                            SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);

                            lvItem.cchTextMax = TAM_TEL;
                            lvItem.iSubItem=2;
                            lvItem.pszText=pAux.telefone;
                            SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);

                            ListView_Update(hwndList, LVNI_ALL);
                        }
                    }
            }
        return TRUE;
        break;

        case WM_COMMAND:

            switch(wp){
            case ID_BOTAO_ACAO_VEIC:
                    auxAntigo->qtProprietario = ListView_GetItemCount(hwndList);
                    for(aux = 0; aux < auxAntigo->qtProprietario;aux ++){
                        ListView_GetItemText(hwndList, aux, 1, cpf2, TAM_CPF);
                        strcpy(auxAntigo->proprietarios[aux], cpf2);
                    }
                    erro = alteraVeiculo(*auxAntigo, auxAntigo->placa);
                    free(auxAntigo);
                    win_trataErros(hwnd, erro);
                    EndDialog(hwnd, 0);
            break;

            case ID_BOTAO_CANCELAR_VEIC:
                EndDialog(hwnd, 0);
            break;

            case ID_VEIC_BOTAO_ADD_PROP:
                auxHnwd = hwnd;
                guardaPegaHandle(&auxHnwd, 0);
                CreateDialog(NULL, MAKEINTRESOURCE(IDD_PEGACPF_VEIC), hwnd, veic_pegaCpfProc);

            break;

            case ID_VEIC_BOTAO_REMOVE_PROP:
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CONFIRM_REMOVE_PROP), TRUE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CANCELA_REMOVE_PROP), TRUE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_TODOS_PROP), TRUE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_ADD_PROP), FALSE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_PROP), FALSE);

                SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "Selecione o proprietario que deseja remover!");

            break;

            case ID_VEIC_BOTAO_CANCELA_REMOVE_PROP:
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CONFIRM_REMOVE_PROP), FALSE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CANCELA_REMOVE_PROP), FALSE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_TODOS_PROP),FALSE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_ADD_PROP), TRUE);
                ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_PROP), TRUE);

                SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "");

            break;

            case ID_VEIC_BOTAO_CONFIRM_REMOVE_PROP:
                flag = 0;
                cont = ListView_GetItemCount(hwndList);
                for(aux = 0; aux < cont; aux++){
                    if(ListView_GetItemState(hwndList, aux, LVNI_SELECTED || LVNI_FOCUSED)){
                        ListView_DeleteItem(hwndList, aux);
                        flag = 1;
                        break;
                    }
                }

                if(flag == 1){
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CONFIRM_REMOVE_PROP), FALSE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CANCELA_REMOVE_PROP), FALSE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_TODOS_PROP), FALSE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_ADD_PROP), TRUE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_PROP), TRUE);

                    SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "");
                }

            break;

            case ID_VEIC_BOTAO_REMOVE_TODOS_PROP:
                flag = 0;
                cont = ListView_GetItemCount(hwndList);
                ListView_DeleteAllItems(hwndList);
                flag = 1;

                if(flag == 1){
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CONFIRM_REMOVE_PROP), FALSE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_CANCELA_REMOVE_PROP), FALSE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_TODOS_PROP), FALSE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_ADD_PROP), TRUE);
                    ShowWindow(GetDlgItem(hwnd, ID_VEIC_BOTAO_REMOVE_PROP), TRUE);

                    SetDlgItemText(hwnd, ID_VEIC_ADD_LOG, "");
                }

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
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrão Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formAlterarVeic(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
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
                            formAlterar = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_ALTERAR_FORM), hwnd, formAlterarVeicBox);

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
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrão Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formExcluirVeicBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Veiculo *auxAntigo;
    Proprietario pAux;
    int erro, aux;
    PCOPYDATASTRUCT pcds;
    static HWND hwndList;
    LVITEM lvItem;

    switch(msg) {
        case WM_INITDIALOG:
            hwndList = GetDlgItem(hwnd, ID_LIST_PROP_VEIC);
            inicializaListPropVeic(hwndList);
        return TRUE;
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
                    for(aux = 0; aux < auxAntigo->qtProprietario; aux++){
                        pegaProprietario(auxAntigo->proprietarios[aux], &pAux);
                        lvItem.mask=LVIF_TEXT;   // Text Style
                        lvItem.cchTextMax = TAM_NOME;
                        lvItem.iItem=aux;          // choose item
                        lvItem.iSubItem=0;       // Put in first coluom
                        lvItem.pszText=pAux.nome; // Text to display (can be from a char variable) (Items)

                        SendMessage(hwndList,LVM_INSERTITEM,aux,(LPARAM)&lvItem);

                        lvItem.cchTextMax = TAM_CPF;
                        lvItem.iSubItem = 1;
                        lvItem.pszText = pAux.cpf;

                        SendMessage(hwndList,LVM_SETITEM,aux,(LPARAM)&lvItem);

                        lvItem.cchTextMax = TAM_TEL;
                        lvItem.iSubItem = 2;
                        lvItem.pszText = pAux.telefone;

                        SendMessage(hwndList,LVM_SETITEM,aux,(LPARAM)&lvItem);
                    }
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
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrão Windows para janelas
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
                            formAlterar = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_EXCLUIR_FORM), hwnd, formExcluirVeicBox);

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
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrão Windows para janelas
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
            formVeicDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_ADD_FORM), GetParent(hwnd), formAddVeic);
            break;

        case ID_BOTAO_ALTERAR_VEIC:
            formVeicDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_ALTERAR), GetParent(hwnd), formAlterarVeic);
            break;

        case ID_BOTAO_EXCLUIR_VEIC:
            formVeicDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_VEIC_EXCLUIR), GetParent(hwnd), formExcluirVeic);
            break;
        }

        guardaPegaHandle(&formVeicDlg, 0);
        return TRUE;
        break;
    }

    return FALSE;
}


