#ifndef _TWOVECTOR4_HPP_INCLUDED_
#define _TWOVECTOR4_HPP_INCLUDED_

#include "Vector4.hpp"

class TwoVector4
{
public:
	TwoVector4() {}
	TwoVector4(const ddouble mxy, const ddouble mxz, const ddouble mxt,
				const ddouble myz, const ddouble myt, const ddouble mzt)
	{
		xy = mxy;
		xz = mxz;
		xt = mxt;
		yz = myz;
		yt = myt;
		zt = mzt;
	}
	TwoVector4(const Vector4 &a, const Vector4 &b)
	{
		xy = a.x * b.y - b.x * a.y;
		xz = a.x * b.z - b.x * a.z;
		xt = a.x * b.t - b.x * a.t;
		yz = a.y * b.z - b.y * a.z;
		yt = a.y * b.t - b.y * a.t;
		zt = a.z * b.t - b.z * a.t;
	}

	bool operator==(const TwoVector4 &m) const
	{
		return (xy == m.xy) && (xz == m.xz) && (xt == m.xt) &&
			(yz == m.yz) && (yt == m.yt) && (zt == m.zt);
	}
	bool operator!=(const TwoVector4 &m) const
	{
		return (xy != m.xy) || (xz != m.xz) || (xt != m.xt) ||
			(yz != m.yz) || (yt != m.yt) || (zt != m.zt);
	}
	TwoVector4 &operator=(const TwoVector4 &m)
	{
		xy = m.xy;
		xz = m.xz;
		xt = m.xt;
		yz = m.yz;
		yt = m.yt;
		zt = m.zt;
		return (*this);
	}
	TwoVector4 &operator+=(const TwoVector4 &m)
	{
		xy += m.xy;
		xz += m.xz;
		xt += m.xt;
		yz += m.yz;
		yt += m.yt;
		zt += m.zt;
		return (*this);
	}
	TwoVector4 &operator-=(const TwoVector4 &m)
	{
		xy -= m.xy;
		xz -= m.xz;
		xt -= m.xt;
		yz -= m.yz;
		yt -= m.yt;
		zt -= m.zt;
		return (*this);
	}
	TwoVector4 &operator*=(const ddouble d)
	{
		xy *= d;
		xz *= d;
		xt *= d;
		yz *= d;
		yt *= d;
		zt *= d;
		return (*this);
	}
	TwoVector4 &operator/=(const ddouble d)
	{
		const ddouble c = 1.0 / d;
		xy *= c;
		xz *= c;
		xt *= c;
		yz *= c;
		yt *= c;
		zt *= c;
		return (*this);
	}
	TwoVector4 operator-() const
	{
		return TwoVector4(-xy, -xz, -xt, -yz, -yt, -zt);
	}
	TwoVector4 operator+(const TwoVector4 &m) const
	{
		return TwoVector4(xy + m.xy, xz + m.xz, xt + m.xt, yz + m.yz, yt + m.yt, zt + m.zt);
	}
	TwoVector4 operator-(const TwoVector4 &m) const
	{
		return TwoVector4(xy - m.xy, xz - m.xz, xt - m.xt, yz - m.yz, yt - m.yt, zt - m.zt);
	}
	TwoVector4 operator*(const ddouble d) const
	{
		return TwoVector4(xy * d, xz * d, xt * d, yz * d, yt * d, zt * d);
	}
	friend TwoVector4 operator*(const ddouble d, const TwoVector4 &m)
	{
		return m * d;
	}
	TwoVector4 operator/(const ddouble d) const
	{
		const ddouble c = 1.0 / d;
		return TwoVector4(xy * c, xz * c, xt * c, yz * c, yt * c, zt * c);
	}
	TwoVector4 dual() const
	{
		return TwoVector4(zt, -yt, yz, xt, -xz, xy);
	}
	ddouble dot(const TwoVector4 &m) const
	{
		return xy * m.xy + xz * m.xz + xt * m.xt + yz * m.yz + yt * m.yt + zt * m.zt;
	}
	Vector4 wedge(const Vector4 &v) const
	{
		return Vector4(zt * v.y - yt * v.z + yz * v.t,
					-zt * v.x + xt * v.z - xz * v.t,
					yt * v.x - xt * v.y + xy * v.t,
					-yz * v.x + xz * v.y - xy * v.z);
	}
	ddouble wedge(const TwoVector4 &m) const
	{
		return xy * m.zt - xz * m.yt + xt * m.yz + yz * m.xt - yt * m.xz + zt * m.xy;
	}
	Vector4 wedgeX() const { return Vector4(0, -zt, yt, -yz); }
	Vector4 wedgeY() const { return Vector4(zt, 0, -xt, xz); }
	Vector4 wedgeZ() const { return Vector4(-yt, xt, 0, -xy); }
	Vector4 wedgeT() const { return Vector4(yz, -xz, xy, 0); }
	ddouble len() const
	{
		return sqrt(lensq());
	}
	ddouble lensq() const
	{
		return xy * xy + xz * xz + xt * xt + yz * yz + yt * yt + zt * zt;
	}
	TwoVector4 unit() const
	{
		return (*this) / len();
	}
	TwoVector4 &normalize()
	{
		return (*this) /= len();
	}

	ddouble xy;
	ddouble xz;
	ddouble xt;
	ddouble yz;
	ddouble yt;
	ddouble zt;
};

#endif //_TWOVECTOR4_HPP_INCLUDED_
