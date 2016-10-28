/********************************************//**
 ** @file Win_DlgMain.c
 * @brief Contem a funcao de controle da janela Principal.
 * @bug Nao contem bugs conhecidos!
 *
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

#include "../include/Win_Functions.h"

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

            Animate_Open(GetDlgItem(hwnd, ID_GIF_CREDITOS_2), "res/matheus.avi");
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
BOOL CALLBACK apresentaTodosDadosProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static HWND hwndTree;
	TV_INSERTSTRUCT tvinsert;
	int qtProp, aux, auxV;
	HTREEITEM noProp;           
	HTREEITEM noVeic;           
	HTREEITEM noManut;
	HTREEITEM noVeicManut;
	FILE *arqProp;
	Proprietario *proprietarios;
	Manutencao *manutencoes;
	Veiculo *veiculos;
	char data[TAM_DATA];
	
    switch(msg) {
        case WM_INITDIALOG:
        	
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
					
					tvinsert.item.pszText=proprietarios[aux].nome;			
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
					tvinsert.hParent=noManut;
					tvinsert.hInsertAfter=TVI_ROOT;
				
					converteDataString(data, manutencoes[aux].data);
					
					tvinsert.item.pszText = data;
					
					noVeicManut = (HTREEITEM)SendDlgItemMessage(hwnd, ID_MOSTRA_DADOS_TREE_VIEW,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
					
					veiculos = carregaVeiculos();
					
					if(veiculos != NULL){
						
						for(auxV = 0; auxV < obtemQuantVeicArquivo(); auxV++){
							tvinsert.hParent=noVeicManut;
							tvinsert.hInsertAfter=TVI_ROOT;
							
							tvinsert.item.pszText=veiculos[auxV].placa;			
							SendDlgItemMessage(hwnd, ID_MOSTRA_DADOS_TREE_VIEW,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
						}
						free(veiculos);
					}
				}
				
				free(manutencoes);
			}
			
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

    switch (message){

        case WM_INITDIALOG:

            tabProp = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_TABPROP), hwnd, (DLGPROC)tabPropPage);
            tabManut = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_TABMANUN), hwnd, (DLGPROC)tabManutPage);
            tabVeic = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_TABVEIC), hwnd, (DLGPROC)tabVeicPage);

            ShowWindow(tabProp, (sel == 0) ? SW_SHOW : SW_HIDE);
            ShowWindow(tabVeic, (sel == 1) ? SW_SHOW : SW_HIDE);
            ShowWindow(tabManut, (sel == 2) ? SW_SHOW : SW_HIDE);

            hFont = CreateFont (20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Microsoft Sans Serif");

            SendDlgItemMessage(hwnd, OFICIAL_NOME, WM_SETFONT, (WPARAM) (hFont), TRUE);

            SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON_PROJETO)));

            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON_PROJETO)));

            if(existeArquivo(ARQUIVO_DADOS_OFICINA)){
                oficinaInfo = fopen(ARQUIVO_DADOS_OFICINA, "r");
                if(oficinaInfo != NULL){
                    fgets(ofic.nome, TAM_NOME, oficinaInfo);
                    fgets(ofic.endereco, TAM_NOME, oficinaInfo);

                    if (win_trataErros(hwnd, fechaArquivo(oficinaInfo)) != 0) return FALSE;

                    if(remove(ARQUIVO_DADOS_OFICINA) == EOF) return FALSE;

                    SetDlgItemText(hwnd, OFICIAL_NOME, ofic.nome);
                    SetDlgItemText(hwnd, OFICIAL_ENDERECO, ofic.endereco);
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
            itemVeic.pszText = "Veiculos";

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
                case ID_CREDITOS_BOTAO:
                    DialogBox(g_inst, MAKEINTRESOURCE(IDD_CREDITOS), hwnd, (DLGPROC)creditosProc);
                break;

				case ID_BOTAO_APRESENTAR_TUDO:
					DialogBox(g_inst, MAKEINTRESOURCE(IDD_MOSTRA_TODOS_DADOS), hwnd, (DLGPROC)apresentaTodosDadosProc);
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
