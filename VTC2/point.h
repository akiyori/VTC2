#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <string>
#include <d2d1.h>

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
		Point diff = to - from;
		if (diff.x == 0 && diff.y == 0)
			return Point(0,0);
		auto distance = Distance(from, to);
		return diff /= distance;
	}

	static Point Rotate(const Point& from, double degree) {
		Point to;
		double radian = degree * M_PI / 180.0;
		to.x = (float)(from.x * std::cosf(radian) - from.y * std::sinf(radian));
		to.y = (float)(from.x * std::sinf(radian) + from.y * std::cosf(radian));
		return to;
	}

	static bool IntEqual(const Point& from, const Point& to) {
		return (int)from.x == (int)to.x && (int)from.y == (int)to.y;
	}

	void FitRange(const Point* start, const Point* end) {
		if (x < start->x)
			x = start->x;
		if (y < start->y)
			y = start->y;
		if (x >= end->x)
			x = end->x-1;
		if (y >= end->y)
			y = end->y-1;
	}

	const std::string ToString() {
		return std::to_string((int)x) + ',' + std::to_string((int)y);
	}

	const D2D1_POINT_2F ToD2D1Point() {
		return D2D1::Point2F(x, y);
	}
};