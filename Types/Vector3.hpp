#ifndef _VECTOR3_HPP_INCLUDED_
#define _VECTOR3_HPP_INCLUDED_

#include "Vector2.hpp"

class Vector3
{
public:
	Vector3() {}
	Vector3(const ddouble vx, const ddouble vy, const ddouble vz)
	{
		x = vx;
		y = vy;
		z = vz;
	}
	Vector3(const Vector2 &v, const ddouble vz)
	{
		x = v.x;
		y = v.y;
		z = vz;
	}
	Vector3(const Vector3 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	bool operator==(const Vector3 &v) const
	{
		return (x == v.x) && (y == v.y) && (z == v.z);
	}
	bool operator!=(const Vector3 &v) const
	{
		return (x != v.x) || (y != v.y) || (z != v.z);
	}
	Vector3 &operator=(const Vector3 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return (*this);
	}
	Vector3 &operator+=(const Vector3 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return (*this);
	}
	Vector3 &operator-=(const Vector3 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return (*this);
	}
	Vector3 &operator*=(const ddouble d)
	{
		x *= d;
		y *= d;
		z *= d;
		return (*this);
	}
	Vector3 &operator/=(const ddouble d)
	{
		const ddouble c = 1.0 / d;
		x *= c;
		y *= c;
		z *= c;
		return (*this);
	}
	Vector3 operator-() const
	{
		return Vector3(-x, -y, -z);
	}
	Vector3 operator+(const Vector3 &v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	Vector3 operator-(const Vector3 &v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	Vector3 operator*(const ddouble d) const
	{
		return Vector3(x * d, y * d, z * d);
	}
	Vector3 operator/(const ddouble d) const
	{
		const ddouble c = 1.0 / d;
		return Vector3(x * c, y * c, z * c);
	}
	friend Vector3 operator*(const ddouble d, const Vector3 &v)
	{
		return v * d;
	}
	Vector3 cross(const Vector3 &v) const
	{
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	ddouble dot(const Vector3 &v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}
	ddouble len() const
	{
		return sqrt(x * x + y * y + z * z);
	}
	ddouble lensq() const
	{
		return x * x + y * y + z * z;
	}
	Vector3 unit() const
	{
		const ddouble c = 1.0 / sqrt(x * x + y * y + z * z);
		return Vector3(x * c, y * c, z * c);
	}
	Vector3 &normalize()
	{
		const ddouble c = 1.0 / sqrt(x * x + y * y + z * z);
		x *= c;
		y *= c;
		z *= c;
		return (*this);
	}
	Vector2 toVector2() const {	return Vector2(x, y); }

	ddouble x;
	ddouble y;
	ddouble z;
};

struct Plane3
{
	Vector3 dir;
	ddouble dot;
	Plane3() {}
	Plane3(const Vector3 &adir, const ddouble adot)
	{
		dir = adir;
		dot = adot;
	}
};


#endif //_VECTOR3_HPP_INCLUDED_
