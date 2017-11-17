#ifndef __HANDLES_H__
#define __HANDLES_H__

#include "Category.h"
#include <vector>
#include <string>
#include "Structs.h"

using namespace std;

class Handles
{
private:
	vector<Category> vCat;
	vector<TypeCategory> vType;

	HWND hListCategories, hInformation, hAmount, btnAdd, hTotalAmount;
	HWND lvCategories;
public:
	Handles();
	Handles(vector<Category> _vCat);
	~Handles();

	HWND GetHandleListCategories(HandleProperties prop, HWND hWndParent, HINSTANCE hInst);
	HWND GetHandleInformation(HandleProperties prop, HWND hWndParent, HINSTANCE hInst);
	HWND GetHandleAmount(HandleProperties prop, HWND hWndParent, HINSTANCE hInst);
	HWND GetHandleAddButton(HandleProperties prop, HWND hWndParent, HINSTANCE hInst);
	HWND GetHandleListviewCategories(HandleProperties prop, HWND hWndParent, HINSTANCE hInst);
	HWND GetHandleTotalAmount(HandleProperties prop, HWND hWndParent, HINSTANCE hInst);

	vector<Category> GetListCategories();
	vector<TypeCategory> GetListTypeCategories();

	void AddCategoryItem(Category cat);
	void EditCategoryItem(int index, Category cat);
	void PushTypeCategory(Category cat);
	bool DeleteCategoryItem(int index);
	void UpdateCategories();
	void UpdateTypeCategory();
};

#endif