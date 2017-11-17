#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <string>

using namespace std;

struct Coord
{
	int x, y;
};

struct HandleProperties
{
	int x, y, width, height;
	HMENU hMenu;
};

struct TypeCategory
{
	wstring type;
	int totalAmount;
};

struct RGBColor
{
	int r, g, b;
};

struct ChartCategory
{
	wstring type;
	RGBColor color;
	int amount;
	float startAngle;
	float sweepAngle;
};



#endif