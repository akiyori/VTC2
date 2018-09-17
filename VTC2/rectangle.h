#pragma once
#include "point.h"

class Rectangle
{
public:
	Point start;
	Point end;

	Rectangle() {}    // 初期化は何もしない

	Rectangle(Point start, Point end)
	{
		this->start = start;
		this->end = end;
	}
};

