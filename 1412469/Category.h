#ifndef __CATEGORY_H__
#define __CATEGORY_H__

#include <string>

using namespace std;

class Category
{
private:
	wstring sCategoryType;
	wstring sCategoryInfo;
	int iAmount;
public:
	Category();
	Category(wstring _type, wstring _info, int _amount);
	~Category();

	wstring GetCategoryType();
	wstring GetCategoryInformation();
	int GetCategoryAmount();

	void SetCategoryType(wstring type);
	void SetCategoryInformation(wstring info);
	void SetCategoryAmount(int amount);
};

#endif