/********************************************//**
 ** @file Win_Dlg_Prop.c
 * @brief Contem as fun��es de controle da tabPage Proprietario.
 * @bug Nao contem bugs conhecidos!
 *
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

#include "../include/Win_Dlg_Prop.h"

/********************************************//**
 * \brief Atualiza a lista de proprietarios em ordem alfabetica
 * 
 * \param a - Arvore com os proprietarios ordenados
 * \param list - Manipulador de uma ListView Control
 *
 * \return void
 *
 ***********************************************/

void atualizaListaArvProp(Arvore *a, HWND list)
{
	 LVITEM lvItem;
	 char tel[TAM_TEL + TAM_DDD + 2];
	 
	 if (a != NULL) {

	    atualizaListaArvProp(a->direita, list);
	    
	    lvItem.mask=LVIF_TEXT;
        lvItem.cchTextMax = TAM_NOME;
        lvItem.iItem=0;
        lvItem.iSubItem=0;
        lvItem.pszText= a->dado.nome;

        ListView_InsertItem(list, &lvItem);

        lvItem.iSubItem = 1;
        lvItem.pszText = a->dado.cpf;

        SendMessage(list,LVM_SETITEM,0,(LPARAM)&lvItem);

        lvItem.iSubItem = 2;
        sprintf(tel, "(%s) %s", a->dado.telefone.ddd, a->dado.telefone.telefone);
        lvItem.pszText = tel;

        SendMessage(list,LVM_SETITEM,0,(LPARAM)&lvItem);
        
	    atualizaListaArvProp(a->esquerda, list);
	    
	    
	 }
}

/********************************************//**
 * \brief Atualiza a lista de proprietarios de acordo
 *        com o cpf e o nome
 * \param hwndList 	- Manipulador de uma ListView Control
 * \param cpf		- Endere�o de mem�ria de uma string contendo um cpf
 * \param nome		- Endere�o de mem�ria de uma string contendo um nome
 *
 * \return void
 *
 ***********************************************/
void atualizaListaProp(HWND hwndList, char *cpf, char *nome)
{
    Proprietario aux;
    FILE *arq;
    Arvore *arv;
    
    SendMessage(hwndList,LVM_DELETEALLITEMS,0,0);
    
    arv = inicializaArvoreProp();

    if(strlen(cpf) != 0 || strlen(nome) != 0){
        if(existeArquivo(ARQUIVO_DADOS_PROPRIETARIO)){
            arq = fopen(ARQUIVO_DADOS_PROPRIETARIO, "rb");
            if(arq != NULL){
                while(fread(&aux, sizeof(Proprietario), 1, arq) == 1){
                    if(strnicmp(aux.cpf, cpf, strlen(cpf)) == 0 && (strnicmp(aux.nome, nome, strlen(nome)) == 0 || stristr(aux.nome, nome) != NULL)){
                    	arv = inserirNaArvoreProp(arv, aux);
                    }
                }
                
                
                if(win_trataErros(hwndList,fechaArquivo(arq)) != 0) return;
            }else{
                if(win_trataErros(hwndList, ERRO_ABRIR_ARQUIVO) != 0) return;
            }
        }
    }
    
    atualizaListaArvProp(arv, hwndList);
    
    liberaArvoreProp(arv);
}

/********************************************//**
 * \brief Le os dados do formulario de proprietario
 *
 * \param hwnd 				- Manipulador da janela
 * \return Manutencao * 	- Endere�o de mem�ria do tipo Proprietario contendo os dados lidos de um formulario
 *
 ***********************************************/
Proprietario *leDadosPropForm(HWND hwnd)
{
    Proprietario *aux;
    aux = (Proprietario *)malloc(sizeof(Proprietario));

    GetDlgItemText(hwnd, ID_EDIT_NOME_PROP, aux->nome, TAM_NOME);
    GetDlgItemText(hwnd, ID_EDIT_CPF_PROP, aux->cpf, TAM_CPF);
    GetDlgItemText(hwnd, ID_EDIT_CIDADE_PROP, aux->endereco.cidade, TAM_CIDADE);
    GetDlgItemText(hwnd, ID_EDIT_ESTADO_PROP, aux->endereco.estado, TAM_ESTADO);
    GetDlgItemText(hwnd, ID_EDIT_DESCRICAO_PROP, aux->endereco.descricao, TAM_DESCRICAO);
    GetDlgItemText(hwnd, ID_EDIT_DDD_PROP, aux->telefone.ddd, TAM_DDD);
    GetDlgItemText(hwnd, ID_EDIT_TELEFONE_PROP, aux->telefone.telefone, TAM_TEL);

    return aux;
}

/********************************************//**
 * \brief Preenche um formulario de proprietario
 *
 * \param hwndForm	- Manipulador da janela
 * \param prop		- Endere�o de mem�ria de uma struct do tipo Proprietario
 *
 * \return void
 *
 ***********************************************/
void preencheFormProp(HWND hwndForm, Proprietario *prop){
    HWND hwndComboBox;

    SetDlgItemText(hwndForm, ID_EDIT_NOME_PROP, prop->nome);
    SetDlgItemText(hwndForm, ID_EDIT_CPF_PROP, prop->cpf);
    SetDlgItemText(hwndForm, ID_EDIT_CIDADE_PROP, prop->endereco.cidade);
    hwndComboBox = GetDlgItem(hwndForm, ID_EDIT_ESTADO_PROP);
    ComboBox_SetCurSel(hwndComboBox,ComboBox_FindString(hwndComboBox, -1, prop->endereco.estado));
    SetDlgItemText(hwndForm, ID_EDIT_DESCRICAO_PROP, prop->endereco.descricao);
    SetDlgItemText(hwndForm, ID_EDIT_DDD_PROP, prop->telefone.ddd);
    SetDlgItemText(hwndForm, ID_EDIT_TELEFONE_PROP, prop->telefone.telefone);
}

/********************************************//**
 * \brief Inicializa um formul�rio de Proprietario
 *
 * \param hwnd - Manipulador de uma ListView Control
 * \return void
 *
 ***********************************************/
void inicializaFormProp(HWND hwnd)
{
        HWND hwndCombo = GetDlgItem(hwnd, ID_EDIT_ESTADO_PROP);

        Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_NOME_PROP), TAM_NOME-1);
        Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_CPF_PROP), TAM_CPF-1);
        Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_CIDADE_PROP), TAM_CIDADE-1);
        Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_DESCRICAO_PROP), TAM_DESCRICAO-1);
        Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_TELEFONE_PROP), TAM_TEL-1);
        Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_DDD_PROP), TAM_DDD-1);

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

}

/********************************************//**
 * \brief le valida e libera o bot�o de a��o de proprietario
 *
 * \param hwnd 				- Manipulador da janela
 * \return void
 *
 ***********************************************/
void validaLiberaFormProp(HWND hwnd)
{
        char cpf[TAM_CPF], tel[TAM_TEL], ddd[TAM_DDD];
        int aux;

        HWND editCPF = GetDlgItem(hwnd, ID_EDIT_CPF_PROP);
        HWND editTel = GetDlgItem(hwnd, ID_EDIT_TELEFONE_PROP);

        GetDlgItemText(hwnd, ID_EDIT_CPF_PROP, cpf, TAM_CPF);
        GetDlgItemText(hwnd, ID_EDIT_TELEFONE_PROP, tel, TAM_TEL);
        GetDlgItemText(hwnd, ID_EDIT_DDD_PROP, ddd, TAM_DDD);

        aux = tel[0] - '0';
        if(aux > 5 && aux < 10){
            Edit_LimitText(editTel, TAM_TEL-1);
        }

        if( Edit_GetTextLength(GetDlgItem(hwnd, ID_EDIT_NOME_PROP)) > 0 &&
            validaCPF(cpf) == CPF_VALIDO && validaTelefone(tel) == TEL_VALIDO && validaDDD(ddd) == DDD_VALIDO&&
            Edit_GetTextLength(GetDlgItem(hwnd, ID_EDIT_CIDADE_PROP)) > 0 &&
            Edit_GetTextLength(GetDlgItem(hwnd, ID_EDIT_DESCRICAO_PROP)) > 0){
            SetDlgItemText(hwnd, ID_PROP_ADD_LOG, "");
            Button_Enable(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), TRUE);
        }else{
            SetDlgItemText(hwnd, ID_PROP_ADD_LOG, "");
            Button_Enable(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), FALSE);
        }

        formataCPF(editCPF);
        formataTel(editTel);

        if(validaCPF(cpf) != CPF_VALIDO && strlen(cpf) > 0) SetDlgItemText(hwnd, ID_PROP_ADD_LOG, "O CPF inserido eh invalido!");
        if(validaTelefone(tel) != TEL_VALIDO && strlen(tel) > 0) SetDlgItemText(hwnd, ID_PROP_ADD_LOG, "O telefone inserido eh invalido!");
        if(validaDDD(ddd) != DDD_VALIDO && strlen(ddd) > 0) SetDlgItemText(hwnd, ID_PROP_ADD_LOG, "O DDD inserido eh invalido!");

}

/********************************************//**
 * \brief Fun��o de controle do janela "Adicionar Proprietario"
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
BOOL CALLBACK formAddProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    Proprietario *aux;
    int erro;

    switch(msg) {
        case WM_INITDIALOG:
        inicializaFormProp(hwnd);

        EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), FALSE);
        break;

        case WM_COMMAND:

            formataCPF(GetDlgItem(hwnd, ID_EDIT_CPF_PROP));

            if(HIWORD(wp) == EN_CHANGE) validaLiberaFormProp(hwnd);

            switch(wp){
            case ID_BOTAO_ACAO_PROP:
                aux = leDadosPropForm(hwnd);
                erro = incluiProprietario(*aux);
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
 * \brief Fun��o de controle do Dialogo "Alterar Proprietario"
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
BOOL CALLBACK formAlterarPropBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    Proprietario *aux;
    static Proprietario *auxAntigo;
    int erro;
    char cpf[TAM_CPF], tel[TAM_TEL];
    PCOPYDATASTRUCT pcds;

    switch(msg) {
        case WM_INITDIALOG:
        inicializaFormProp(hwnd);

        EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), FALSE);
        return TRUE;
        break;

        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lp;
			auxAntigo = (Proprietario *)(pcds->lpData);
			switch(pcds->dwData){
				case 0:
                    preencheFormProp(hwnd, auxAntigo);
                break;
			}
        return TRUE;
        break;

        case WM_COMMAND:


            validaLiberaFormProp(hwnd);

            switch(wp){
            case ID_BOTAO_ACAO_PROP:

                    aux = leDadosPropForm(hwnd);

                    erro = alteraProprietario(*aux, auxAntigo->cpf);
                    free(aux);
                    if(win_trataErros(hwnd, erro) == 0){
                    EndDialog(hwnd, 0);
                    }
            break;

            case ID_BOTAO_CANCELAR_PROP:
                EndDialog(hwnd, 0);
            break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Fun��o de controle do Dialogo "Excluir Proprietario"
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
BOOL CALLBACK formExcluirPropBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Proprietario *auxAntigo;
    int erro;
    PCOPYDATASTRUCT pcds;

    switch(msg) {
        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lp;
			auxAntigo = (Proprietario *)(pcds->lpData);
			switch(pcds->dwData){
				case 0:
				    inicializaFormProp(hwnd);
                    preencheFormProp(hwnd, auxAntigo);
                break;
			}
        return TRUE;
        break;

        case WM_COMMAND:
            switch(wp){
            case ID_BOTAO_ACAO_PROP:
                    erro = excluiProprietario(auxAntigo->cpf);
                    win_trataErros(hwnd, erro);
                    EndDialog(hwnd, 0);
            break;

            case ID_BOTAO_CANCELAR_PROP:
                EndDialog(hwnd, 0);
            break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}


/********************************************//**
 * \brief Nomeia as colunas da lista de proprietarios
 *
 * \param hwndList 	- Manipulador de uma ListView Control
 * \return void
 *
 ***********************************************/
void inicializaListProp(HWND hwndList)
{
	ListView_SetExtendedListViewStyle(hwndList, LVS_REPORT | LVS_EX_FULLROWSELECT);

    LVCOLUMN lvCol;

    lvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
    lvCol.cx=28;

    lvCol.pszText="Nome";
    lvCol.cx=120;
    ListView_InsertColumn(hwndList, 0, &lvCol);


    lvCol.pszText="CPF";
    lvCol.cx=120;
    ListView_InsertColumn(hwndList, 1, &lvCol);


    lvCol.pszText="Telefone";
    lvCol.cx=103;
    ListView_InsertColumn(hwndList, 2, &lvCol);
}

/********************************************//**
 * \brief Fun��o de controle da janela "Alterar Proprietario"
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
BOOL CALLBACK formAlterarProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Proprietario auxEnvio;
    static HINSTANCE g_inst;
    static HWND hwndList;
    int iSelect;
    char cpf[TAM_CPF], nome[TAM_NOME];
    LV_ITEM lvItem;
    COPYDATASTRUCT CDS;
    HWND formAlterar;

    switch(msg) {
        case WM_INITDIALOG:
            hwndList = GetDlgItem(hwnd, ID_PROP_LIST);
            inicializaListProp(GetDlgItem(hwnd, ID_PROP_LIST));

            Edit_LimitText(GetDlgItem(hwnd, ID_PROP_BUSCA_CPF), TAM_CPF-1);
            Edit_LimitText(GetDlgItem(hwnd, ID_PROP_BUSCA_NOME), TAM_NOME-1);
            return TRUE;
        break;

        case WM_COMMAND:

            iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);

            formataCPF(GetDlgItem(hwnd, ID_PROP_BUSCA_CPF));

            if(HIWORD(wp) == EN_CHANGE){

                GetDlgItemText(hwnd, ID_PROP_BUSCA_CPF, cpf, TAM_CPF);
                GetDlgItemText(hwnd, ID_PROP_BUSCA_NOME, nome, TAM_NOME);
                atualizaListaProp(hwndList, cpf, nome);

            }
            switch(LOWORD(wp)){
                case ID_BOTAO_ACAO_PROP:
                    if(iSelect == -1){
                        MessageBox(hwnd,"Nenhum proprietario selecionado!",
                        "Erro!",MB_OK|MB_ICONINFORMATION);
                    }else{
                        formAlterar = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_ALTERAR_FORM), hwnd, (DLGPROC)formAlterarPropBox);

                        ListView_GetItemText(hwndList, iSelect, 1, cpf, TAM_CPF);
                        pegaProprietario(cpf, &auxEnvio);

                        CDS.dwData = 0;
                        CDS.cbData = sizeof(Proprietario);
                        CDS.lpData = &auxEnvio;

                        SendMessage(formAlterar, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_CPF, "");
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_NOME, "");
                    }
                break;

                case ID_PROP_LIMPAR_BOTAO:
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_CPF, "");
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_NOME, "");
                break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Fun��o de controle da janela "Excluir Proprietario"
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
BOOL CALLBACK formExcluirProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Proprietario auxEnvio;
    static HINSTANCE g_inst;
    static HWND hwndList;
    int  iSelect;
    char cpf[TAM_CPF], nome[TAM_NOME];
    LV_COLUMN lvCol;
    LV_ITEM lvItem;
    COPYDATASTRUCT CDS;
    HWND formExcluir;

    switch(msg) {
        case WM_INITDIALOG:
            hwndList = GetDlgItem(hwnd, ID_PROP_LIST);

            inicializaListProp(hwndList);

            Edit_LimitText(GetDlgItem(hwnd, ID_PROP_BUSCA_CPF), TAM_CPF-1);
            Edit_LimitText(GetDlgItem(hwnd, ID_PROP_BUSCA_NOME), TAM_NOME-1);
        return TRUE;
        break;

        case WM_COMMAND:

            iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);

            formataCPF(GetDlgItem(hwnd, ID_PROP_BUSCA_CPF));

            if(HIWORD(wp) == EN_CHANGE){
                GetDlgItemText(hwnd, ID_PROP_BUSCA_CPF, cpf, TAM_CPF);
                GetDlgItemText(hwnd, ID_PROP_BUSCA_NOME, nome, TAM_NOME);
                atualizaListaProp(hwndList, cpf, nome);
            }
            switch(LOWORD(wp)){
                case ID_BOTAO_ACAO_PROP:
                    if(iSelect == -1){
                        MessageBox(hwnd,"Nenhum proprietario selecionado!",
                        "Erro!",MB_OK|MB_ICONINFORMATION);
                    }else{
                        formExcluir = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_EXCLUIR_FORM), hwnd, (DLGPROC)formExcluirPropBox);

                        ListView_GetItemText(hwndList, iSelect, 1, cpf, TAM_CPF);

                        pegaProprietario(cpf, &auxEnvio);

                        CDS.dwData = 0;
                        CDS.cbData = sizeof(Proprietario);
                        CDS.lpData = &auxEnvio;

                        SendMessage(formExcluir, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_CPF, "");
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_NOME, "");
                    }
                break;

                case ID_PROP_LIMPAR_BOTAO:
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_CPF, "");
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_NOME, "");
                break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Atualiza uma lista de veiculos de um proprietario de
 *        acordo com uma placa
 * \param hwndList 	- Manipulador de uma ListView Control
 * \param placa  	- Placa que ser� utilizada como filtro na pesquisa
 * \return void
 *
 ***********************************************/
void atualizaListaVeicProp(HWND hwndList, char *placa)
{

    LVITEM lvItem;
    static int cont = 0;
    Veiculo aux;
    FILE *arq;

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
    }else{
    	cont = 0;
	}
}


/********************************************//**
 * \brief Fun��o de controle da janela "Mostra veiculos de um prorpietario que ja foi pra manutencao"
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
BOOL CALLBACK formMostraVeicProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Veiculo *auxEnvio;
    static HINSTANCE g_inst;
    static HWND hwndList, formVerDados;
    int iSelect, qtManut, aux;
    char cpf[TAM_CPF], placa[TAM_PLACA];
    Manutencao *manut = NULL;
    LV_ITEM lvItem;
    COPYDATASTRUCT CDS;
    HWND formAlterar;

    switch(msg) {
        case WM_INITDIALOG:
        	SendMessage(GetDlgItem(hwnd, ID_PROP_BUSCA_CPF), EM_LIMITTEXT, TAM_CPF-1, 0);
            hwndList = GetDlgItem(hwnd, ID_VEIC_LIST);
            inicializaListVeic(GetDlgItem(hwnd, ID_VEIC_LIST));

            return TRUE;
        break;

        case WM_COMMAND:

            iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);

            formataCPF(GetDlgItem(hwnd, ID_PROP_BUSCA_CPF));

            if(HIWORD(wp) == EN_CHANGE){
    			SendMessage(hwndList,LVM_DELETEALLITEMS,0,0);
    			atualizaListaVeicProp(GetDlgItem(hwnd, ID_VEIC_LIST), "");

                GetDlgItemText(hwnd, ID_PROP_BUSCA_CPF, cpf, TAM_CPF);
                if(strlen(cpf) == TAM_CPF-1){


	                manut = carregaManutencoesCPF(cpf, &qtManut);

		            if(manut != NULL){

						for(aux = 0; aux<qtManut;aux++){
							atualizaListaVeicProp(GetDlgItem(hwnd, ID_VEIC_LIST), manut[aux].placa);
						}

						free(manut);
		            }

            	}

            }
            switch(LOWORD(wp)){
                case ID_BOTAO_ACAO_PROP:
                    if(iSelect == -1){
                        MessageBox(hwnd,"Nenhum veiculo selecionado!",
                        "Erro!",MB_OK|MB_ICONINFORMATION);
                    }else{
						formVerDados = CreateDialog(NULL, MAKEINTRESOURCE(IDD_VEIC_MOSTRA_DADOS_FORM), hwnd, (DLGPROC)formDadosVeicBox);

                        ListView_GetItemText(hwndList, iSelect, 1, placa, TAM_PLACA);

						auxEnvio = (Veiculo *)malloc(sizeof(Veiculo));
                        pegaVeiculo(placa, auxEnvio);

                        CDS.dwData = 0;
                        CDS.cbData = sizeof(Veiculo);
                        CDS.lpData = auxEnvio;

                        SendMessage(formVerDados, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
                    }
                break;

                case ID_PROP_MOSTRAR_ATUALIZAR_BOTAO:
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_CPF, "");
                break;
            }
        return TRUE;
        break;

    }
    return FALSE;
}

/********************************************//**
 * \brief Fun��o de controle do Dialogo "Pesquisar Proprietario"
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
BOOL CALLBACK formPesquisarPropBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Proprietario *auxAntigo;
    int erro;
    PCOPYDATASTRUCT pcds;
    switch(msg) {
        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lp;
			auxAntigo = (Proprietario *)(pcds->lpData);
			switch(pcds->dwData){
				case 0:
				    inicializaFormProp(hwnd);
                    preencheFormProp(hwnd, auxAntigo);
                break;
			}
        return TRUE;
        break;

        case WM_COMMAND:
            switch(wp){
	            case ID_BOTAO_CANCELAR_PROP:
	                EndDialog(hwnd, 0);
	            	break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Fun��o de controle da janela "Pesquisar Proprietario"
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
BOOL CALLBACK formPesquisarProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Proprietario auxEnvio;
    static HINSTANCE g_inst;
    static HWND hwndList;
    int  iSelect;
    char cpf[TAM_CPF], nome[TAM_NOME];
    LV_COLUMN lvCol;
    LV_ITEM lvItem;
    COPYDATASTRUCT CDS;
    HWND formPesquisar;

    switch(msg) {
        case WM_INITDIALOG:

            hwndList = GetDlgItem(hwnd, ID_PROP_LIST);

            inicializaListProp(hwndList);

            Edit_LimitText(GetDlgItem(hwnd, ID_PROP_BUSCA_CPF), TAM_CPF-1);
            Edit_LimitText(GetDlgItem(hwnd, ID_PROP_BUSCA_NOME), TAM_NOME-1);

        return TRUE;
        break;

        case WM_COMMAND:

            iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);

            formataCPF(GetDlgItem(hwnd, ID_PROP_BUSCA_CPF));

            if(HIWORD(wp) == EN_CHANGE){
                GetDlgItemText(hwnd, ID_PROP_BUSCA_CPF, cpf, TAM_CPF);
                GetDlgItemText(hwnd, ID_PROP_BUSCA_NOME, nome, TAM_NOME);
                atualizaListaProp(hwndList, cpf, nome);
            }
            switch(LOWORD(wp)){
                case ID_BOTAO_ACAO_PROP:
                    if(iSelect == -1){

                        MessageBox(hwnd,"Nenhum proprietario selecionado!", "Erro!",MB_OK|MB_ICONINFORMATION);

                    }else{

                        formPesquisar = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_PESQUISAR_FORM), hwnd, (DLGPROC)formPesquisarPropBox);

                        ListView_GetItemText(hwndList, iSelect, 1, cpf, TAM_CPF);

                        pegaProprietario(cpf, &auxEnvio);

                        CDS.dwData = 0;
                        CDS.cbData = sizeof(Proprietario);
                        CDS.lpData = &auxEnvio;

						SendMessage(formPesquisar, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_CPF, "");
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_NOME, "");
                    }
                break;

                case ID_PROP_LIMPAR_BOTAO:
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_CPF, "");
                        SetDlgItemText(hwnd, ID_PROP_BUSCA_NOME, "");
                break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}


/********************************************//**
 * \brief Fun��o de controle da tabPage "Proprietario"
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
BOOL CALLBACK tabPropPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND formPropDlg, *formAux;
    static HINSTANCE g_inst;

    switch(msg) {
    case WM_COMMAND:

        formAux = guardaPegaHandle(NULL, 1);
        if(formAux != NULL) EndDialog(*formAux, 0);

        switch (wp) {
        case ID_BOTAO_ADD_PROP:
            formPropDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_ADD_FORM), GetParent(hwnd), (DLGPROC)formAddProc);
            break;

        case ID_BOTAO_ALTERAR_PROP:
            formPropDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_ALTERAR), GetParent(hwnd), (DLGPROC)formAlterarProc);
            break;

        case ID_BOTAO_EXCLUIR_PROP:
            formPropDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_EXCLUIR), GetParent(hwnd), (DLGPROC)formExcluirProc);
            break;

        case ID_BOTAO_PESQUISAR_PROP:
        	formPropDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_PESQUISAR), GetParent(hwnd), (DLGPROC)formPesquisarProc);
        	break;

        case ID_BOTAO_APRESENTAR_VEIC_PROP:
        	formPropDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_MOSTRA_VEIC), GetParent(hwnd), (DLGPROC)formMostraVeicProc);
        	break;

        }

        guardaPegaHandle(&formPropDlg, 0);
        return TRUE;
    }
    return FALSE;
}
