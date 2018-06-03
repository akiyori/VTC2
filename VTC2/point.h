#pragma once

#include <cmath>

class Point
{
public:
	float x;
	float y;

	Point() {}    // èâä˙âªÇÕâΩÇ‡ÇµÇ»Ç¢

	Point(float x0, float y0)
	{
		x = x0;
		y = y0;
	}

	bool operator == (const Point& p0) const
	{
		return (x == p0.x) && (y == p0.y);
	}	
	bool operator != (const Point& p0) const
	{
		return (x != p0.x) || (y != p0.y);
	}

	Point operator + (const Point& p0) const
	{
		Point p1;
		p1.x = x + p0.x;
		p1.y = y + p0.y;
		return p1;
	}
	Point operator - (const Point& p0) const
	{
		Point p1;
		p1.x = x - p0.x;
		p1.y = y - p0.y;
		return p1;
	}
	Point operator * (const Point& p0) const
	{
		Point p1;
		p1.x = x * p0.x;
		p1.y = y * p0.y;
		return p1;
	}
	Point operator / (const Point& p0) const
	{
		Point p1;
		p1.x = x / p0.x;
		p1.y = y / p0.y;
		return p1;
	}

	Point& operator += (const Point& p0)
	{
		x += p0.x;
		y += p0.y;
		return *this;
	}
	Point& operator -= (const Point& p0)
	{
		x -= p0.x;
		y -= p0.y;
		return *this;
	}
	Point& operator *= (const Point& p0)
	{
		x *= p0.x;
		y *= p0.y;
		return *this;
	}
	Point& operator /= (const Point& p0)
	{
		x /= p0.x;
		y /= p0.y;
		return *this;
	}

	Point operator + (float value) const
	{
		Point p1;
		p1.x = x + value;
		p1.y = y + value;
		return p1;
	}
	Point operator - (float value) const
	{
		Point p1;
		p1.x = x - value;
		p1.y = y - value;
		return p1;
	}
	Point operator * (float value) const
	{
		Point p1;
		p1.x = x * value;
		p1.y = y * value;
		return p1;
	}
	Point operator / (float value) const
	{
		Point p1;
		p1.x = x / value;
		p1.y = y / value;
		return p1;
	}

	Point& operator += (float value)
	{
		x += value;
		y += value;
		return *this;
	}
	Point& operator -= (float value)
	{
		x -= value;
		y -= value;
		return *this;
	}
	Point& operator *= (float value)
	{
		x *= value;
		y *= value;
		return *this;
	}
	Point& operator /= (float value)
	{
		x /= value;
		y /= value;
		return *this;
	}


	static float Distance(const Point& from, const Point& to)
	{
		Point diff = to - from;
		return std::sqrt(std::pow(diff.x, 2) + std::pow(diff.y, 2));
	}

	static Point Direction(const Point& from, const Point& to)
	{
		auto distance = Distance(from, to);
		Point diff = to - from;
		return diff /= distance;
	}

	void FitRange(const Point* start, const Point* end) {
		if (x < start->x)
			x = start->x;
		if (y < start->y)
			y = start->y;
		if (x > end->x)
			x = end->x;
		if (y > end->y)
			y = end->y;
	}
};