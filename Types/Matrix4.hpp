#ifndef _MATRIX4_HPP_INCLUDED_
#define _MATRIX4_HPP_INCLUDED_

#include "SymmMatrix4.hpp"
#include "Matrix3.hpp"

class Matrix4
{
public:
	Matrix4() {}
	Matrix4(const ddouble mxx, const ddouble mxy, const ddouble mxz, const ddouble mxt,
					const ddouble myx, const ddouble myy, const ddouble myz, const ddouble myt,
					const ddouble mzx, const ddouble mzy, const ddouble mzz, const ddouble mzt,
					const ddouble mtx, const ddouble mty, const ddouble mtz, const ddouble mtt)
	{
		x = Vector4(mxx, mxy, mxz, mxt);
		y = Vector4(myx, myy, myz, myt);
		z = Vector4(mzx, mzy, mzz, mzt);
		t = Vector4(mtx, mty, mtz, mtt);
	}
	Matrix4(const Vector4 &mx, const Vector4 &my, const Vector4 &mz, const Vector4 &mt)
	{
		x = mx;
		y = my;
		z = mz;
		t = mt;
	}
	Matrix4(const Matrix4 &m)
	{
		x = m.x;
		y = m.y;
		z = m.z;
		t = m.t;
	}
	Matrix4(const SymmMatrix4 &m)
	{
		x = Vector4(m.xx, m.xy, m.xz, m.xt);
		y = Vector4(m.xy, m.yy, m.yz, m.yt);
		z = Vector4(m.xz, m.yz, m.zz, m.zt);
		t = Vector4(m.xt, m.yt, m.zt, m.tt);
	}
	Matrix4(const Matrix3 &m, const Vector3 &lastcolumn, const Vector4 &mt)
	{
		x = Vector4(m.x, lastcolumn.x);
		y = Vector4(m.y, lastcolumn.y);
		z = Vector4(m.z, lastcolumn.z);
		t = mt;
	}
	bool operator==(const Matrix4 &m) const
	{
		return (x == m.x) && (y == m.y) && (z == m.z) && (t == m.t);
	}
	bool operator!=(const Matrix4 &m) const
	{
		return (x != m.x) || (y != m.y) || (z != m.z) || (t != m.t);
	}
	Matrix4 &operator=(const Matrix4 &m)
	{
		x = m.x;
		y = m.y;
		z = m.z;
		t = m.t;
		return (*this);
	}
	Matrix4 &operator+=(const Matrix4 &m)
	{
		x += m.x;
		y += m.y;
		z += m.z;
		t += m.t;
		return (*this);
	}
	Matrix4 &operator-=(const Matrix4 &m)
	{
		x -= m.x;
		y -= m.y;
		z -= m.z;
		t -= m.t;
		return (*this);
	}
	Matrix4 &operator*=(const ddouble d)
	{
		x *= d;
		y *= d;
		z *= d;
		t *= d;
		return (*this);
	}
	Matrix4 &operator/=(const ddouble d)
	{
		const ddouble c = 1.0 / d;
		x *= c;
		y *= c;
		z *= c;
		t *= c;
		return (*this);
	}
	Matrix4 &operator*=(const Matrix4 &m)
	{
		x = x.x * m.x + x.y * m.y + x.z * m.z + x.t * m.t;
		y = y.x * m.x + y.y * m.y + y.z * m.z + y.t * m.t;
		z = z.x * m.x + z.y * m.y + z.z * m.z + z.t * m.t;
		t = t.x * m.x + t.y * m.y + t.z * m.z + t.t * m.t;
		return (*this);
	}
	Matrix4 operator-() const
	{
		return Matrix4(-x, -y, -z, -t);
	}
	Matrix4 operator+(const Matrix4 &m) const
	{
		return Matrix4(x + m.x, y + m.y, z + m.z, t + m.t);
	}
	Matrix4 operator-(const Matrix4 &m) const
	{
		return Matrix4(x - m.x, y - m.y, z - m.z, t - m.t);
	}
	Matrix4 operator*(const ddouble d) const
	{
		return Matrix4(x * d, y * d, z * d, t * d);
	}
	friend Matrix4 operator*(const ddouble d, const Matrix4 &m)
	{
		return m * d;
	}
	Matrix4 operator/(const ddouble d) const
	{
		const ddouble c = 1.0 / d;
		return Matrix4(x * c, y * c, z * c, t * c);
	}
	friend Matrix4 operator/(const ddouble d, const Matrix4 &m)
	{
		return m.inverse() * d;
	}
	Vector4 operator*(const Vector4 &v) const
	{
		return Vector4(x.dot(v), y.dot(v), z.dot(v), t.dot(v));
	}
	friend Vector4 operator*(const Vector4 &v, const Matrix4 &m)
	{
		return v.x * m.x + v.y * m.y + v.z * m.z + v.t * m.t;
	}
	Matrix4 operator*(const Matrix4 &m) const
	{
		return Matrix4(x.x * m.x + x.y * m.y + x.z * m.z + x.t * m.t,
					y.x * m.x + y.y * m.y + y.z * m.z + y.t * m.t,
					z.x * m.x + z.y * m.y + z.z * m.z + z.t * m.t,
					t.x * m.x + t.y * m.y + t.z * m.z + t.t * m.t);
	}
	Matrix4 transpose() const
	{
		return Matrix4(x.x,y.x,z.x,t.x, x.y,y.y,z.y,t.y, x.z,y.z,z.z,t.z, x.t,y.t,z.t,t.t);
	}
	ddouble det() const
	{
		return x.dot(y.cross(z, t));
	}
	Matrix4 inverse() const
	{
		const Vector4 yzt = y.cross(z,t);
		const ddouble div = 1.0 / x.dot(yzt);
		const Vector4 nx = yzt * div;
		const Vector4 ny = x.cross(t,z) * div;
		const Vector4 nz = x.cross(y,t) * div;
		const Vector4 nt = x.cross(z,y) * div;
		return Matrix4(nx.x,ny.x,nz.x,nt.x, nx.y,ny.y,nz.y,nt.y, nx.z,ny.z,nz.z,nt.z, nx.t,ny.t,nz.t,nt.t);
	}
	ddouble normsq(const Vector4 &v) const
	{
		return v.dot((*this) * v);
	}
	SymmMatrix4 toSymmMatrix4() const {	return SymmMatrix4(x.x, 0.5 * (x.y + y.x), 0.5 * (x.z + z.x), 0.5 * (x.t + t.x), y.y, 0.5 * (y.z + z.y), 0.5 * (y.t + t.y), z.z, 0.5 * (z.t + t.z), t.t); }

	Vector4 x;
	Vector4 y;
	Vector4 z;
	Vector4 t;
};

const Matrix4 IDENTITYMATRIX4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
const Matrix4 ZEROMATRIX4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

#endif //_MATRIX4_HPP_INCLUDED_
