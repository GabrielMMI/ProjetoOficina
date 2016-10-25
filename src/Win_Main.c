#include "../include/Win_Functions.h"

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void CreateWindowMain(HWND *hwnd, HINSTANCE hThisInsctance, int nFunsterStil);
int RegisterWindowMain(char *nome, HINSTANCE hThisInstance);

void CreateWindowMain(HWND *hwnd, HINSTANCE hThisInstance, int nFunsterStil){
	*hwnd = CreateWindowEx ( 0, "Main", "Projeto Final", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, //estilo da janela
        350, 100, 650, 590, HWND_DESKTOP, NULL, hThisInstance, NULL);

    ShowWindow (*hwnd, nFunsterStil);
}

int RegisterWindowMain(char *nome, HINSTANCE hThisInstance){
	WNDCLASSEX wincl;                                                   //classe

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = nome;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (hThisInstance, MAKEINTRESOURCE(ICON_PROJETO));
    wincl.hIconSm = LoadIcon (hThisInstance, MAKEINTRESOURCE(ICON_PROJETO));
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);                       //cursor default
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) (COLOR_WINDOW);

	return RegisterClassEx (&wincl);
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE g_inst;
	static HWND nomeOfic, enderOfic, hTab, hTest;
	TCITEM itemProp, itemVeic, itemManu;
	PCOPYDATASTRUCT pcds;
	HFONT hFont;
	LRESULT count;

    switch (message){
        case WM_CREATE:

        hTab = CreateWindow(WC_TABCONTROL, NULL, WS_CHILD | WS_VISIBLE,
                10, 10, 232, 510, hwnd,(HMENU) ID_TABCONTROL, NULL, NULL);

        hTest = CreateWindowEx(0, WC_BUTTON, "Clique", WS_CHILD | WS_VISIBLE, 10, 30, 40, 40, hTab, (HMENU) ID_BUTTON, g_inst, NULL);

        hFont = CreateFont (15, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Microsoft Sans Serif");
        SendMessage (hTab, WM_SETFONT, (WPARAM) (hFont), TRUE);


        itemProp.mask = TCIF_TEXT;
        itemProp.pszText = "Proprietários";

        count = SendMessage(hTab, TCM_GETITEMCOUNT, 0, 0);
        SendMessage(hTab, TCM_INSERTITEM, count,
            (LPARAM) (LPTCITEM) &itemProp);

        itemVeic.mask = TCIF_TEXT;
        itemVeic.pszText = "Veiculos";

        count = SendMessage(hTab, TCM_GETITEMCOUNT, 0, 0);
        SendMessage(hTab, TCM_INSERTITEM, count,
            (LPARAM) (LPTCITEM) &itemVeic);

        itemManu.mask = TCIF_TEXT;
        itemManu.pszText = "Manuntenção";

        count = SendMessage(hTab, TCM_GETITEMCOUNT, 0, 0);
        SendMessage(hTab, TCM_INSERTITEM, count,
            (LPARAM) (LPTCITEM) &itemManu);

        break;

        case WM_NOTIFY:
            break;

        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lParam;
			switch(pcds->dwData){
				case 0:
					nomeOfic = CreateWindowEx(0, "STATIC", ((Oficina *)(pcds->lpData))->nome, WS_VISIBLE|WS_CHILD|SS_LEFT, 260, 10, TAM_NOME*8, 20, hwnd, NULL, g_inst, NULL);
					enderOfic = CreateWindowEx(0, "STATIC", ((Oficina *)(pcds->lpData))->endereco, WS_VISIBLE|WS_CHILD|SS_LEFT, 260, 30, TAM_NOME*10, 15, hwnd, NULL, g_inst, NULL);
					hFont = CreateFont (20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Microsoft Sans Serif");
    				SendMessage (nomeOfic, WM_SETFONT, (WPARAM) (hFont), TRUE);
    				hFont = CreateFont (15, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Microsoft Sans Serif");
    				SendMessage (enderOfic, WM_SETFONT, (WPARAM) (hFont), TRUE);
					break;
			}
        break;
        case WM_DESTROY:
            PostQuitMessage (0);
        break;
    }//switch (message)
    return DefWindowProc (hwnd, message, wParam, lParam);
}
