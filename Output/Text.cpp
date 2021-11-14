#include "Text.hpp"
#include <fstream>
#include <cstdlib>

static const uint MAXLINEWIDTH = 4096;

void Text::clear()
{
	str("");
}

bool Text::load(const std::string &path)
{
  clear();

  std::ifstream fs(path.c_str(), std::ios::in);
  if(fs.fail() != 0) return false;

	// get size of the file
	fs.seekg(0, std::ios::end);
	const uint size = fs.tellg();
	fs.seekg(0, std::ios::beg);

  // read the content of *this
	char *buffer = new char[size];
	fs.read(buffer, size);

  // write the content to the file stream
	write(buffer, size);
	delete[] buffer;

	// close the file and exit
	fs.close();
	return true;
}

bool Text::save(const std::string &path)
{
  std::ofstream fs(path.c_str(), std::ios_base::trunc);
  if(fs.fail() != 0) return false;

	// get size of *this
	seekg(0, std::ios::end);
	const uint size = tellg();
	seekg(0, std::ios::beg);

  // read the content of *this
	char *buffer = new char[size];
	read(buffer, size);

  // write the content to the file stream
	fs.write(buffer, size);
	delete[] buffer;

	// close the file and exit
	fs.close();
  return true;
}

bool Text::hasLine()
{
	if(eof())
	{
		clear();
		return false;
	}
	return true;
}

const std::string Text::getLine()
{
	char str[MAXLINEWIDTH];
	getline(str, MAXLINEWIDTH);
	return str;
}
