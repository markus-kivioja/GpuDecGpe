#ifndef _SYMMMATRIX2_HPP_INCLUDED_
#define _SYMMMATRIX2_HPP_INCLUDED_

#include "Vector2.hpp"

class SymmMatrix2
{
public:
	SymmMatrix2() {}
	SymmMatrix2(const ddouble mxx, const ddouble mxy, const ddouble myy)
	{
		xx = mxx;
		xy = mxy;
		yy = myy;
	}
	SymmMatrix2(const SymmMatrix2 &m)
	{
		xx = m.xx;
		xy = m.xy;
		yy = m.yy;
	}
	SymmMatrix2(const Vector2 &v)
	{
		xx = v.x * v.x;
		xy = v.x * v.y;
		yy = v.y * v.y;
	}
	bool operator==(const SymmMatrix2 &m) const
	{
		return (xx == m.xx) && (xy == m.xy) && (yy == m.yy);
	}
	bool operator!=(const SymmMatrix2 &m) const
	{
		return (xx != m.xx) || (xy != m.xy) || (yy != m.yy);
	}
	SymmMatrix2 &operator=(const SymmMatrix2 &m)
	{
		xx = m.xx;
		xy = m.xy;
		yy = m.yy;
		return (*this);
	}
	SymmMatrix2 &operator+=(const SymmMatrix2 &m)
	{
		xx += m.xx;
		xy += m.xy;
		yy += m.yy;
		return (*this);
	}
	SymmMatrix2 &operator-=(const SymmMatrix2 &m)
	{
		xx -= m.xx;
		xy -= m.xy;
		yy -= m.yy;
		return (*this);
	}
	SymmMatrix2 &operator*=(const ddouble d)
	{
		xx *= d;
		xy *= d;
		yy *= d;
		return (*this);
	}
	SymmMatrix2 &operator/=(const ddouble d)
	{
		const ddouble c = 1.0 / d;
		xx *= c;
		xy *= c;
		yy *= c;
		return (*this);
	}
	SymmMatrix2 &operator*=(const SymmMatrix2 &m)
	{
		(*this) = (*this) * m;
		return (*this);
	}
	SymmMatrix2 operator-() const
	{
		return SymmMatrix2(-xx, -xy, -yy);
	}
	SymmMatrix2 operator+(const SymmMatrix2 &m) const
	{
		return SymmMatrix2(xx + m.xx, xy + m.xy, yy + m.yy);
	}
	SymmMatrix2 operator-(const SymmMatrix2 &m) const
	{
		return SymmMatrix2(xx - m.xx, xy - m.xy, yy - m.yy);
	}
	SymmMatrix2 operator*(const ddouble d) const
	{
		return SymmMatrix2(xx * d, xy * d, yy * d);
	}
	friend SymmMatrix2 operator*(const ddouble d, const SymmMatrix2 &m)
	{
		return m * d;
	}
	SymmMatrix2 operator/(const ddouble d) const
	{
		const ddouble c = 1.0 / d;
		return SymmMatrix2(xx * c, xy * c, yy * c);
	}
	friend SymmMatrix2 operator/(const ddouble d, const SymmMatrix2 &m)
	{
		return m.inverse() * d;
	}
	Vector2 operator*(const Vector2 &v) const
	{
		return Vector2(xx * v.x + xy * v.y, xy * v.x + yy * v.y);
	}
	friend Vector2 operator*(const Vector2 &v, const SymmMatrix2 &m)
	{
		return m * v;
	}
	SymmMatrix2 operator*(const SymmMatrix2 &m) const
	{
		return SymmMatrix2(xx * m.xx + xy * m.xy, xx * m.xy + xy * m.yy, xy * m.xy + yy * m.yy);
	}
	ddouble det() const
	{
		return xx * yy - xy * xy;
	}
	SymmMatrix2 inverse() const
	{
		const ddouble div = 1.0 / det();
		return SymmMatrix2(yy*div, -xy*div, xx*div);
	}
	ddouble normsq(const Vector2 &v) const
	{
		return v.dot((*this) * v);
	}

	ddouble xx;
	ddouble xy;
	ddouble yy;
};

const SymmMatrix2 IDENTITYSYMMMATRIX2(1,0,1);
const SymmMatrix2 ZEROSYMMMATRIX2(0,0,0);

#endif //_SYMMMATRIX2_HPP_INCLUDED_
