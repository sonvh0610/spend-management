#include "stdafx.h"
#include "Handles.h"
#include <CommCtrl.h>
#include "resource.h"

#pragma comment(lib, "comctl32.lib")

vector<wstring> vDefaultType = {
	L"Ăn uống",
	L"Di chuyển",
	L"Nhà cửa",
	L"Xe cộ",
	L"Nhu yếu phẩm",
	L"Dịch vụ"
};

Handles::Handles()
{
	this->hListCategories = NULL;
	this->hInformation = NULL;
	this->btnAdd = NULL;
	
	this->lvCategories = NULL;
	this->hTotalAmount = NULL;
	this->hAmount = 0;
}

Handles::Handles(vector<Category> _vCat)
{
	this->hListCategories = NULL;
	this->hInformation = NULL;
	this->btnAdd = NULL;

	this->lvCategories = NULL;
	this->hTotalAmount = NULL;
	this->hAmount = 0;

	this->vCat = _vCat;

	for (int i = 0; i < vDefaultType.size(); ++i)
	{
		TypeCategory type = { vDefaultType[i], 0 };
		this->vType.push_back(type);
	}

	for (int i = 0; i < this->vCat.size(); ++i)
	{
		this->PushTypeCategory(this->vCat[i]);
	}
}

Handles::~Handles()
{
}

HWND Handles::GetHandleListCategories(HandleProperties prop, HWND hWndParent, HINSTANCE hInst)
{
	if (this->hListCategories == NULL)
	{
		this->hListCategories = CreateWindowEx(0, L"COMBOBOX", L"MyCombo", CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
			prop.x, prop.y, prop.width, prop.height, hWndParent, prop.hMenu, hInst, NULL);

		for (int i = 0; i < this->vType.size(); ++i)
		{
			SendMessage(this->hListCategories, CB_ADDSTRING,
				0, LPARAM(this->vType.at(i).type.c_str()));
		}
	}
	
	return this->hListCategories;
}

HWND Handles::GetHandleInformation(HandleProperties prop, HWND hWndParent, HINSTANCE hInst)
{
	if (this->hInformation == NULL)
	{
		this->hInformation = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			prop.x, prop.y, prop.width, prop.height, hWndParent, prop.hMenu, hInst, NULL);
		SendMessage(this->hInformation, EM_SETCUEBANNER, 0, LPARAM(L"Chi tiết loại chi tiêu"));
	}

	return this->hInformation;
}

HWND Handles::GetHandleAmount(HandleProperties prop, HWND hWndParent, HINSTANCE hInst)
{
	if (this->hAmount == NULL)
	{
		this->hAmount = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			prop.x, prop.y, prop.width, prop.height, hWndParent, prop.hMenu, hInst, NULL);
		SendMessage(this->hAmount, EM_SETCUEBANNER, 0, LPARAM(L"Số tiền"));
	}

	return this->hAmount;
}

HWND Handles::GetHandleAddButton(HandleProperties prop, HWND hWndParent, HINSTANCE hInst)
{
	if (this->btnAdd == NULL)
	{
		this->btnAdd = CreateWindowEx(0, L"BUTTON", L"Thêm", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			prop.x, prop.y, prop.width, prop.height, hWndParent, prop.hMenu, hInst, NULL);
	}

	return this->btnAdd;
}

HWND Handles::GetHandleListviewCategories(HandleProperties prop, HWND hWndParent, HINSTANCE hInst)
{
	InitCommonControls();
	if (this->lvCategories == NULL)
	{
		this->lvCategories = CreateWindowEx(LVS_EX_FULLROWSELECT, WC_LISTVIEW, L"",
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LVS_REPORT | LVS_EX_GRIDLINES,
			prop.x, prop.y, prop.width, prop.height, hWndParent, prop.hMenu, hInst, NULL);

		SendMessage(this->lvCategories, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

		LVCOLUMN lvCol;
		
		// Category column
		lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol.cx = 150;
		lvCol.pszText = _T("Loại chi tiêu");
		ListView_InsertColumn(this->lvCategories, 0, &lvCol);

		// Information column
		lvCol.cx = 300;
		lvCol.fmt = LVCFMT_LEFT;
		lvCol.pszText = _T("Nội dung chi tiêu");
		ListView_InsertColumn(this->lvCategories, 1, &lvCol);

		// Amount column
		lvCol.cx = 100;
		lvCol.pszText = _T("Số tiền (VND)");
		lvCol.fmt = LVCFMT_RIGHT;
		ListView_InsertColumn(this->lvCategories, 2, &lvCol);

		for (int i = 0; i < this->vCat.size(); ++i)
		{
			LVITEM lv;

			lv.mask = LVIF_TEXT;
			lv.iItem = i;
			lv.iSubItem = 0;
			lv.pszText = new WCHAR[this->vCat[i].GetCategoryType().length() + 1];
			wcscpy(lv.pszText, this->vCat[i].GetCategoryType().c_str());
			ListView_InsertItem(lvCategories, &lv);

			lv.iSubItem = 1;
			lv.pszText = new WCHAR[this->vCat[i].GetCategoryInformation().length() + 1];
			wcscpy(lv.pszText, this->vCat[i].GetCategoryInformation().c_str());
			ListView_SetItem(lvCategories, &lv);

			lv.iSubItem = 2;
			_itow(this->vCat[i].GetCategoryAmount(), lv.pszText, 10);
			ListView_SetItem(lvCategories, &lv);
		}
	}

	return this->lvCategories;
}

HWND Handles::GetHandleTotalAmount(HandleProperties prop, HWND hWndParent, HINSTANCE hInst)
{
	if (this->hTotalAmount == NULL)
	{
		this->hTotalAmount = CreateWindowEx(0, L"STATIC", L"Tổng: 0 VND", WS_CHILD | WS_VISIBLE | SS_RIGHT,
			prop.x, prop.y, prop.width, prop.height, hWndParent, NULL, hInst, NULL);
		this->UpdateCategories();
	}

	return this->hTotalAmount;
}

vector<Category> Handles::GetListCategories() {	return this->vCat; }
vector<TypeCategory> Handles::GetListTypeCategories() { return this->vType; }

void Handles::AddCategoryItem(Category cat)
{
	this->vCat.push_back(cat);

	LVITEM lv;

	lv.mask = LVIF_TEXT;
	lv.iItem = this->vCat.size() - 1;
	lv.iSubItem = 0;
	lv.pszText = new WCHAR[cat.GetCategoryType().length() + 1];
	wcscpy(lv.pszText, cat.GetCategoryType().c_str());
	ListView_InsertItem(lvCategories, &lv);

	lv.iSubItem = 1;
	lv.pszText = new WCHAR[cat.GetCategoryInformation().length() + 1];
	wcscpy(lv.pszText, cat.GetCategoryInformation().c_str());
	ListView_SetItem(lvCategories, &lv);

	lv.iSubItem = 2;
	_itow(cat.GetCategoryAmount(), lv.pszText, 10);
	ListView_SetItem(lvCategories, &lv);

	this->UpdateCategories();
	this->UpdateTypeCategory();
}

void Handles::EditCategoryItem(int index, Category cat)
{
	this->vCat[index].SetCategoryType(cat.GetCategoryType());
	this->vCat[index].SetCategoryInformation(cat.GetCategoryInformation());
	this->vCat[index].SetCategoryAmount(cat.GetCategoryAmount());

	ListView_DeleteItem(this->lvCategories, index);

	LVITEM lv;

	lv.mask = LVIF_TEXT;
	lv.iItem = index;
	lv.iSubItem = 0;
	lv.pszText = new WCHAR[cat.GetCategoryType().length() + 1];
	wcscpy(lv.pszText, cat.GetCategoryType().c_str());
	ListView_InsertItem(lvCategories, &lv);

	lv.iSubItem = 1;
	lv.pszText = new WCHAR[cat.GetCategoryInformation().length() + 1];
	wcscpy(lv.pszText, cat.GetCategoryInformation().c_str());
	ListView_SetItem(lvCategories, &lv);

	lv.iSubItem = 2;
	_itow(cat.GetCategoryAmount(), lv.pszText, 10);
	ListView_SetItem(lvCategories, &lv);

	this->UpdateCategories();
	this->UpdateTypeCategory();
}

void Handles::PushTypeCategory(Category cat)
{
	for (int i = 0; i < this->vType.size(); ++i)
	{
		if (cat.GetCategoryType() == this->vType[i].type)
		{
			this->vType[i].totalAmount = this->vType[i].totalAmount + cat.GetCategoryAmount();
			return;
		}
	}
}

bool Handles::DeleteCategoryItem(int index)
{
	if (index >= vCat.size() || index < 0) return false;
	else
	{
		vCat.erase(vCat.begin() + index);
		ListView_DeleteItem(this->lvCategories, index);
		this->UpdateCategories();
		this->UpdateTypeCategory();
		return true;
	}
}

void Handles::UpdateCategories()
{
	int total = 0;
	for (int i = 0; i < vCat.size(); ++i)
	{
		total += vCat[i].GetCategoryAmount();
	}

	wstring result = L"Tổng: " + to_wstring(total) + L" VND";
	SetWindowText(this->hTotalAmount, result.c_str());
}

void Handles::UpdateTypeCategory()
{
	for (int i = 0; i < this->vType.size(); ++i)
	{
		this->vType[i].totalAmount = 0;
		for (int j = 0; j < vCat.size(); ++j)
		{
			if (this->vType[i].type == vCat[j].GetCategoryType())
			{
				this->vType[i].totalAmount = this->vType[i].totalAmount + vCat[j].GetCategoryAmount();
			}
		}
	}
}
