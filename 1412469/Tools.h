#ifndef __TOOLS_H__
#define __TOOLS_H__
#include <string>

using namespace std;

class Tools
{
public:
	Tools();
	~Tools();

	static wstring GetCurrentCombobox(HWND hWnd, int index);
	static wstring GetTextboxW(HWND hWnd);
	static int GetTextboxI(HWND hWnd);
};

#endif