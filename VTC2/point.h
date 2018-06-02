#pragma once

#include <cmath>

class Point
{
public:
	int x;
	int y;

	Point() {}    // ‰Šú‰»‚Í‰½‚à‚µ‚È‚¢

	Point(int x0, int y0)
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

	Point operator + (const double& value) const
	{
		Point p1;
		p1.x = x + value;
		p1.y = y + value;
		return p1;
	}
	Point operator - (const double& value) const
	{
		Point p1;
		p1.x = x - value;
		p1.y = y - value;
		return p1;
	}
	Point operator * (const double& value) const
	{
		Point p1;
		p1.x = x * value;
		p1.y = y * value;
		return p1;
	}
	Point operator / (const double& value) const
	{
		Point p1;
		p1.x = x / value;
		p1.y = y / value;
		return p1;
	}

	Point& operator += (double& value)
	{
		x += value;
		y += value;
		return *this;
	}
	Point& operator -= (double& value)
	{
		x -= value;
		y -= value;
		return *this;
	}
	Point& operator *= (double& value)
	{
		x *= value;
		y *= value;
		return *this;
	}
	Point& operator /= (double& value)
	{
		x /= value;
		y /= value;
		return *this;
	}


	static int Distance(Point& from, Point& to)
	{
		Point diff = to - from;
		return std::sqrt(std::pow(diff.x, 2) + std::pow(diff.y, 2));
	}

	static Point Direction(Point& from, Point& to)
	{
		Point diff = to - from;
		diff.x = (diff.x > 0) - (diff.x < 0);
		diff.y = (diff.y > 0) - (diff.y < 0);
		return diff;
	}

	void FitRange(Point* start, Point* end) {
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