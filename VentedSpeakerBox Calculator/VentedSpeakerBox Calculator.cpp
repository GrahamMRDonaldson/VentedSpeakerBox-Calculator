#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <iostream>		//std::cout, std::endl
#include <string>		//std::wstring, std::to_wstring

struct dimension {
	float x = 0;
	float y = 0;
	void print() {
		std::cout << "(" << x << ", " << y << ")" << std::endl;
	}
	std::wstring val() {
		std::wstring a = L"(";
		a += std::to_wstring(x);
		a += std::wstring(L", ");
		a+= std::to_wstring(y);
		a += std::wstring(L")");
		return a;
	}
};

class panels {
public:
	dimension frontPanel;
	dimension backPanel;
	dimension sidePanel;
	dimension bottomPanel;
	dimension topPanel;
	dimension tubetopPanel;
	dimension tubesidePanel;

	panels(dimension frontPanel, dimension backPanel, dimension sidePanel,
		dimension bottomPanel, dimension topPanel, dimension tubetopPanel,
		dimension tubesidePanel) {
		this->frontPanel = frontPanel;
		this->backPanel = backPanel;
		this->sidePanel = sidePanel;
		this->backPanel = bottomPanel;
		this->topPanel = topPanel;
		this->tubetopPanel = tubetopPanel;
		this->tubesidePanel = tubesidePanel;
	}

	panels() {} 
};

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_SAVE 3
#define SUBMIT 4

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void AddMenus(HWND);

void AddControls(HWND hWnd);

//input HWND
HWND tubeArea_HWND;
HWND tubeLen_HWND;
HWND boxVol_HWND;
HWND boardThickness_HWND;

//output HWND
HWND frontPanel_HWND;
HWND backPanel_HWND;
HWND sidePanel_HWND;
HWND bottomPanel_HWND;
HWND topPanel_HWND;
HWND tubetopPanel_HWND;
HWND tubesidePanel_HWND;

float to_float(std::string str) {
	std::string::size_type sz;
	return (float)(std::stof(str, &sz));
}

std::string to_str(wchar_t wstr[100]) {
	std::wstring ws(wstr);
	std::string val(ws.begin(), ws.end());
	return val;
}

panels do_calc(std::string wtubeArea, std::string wtubeLen, std::string wboxVol, std::string wboardThickness) {
	//redefine parsed string as floats
	float tubeArea = to_float(wtubeArea);
	float tubeLen = to_float(wtubeLen);
	float boxVol = to_float(wboxVol);
	float boardThickness = to_float(wboardThickness);

	//calculations
	float tube_width = tubeArea / boardThickness;
	float chunk_height = 2 * boardThickness;

	//box_vol + (chunk_height * (tube_len-board_thickness) * (tube_width + x)) - (tube_width + x)**3
	//a + (2b(c-b)((d/b)+x))) - ((d/b)*x)^3
	//TODO 
	//figure out how to solve this equation, then put it into panels form
	return panels();
}

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
	case WM_COMMAND:			//any of the buttons were clicked
		switch (wp) {
		case FILE_MENU_NEW:		//when the new button is pressed
			break;
		case FILE_MENU_SAVE:	//when the save button is pressed
			break;
		case FILE_MENU_OPEN:	//when the open button is pressed
			break;
		case SUBMIT:			//when the submit button is pressed
			//gets the values of the users inputs
			wchar_t tubeArea[100];
			GetWindowText(tubeArea_HWND, tubeArea, 100);
			wchar_t tubeLen[100];
			GetWindowText(tubeLen_HWND, tubeLen, 100);
			wchar_t boxVol[100];
			GetWindowText(boxVol_HWND, boxVol, 100);
			wchar_t boardThickness[100];
			GetWindowText(boardThickness_HWND, boardThickness, 100);

			//calculating the values
			panels calc_dimensions = do_calc(to_str(tubeArea), to_str(tubeLen), to_str(boxVol), to_str(boardThickness));

			//setting the output windows to the correct ones
			SetWindowTextW(frontPanel_HWND, calc_dimensions.frontPanel.val().c_str());
			SetWindowTextW(backPanel_HWND, calc_dimensions.backPanel.val().c_str());
			SetWindowTextW(sidePanel_HWND, calc_dimensions.sidePanel.val().c_str());
			SetWindowTextW(bottomPanel_HWND, calc_dimensions.bottomPanel.val().c_str());
			SetWindowTextW(topPanel_HWND, calc_dimensions.topPanel.val().c_str());
			SetWindowTextW(tubetopPanel_HWND, calc_dimensions.tubetopPanel.val().c_str());
			SetWindowTextW(tubesidePanel_HWND, calc_dimensions.tubesidePanel.val().c_str());
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
	tubeArea_HWND = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
		204, 0, 100, 30, hWnd, NULL, NULL, NULL); 
	tubeLen_HWND = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
		204, 30 + spacing, 100, 30, hWnd, NULL, NULL, NULL);
	boxVol_HWND = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
		204, 2 * (30 + spacing), 100, 30, hWnd, NULL, NULL, NULL);
	boardThickness_HWND = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
		204, 3 * (30 + spacing), 100, 30, hWnd, NULL, NULL, NULL);

	//SUBMIT BUTTON
	CreateWindowW(L"button", L"SUBMIT", WS_VISIBLE | WS_CHILD, 0, 4 * (30 + spacing), 100, 30, hWnd, (HMENU)SUBMIT,
		NULL, NULL);//class name isn't case sensitive

	//Output (statics)
	int subButtonSpace = 2;
	//Labels
	CreateWindowW(L"static", L"Front Panel Dimensions    :", WS_VISIBLE | WS_CHILD | SS_LEFT, 2, 5 * (30 + spacing) + subButtonSpace, 200, 30, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Back Panel Dimensions    :", WS_VISIBLE | WS_CHILD | SS_LEFT, 2, 6 * (30 + spacing) + subButtonSpace, 200, 30, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Side Panel Dimensions     :", WS_VISIBLE | WS_CHILD | SS_LEFT, 2, 7 * (30 + spacing) + subButtonSpace, 200, 30, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Bottom Panel Dimensions :", WS_VISIBLE | WS_CHILD | SS_LEFT, 2, 8 * (30 + spacing), 200, 30, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Top Panel Dimensions      :", WS_VISIBLE | WS_CHILD | SS_LEFT, 2, 9 * (30 + spacing), 200, 30, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Tube Top Panel Dimensions :", WS_VISIBLE | WS_CHILD | SS_LEFT, 2, 10 * (30 + spacing), 200, 30, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Tube Side Panel Dimensions:", WS_VISIBLE | WS_CHILD | SS_LEFT, 2, 11 * (30 + spacing), 200, 30, hWnd, NULL, NULL, NULL);

	//Output
	frontPanel_HWND = CreateWindowW(L"static", L"<?>", WS_VISIBLE | WS_CHILD | SS_LEFT, 204, 5 * (30 + spacing) + subButtonSpace, 200, 30, hWnd, NULL, NULL, NULL);

	backPanel_HWND = CreateWindowW(L"static", L"<?>", WS_VISIBLE | WS_CHILD | SS_LEFT, 204, 6 * (30 + spacing) + subButtonSpace, 200, 30, hWnd, NULL, NULL, NULL);

	sidePanel_HWND = CreateWindowW(L"static", L"<?>", WS_VISIBLE | WS_CHILD | SS_LEFT, 204, 7 * (30 + spacing) + subButtonSpace, 200, 30, hWnd, NULL, NULL, NULL);

	bottomPanel_HWND = CreateWindowW(L"static", L"<?>", WS_VISIBLE | WS_CHILD | SS_LEFT, 204, 8 * (30 + spacing) + subButtonSpace, 200, 30, hWnd, NULL, NULL, NULL);

	topPanel_HWND = CreateWindowW(L"static", L"<?>", WS_VISIBLE | WS_CHILD | SS_LEFT, 204, 9 * (30 + spacing) + subButtonSpace, 200, 30, hWnd, NULL, NULL, NULL);

	tubetopPanel_HWND = CreateWindowW(L"static", L"<?>", WS_VISIBLE | WS_CHILD | SS_LEFT, 204, 10 * (30 + spacing) + subButtonSpace, 200, 30, hWnd, NULL, NULL, NULL);

	tubesidePanel_HWND = CreateWindowW(L"static", L"<?>", WS_VISIBLE | WS_CHILD | SS_LEFT, 204, 11 * (30 + spacing) + subButtonSpace, 200, 30, hWnd, NULL, NULL, NULL);
}