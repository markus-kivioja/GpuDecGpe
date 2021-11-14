#ifndef _SYMMMATRIX3_HPP_INCLUDED_
#define _SYMMMATRIX3_HPP_INCLUDED_

#include "Vector3.hpp"
#include "SymmMatrix2.hpp"

class SymmMatrix3
{
public:
	SymmMatrix3() {}
	SymmMatrix3(const ddouble mxx, const ddouble mxy, const ddouble mxz,
				const ddouble myy, const ddouble myz,
				const ddouble mzz)
	{
		xx = mxx;
		xy = mxy;
		xz = mxz;
		yy = myy;
		yz = myz;
		zz = mzz;
	}
	SymmMatrix3(const SymmMatrix3 &m)
	{
		xx = m.xx;
		xy = m.xy;
		xz = m.xz;
		yy = m.yy;
		yz = m.yz;
		zz = m.zz;
	}
	SymmMatrix3(const Vector3 &v)
	{
		xx = v.x * v.x;
		xy = v.x * v.y;
		xz = v.x * v.z;
		yy = v.y * v.y;
		yz = v.y * v.z;
		zz = v.z * v.z;
	}
	bool operator==(const SymmMatrix3 &m) const
	{
		return (xx == m.xx) && (xy == m.xy) && (xz == m.xz) &&
			(yy == m.yy) && (yz == m.yz) && (zz == m.zz);
	}
	bool operator!=(const SymmMatrix3 &m) const
	{
		return (xx != m.xx) || (xy != m.xy) || (xz != m.xz) ||
			(yy != m.yy) || (yz != m.yz) || (zz != m.zz);
	}
	SymmMatrix3 &operator=(const SymmMatrix3 &m)
	{
		xx = m.xx;
		xy = m.xy;
		xz = m.xz;
		yy = m.yy;
		yz = m.yz;
		zz = m.zz;
		return (*this);
	}
	SymmMatrix3 &operator+=(const SymmMatrix3 &m)
	{
		xx += m.xx;
		xy += m.xy;
		xz += m.xz;
		yy += m.yy;
		yz += m.yz;
		zz += m.zz;
		return (*this);
	}
	SymmMatrix3 &operator-=(const SymmMatrix3 &m)
	{
		xx -= m.xx;
		xy -= m.xy;
		xz -= m.xz;
		yy -= m.yy;
		yz -= m.yz;
		zz -= m.zz;
		return (*this);
	}
	SymmMatrix3 &operator*=(const ddouble d)
	{
		xx *= d;
		xy *= d;
		xz *= d;
		yy *= d;
		yz *= d;
		zz *= d;
		return (*this);
	}
	SymmMatrix3 &operator/=(const ddouble d)
	{
		const ddouble c = 1.0 / d;
		xx *= c;
		xy *= c;
		xz *= c;
		yy *= c;
		yz *= c;
		zz *= c;
		return (*this);
	}
	SymmMatrix3 &operator*=(const SymmMatrix3 &m)
	{
		(*this) = (*this) * m;
		return (*this);
	}
	SymmMatrix3 operator-() const
	{
		return SymmMatrix3(-xx, -xy, -xz, -yy, -yz, -zz);
	}
	SymmMatrix3 operator+(const SymmMatrix3 &m) const
	{
		return SymmMatrix3(xx + m.xx, xy + m.xy, xz + m.xz, yy + m.yy, yz + m.yz, zz + m.zz);
	}
	SymmMatrix3 operator-(const SymmMatrix3 &m) const
	{
		return SymmMatrix3(xx - m.xx, xy - m.xy, xz - m.xz, yy - m.yy, yz - m.yz, zz - m.zz);
	}
	SymmMatrix3 operator*(const ddouble d) const
	{
		return SymmMatrix3(xx * d, xy * d, xz * d, yy * d, yz * d, zz * d);
	}
	friend SymmMatrix3 operator*(const ddouble d, const SymmMatrix3 &m)
	{
		return m * d;
	}
	SymmMatrix3 operator/(const ddouble d) const
	{
		const ddouble c = 1.0 / d;
		return SymmMatrix3(xx * c, xy * c, xz * c, yy * c, yz * c, zz * c);
	}
	friend SymmMatrix3 operator/(const ddouble d, const SymmMatrix3 &m)
	{
		return m.inverse() * d;
	}
	Vector3 operator*(const Vector3 &v) const
	{
		return Vector3(xx * v.x + xy * v.y + xz * v.z,
			xy * v.x + yy * v.y + yz * v.z,
			xz * v.x + yz * v.y + zz * v.z);
	}
	friend Vector3 operator*(const Vector3 &v, const SymmMatrix3 &m)
	{
		return m * v;
	}
	SymmMatrix3 operator*(const SymmMatrix3 &m) const
	{
		return SymmMatrix3(xx * m.xx + xy * m.xy + xz * m.xz,
			xx * m.xy + xy * m.yy + xz * m.yz,
			xx * m.xz + xy * m.yz + xz * m.zz,
			xy * m.xy + yy * m.yy + yz * m.yz,
			xy * m.xz + yy * m.yz + yz * m.zz,
			xz * m.xz + yz * m.yz + zz * m.zz);
	}
	ddouble det() const
	{
		return xx * yy * zz + 2.0 * xy * yz * xz - yz * yz * xx - xz * xz * yy - xy * xy * zz;
	}
	SymmMatrix3 inverse() const
	{
		const Vector3 xcrossy(xy * yz - xz * yy, xz * xy - xx * yz, xx * yy - xy * xy);
		const ddouble div = 1.0 / (xcrossy.x * xz + xcrossy.y * yz + xcrossy.z * zz);
		return SymmMatrix3((yy * zz - yz * yz) * div, (yz * xz - zz * xy) * div, xcrossy.x * div,
			(zz * xx - xz * xz) * div, xcrossy.y * div, xcrossy.z * div);
	}
	ddouble normsq(const Vector3 &v) const
	{
		return v.dot((*this) * v);
	}
	SymmMatrix2 toSymmMatrix2() const { return SymmMatrix2(xx, xy, yy); }

	ddouble xx;
	ddouble xy;
	ddouble xz;
	ddouble yy;
	ddouble yz;
	ddouble zz;
};

const SymmMatrix3 IDENTITYSYMMMATRIX3(1,0,0,1,0,1);
const SymmMatrix3 ZEROSYMMMATRIX3(0,0,0,0,0,0);

#endif //_SYMMMATRIX3_HPP_INCLUDED_
