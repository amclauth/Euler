#ifndef __IO_HELPER_H__
#define __IO_HELPER_H__

#include <vector>
#include <string>
#include <set>

namespace io
{
	// read a string into a vector of ints
	std::vector<int>* readIntoArray(std::string nums, std::string sep);

	// read a string into a set of ints (sorted)
	std::set<int>* readIntoSet(std::string nums, std::string sep);

	// read a string into a vector of string
	std::vector<std::string>* readIntoStringArray(std::string nums, std::string sep);

	// read a string into a set of string (sorted)
	std::set<std::string>* readIntoStringSet(std::string nums, std::string sep);

	// read a file into a string
	std::string readFile(std::string filename);
}

#endif
