#ifndef __IO_HELPER_H__
#define __IO_HELPER_H__

#include <vector>
#include <string>
#include <set>

namespace io
{
	// read a string into an array chars
	void readIntoCharArray(char* array, std::string str, std::string sep, int l);

	// read a file into a string
	std::string readFile(std::string filename);
}

#endif
