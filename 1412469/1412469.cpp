// 1412469.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1412469.h"
#include <windowsx.h>
#include <CommCtrl.h>
#include "Tools.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY1412469, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1412469));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1412469));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1412469);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	main_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		10, 10, 1260, 680, nullptr, nullptr, hInstance, nullptr);

	if (!main_hWnd)
	{
		return FALSE;
	}

	ShowWindow(main_hWnd, nCmdShow);
	UpdateWindow(main_hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDM_ABOUT:
				{
					wstring info = L"- Họ và tên: Võ Hoài Sơn\n- MSSV: 1412469\n- Email: vector.mic@gmail.com";
					info += L"\n\nPhần mềm quản lý chi tiêu - Version 1.0-alpha";
					MessageBox(0, info.c_str(), L"Thông tin cá nhân", MB_OK | MB_ICONQUESTION);
					break;
				}
				case IDM_EXIT:
				{
					mFile->SaveFile(mHandle->GetListCategories());
					PostQuitMessage(0);
					break;
				}
			}
			break;
		}
		
		case WM_PAINT:
        {
			PAINTSTRUCT ps;

			hdc = BeginPaint(hWnd, &ps);
			mChart->Draw(hdc);
			mChart->ShowNote(hdc);

			EndPaint(hWnd, &ps);
			break;
        }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK EditWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnEditCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnEditCommand);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK GBCategoryWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_COMMAND, OnCategoryCommand);
	}
	return CallWindowProc(wndProcCategory, hWnd, message, wParam, lParam);
}

LRESULT CALLBACK GBListviewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_NOTIFY, OnListviewNotify);
		HANDLE_MSG(hWnd, WM_COMMAND, OnListviewCommand);
	}
	return CallWindowProc(wndProcListview, hWnd, message, wParam, lParam);
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	mFile = new FileStream("data.txt");
	mHandle = new Handles(mFile->ReadFile());
	hFont = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, VIETNAMESE_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Calibri"));

	IncludeAddCategoryControls(hWnd);
	IncludeListCategoryControls(hWnd);
	IncludePieChartControls(hWnd);

	return true;
}

BOOL OnEditCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	hEditListCategories = CreateWindowEx(0, L"COMBOBOX", L"MyCombo", CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
		15, 10, 200, 300, hWnd, HMENU(IDC_EDITLISTCAT), hEditInst, NULL);
	SendMessage(hEditListCategories, WM_SETFONT, WPARAM(hFont), TRUE);

	vector<TypeCategory> vType = mHandle->GetListTypeCategories();
	int lvSelIndex = -1;
	for (int i = 0; i < vType.size(); ++i)
	{
		SendMessage(hEditListCategories, CB_ADDSTRING, 0, LPARAM(vType.at(i).type.c_str()));
		if (vType[i].type == mSelectCat.GetCategoryType()) lvSelIndex = i;
	}
	SendMessage(hEditListCategories, CB_SETCURSEL, lvSelIndex, 0);

	hEditInformation = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
		15, 35, 200, 22, hWnd, HMENU(IDC_EDITINFO), hEditInst, NULL);
	SendMessage(hEditInformation, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(hEditInformation, EM_SETCUEBANNER, 0, LPARAM(L"Chi tiết loại chi tiêu"));
	SetWindowText(hEditInformation, mSelectCat.GetCategoryInformation().c_str());

	hEditAmount = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
		15, 60, 200, 22, hWnd, HMENU(IDC_EDITAMOUNT), hEditInst, NULL);
	SendMessage(hEditAmount, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(hEditAmount, EM_SETCUEBANNER, 0, LPARAM(L"Số tiền"));
	SetWindowText(hEditAmount, to_wstring(mSelectCat.GetCategoryAmount()).c_str());

	hEditOKBtn = CreateWindowEx(0, L"BUTTON", L"Đồng ý", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		55, 92, 50, 22, hWnd, HMENU(IDC_EDITOKBTN), hEditInst, NULL);
	SendMessage(hEditOKBtn, WM_SETFONT, WPARAM(hFont), TRUE);

	hEditCancelBtn = CreateWindowEx(0, L"BUTTON", L"Huỷ bỏ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		120, 92, 50, 22, hWnd, HMENU(IDC_EDITCANCELBTN), hEditInst, NULL);
	SendMessage(hEditCancelBtn, WM_SETFONT, WPARAM(hFont), TRUE);

	return true;
}

void OnCategoryCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
		case IDC_MYADDBUTTON:
		{
			LRESULT wSelection = SendMessage(hListCategories, CB_GETCURSEL, 0, 0);
			vector<wstring> vError;
			Category cat;
			wstring info = Tools::GetTextboxW(hInformation);
			int amount = Tools::GetTextboxI(hAmount);

			if (wSelection < 0) vError.push_back(L"Lỗi #001: Bạn phải chọn một loại chi tiêu!");
			if (info.length() == 0) vError.push_back(L"Lỗi #002: Bạn phải nhập chi tiết loại chi tiêu!");

			if (amount == INT_MIN) vError.push_back(L"Lỗi #003: Bạn phải nhập số tiền!");
			else if (amount <= 0) vError.push_back(L"Lỗi #004: Số tiền đã nhập không hợp lệ!");

			if (vError.size() > 0)
			{
				wstring wShowError;
				for (int i = 0; i < vError.size(); ++i) wShowError += vError[i] + L'\n';
				MessageBox(hWnd, wShowError.c_str(), L"Lỗi", MB_OK | MB_ICONERROR);
			}
			else
			{
				cat.SetCategoryType(Tools::GetCurrentCombobox(hListCategories, wSelection));
				cat.SetCategoryInformation(info);
				cat.SetCategoryAmount(amount);

				mHandle->AddCategoryItem(cat);
				mChart->UpdateCoordParts(mHandle->GetListTypeCategories());
				ClearAllFields();

				InvalidateRect(main_hWnd, NULL, TRUE);
			}
			break;
		}
	}
}

void OnListviewCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
		case IDM_LVEDIT:
		{
			mSelectCat = mHandle->GetListCategories()[lvSelectID];
			ShowEditWindow();
			break;
		}
		case IDM_LVDELETE:
		{
			int result = MessageBox(0, L"Bạn có chắc chắn muốn xoá?", L"Thông báo", MB_OKCANCEL | MB_ICONQUESTION);
			
			if (result == 1)
			{
				mHandle->DeleteCategoryItem(lvSelectID);
				mChart->UpdateCoordParts(mHandle->GetListTypeCategories());

				InvalidateRect(main_hWnd, NULL, TRUE);
			}

			break;
		}
	}
}

void OnEditCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
		case IDC_EDITOKBTN:
		{
			LRESULT wSelection = SendMessage(hEditListCategories, CB_GETCURSEL, 0, 0);
			vector<wstring> vError;
			Category cat;
			wstring info = Tools::GetTextboxW(hEditInformation);
			int amount = Tools::GetTextboxI(hEditAmount);

			if (wSelection < 0) vError.push_back(L"Lỗi #001: Bạn phải chọn một loại chi tiêu!");
			if (info.length() == 0) vError.push_back(L"Lỗi #002: Bạn phải nhập chi tiết loại chi tiêu!");

			if (amount == INT_MIN) vError.push_back(L"Lỗi #003: Bạn phải nhập số tiền!");
			else if (amount <= 0) vError.push_back(L"Lỗi #004: Số tiền đã nhập không hợp lệ!");

			if (vError.size() > 0)
			{
				wstring wShowError;
				for (int i = 0; i < vError.size(); ++i) wShowError += vError[i] + L'\n';
				MessageBox(hWnd, wShowError.c_str(), L"Lỗi", MB_OK | MB_ICONERROR);

				SetWindowText(hEditInformation, mSelectCat.GetCategoryInformation().c_str());
				SetWindowText(hEditAmount, to_wstring(mSelectCat.GetCategoryAmount()).c_str());
			}
			else
			{
				cat.SetCategoryType(Tools::GetCurrentCombobox(hEditListCategories, wSelection));
				cat.SetCategoryInformation(info);
				cat.SetCategoryAmount(amount);

				mHandle->EditCategoryItem(lvSelectID, cat);
				mChart->UpdateCoordParts(mHandle->GetListTypeCategories());

				InvalidateRect(main_hWnd, NULL, TRUE);
				PostMessage(hWnd, WM_CLOSE, 0, 0);

			}
			break;
		}
		case IDC_EDITCANCELBTN:
		{
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		}
	}
}

LRESULT OnListviewNotify(HWND hWnd, int idFrom, NMHDR* pnm)
{
	switch (pnm->code)
	{
		case NM_RCLICK:
		{
			lvSelectID = SendMessage(lvCategories, LVM_GETNEXTITEM, -1, LVNI_SELECTED);

			if (lvSelectID != -1)
			{
				SendMessage(lvCategories, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
				hPopupMenu = CreatePopupMenu();
				InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, IDM_LVEDIT, L"Sửa");
				InsertMenu(hPopupMenu, 1, MF_BYPOSITION | MF_STRING, IDM_LVDELETE, L"Xoá");
				POINT p;
				GetCursorPos(&p);
				TrackPopupMenu(hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN, p.x, p.y, 0, hWnd, NULL);
			}

			break;
		}
	}
	
	return 0;
}

void OnDestroy(HWND hWnd)
{
	mFile->SaveFile(mHandle->GetListCategories());
	PostQuitMessage(0);
}


void IncludeAddCategoryControls(HWND hWnd)
{
	gbCategories = CreateWindowEx(0, L"Button", L"Thêm chi tiêu", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		10, 10, 600, 100, hWnd, NULL, hInst, NULL);
	SendMessage(gbCategories, WM_SETFONT, WPARAM(hFont), TRUE);

	HandleProperties prop = { 30, 30, 150, 300, NULL };
	hListCategories = mHandle->GetHandleListCategories(prop, gbCategories, hInst);
	SendMessage(hListCategories, WM_SETFONT, WPARAM(hFont), TRUE);

	prop = { 200, 30, 150, 22, NULL };
	hInformation = mHandle->GetHandleInformation(prop, gbCategories, hInst);
	SendMessage(hInformation, WM_SETFONT, WPARAM(hFont), TRUE);

	prop = { 370, 30, 100, 22, NULL };
	hAmount = mHandle->GetHandleAmount(prop, gbCategories, hInst);
	SendMessage(hAmount, WM_SETFONT, WPARAM(hFont), TRUE);

	prop = { 490, 30, 60, 22, (HMENU)IDC_MYADDBUTTON };
	btnAdd = mHandle->GetHandleAddButton(prop, gbCategories, hInst);
	SendMessage(btnAdd, WM_SETFONT, WPARAM(hFont), TRUE);

	wndProcCategory = (WNDPROC)SetWindowLongPtr(gbCategories, GWLP_WNDPROC, (LONG_PTR)&GBCategoryWndProc);
}

void IncludeListCategoryControls(HWND hWnd)
{
	HFONT hFontTotal = CreateFont(25, 0, 0, 0, 800, FALSE, FALSE, FALSE, VIETNAMESE_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Calibri"));

	gbListCat = CreateWindowEx(0, L"Button", L"Danh sách chi tiêu", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		10, 120, 600, 300, hWnd, NULL, hInst, NULL);
	SendMessage(gbListCat, WM_SETFONT, WPARAM(hFont), TRUE);

	HandleProperties prop = { 20, 30, 550, 200, NULL };
	lvCategories = mHandle->GetHandleListviewCategories(prop, gbListCat, hInst);
	SendMessage(lvCategories, WM_SETFONT, WPARAM(hFont), TRUE);

	prop = { 20, 240, 550, 24, NULL };
	hTotalAmount = mHandle->GetHandleTotalAmount(prop, gbListCat, hInst);
	SendMessage(hTotalAmount, WM_SETFONT, WPARAM(hFontTotal), TRUE);

	wndProcListview = (WNDPROC)SetWindowLongPtr(gbListCat, GWLP_WNDPROC, (LONG_PTR)&GBListviewWndProc);
}

void IncludePieChartControls(HWND hWnd)
{
	HandleProperties prop = { 630, 10, 600, 600, NULL };
	gbPieChart = CreateWindowEx(0, L"Button", L"Biểu đồ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		prop.x, prop.y, prop.width, prop.height, hWnd, prop.hMenu, hInst, NULL);
	SendMessage(gbPieChart, WM_SETFONT, WPARAM(hFont), TRUE);

	int radius = 180;
	Coord origin = { prop.x + prop.width / 2, prop.y + radius + 60 };
	mChart = new Chart(origin, radius);
	mChart->UpdateCoordParts(mHandle->GetListTypeCategories());
}

void ClearAllFields()
{
	SendMessage(hListCategories, CB_SETCURSEL, -1, 0);
	SetWindowText(hInformation, L"");
	SetWindowText(hAmount, L"");
}

void ShowEditWindow()
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = EditWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hEditInst;
	wc.hIcon = LoadIcon(hEditInst, MAKEINTRESOURCE(IDI_MY1412469));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"EditCategory";
	wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wc);

	POINT p;
	GetCursorPos(&p);

	edit_hWnd = CreateWindow(L"EditCategory", L"Sửa chi tiêu", 
		WS_OVERLAPPED | WS_CAPTION,
		p.x, p.y, 250, 165, nullptr, nullptr, hEditInst, nullptr);

	ShowWindow(edit_hWnd, SW_SHOW);
	UpdateWindow(edit_hWnd);
}