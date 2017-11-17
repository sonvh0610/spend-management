#include "stdafx.h"
#include "Tools.h"
#include <CommCtrl.h>

Tools::Tools()
{
}


Tools::~Tools()
{
}

wstring Tools::GetCurrentCombobox(HWND hWnd, int index)
{
	if (index >= 0)
	{
		int bufferSize = SendMessage(hWnd, CB_GETLBTEXTLEN, index, 0);
		WCHAR* buffer = new WCHAR[bufferSize + 1];
		SendMessage(hWnd, CB_GETLBTEXT, index, (LPARAM)buffer);

		wstring result(buffer);
		delete[] buffer;
		return result;
	}
	else return L"";
}

wstring Tools::GetTextboxW(HWND hWnd)
{
	int bufferSize = GetWindowTextLength(hWnd);
	WCHAR* buffer = new WCHAR[bufferSize + 1];

	GetWindowText(hWnd, buffer, bufferSize + 1);
	wstring result(buffer);
	delete[] buffer;
	return result;
}

int Tools::GetTextboxI(HWND hWnd)
{
	int bufferSize = GetWindowTextLength(hWnd);
	WCHAR* buffer = new WCHAR[bufferSize + 1];

	GetWindowText(hWnd, buffer, bufferSize + 1);
	int result = (bufferSize != 0) ? _wtoi(buffer) : INT_MIN;
	delete[] buffer;
	return result;
}
