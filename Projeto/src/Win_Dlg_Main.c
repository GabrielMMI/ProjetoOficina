/********************************************//**
 ** @file Win_Dlg_Main.c
 * @brief Implementa todas as funções de Win_Dlg_Main.h
 *
 *
 * @bug Nenhum problema conhecido!
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

#include "../include/Win_Dlg_Main.h"

/********************************************//**
 * \brief Função de controle da janela "Créditos"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK creditosProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{

    switch(msg) {
        case WM_INITDIALOG:
            Animate_Open(GetDlgItem(hwnd, ID_GIF_CREDITOS), "res/matheus.avi");
            Animate_Play(GetDlgItem(hwnd, ID_GIF_CREDITOS), 0, -1, -1);

            Animate_Open(GetDlgItem(hwnd, ID_GIF_CREDITOS_2), "res/gabriel.avi");
            Animate_Play(GetDlgItem(hwnd, ID_GIF_CREDITOS_2), 0, -1, -1);
            return TRUE;
        break;

        case WM_COMMAND:
        return TRUE;
        break;

        case WM_CLOSE:
            EndDialog(hwnd, 0);
        break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Função de controle do formulario auto-completo de Proprietario
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK mostraDadosProp(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
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
    }
    return FALSE;
}

/********************************************//**
 * \brief Função de controle do formulario auto-completo de Veiculo
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK mostraDadosVeic(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static Veiculo *auxAntigo;
    int erro;
    PCOPYDATASTRUCT pcds;

    switch(msg) {
        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lp;
			if(pcds->dwData == 0){
				auxAntigo = (Veiculo *)(pcds->lpData);
                preencheFormVeic(hwnd, auxAntigo);
            }
        return TRUE;
        break;

    }
    return FALSE;
}

/********************************************//**
 * \brief Função de controle do formulario auto-completo de Manutenção
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK mostraDadosManut(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
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
    return TRUE;
    break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Função de controle da janela "Apresentar todos os dados"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informações adicionais sobre o comando ou não
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK apresentaTodosDadosProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static HWND hwndTree, telaAux, *hwndAux;
	HWND editControl;
	static Proprietario auxProp;
	static Veiculo auxVeic;
	static Manutencao auxManut;
	TV_INSERTSTRUCT tvinsert;
	TVITEM tvitem;
	int qtProp, aux, auxV, iSelect;
	static HTREEITEM noProp, noVeic, noManut, noVeicManut, noSelected, noAux;
    static HINSTANCE g_inst;
	FILE *arqProp;
	Proprietario *proprietarios;
	Manutencao *manutencoes;
	Veiculo *veiculos;
	char data[TAM_DATA], cpf[TAM_CPF], placa[TAM_PLACA];
	Data dataAux;
	COPYDATASTRUCT CDS;

    switch(msg) {
        case WM_INITDIALOG:
			hwndTree = GetDlgItem(hwnd, ID_MOSTRA_DADOS_TREE_VIEW);
			
			tvinsert.hParent=NULL;
			tvinsert.hInsertAfter=TVI_ROOT;
			tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;

			tvinsert.item.pszText="Proprietários";
			noProp=(HTREEITEM)SendDlgItemMessage(hwnd, ID_MOSTRA_DADOS_TREE_VIEW,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

			tvinsert.item.pszText="Veiculos";
			noVeic=(HTREEITEM)SendDlgItemMessage(hwnd, ID_MOSTRA_DADOS_TREE_VIEW,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

			tvinsert.item.pszText="Manutenções";
			noManut=(HTREEITEM)SendDlgItemMessage(hwnd, ID_MOSTRA_DADOS_TREE_VIEW,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

			proprietarios = carregaProprietarios();

			if(proprietarios != NULL){
				for(aux = 0; aux < obtemQuantPropArquivo(); aux++){
					tvinsert.hParent=noProp;
					tvinsert.hInsertAfter=TVI_ROOT;

					tvinsert.item.pszText=proprietarios[aux].cpf;
					SendDlgItemMessage(hwnd, ID_MOSTRA_DADOS_TREE_VIEW,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
				}
				free(proprietarios);
			}

			veiculos = carregaVeiculos();

			if(veiculos != NULL){
				for(aux = 0; aux < obtemQuantVeicArquivo(); aux++){
					tvinsert.hParent=noVeic;
					tvinsert.hInsertAfter=TVI_ROOT;

					tvinsert.item.pszText=veiculos[aux].placa;
					SendDlgItemMessage(hwnd, ID_MOSTRA_DADOS_TREE_VIEW,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
				}
				free(veiculos);
			}

			manutencoes = carregaManutencoes();

			if(manutencoes != NULL){
				for(aux = 0; aux < obtemQuantManutArquivo(); aux++){
					if(comparaData(dataAux,  manutencoes[aux].data) != 0){
						tvinsert.hParent=noManut;
						tvinsert.hInsertAfter=TVI_ROOT;

						dataAux =  manutencoes[aux].data;
						converteDataString(data, dataAux);

						tvinsert.item.pszText = data;

						noVeicManut = (HTREEITEM)SendDlgItemMessage(hwnd, ID_MOSTRA_DADOS_TREE_VIEW,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

						for(auxV = 0; auxV < obtemQuantManutArquivo(); auxV++){
							if(comparaData(dataAux,  manutencoes[auxV].data) == 0){

								tvinsert.hParent=noVeicManut;
								tvinsert.hInsertAfter=TVI_ROOT;

								tvinsert.item.pszText=manutencoes[auxV].placa;
								SendDlgItemMessage(hwnd, ID_MOSTRA_DADOS_TREE_VIEW,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

							}
						}
					}
				}

				free(manutencoes);
			}
			
            return TRUE;
        break;

        case WM_COMMAND:
        	
        	return TRUE;
        break;

		case WM_NOTIFY:
		      switch(LOWORD(wp))
		      {
		        case ID_MOSTRA_DADOS_TREE_VIEW:
		          if(((LPNMHDR)lp)->code == NM_DBLCLK)
		          {
		          	
				   	noSelected = TreeView_GetNextItem(hwndTree, noSelected, TVGN_CARET);
				   	
		        	if(noSelected != NULL){
						
						hwndAux = guardaPegaHandle(NULL, 1);
	        			if(hwndAux != NULL) EndDialog(*hwndAux, 0);
						
						if(TreeView_GetParent(hwndTree, noSelected) == noProp){
							telaAux = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_TODOS_DADOS_PROP), hwnd, (DLGPROC)mostraDadosProp);
							
							tvitem.hItem = noSelected;
							tvitem.mask = TVIF_TEXT;
							tvitem.pszText = cpf;
							tvitem.cchTextMax = TAM_CPF;
							
							TreeView_GetItem(hwndTree, &tvitem);
							
							pegaProprietario(cpf, &auxProp);

	                        CDS.dwData = 0;
	                        CDS.cbData = sizeof(Proprietario);
	                        CDS.lpData = &auxProp;
	
	                        SendMessage(telaAux, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
						}
						
						if(TreeView_GetParent(hwndTree, noSelected) == noVeic){
							telaAux = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_TODOS_DADOS_VEIC), hwnd, (DLGPROC)mostraDadosVeic);
							
							tvitem.hItem = noSelected;
							tvitem.mask = TVIF_TEXT;
							tvitem.pszText = placa;
							tvitem.cchTextMax = TAM_PLACA;
							
							TreeView_GetItem(hwndTree, &tvitem);
							
							pegaVeiculo(placa, &auxVeic);

	                        CDS.dwData = 0;
	                        CDS.cbData = sizeof(Veiculo);
	                        CDS.lpData = &auxVeic;
	
	                        SendMessage(telaAux, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
						}
						
						if(TreeView_GetParent(hwndTree, TreeView_GetParent(hwndTree, noSelected)) == noManut){
							telaAux = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_TODOS_DADOS_MANUT), hwnd, (DLGPROC)mostraDadosManut);
							
							noAux = TreeView_GetParent(hwndTree, noSelected);
							tvitem.hItem = noAux;
							tvitem.mask = TVIF_TEXT;
							tvitem.pszText = data;
							tvitem.cchTextMax = TAM_DATA;
							
							TreeView_GetItem(hwndTree, &tvitem);
							tvitem.hItem = noSelected;
							tvitem.mask = TVIF_TEXT;
							tvitem.pszText = placa;
							tvitem.cchTextMax = TAM_PLACA;
							
							TreeView_GetItem(hwndTree, &tvitem);
							
							converteStringData(data, &dataAux);
							
							pegaManutencaoPlacDat(placa, dataAux, &auxManut);

	                        CDS.dwData = 0;
	                        CDS.cbData = sizeof(Manutencao);
	                        CDS.lpData = &auxManut;
	
	                        SendMessage(telaAux, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
						}
						
						guardaPegaHandle(&telaAux, 0);
						
		            }
		          }
		      }
		break;

        case WM_CLOSE:
            EndDialog(hwnd, 0);
        break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Função de controle da janela Principal
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuário
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou não
 * \return Padrao Windows para janelas
 *
 ***********************************************/
LRESULT CALLBACK DlgMainProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE g_inst;
	static HWND hTab, tabProp, tabVeic, tabManut;
	TCITEM itemProp, itemVeic, itemManu;
	HFONT hFont;
	LRESULT count;
	FILE *oficinaInfo;
	static Oficina ofic;
	int sel;
	char endereco[TAM_CIDADE+TAM_ESTADO];

    switch (message){

        case WM_INITDIALOG:
			
            tabProp = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_TABPROP), hwnd, (DLGPROC)tabPropPage);
            tabManut = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_TABMANUN), hwnd, (DLGPROC)tabManutPage);
            tabVeic = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_TABVEIC), hwnd, (DLGPROC)tabVeicPage);

            ShowWindow(tabProp, (sel == 0) ? SW_SHOW : SW_HIDE);
            ShowWindow(tabVeic, (sel == 1) ? SW_SHOW : SW_HIDE);
            ShowWindow(tabManut, (sel == 2) ? SW_SHOW : SW_HIDE);

            SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(ICON_PROJETO)));

            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(ICON_PROJETO)));

            if(existeArquivo(ARQUIVO_DADOS_OFICINA)){
                oficinaInfo = fopen(ARQUIVO_DADOS_OFICINA, "rb");
                if(oficinaInfo != NULL){
                    if(fread(&ofic, sizeof(Oficina), 1, oficinaInfo)!=1){
		            	MessageBox(hwnd, "Erro ao gerar dados de oficina!", "Erro!", MB_ICONERROR);
		            	if(win_trataErros(hwnd, fechaArquivo(oficinaInfo)) == 0) PostQuitMessage(0);	
					}

					sprintf(endereco, "%s, %s - %.30s", ofic.endereco.cidade, ofic.endereco.estado, ofic.endereco.descricao);
					
					Button_SetText(GetDlgItem(hwnd, ID_DADOS_OFICINA), ofic.nome);
					Button_SetText(GetDlgItem(hwnd, ID_DADOS_OFICINA_ENDER), endereco);
					
                    if (win_trataErros(hwnd, fechaArquivo(oficinaInfo)) != 0) return FALSE;

                    if(remove(ARQUIVO_DADOS_OFICINA) == EOF) return FALSE;
                    
                }else{
                    if(win_trataErros(hwnd, ERRO_ABRIR_ARQUIVO) != 0) return FALSE;
                }
            }

            hTab = GetDlgItem(hwnd, HTAB);

            itemProp.mask = TCIF_TEXT;
            itemProp.pszText = "Proprietarios";

            count = SendMessage(hTab, TCM_GETITEMCOUNT, 0, 0);
            SendMessage(hTab, TCM_INSERTITEM, count,
                (LPARAM) (LPTCITEM) &itemProp);

            itemVeic.mask = TCIF_TEXT;
            itemVeic.pszText = "   Veiculos  ";

            count = SendMessage(hTab, TCM_GETITEMCOUNT, 0, 0);
            SendMessage(hTab, TCM_INSERTITEM, count,
                (LPARAM) (LPTCITEM) &itemVeic);

            itemManu.mask = TCIF_TEXT;
            itemManu.pszText = "Manutencao";

            count = SendMessage(hTab, TCM_GETITEMCOUNT, 0, 0);
            SendMessage(hTab, TCM_INSERTITEM, count,
                (LPARAM) (LPTCITEM) &itemManu);

            return TRUE;
        break;

        case WM_COMMAND:

            switch(LOWORD(wParam)){
                case ID_APRESENTAR_TUDO_BOTAO:
                    DialogBox(g_inst, MAKEINTRESOURCE(IDD_MOSTRA_TODOS), hwnd, (DLGPROC)apresentaTodosDadosProc);
                break;

                case ID_CREDITOS_BOTAO:
                    DialogBox(g_inst, MAKEINTRESOURCE(IDD_CREDITOS), hwnd, (DLGPROC)creditosProc);
                break;

            }
            return TRUE;
		break;

		case WM_NOTIFY: {
            switch (((LPNMHDR)lParam)->code) {
	            case TCN_SELCHANGE:
	                sel = TabCtrl_GetCurSel(hTab);
	                ShowWindow(tabProp, (sel == 0) ? SW_SHOW : SW_HIDE);
	                ShowWindow(tabVeic, (sel == 1) ? SW_SHOW : SW_HIDE);
	                ShowWindow(tabManut, (sel == 2) ? SW_SHOW : SW_HIDE);
	                break;
            }
        	return TRUE;
            break;
        }

        case WM_CLOSE:
            PostQuitMessage(0);
            return TRUE;
        break;
    }

	return FALSE;
}
