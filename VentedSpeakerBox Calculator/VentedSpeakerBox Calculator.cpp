#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_SAVE 3
#define SUBMIT 4

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void AddMenus(HWND);

void AddControls(HWND hWnd);

HWND tubeArea;
HWND tubeLen;
HWND boxVol;
HWND boardThickness;


int main(HINSTANCE hInst, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASS wc = { };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"VentBoxClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindowW(L"VentBoxClass", L"Vented Speaker Box Calculator", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
		NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND: //any of the buttons were clicked
		switch (wp) {
		case FILE_MENU_NEW: //when the new button is pressed
			break;
		case FILE_MENU_SAVE: //when the save button is pressed
			break;
		case FILE_MENU_OPEN: //when the open button is pressed
			break;
		}
		break;
	case WM_DESTROY: //when a window is being destroyed
		PostQuitMessage(0);
		break;
	case WM_CREATE: //on creation of the menu
		AddMenus(hwnd);
		AddControls(hwnd);
		break;
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

void AddMenus(HWND hWnd) { //AddS MENU
	HMENU hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hFileSubMenu = CreateMenu();

	//hFileMen
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"New");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_OPEN, L"Open");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_SAVE, L"Save As...");

	//hMenu
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
	//AppendMenu(hMenu, MF_STRING, NULL, L"Help"); //TODO Add Help Menu

	SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd) {
	int spacing = 2;
	//Labels (statics)
	CreateWindowW(L"static", L"Area of Tube :", WS_VISIBLE | WS_CHILD | SS_LEFT, 2, 0, 200, 30, hWnd, NULL, NULL, NULL); 

	CreateWindowW(L"static", L"Length of Tube :", WS_VISIBLE | WS_CHILD | SS_LEFT, 2, 30 + spacing, 200, 30, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Volume of Box w/o Tube in it:", WS_VISIBLE | WS_CHILD | SS_LEFT, 2, 2 * (30 + spacing), 200, 30, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Length of Tube :", WS_VISIBLE | WS_CHILD | SS_LEFT, 2, 3 * (30 + spacing), 200, 30, hWnd, NULL, NULL, NULL);

	//Inputs (edits)
	//USER INPUT
	tubeArea = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 
		204, 0, 100, 30, hWnd, NULL, NULL, NULL); 
	tubeLen = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 
		204, 30 + spacing, 100, 30, hWnd, NULL, NULL, NULL);
	boxVol = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 
		204, 2 * (30 + spacing), 100, 30, hWnd, NULL, NULL, NULL);
	boardThickness = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 
		204, 3 * (30 + spacing), 100, 30, hWnd, NULL, NULL, NULL);
	//SUBMIT BUTTON
	CreateWindowW(L"button", L"SUBMIT", WS_VISIBLE | WS_CHILD, 0, 4 * (30 + spacing), 100, 30, hWnd, (HMENU)SUBMIT,
		NULL, NULL);//class name isn't case sensitive


}