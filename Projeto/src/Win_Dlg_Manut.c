/********************************************//**
 ** @file Win_Dlg_Manut.c
 * @brief Contem as fun��es de controle da tabPage Manuten��o.
 * @bug Nao contem bugs conhecidos!
 *
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/
#include "../include/Win_Dlg_Manut.h"
#include "../include/Arvore_Prop.h"

/********************************************//**
 * \brief Le os dados do formulario de manuten��o
 *
 * \param hwnd 				- Manipulador da janela
 * \return Manutencao * 	- Endere�o de mem�ria do tipo Manuten��o contendo os dados lidos de um formulario
 *
 ***********************************************/
Manutencao *leDadosManutForm(HWND hwnd)
{
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

void atualizaComboBoxProp(Arvore *a, HWND comboBox)
{
 char nomeFormat[TAM_CPF + TAM_NOME + 3];
 if (a != NULL) {
    abb_imprime(a->esquerda);
    sprintf(nomeFormat, "%s (%s)", a->dado.cpf, a->dado.nome);
    ComboBox_AddString(comboBox, nomeFormat);
    abb_imprime(a->direita);
 }
}

void preencheComboBoxProp(HWND comboBox, char *filtroCPF){
    FILE *arqProp;
    Proprietario prop;
    ArvoreProp *arv;
    int cont = 0, x;

    ComboBox_ResetContent(comboBox);

    arv = inicializaArvoreProp();

    if(existeArquivo(ARQUIVO_DADOS_PROPRIETARIO) == ERRO_ARQUIVO_INEXISTENTE) return;

    arqProp = fopen(ARQUIVO_DADOS_PROPRIETARIO ,"rb");
    if(arqProp!=NULL){
        if(fread(&prop, sizeof(Proprietario), 1, arqProp) == 1){
            if(strnicmp(filtroCPF, prop.cpf, strlen(filtroCPF)) == 0){
                inserirNaArvoreProp(arv, prop);
                cont++;
            }
        }
    }

    atualizaComboBoxProp(arv, comboBox);

    liberaArvoreProp(arv);
}

/********************************************//**
 * \brief Atualiza a lista de manuten��es de acordo
 *        com a data inicial e a data final
 * \param hwndList 	- Manipulador de uma ListView Control
 * \param dataI 	- Uma struct do tipo Data contendo uma data inicial
 * \param dataF 	- Uma struct do tipo Data contendo uma data final
 *
 * \return void
 *
 ***********************************************/
void atualizaListaManut(HWND hwndList, Data dataI, Data dataF)
{

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
			
            if(win_trataErros(hwndList,fechaArquivo(arq)) != 0) return;
        }else{
            if(win_trataErros(hwndList, ERRO_ABRIR_ARQUIVO) != 0) return;
        }
    }

}

/********************************************//**
 * \brief Atualiza a lista de manuten��es de acordo
 *        com a data inicial e a data final
 * \param hwnd 		- Manipulador de uma janela
 * \param dataI 	- Uma struct do tipo Data contendo uma data inicial
 * \param dataF 	- Uma struct do tipo Data contendo uma data final
 *
 * \return void
 *
 ***********************************************/
void atualizaListaManutBusca(HWND hwnd, Data dataI, Data dataF)
{

    LVITEM lvItem;
    int cont = 0;
    Manutencao aux;
    char data[TAM_DATA];
    FILE *arq;
    float totalPecas = 0, totalObra = 0;
    char pontoFlutuante[10];
    HWND pecas, maoObra, hwndList;
    
    hwndList = GetDlgItem(hwnd, ID_MANUT_LIST);

    SendMessage(hwndList,LVM_DELETEALLITEMS,0,0);
    
	pecas = GetDlgItem(hwnd, ID_MANUT_TOTAL_PECAS);
	maoObra = GetDlgItem(hwnd, ID_MANUT_TOTAL_OBRA);

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

					totalPecas += aux.valorPecas;
					totalObra  += aux.valorObra;
					 
                    SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem); // Send info to the Listview

                    cont++;
                }
            }
            if(pecas && maoObra){
				sprintf(pontoFlutuante, "%.2f R$", totalPecas);
				Edit_SetText(pecas, pontoFlutuante);
				sprintf(pontoFlutuante, "%.2f R$", totalObra);
				Edit_SetText(maoObra, pontoFlutuante);
			}
			
            if(win_trataErros(hwndList,fechaArquivo(arq)) != 0) return;
        }else{
            if(win_trataErros(hwndList, ERRO_ABRIR_ARQUIVO) != 0) return;
        }
    }

}

/********************************************//**
 * \brief Atualiza a lista de manuten��es de acordo
 *        com a data inicial e a data final
 * \param hwndList 	- Manipulador de uma ListView Control
 * \param cpf		- Endere�o de mem�ria de uma string contendo um cpf
 * \param dataI 	- Uma struct do tipo Data contendo uma data inicial
 *
 * \return void
 *
 ***********************************************/
void atualizaListaManutExcluir(HWND hwndList, char *cpf,char *placa,Data dataI)
{

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
                if(comparaData(aux.data, dataI) == 0 && strnicmp(aux.cpf,cpf,strlen(cpf))==0 && strnicmp(aux.placa,placa,strlen(placa))==0){
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
            if(win_trataErros(hwndList,fechaArquivo(arq)) != 0) return;
        }else{
            if(win_trataErros(hwndList, ERRO_ABRIR_ARQUIVO) != 0) return;
        }
    }
}

/********************************************//**
 * \brief Nomeia as colunas da lista de Manuten��es
 *
 * \param hwndList - Manipulador de uma ListView Control
 * \return void
 *
 ***********************************************/
void inicializaListManut(HWND hwndList)
{
	ListView_SetExtendedListViewStyle(hwndList, LVS_REPORT | LVS_EX_FULLROWSELECT);
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
 * \brief Fun��o de controle do Dialogo "Ver dados"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usu�rio
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou n�o
 * \return Padr�o Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formDadosManutBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
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
				    auxAntigo = (Manutencao *)(pcds->lpData);
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
            case ID_BOTAO_SAIR_MANUT:
                EndDialog(hwnd, 0);
            break;
            }

        return TRUE;
        break;
    }
    return FALSE;
}


/********************************************//**
 * \brief Fun��o de controle da janela "Pesquisa Manuten��o"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usu�rio
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou n�o
 * \return Padr�o Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formPesquisarManut(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
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

            DateTime_GetSystemtime(GetDlgItem(hwnd, ID_MANUT_DATA_INICIO), &dateT);
            dataI = convertTime(dateT);
            DateTime_GetSystemtime(GetDlgItem(hwnd, ID_MANUT_DATA_FIM), &dateT);
            dataF = convertTime(dateT);
            atualizaListaManutBusca(hwnd, dataI, dataF);

            return TRUE;
        break;

        case WM_NOTIFY:

            switch(((LPNMHDR)lp)->code){

                case DTN_DATETIMECHANGE:{
                    DateTime_GetSystemtime(GetDlgItem(hwnd, ID_MANUT_DATA_INICIO), &dateT);
                    dataI = convertTime(dateT);
                    DateTime_GetSystemtime(GetDlgItem(hwnd, ID_MANUT_DATA_FIM), &dateT);
                    dataF = convertTime(dateT);
                    atualizaListaManutBusca(hwnd, dataI, dataF);
                }
                break;

            break;
            }

        break;

        case WM_COMMAND:

            iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);

            switch(LOWORD(wp)){
                case 3:
                    atualizaListaManutBusca(hwnd, dataI, dataF);
                break;
                case ID_MANUT_BOTAO_VER_DADOS:
                    if(iSelect == -1){
                        MessageBox(hwnd,"Nenhum proprietario selecionado!",
                        "Erro!",MB_OK|MB_ICONINFORMATION);
                    }else{
                        formExcluir = CreateDialog(NULL, MAKEINTRESOURCE(IDD_MANUT_DADOS_FORM), hwnd, (DLGPROC)formDadosManutBox);

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
 * \brief Inicializa um formul�rio de manuten��o
 *
 * \param hwnd 				- Manipulador da janela
 * \return void
 *
 ***********************************************/
void inicializaFormManut(HWND hwnd){
	
    SendMessage(GetDlgItem(hwnd, ID_EDIT_PLACA_MANUT), EM_LIMITTEXT, TAM_PLACA-1, 0);
    SendMessage(GetDlgItem(hwnd, ID_EDIT_CPF_MANUT), EM_LIMITTEXT, TAM_CPF-1, 0);
    SendMessage(GetDlgItem(hwnd, ID_EDIT_DESCRICAO_MANUT), EM_LIMITTEXT, TAM_DESCRICAO-1, 0);

    EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_MANUT), FALSE);
}

/********************************************//**
 * \brief le valida e libera o bot�o de a��o de manuten��o
 *
 * \param hwnd 				- Manipulador da janela
 * \return void
 *
 ***********************************************/
void validaLiberaFormManut(HWND hwnd){
    char cpf[TAM_CPF], placa[TAM_PLACA];

    GetDlgItemText(hwnd, ID_EDIT_CPF_MANUT, cpf, TAM_CPF);
    GetDlgItemText(hwnd, ID_EDIT_PLACA_MANUT, placa, TAM_PLACA);

    preencheComboBoxProp(GetDlgItem(hwnd, ID_EDIT_CPF_MANUT), cpf);

    if( GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_PECAS_MANUT)) > 0 &&
        validaCPF(cpf) == CPF_VALIDO && validaPlaca(placa) == PLACA_VALIDA &&
        GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_OBRA_MANUT)) > 0 &&
        GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_DESCRICAO_MANUT)) > 0){
        SetDlgItemText(hwnd, ID_MANUT_ADD_LOG, "");
        EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_MANUT), TRUE);
    }else{
        SetDlgItemText(hwnd, ID_MANUT_ADD_LOG, "");
        EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_MANUT), FALSE);
    }

    if(validaCPF(cpf) != CPF_VALIDO && strlen(cpf) == TAM_CPF-1) SetDlgItemText(hwnd, ID_MANUT_ADD_LOG, "O CPF inserido e invalido!");
    if(validaPlaca(placa) != PLACA_VALIDA && strlen(placa) == TAM_PLACA-1) SetDlgItemText(hwnd, ID_MANUT_ADD_LOG, "A placa inserida a invalida!");

}

/********************************************//**
 * \brief Fun��o de controle do janela "Adicionar Manuten��o"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuario
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou n�o
 * \return Padr�o Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formAddManut(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    Manutencao *aux;
    int erro;
    SYSTEMTIME data;

    switch(msg) {
        case WM_INITDIALOG:
            inicializaFormManut(hwnd);
        break;

        case WM_COMMAND:

            if(HIWORD(wp)==EN_CHANGE){
                formataCPF(GetDlgItem(hwnd, ID_EDIT_CPF_MANUT));
                formataPlaca(GetDlgItem(hwnd, ID_EDIT_PLACA_MANUT));
                editTextFloat(hwnd, ID_EDIT_PECAS_MANUT);
                editTextFloat(hwnd, ID_EDIT_OBRA_MANUT);
            }

            validaLiberaFormManut(hwnd);

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
 * \brief Fun��o de controle do Dialogo "Excluir Manutencao"
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
BOOL CALLBACK formExcluirManutBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Manutencao *auxAntigo;
    int erro;
    PCOPYDATASTRUCT pcds;
    HWND hwndList, *hwndAux;
    char valor[10];

    switch(msg) {
        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lp;
			auxAntigo = (Manutencao *)(pcds->lpData);
			if(pcds->dwData == 0){
				    auxAntigo = (Manutencao *)(pcds->lpData);
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
                    erro = excluiManutencao(auxAntigo->placa,auxAntigo->cpf, auxAntigo->data);

                    if(win_trataErros(hwnd, erro)==0){
                    	hwndAux = guardaPegaHandle(NULL, 1);
                    	hwndList = GetDlgItem(*hwndAux, ID_MANUT_EXCLUIR_LIST);
                    	ListView_DeleteAllItems(hwndList);
					}
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
 * \brief Fun��o de controle do janela "Exclui Manuten��o"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuario
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou n�o
 * \return Padr�o Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formExcluirManut(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    Manutencao *auxEnvio=NULL;
    int erro;
    static char cpf[TAM_CPF], placa[TAM_PLACA];
    static HWND hwndList,hwndProprio;
    Data dataI;
    int iSelect;
    static HINSTANCE g_inst;
    static HWND fromExclui;
    SYSTEMTIME dateT;
    COPYDATASTRUCT CDS;

    switch(msg) {
    	case WM_INITDIALOG:
    		hwndList = GetDlgItem(hwnd, ID_MANUT_EXCLUIR_LIST);
    		
    		SendMessage(GetDlgItem(hwnd, ID_MANUT_EXCLUIR_BUSCA_CPF), EM_LIMITTEXT, TAM_CPF-1, 0);
    		SendMessage(GetDlgItem(hwnd, ID_MANUT_EXCLUIR_BUSCA_PLACA), EM_LIMITTEXT, TAM_PLACA-1, 0);

    		GetLocalTime(&dateT);
		    DateTime_GetSystemtime(GetDlgItem(hwnd, ID_MANUT_EXCLUIR_BUSCA_DATA), &dateT);
		    dataI = convertTime(dateT);

    		inicializaListManut(hwndList);

    		GetDlgItemText(hwnd, ID_MANUT_EXCLUIR_BUSCA_PLACA, placa, TAM_PLACA);
            GetDlgItemText(hwnd, ID_MANUT_EXCLUIR_BUSCA_CPF, cpf, TAM_CPF);

    		atualizaListaManutExcluir(hwndList,cpf,placa,dataI);

    		return TRUE;
    		break;
    	case WM_COMMAND:
            iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);

			DateTime_GetSystemtime(GetDlgItem(hwnd, ID_MANUT_EXCLUIR_BUSCA_DATA), &dateT);
		    dataI = convertTime(dateT);

            if(HIWORD(wp) == EN_CHANGE){

					formataCPF(GetDlgItem(hwnd, ID_MANUT_EXCLUIR_BUSCA_CPF));
		    		formataPlaca(GetDlgItem(hwnd, ID_MANUT_EXCLUIR_BUSCA_PLACA));

                    GetDlgItemText(hwnd, ID_MANUT_EXCLUIR_BUSCA_PLACA, placa, TAM_PLACA);
                    GetDlgItemText(hwnd, ID_MANUT_EXCLUIR_BUSCA_CPF, cpf, TAM_CPF);

           			atualizaListaManutExcluir(hwndList,cpf,placa,dataI);
            }
            switch(LOWORD (wp)){
            	case ID_MANUT_EXCLUIR_BOTAO:
            		if(iSelect == -1){
                            MessageBox(hwnd,"Nenhum veiculo selecionado!",
                            "Erro!",MB_OK|MB_ICONERROR);
                            return FALSE;
                        }else{
                            fromExclui = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_MANUT_EXCLUIR_FORM), hwnd, (DLGPROC)formExcluirManutBox);

                            ListView_GetItemText(hwndList, iSelect, 0, placa, TAM_PLACA);
                            ListView_GetItemText(hwndList, iSelect, 1, cpf, TAM_CPF);

                            auxEnvio = (Manutencao *)malloc(sizeof(Manutencao));

                            pegaManutencao(placa,cpf,dataI,auxEnvio);

                            CDS.dwData = 0;
                            CDS.cbData = sizeof(Manutencao);
                            CDS.lpData = auxEnvio;

                            SendMessage(fromExclui, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
                            SetDlgItemText(hwnd, ID_MANUT_EXCLUIR_BUSCA_CPF, "");
                            SetDlgItemText(hwnd, ID_MANUT_EXCLUIR_BUSCA_PLACA, "");

                            return TRUE;
                        }
            		break;
            	case ID_MANUT_EXCLUIR_ATUALIZAR_BOTAO:
                    SetDlgItemText(hwnd, ID_MANUT_EXCLUIR_BUSCA_CPF, "");
                    SetDlgItemText(hwnd, ID_MANUT_EXCLUIR_BUSCA_PLACA, "");
                    return TRUE;
                break;
			}
			return TRUE;
			break;
		case WM_NOTIFY:
			switch (((LPNMHDR)lp)->code){
				case DTN_DATETIMECHANGE:
					DateTime_GetSystemtime(GetDlgItem(hwnd, ID_MANUT_EXCLUIR_BUSCA_DATA), &dateT);
		  			dataI = convertTime(dateT);
		  			atualizaListaManutExcluir(hwndList,cpf,placa,dataI);
		  			break;
			}
			break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Fun��o de controle da tabPage "Manuten��o"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuario
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padr�o Windows para janelas
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
            formManutDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_MANUT_ADD_FORM), GetParent(hwnd), (DLGPROC)formAddManut);
            break;

        case ID_BOTAO_PESQUISAR_MANUT:
            formManutDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_MANUT_DADOS), GetParent(hwnd), (DLGPROC)formPesquisarManut);
            break;

        case ID_BOTAO_EXCLUIR_MANUT:
        	formManutDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_MANUT_EXCLUIR), GetParent(hwnd), (DLGPROC)formExcluirManut);
        	break;
        }

        guardaPegaHandle(&formManutDlg, 0);
        return TRUE;
        break;
    }

    return FALSE;
}
