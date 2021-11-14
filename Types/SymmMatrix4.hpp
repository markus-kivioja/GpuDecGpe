#ifndef _SYMMMATRIX4_HPP_INCLUDED_
#define _SYMMMATRIX4_HPP_INCLUDED_

#include "Vector4.hpp"
#include "SymmMatrix3.hpp"

class SymmMatrix4
{
public:
	SymmMatrix4() {}
	SymmMatrix4(const ddouble mxx, const ddouble mxy, const ddouble mxz, const ddouble mxt,
				const ddouble myy, const ddouble myz, const ddouble myt,
				const ddouble mzz, const ddouble mzt,
				const ddouble mtt)
	{
		xx = mxx;
		xy = mxy;
		xz = mxz;
		xt = mxt;
		yy = myy;
		yz = myz;
		yt = myt;
		zz = mzz;
		zt = mzt;
		tt = mtt;
	}
	SymmMatrix4(const SymmMatrix4 &m)
	{
		xx = m.xx;
		xy = m.xy;
		xz = m.xz;
		xt = m.xt;
		yy = m.yy;
		yz = m.yz;
		yt = m.yt;
		zz = m.zz;
		zt = m.zt;
		tt = m.tt;
	}
	SymmMatrix4(const Vector4 &v)
	{
		xx = v.x * v.x;
		xy = v.x * v.y;
		xz = v.x * v.z;
		xt = v.x * v.t;
		yy = v.y * v.y;
		yz = v.y * v.z;
		yt = v.y * v.t;
		zz = v.z * v.z;
		zt = v.z * v.t;
		tt = v.t * v.t;
	}
	bool operator==(const SymmMatrix4 &m) const
	{
		return (xx == m.xx) && (xy == m.xy) && (xz == m.xz) && (xt == m.xt) &&
			(yy == m.yy) && (yz == m.yz) && (yt == m.yt) &&
			(zz == m.zz) && (zt == m.zt) &&
			(tt == m.tt);
	}
	bool operator!=(const SymmMatrix4 &m) const
	{
		return (xx != m.xx) || (xy != m.xy) || (xz != m.xz) || (xt != m.xt) ||
			(yy != m.yy) || (yz != m.yz) || (yt != m.yt) ||
			(zz != m.zz) || (zt != m.zt) ||
			(tt != m.tt);
	}
	SymmMatrix4 &operator=(const SymmMatrix4 &m)
	{
		xx = m.xx;
		xy = m.xy;
		xz = m.xz;
		xt = m.xt;
		yy = m.yy;
		yz = m.yz;
		yt = m.yt;
		zz = m.zz;
		zt = m.zt;
		tt = m.tt;
		return (*this);
	}
	SymmMatrix4 &operator+=(const SymmMatrix4 &m)
	{
		xx += m.xx;
		xy += m.xy;
		xz += m.xz;
		xt += m.xt;
		yy += m.yy;
		yz += m.yz;
		yt += m.yt;
		zz += m.zz;
		zt += m.zt;
		tt += m.tt;
		return (*this);
	}
	SymmMatrix4 &operator-=(const SymmMatrix4 &m)
	{
		xx -= m.xx;
		xy -= m.xy;
		xz -= m.xz;
		xt -= m.xt;
		yy -= m.yy;
		yz -= m.yz;
		yt -= m.yt;
		zz -= m.zz;
		zt -= m.zt;
		tt -= m.tt;
		return (*this);
	}
	SymmMatrix4 &operator*=(const ddouble d)
	{
		xx *= d;
		xy *= d;
		xz *= d;
		xt *= d;
		yy *= d;
		yz *= d;
		yt *= d;
		zz *= d;
		zt *= d;
		tt *= d;
		return (*this);
	}
	SymmMatrix4 &operator/=(const ddouble d)
	{
		const ddouble c = 1.0 / d;
		xx *= c;
		xy *= c;
		xz *= c;
		xt *= c;
		yy *= c;
		yz *= c;
		yt *= c;
		zz *= c;
		zt *= c;
		tt *= c;
		return (*this);
	}
	SymmMatrix4 &operator*=(const SymmMatrix4 &m)
	{
		(*this) = (*this) * m;
		return (*this);
	}
	SymmMatrix4 operator-() const
	{
		return SymmMatrix4(-xx, -xy, -xz, -xt, -yy, -yz, -yt, -zz, -zt, -tt);
	}
	SymmMatrix4 operator+(const SymmMatrix4 &m) const
	{
		return SymmMatrix4(xx + m.xx, xy + m.xy, xz + m.xz, xt + m.xt, yy + m.yy, yz + m.yz, yt + m.yt, zz + m.zz, zt + m.zt, tt + m.tt);
	}
	SymmMatrix4 operator-(const SymmMatrix4 &m) const
	{
		return SymmMatrix4(xx - m.xx, xy - m.xy, xz - m.xz, xt - m.xt, yy - m.yy, yz - m.yz, yt - m.yt, zz - m.zz, zt - m.zt, tt - m.tt);
	}
	SymmMatrix4 operator*(const ddouble d) const
	{
		return SymmMatrix4(xx * d, xy * d, xz * d, xt * d, yy * d, yz * d, yt * d, zz * d, zt * d, tt * d);
	}
	friend SymmMatrix4 operator*(const ddouble d, const SymmMatrix4 &m)
	{
		return m * d;
	}
	SymmMatrix4 operator/(const ddouble d) const
	{
		const ddouble c = 1.0 / d;
		return SymmMatrix4(xx * c, xy * c, xz * c, xt * c, yy * c, yz * c, yt * c, zz * c, zt * c, tt * c);
	}
	friend SymmMatrix4 operator/(const ddouble d, const SymmMatrix4 &m)
	{
		return m.inverse() * d;
	}
	Vector4 operator*(const Vector4 &v) const
	{
		return Vector4(xx * v.x + xy * v.y + xz * v.z + xt * v.t,
			xy * v.x + yy * v.y + yz * v.z + yt * v.t,
			xz * v.x + yz * v.y + zz * v.z + zt * v.t,
			xt * v.x + yt * v.y + zt * v.z + tt * v.t);
	}
	friend Vector4 operator*(const Vector4 &v, const SymmMatrix4 &m)
	{
		return m * v;
	}
	SymmMatrix4 operator*(const SymmMatrix4 &m) const
	{
		return SymmMatrix4(xx * m.xx + xy * m.xy + xz * m.xz + xt * m.xt,
			xx * m.xy + xy * m.yy + xz * m.yz + xt * m.yt,
			xx * m.xz + xy * m.yz + xz * m.zz + xt * m.zt,
			xx * m.xt + xy * m.yt + xz * m.zt + xt * m.tt,
			xy * m.xy + yy * m.yy + yz * m.yz + yt * m.yt,
			xy * m.xz + yy * m.yz + yz * m.zz + yt * m.zt,
			xy * m.xt + yy * m.yt + yz * m.zt + yt * m.tt,
			xz * m.xz + yz * m.yz + zz * m.zz + zt * m.zt,
			xz * m.xt + yz * m.yt + zz * m.zt + zt * m.tt,
			xt * m.xt + yt * m.yt + zt * m.zt + tt * m.tt);
	}
	ddouble det() const
	{
		const ddouble dxy = xz * yt - xt * yz;
		const ddouble dyz = yz * zt - yt * zz;
		const ddouble dzt = zz * tt - zt * zt;
		const ddouble dxz = xz * zt - xt * zz;
		const ddouble dxt = xz * tt - xt * zt;
		const ddouble dyt = yz * tt - yt * zt;
		return xx * (yy * dzt - yz * dyt + yt * dyz) -
			xy * (xy * dzt - yz * dxt + yt * dxz) +
			xz * (xy * dyt - yy * dxt + yt * dxy) -
			xt * (xy * dyz - yy * dxz + yz * dxy);
	}
	SymmMatrix4 inverse() const
	{
		const ddouble dxy = xz * yt - xt * yz;
		const ddouble dyz = yz * zt - yt * zz;
		const ddouble dzt = zz * tt - zt * zt;
		const ddouble dxt = xz * tt - xt * zt;
		const ddouble dyt = yz * tt - yt * zt;
		const ddouble dxz = xz * zt - xt * zz;
		const ddouble dyzt = yy * dzt - yz * dyt + yt * dyz;
		const ddouble dxzt = xy * dzt - yz * dxt + yt * dxz;
		const ddouble dxyt = xy * dyt - yy * dxt + yt * dxy;
		const ddouble dxyz = xy * dyz - yy * dxz + yz * dxy;
		const ddouble axy = xx * yy - xy * xy;
		const ddouble ayz = xy * yz - yy * xz;
		const ddouble axz = xx * yz - xy * xz;
		const ddouble ayt = xy * yt - yy * xt;
		const ddouble axt = xx * yt - xy * xt;
		const ddouble det = xx * dyzt - xy * dxzt + xz * dxyt - xt * dxyz;
		return SymmMatrix4(dyzt, -dxzt, dxyt, -dxyz,
			xx * dzt - xz * dxt + xt * dxz,
			-xx * dyt + xy * dxt - xt * dxy,
			xx * dyz - xy * dxz + xz * dxy,
			xt * ayt - yt * axt + tt * axy,
			-xt * ayz + yt * axz - zt * axy,
			xz * ayz - yz * axz + zz * axy) / det;
	}
	ddouble normsq(const Vector4 &v) const
	{
		return v.dot((*this) * v);
	}
	SymmMatrix3 toSymmMatrix3() const { return SymmMatrix3(xx, xy, xz, yy, yz, zz); }
	SymmMatrix2 toSymmMatrix2() const { return SymmMatrix2(xx, xy, yy); }

	ddouble xx;
	ddouble xy;
	ddouble xz;
	ddouble xt;
	ddouble yy;
	ddouble yz;
	ddouble yt;
	ddouble zz;
	ddouble zt;
	ddouble tt;
};

const SymmMatrix4 IDENTITYSYMMMATRIX4(1,0,0,0,1,0,0,1,0,1);
const SymmMatrix4 ZEROSYMMMATRIX4(0,0,0,0,0,0,0,0,0,0);

#endif //_SYMMMATRIX4_HPP_INCLUDED_
