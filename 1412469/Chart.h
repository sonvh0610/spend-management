#ifndef __CHART_H__
#define __CHART_H__

#include <vector>
#include "Structs.h"


class Chart
{
private:
	Coord mOrigin;
	int iRadius;
	vector<ChartCategory> vCat;
	float GetSweepAngle(int index);
	Coord GetCoordCenterTwoPoints(Coord p1, Coord p2, float percent);
	
public:
	Chart();
	Chart(Coord _origin, int _radius);
	void Draw(HDC hdc);
	void UpdateCoordParts(vector<TypeCategory> _vCat);
	void ShowNote(HDC hdc);
	~Chart();
};

#endif