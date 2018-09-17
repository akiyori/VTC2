#pragma once
#include "point.h"

class Rectangle
{
public:
	Point start;
	Point end;

	Rectangle() {}    // ‰Šú‰»‚Í‰½‚à‚µ‚È‚¢

	Rectangle(Point start, Point end)
	{
		this->start = start;
		this->end = end;
	}
};

