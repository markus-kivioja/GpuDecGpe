#ifndef _PICTURE_HPP_INCLUDED_
#define _PICTURE_HPP_INCLUDED_

/*
  Picture is a 2D map of colors.
  Picture is able to load and save itself.
*/

#include "../Types/Buffer.hpp"
#include <string>

class Picture
{
private:
	Picture(const Picture &rhs) { *this = rhs; }
	Picture &operator = (const Picture &rhs) { return *this; }

public:
	Picture(const uint width = 1, const uint height = 1) { init(width, height); }
	virtual ~Picture() { clear(); }
	void init(const uint width, const uint height);
	void clear();

	void fillColor(const Vector4 &color);

	bool empty() const { return m_pixels.empty(); }
	uint size() const { return m_pixels.size(); }

	uint getWidth() const { return m_width; }
	uint getHeight() const { return m_height; }
	const Vector4 &getColor(const uint x, const uint y) const { return m_pixels[m_width * y + x]; }
	Vector4 *getPixels() { return &m_pixels[0]; }

	bool addPicture(const Picture &pic);
	void setColor(const uint x, const uint y, const Vector4 &color) { m_pixels[m_width * y + x] = color; }
	void addColor(const uint x, const uint y, const Vector4 &color) { m_pixels[m_width * y + x] += color; }
	void multiplyColor(const uint x, const uint y, const Vector4 &color);

	void translate(const Matrix4 &m);
	void square();
	void sqroot();
	Vector4 getSum() const;

	bool save(const std::string &file, const bool middle = true) const;
	bool load(const std::string &file, const bool middle = true);

protected:
	uint m_width; // picture width
	uint m_height; // picture height
	Buffer<Vector4> m_pixels; // pixels of the picture
};

#endif //_PICTURE_HPP_INCLUDED_
