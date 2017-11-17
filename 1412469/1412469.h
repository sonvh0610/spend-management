#pragma once

#include "resource.h"
#include "Handles.h"
#include <vector>
#include <string>
#include "Chart.h"
#include "FileStream.h"

using namespace std;

#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#define MAX_LOADSTRING 100

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    EditWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL				OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
BOOL				OnEditCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void				OnCategoryCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
void				OnListviewCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
void				OnEditCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
LRESULT				OnListviewNotify(HWND hWnd, int idFrom, NMHDR* pnm);
void				OnDestroy(HWND hWnd);
LRESULT CALLBACK	GBCategoryWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	GBListviewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void				IncludeAddCategoryControls(HWND hWnd);
void				IncludeListCategoryControls(HWND hWnd);
void				IncludePieChartControls(HWND hWnd);
void				ClearAllFields();
void				ShowEditWindow();
void				ShowEditCommonControls();

HWND main_hWnd, edit_hWnd;

// Global Variables:
HINSTANCE hInst, hEditInst;                     // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

Handles *mHandle = NULL;
Chart *mChart = NULL;
FileStream *mFile = NULL;
HFONT hFont = NULL;

HWND gbCategories = NULL;
HWND gbListCat = NULL;
HWND gbPieChart = NULL;

HWND hListCategories = NULL;
HWND hInformation = NULL;
HWND hAmount = NULL;
HWND btnAdd = NULL;

HWND lvCategories = NULL;
HWND hTotalAmount = NULL;

HWND hEditListCategories = NULL;
HWND hEditInformation = NULL;
HWND hEditAmount = NULL;
HWND hEditOKBtn = NULL;
HWND hEditCancelBtn = NULL;

HMENU hPopupMenu;

WNDPROC wndProcCategory;
WNDPROC wndProcListview;

int lvSelectID = -1;
Category mSelectCat;

HDC hdc;