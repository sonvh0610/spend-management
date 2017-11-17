#include "stdafx.h"
#include "Category.h"


Category::Category()
{
}

Category::Category(wstring _type, wstring _info, int _amount)
{
	this->sCategoryType = _type;
	this->sCategoryInfo = _info;
	this->iAmount = _amount;
}

Category::~Category()
{
}

wstring Category::GetCategoryType() { return this->sCategoryType; }
wstring Category::GetCategoryInformation() { return this->sCategoryInfo; }
int Category::GetCategoryAmount() { return this->iAmount; }

void Category::SetCategoryType(wstring type) { this->sCategoryType = type; }
void Category::SetCategoryInformation(wstring info) { this->sCategoryInfo = info; }
void Category::SetCategoryAmount(int amount) { this->iAmount = amount; }
