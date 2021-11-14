#ifndef _TEXT_HPP_INCLUDED_
#define _TEXT_HPP_INCLUDED_

/*
  Text contains lines of strings
  and is able to load and save
*/

#include "../Types/Types.hpp"
#include <vector>
#include <string>
#include <sstream>

class Text : public std::stringstream
{
private:
  Text(const Text &rhs) { *this = rhs; }
  Text &operator = (const Text &rhs) { return *this; }

public:
  Text() {}
  virtual ~Text() {}

	void clear();

  // reads output from a text file
  bool load(const std::string &path);
  // saves output into a text file
  bool save(const std::string &path);

	// is there lines anymore
	bool hasLine();
	// get the next line
	const std::string getLine();

};

#endif //_TEXT_HPP_INCLUDED_
