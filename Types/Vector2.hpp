#ifndef _VECTOR2_HPP_INCLUDED_
#define _VECTOR2_HPP_INCLUDED_

#include <cmath>
#include "Complex.hpp"

class Vector2
{
public:
	Vector2() {}
	Vector2(const ddouble vx, const ddouble vy)
	{
		x = vx;
		y = vy;
	}
	Vector2(const Vector2 &v)
	{
		x = v.x;
		y = v.y;
	}
	bool operator==(const Vector2 &v) const
	{
		return (x == v.x) && (y == v.y);
	}
	bool operator!=(const Vector2 &v) const
	{
		return (x != v.x) || (y != v.y);
	}
	Vector2 &operator=(const Vector2 &v)
	{
		x = v.x;
		y = v.y;
		return (*this);
	}
	Vector2 &operator+=(const Vector2 &v)
	{
		x += v.x;
		y += v.y;
		return (*this);
	}
	Vector2 &operator-=(const Vector2 &v)
	{
		x -= v.x;
		y -= v.y;
		return (*this);
	}
	Vector2 &operator*=(const ddouble d)
	{
		x *= d;
		y *= d;
		return (*this);
	}
	Vector2 &operator/=(const ddouble d)
	{
		const ddouble c = 1.0 / d;
		x *= c;
		y *= c;
		return (*this);
	}
	Vector2 operator-() const
	{
		return Vector2(-x, -y);
	}
	Vector2 operator+(const Vector2 &v) const
	{
		return Vector2(x + v.x, y + v.y);
	}
	Vector2 operator-(const Vector2 &v) const
	{
		return Vector2(x - v.x, y - v.y);
	}
	Vector2 operator*(const ddouble d) const
	{
		return Vector2(x * d, y * d);
	}
	Vector2 operator/(const ddouble d) const
	{
		const ddouble c = 1.0 / d;
		return Vector2(x * c, y * c);
	}
	friend Vector2 operator*(const ddouble d, const Vector2 &v)
	{
		return v * d;
	}
	Vector2 cross() const
	{
		return Vector2(y, -x);
	}
	ddouble cross(const Vector2 &v) const
	{
		return x * v.y - y * v.x;
	}
	ddouble dot(const Vector2 &v) const
	{
		return x * v.x + y * v.y;
	}
	ddouble len() const
	{
		return sqrt(x * x + y * y);
	}
	ddouble lensq() const
	{
		return x * x + y * y;
	}
	Vector2 unit() const
	{
		const ddouble c = 1.0 / sqrt(x * x + y * y);
		return Vector2(x * c, y * c);
	}
	Vector2 &normalize()
	{
		const ddouble c = 1.0 / sqrt(x * x + y * y);
		x *= c;
		y *= c;
		return (*this);
	}
	ddouble x;
	ddouble y;
};

#endif //_VECTOR2_HPP_INCLUDED_
