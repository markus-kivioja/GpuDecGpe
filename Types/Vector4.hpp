#ifndef _VECTOR4_HPP_INCLUDED_
#define _VECTOR4_HPP_INCLUDED_

#include "Vector3.hpp"

class Vector4
{
public:
	Vector4() {}
	Vector4(const ddouble vx, const ddouble vy, const ddouble vz, const ddouble vt)
	{
		x = vx;
		y = vy;
		z = vz;
		t = vt;
	}
	Vector4(const Vector2 &v, const ddouble vz, const ddouble vt)
	{
		x = v.x;
		y = v.y;
		z = vz;
		t = vt;
	}
	Vector4(const Vector3 &v, const ddouble vt)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		t = vt;
	}
	Vector4(const Vector4 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		t = v.t;
	}
	bool operator==(const Vector4 &v) const
	{
		return (x == v.x) && (y == v.y) && (z == v.z) && (t == v.t);
	}
	bool operator!=(const Vector4 &v) const
	{
		return (x != v.x) || (y != v.y) || (z != v.z) || (t != v.t);
	}
	Vector4 &operator=(const Vector4 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		t = v.t;
		return (*this);
	}
	Vector4 &operator+=(const Vector4 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		t += v.t;
		return (*this);
	}
	Vector4 &operator-=(const Vector4 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		t -= v.t;
		return (*this);
	}
	Vector4 &operator*=(const ddouble d)
	{
		x *= d;
		y *= d;
		z *= d;
		t *= d;
		return (*this);
	}
	Vector4 &operator/=(const ddouble d)
	{
		const ddouble c = 1.0 / d;
		x *= c;
		y *= c;
		z *= c;
		t *= c;
		return (*this);
	}
	Vector4 operator-() const
	{
		return Vector4(-x, -y, -z, -t);
	}
	Vector4 operator+(const Vector4 &v) const
	{
		return Vector4(x + v.x, y + v.y, z + v.z, t + v.t);
	}
	Vector4 operator-(const Vector4 &v) const
	{
		return Vector4(x - v.x, y - v.y, z - v.z, t - v.t);
	}
	Vector4 operator*(const ddouble d) const
	{
		return Vector4(x * d, y * d, z * d, t * d);
	}
	Vector4 operator/(const ddouble d) const
	{
		const ddouble c = 1.0 / d;
		return Vector4(x * c, y * c, z * c, t * c);
	}
	friend Vector4 operator*(const ddouble d, const Vector4 &v)
	{
		return v * d;
	}
	ddouble dot(const Vector4 &v) const
	{
		return x * v.x + y * v.y + z * v.z + t * v.t;
	}
	Vector4 cross(const Vector4 &v, const Vector4 &w) const
	{
		const ddouble dxy = v.x * w.y - v.y * w.x;
		const ddouble dyz = v.y * w.z - v.z * w.y;
		const ddouble dzt = v.z * w.t - v.t * w.z;
		const ddouble dxz = v.x * w.z - v.z * w.x;
		const ddouble dxt = v.x * w.t - v.t * w.x;
		const ddouble dyt = v.y * w.t - v.t * w.y;
		return Vector4(y * dzt - z * dyt + t * dyz,
					-x * dzt + z * dxt - t * dxz,
					x * dyt - y * dxt + t * dxy,
					-x * dyz + y * dxz - z * dxy);
	}
	ddouble len() const
	{
		return sqrt(lensq());
	}
	ddouble lensq() const
	{
		return x * x + y * y + z * z + t * t;
	}
	ddouble area(const Vector4 &v) const
	{
		return sqrt(areasq(v));
	}
	ddouble areasq(const Vector4 &v) const
	{
		const ddouble d = dot(v);
		return lensq() * v.lensq() - d * d;
	}
	Vector4 unit() const
	{
		const ddouble c = 1.0 / sqrt(x * x + y * y + z * z + t * t);
		return Vector4(x * c, y * c, z * c, t * c);
	}
	Vector4 &normalize()
	{
		const ddouble c = 1.0 / sqrt(x * x + y * y + z * z + t * t);
		x *= c;
		y *= c;
		z *= c;
		t *= c;
		return (*this);
	}
	Vector2 toVector2() const {	return Vector2(x, y); }
	Vector3 toVector3() const {	return Vector3(x, y, z); }
	ddouble x;
	ddouble y;
	ddouble z;
	ddouble t;
};

#endif //_VECTOR4_HPP_INCLUDED_
