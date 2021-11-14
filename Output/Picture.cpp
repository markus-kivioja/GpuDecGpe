#include "Picture.hpp"
#include <fstream>
#include <iostream>

void Picture::init(const uint width, const uint height)
{
	clear();
	m_width = width;
	m_height = height;
	m_pixels.resize(m_width * m_height);
	fillColor(Vector4(0,0,0,0));
}

void Picture::clear()
{
	m_width = 0;
	m_height = 0;
	m_pixels.clear();
}

void Picture::fillColor(const Vector4 &color)
{
	for(uint i=0; i<m_pixels.size(); i++) m_pixels[i] = color;
}

bool Picture::addPicture(const Picture &pic)
{
	if(m_pixels.size() != pic.m_pixels.size()) return false;
	for(uint i=0; i<m_pixels.size(); i++) m_pixels[i] += pic.m_pixels[i];
	return true;
}

void Picture::multiplyColor(const uint x, const uint y, const Vector4 &color)
{
  Vector4 &pixel = m_pixels[m_width * y + x];
  pixel.x *= color.x;
  pixel.y *= color.y;
  pixel.z *= color.z;
  pixel.t *= color.t;
}

void Picture::translate(const Matrix4 &m)
{
	for(uint i=0; i<m_pixels.size(); i++)
	{
		m_pixels[i] = m_pixels[i] * m;
	}
}

void Picture::square()
{
	for(uint i=0; i<m_pixels.size(); i++)
	{
		m_pixels[i].x = m_pixels[i].x * m_pixels[i].x;
		m_pixels[i].y = m_pixels[i].y * m_pixels[i].y;
		m_pixels[i].z = m_pixels[i].z * m_pixels[i].z;
	}
}

void Picture::sqroot()
{
	for(uint i=0; i<m_pixels.size(); i++)
	{
		m_pixels[i].x = sqrt(m_pixels[i].x);
		m_pixels[i].y = sqrt(m_pixels[i].y);
		m_pixels[i].z = sqrt(m_pixels[i].z);
	}
}

Vector4 Picture::getSum() const
{
	Vector4 sum(0,0,0,0);
	for(uint i=0; i<m_pixels.size(); i++)
	{
		sum += m_pixels[i];
	}
	return sum;
}


bool Picture::save(const std::string &file, const bool middle) const
{
	// save bmp file
	std::ofstream fs(file.c_str(), std::ios_base::binary | std::ios::trunc);
	if(fs.fail()) return false;

	const char *id = "BM";
	fs.write(id, 2);

	// File header
	uint offs = 14 + 40,
	   data = 4 * m_pixels.size(),
	   size = offs + data;
	fs.write((char*)&size, 4);
	uint zero = 0;
	fs.write((char*)&zero, 4);
	fs.write((char*)&offs, 4);

	// Info header
	uint header = 40;
	fs.write((char*)&header, 4);
	fs.write((char*)&m_width, 4);
	fs.write((char*)&m_height, 4);
	ushort one = 1;
	fs.write((char*)&one, 2);
	ushort bits = 24;
	fs.write((char*)&bits, 2);
	fs.write((char*)&zero, 4);
	fs.write((char*)&data, 4);
	fs.write((char*)&zero, 4);
	fs.write((char*)&zero, 4);
	fs.write((char*)&zero, 4);
	fs.write((char*)&zero, 4);

	// Data
	uint x, y, i;

	const uint rowend = 3 - ((3 * m_width + 3) % 4);
	for(y=0,i=0; y<m_height; y++)
	{
		for(x=0; x<m_width; x++,i++)
		{
		  const Vector3 col = (middle ? 128.0 * m_pixels[i].toVector3() + Vector3(128.0, 128.0, 128.0) : 256.0 * m_pixels[i].toVector3());
		  uchar red = (col.x < 1 ? 0 : (col.x > 255 ? 255 : char(col.x))),
			   green = (col.y < 1 ? 0 : (col.y > 255 ? 255 : char(col.y))),
			   blue = (col.z < 1 ? 0 : (col.z > 255 ? 255 : char(col.z)));

		  fs.write((char*)&blue, 1);
		  fs.write((char*)&green, 1);
		  fs.write((char*)&red, 1);
		}
		if(rowend > 0) fs.write((char*)&zero, rowend);
	}
	fs.close();

	return true;
}

bool Picture::load(const std::string &file, const bool middle)
{
	// load bmp file
	std::ifstream fs(file.c_str(), std::ios::binary | std::ios::in);
	if(fs.fail()) return false;

	char id[2];
	fs.read(id, 2);
	if(strncmp(id, "BM", 2) != 0)
	{
		fs.close();
		return false;
	}

	// File header
	uint offs, size, zero;
	fs.read((char*)&size, 4);
	fs.read((char*)&zero, 4);
	fs.read((char*)&offs, 4);

	// Info header
	uint header;
	fs.read((char*)&header, 4);
	fs.read((char*)&m_width, 4);
	fs.read((char*)&m_height, 4);
	ushort one;
	fs.read((char*)&one, 2);
	ushort bits;
	fs.read((char*)&bits, 2);
	for(uint i=16; i<header; i+=4) fs.read((char*)&zero, 4);

	m_pixels.resize(m_width * m_height);

	uint x, y, i;

	const uint rowend = 3 - ((3 * m_width + 3) % 4);
	uchar nil, red, green, blue;
	for(y=0,i=0; y<m_height; y++)
	{
		for(x=0; x<m_width; x++,i++)
		{
		  fs.read((char*)&blue, 1);
		  fs.read((char*)&green, 1);
		  fs.read((char*)&red, 1);
		  if(bits > 24) fs.read((char*)&nil, 1);
		  if(middle) m_pixels[i] = Vector4(ddouble(red) / 128.0 - 1.0, ddouble(green) / 128.0 - 1.0, ddouble(blue) / 128.0 - 1.0, 0.0);
		  else m_pixels[i] = Vector4(ddouble(red) / 256.0, ddouble(green) / 256.0, ddouble(blue) / 256.0, 0.0);
		  //std::cout << ddouble(red) << " " << ddouble(green) << " " << ddouble(blue) << std::endl;
		}
		if(rowend > 0) fs.read((char*)&zero, rowend);
	}
	fs.close();

	return true;
}
