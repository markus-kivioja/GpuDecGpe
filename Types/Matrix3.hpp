#ifndef _MATRIX3_HPP_INCLUDED_
#define _MATRIX3_HPP_INCLUDED_

#include "SymmMatrix3.hpp"
#include "Matrix2.hpp"

class Matrix3
{
public:
	Matrix3() {}
	Matrix3(const ddouble mxx, const ddouble mxy, const ddouble mxz,
					const ddouble myx, const ddouble myy, const ddouble myz,
					const ddouble mzx, const ddouble mzy, const ddouble mzz)
	{
		x = Vector3(mxx, mxy, mxz);
		y = Vector3(myx, myy, myz);
		z = Vector3(mzx, mzy, mzz);
	}
	Matrix3(const Vector3 &mx, const Vector3 &my, const Vector3 &mz)
	{
		x = mx;
		y = my;
		z = mz;
	}
	Matrix3(const Matrix3 &m)
	{
		x = m.x;
		y = m.y;
		z = m.z;
	}
	Matrix3(const SymmMatrix3 &m)
	{
		x = Vector3(m.xx, m.xy, m.xz);
		y = Vector3(m.xy, m.yy, m.yz);
		z = Vector3(m.xz, m.yz, m.zz);
	}
	Matrix3(const Matrix2 &m, const Vector2 &lastcolumn, const Vector3 &mz)
	{
		x = Vector3(m.x, lastcolumn.x);
		y = Vector3(m.y, lastcolumn.y);
		z = mz;
	}
	bool operator==(const Matrix3 &m) const
	{
		return (x == m.x) && (y == m.y) && (z == m.z);
	}
	bool operator!=(const Matrix3 &m) const
	{
		return (x != m.x) || (y != m.y) || (z != m.z);
	}
	Matrix3 &operator=(const Matrix3 &m)
	{
		x = m.x;
		y = m.y;
		z = m.z;
		return (*this);
	}
	Matrix3 &operator+=(const Matrix3 &m)
	{
		x += m.x;
		y += m.y;
		z += m.z;
		return (*this);
	}
	Matrix3 &operator-=(const Matrix3 &m)
	{
		x -= m.x;
		y -= m.y;
		z -= m.z;
		return (*this);
	}
	Matrix3 &operator*=(const ddouble d)
	{
		x *= d;
		y *= d;
		z *= d;
		return (*this);
	}
	Matrix3 &operator/=(const ddouble d)
	{
		const ddouble c = 1.0 / d;
		x *= c;
		y *= c;
		z *= c;
		return (*this);
	}
	Matrix3 &operator*=(const Matrix3 &m)
	{
		x = x.x * m.x + x.y * m.y + x.z * m.z;
		y = y.x * m.x + y.y * m.y + y.z * m.z;
		z = z.x * m.x + z.y * m.y + z.z * m.z;
		return (*this);
	}
	Matrix3 operator-() const
	{
		return Matrix3(-x, -y, -z);
	}
	Matrix3 operator+(const Matrix3 &m) const
	{
		return Matrix3(x + m.x, y + m.y, z + m.z);
	}
	Matrix3 operator-(const Matrix3 &m) const
	{
		return Matrix3(x - m.x, y - m.y, z - m.z);
	}
	Matrix3 operator*(const ddouble d) const
	{
		return Matrix3(x * d, y * d, z * d);
	}
	friend Matrix3 operator*(const ddouble d, const Matrix3 &m)
	{
		return m * d;
	}
	Matrix3 operator/(const ddouble d) const
	{
		const ddouble c = 1.0 / d;
		return Matrix3(x * c, y * c, z * c);
	}
	friend Matrix3 operator/(const ddouble d, const Matrix3 &m)
	{
		return m.inverse() * d;
	}
	Vector3 operator*(const Vector3 &v) const
	{
		return Vector3(x.dot(v), y.dot(v), z.dot(v));
	}
	friend Vector3 operator*(const Vector3 &v, const Matrix3 &m)
	{
		return v.x * m.x + v.y * m.y + v.z * m.z;
	}
	Matrix3 operator*(const Matrix3 &m) const
	{
		return Matrix3(x.x * m.x + x.y * m.y + x.z * m.z,
					y.x * m.x + y.y * m.y + y.z * m.z,
					z.x * m.x + z.y * m.y + z.z * m.z);
	}
	Matrix3 transpose() const
	{
		return Matrix3(x.x,y.x,z.x, x.y,y.y,z.y, x.z,y.z,z.z);
	}
	ddouble det() const
	{
		return x.dot(y.cross(z));
	}
	Matrix3 inverse() const
	{
		const Vector3 xcrossy = x.cross(y);
		const ddouble div = 1.0 / xcrossy.dot(z);
		const Vector3 nx = y.cross(z) * div;
		const Vector3 ny = z.cross(x) * div;
		const Vector3 nz = xcrossy * div;
		return Matrix3(nx.x,ny.x,nz.x, nx.y,ny.y,nz.y, nx.z,ny.z,nz.z);
	}
	Matrix3 &rotateX(const ddouble a)
	{
		const ddouble c = cos(a), s = sin(a);
		const Vector3 v = y;
		y = c * v + s * z;
		z = c * z - s * v;
		return (*this);
	}
	Matrix3 &rotateY(const ddouble a)
	{
		const ddouble c = cos(a), s = sin(a);
		const Vector3 v = z;
		z = c * v + s * x;
		x = c * x - s * v;
		return (*this);
	}
	Matrix3 &rotateZ(const ddouble a)
	{
		const ddouble c = cos(a), s = sin(a);
		const Vector3 v = x;
		x = c * v + s * y;
		y = c * y - s * v;
		return (*this);
	}
	Matrix3 &rotate(const Vector3 &v)
	{
		const ddouble len = v.len();
		const ddouble c = cos(len);
		if(len < 1e-8)
		{
			x = c * x + 0.5 * v.dot(x) * v + v.cross(x);
			y = c * y + 0.5 * v.dot(y) * v + v.cross(y);
			z = c * z + 0.5 * v.dot(z) * v + v.cross(z);
		}
		else
		{
			const ddouble t = (1.0 - c) / (len * len);
			const Vector3 s = (sin(len) / len) * v;
			x = c * x + t * v.dot(x) * v + s.cross(x);
			y = c * y + t * v.dot(y) * v + s.cross(y);
			z = c * z + t * v.dot(z) * v + s.cross(z);
		}
		return (*this);
	}
	ddouble normsq(const Vector3 &v) const
	{
		return v.x * v.dot(x) + v.y * v.dot(y) + v.z * v.dot(z);
	}
	SymmMatrix3 toSymmMatrix3() const {	return SymmMatrix3(x.x, 0.5 * (x.y + y.x), 0.5 * (x.z + z.x), y.y, 0.5 * (y.z + z.y), z.z); }

	Vector3 x;
	Vector3 y;
	Vector3 z;
};

const Matrix3 IDENTITYMATRIX3(1,0,0,0,1,0,0,0,1);
const Matrix3 ZEROMATRIX3(0,0,0,0,0,0,0,0,0);

#endif //_MATRIX3_HPP_INCLUDED_
