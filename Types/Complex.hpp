#ifndef _COMPLEX_HPP_INCLUDED_
#define _COMPLEX_HPP_INCLUDED_

#include <cmath>
#include <stdio.h>
#include <math.h>

//typedef long double ddouble;
typedef double ddouble;

class Complex
{
public:
	Complex() {}
	Complex(const ddouble cr, const ddouble ci = 0.0)
	{
		r = cr;
		i = ci;
	}
	Complex(const Complex &c)
	{
		r = c.r;
		i = c.i;
	}
	bool operator==(const Complex &c) const
	{
		return (r == c.r) && (i == c.i);
	}
	bool operator!=(const Complex &c) const
	{
		return (r != c.r) || (i != c.i);
	}
	Complex &operator=(const Complex &c)
	{
		r = c.r;
		i = c.i;
		return (*this);
	}
	Complex &operator+=(const Complex &c)
	{
		r += c.r;
		i += c.i;
		return (*this);
	}
	Complex &operator-=(const Complex &c)
	{
		r -= c.r;
		i -= c.i;
		return (*this);
	}
	Complex &operator*=(const ddouble d)
	{
		r *= d;
		i *= d;
		return (*this);
	}
	Complex &operator*=(const Complex &c)
	{
		const ddouble rr = r;
		r = rr * c.r - i * c.i;
		i = i * c.r + rr * c.i;
		return (*this);
	}
	Complex &operator/=(const ddouble d)
	{
		const ddouble h = 1.0 / d;
		r *= h;
		i *= h;
		return (*this);
	}
	Complex &operator/=(const Complex &c)
	{
		const ddouble h = 1.0 / (c.r * c.r + c.i * c.i);
		const ddouble rr = r;
		r = (rr * c.r + i * c.i) * h;
		i = (i * c.r - rr * c.i) * h;
		return (*this);
	}
	Complex operator-() const
	{
		return Complex(-r, -i);
	}
	Complex operator+(const Complex &c) const
	{
		return Complex(r + c.r, i + c.i);
	}
	Complex operator-(const Complex &c) const
	{
		return Complex(r - c.r, i - c.i);
	}
	const Complex operator*(const ddouble d) const
	{
		return Complex(r * d, i * d);
	}
	Complex operator*(const Complex &c) const
	{
		return Complex(r * c.r - i * c.i, i * c.r + r * c.i);
	}
	Complex operator/(const ddouble d) const
	{
		const ddouble h = 1.0 / d;
		return Complex(r * h, i * h);
	}
	Complex operator/(const Complex &c) const
	{
		const ddouble h = 1.0 / (c.r * c.r + c.i * c.i);
		return Complex((r * c.r + i * c.i) * h, (i * c.r - r * c.i) * h);
	}
	friend Complex operator*(const ddouble d, const Complex &c)
	{
		return c * d;
	}
	friend Complex operator/(const ddouble d, const Complex &c)
	{
		const ddouble h = d / (c.r * c.r + c.i * c.i);
		return Complex(c.r * h, -c.i * h);
	}
	Complex con() const
	{
		return Complex(r, -i);
	}
	ddouble dot(const Complex &c) const
	{
		return r * c.r + i * c.i;
	}
	ddouble norm() const
	{
		return sqrt(r * r + i * i);
	}
	ddouble normsq() const
	{
		return r * r + i * i;
	}
	Complex sqroot() const
	{
		const ddouble h = sqrt(r * r + i * i);
		return Complex(h > -r ? sqrt(0.5 * (h + r)) : 0.0, h > r ? sqrt(0.5 * (h - r)) : 0.0);
	}
	Complex unit() const
	{
		const ddouble h = 1.0 / sqrt(r * r + i * i);
		return Complex(r * h, i * h);
	}
	Complex &normalize()
	{
		const ddouble h = 1.0 / sqrt(r * r + i * i);
		r *= h;
		i *= h;
		return (*this);
	}
	Complex exponential() const
	{
		const ddouble h = exp(r);
		return Complex(h * cos(i), h * sin(i));
	}

	ddouble r;
	ddouble i;
};

#endif //_COMPLEX_HPP_INCLUDED_
