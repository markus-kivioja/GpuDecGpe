#ifndef _MATRIX2_HPP_INCLUDED_
#define _MATRIX2_HPP_INCLUDED_

#include "SymmMatrix2.hpp"

class Matrix2
{
public:
	Matrix2() {}
	Matrix2(const ddouble mxx, const ddouble mxy, const ddouble myx, const ddouble myy)
	{
		x = Vector2(mxx, mxy);
		y = Vector2(myx, myy);
	}
	Matrix2(const Vector2 &mx, const Vector2 &my)
	{
		x = mx;
		y = my;
	}
	Matrix2(const Matrix2 &m)
	{
		x = m.x;
		y = m.y;
	}
	Matrix2(const SymmMatrix2 &m)
	{
		x = Vector2(m.xx, m.xy);
		y = Vector2(m.xy, m.yy);
	}
	bool operator==(const Matrix2 &m) const
	{
		return (x == m.x) && (y == m.y);
	}
	bool operator!=(const Matrix2 &m) const
	{
		return (x != m.x) || (y != m.y);
	}
	Matrix2 &operator=(const Matrix2 &m)
	{
		x = m.x;
		y = m.y;
		return (*this);
	}
	Matrix2 &operator+=(const Matrix2 &m)
	{
		x += m.x;
		y += m.y;
		return (*this);
	}
	Matrix2 &operator-=(const Matrix2 &m)
	{
		x -= m.x;
		y -= m.y;
		return (*this);
	}
	Matrix2 &operator*=(const ddouble d)
	{
		x *= d;
		y *= d;
		return (*this);
	}
	Matrix2 &operator/=(const ddouble d)
	{
		const ddouble c = 1.0 / d;
		x *= c;
		y *= c;
		return (*this);
	}
	Matrix2 &operator*=(const Matrix2 &m)
	{
		x = x.x * m.x + x.y * m.y;
		y = y.x * m.x + y.y * m.y;
		return (*this);
	}
	Matrix2 operator-() const
	{
		return Matrix2(-x, -y);
	}
	Matrix2 operator+(const Matrix2 &m) const
	{
		return Matrix2(x + m.x, y + m.y);
	}
	Matrix2 operator-(const Matrix2 &m) const
	{
		return Matrix2(x - m.x, y - m.y);
	}
	Matrix2 operator*(const ddouble d) const
	{
		return Matrix2(x * d, y * d);
	}
	friend Matrix2 operator*(const ddouble d, const Matrix2 &m)
	{
		return m * d;
	}
	Matrix2 operator/(const ddouble d) const
	{
		const ddouble c = 1.0 / d;
		return Matrix2(x * c, y * c);
	}
	friend Matrix2 operator/(const ddouble d, const Matrix2 &m)
	{
		return m.inverse() * d;
	}
	Vector2 operator*(const Vector2 &v) const
	{
		return Vector2(x.dot(v), y.dot(v));
	}
	friend Vector2 operator*(const Vector2 &v, const Matrix2 &m)
	{
		return v.x * m.x + v.y * m.y;
	}
	Matrix2 operator*(const Matrix2 &m) const
	{
		return Matrix2(x.x * m.x + x.y * m.y, y.x * m.x + y.y * m.y);
	}
	Matrix2 transpose() const
	{
		return Matrix2(x.x,y.x, x.y,y.y);
	}
	ddouble det() const
	{
		return x.cross(y);
	}
	Matrix2 inverse() const
	{
		const ddouble div = 1.0 / det();
		return Matrix2(y.y*div, -y.x*div, -x.y*div, x.x*div);
	}
	ddouble normsq(const Vector2 &v) const
	{
		return v.x * v.dot(x) + v.y * v.dot(y);
	}
	SymmMatrix2 toSymmMatrix2() const {	return SymmMatrix2(x.x, 0.5 * (x.y + y.x), y.y); }

	Vector2 x;
	Vector2 y;
};

const Matrix2 IDENTITYMATRIX2(1,0,0,1);
const Matrix2 ZEROMATRIX2(0,0,0,0);

#endif //_MATRIX2_HPP_INCLUDED_
