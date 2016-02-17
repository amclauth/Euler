#include "io.h"

#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace io
{
	/**
	 * Reads a string into an array using the separator
	 * @param array
	 * @param str
	 * @param sep
	 * @param l - the length of the individual pieces
	 * @return
	 */
	void readIntoCharArray(char* array, std::string str, std::string sep, int l)
	{
		uint c_idx = 0;
		uint s_idx = 0;
		uint next = str.find(sep,s_idx);
		while (next != (uint)std::string::npos)
		{
			int wordSize = next - s_idx;
			if (wordSize > l)
			{
				std::cout << "***ERROR ... word size of " << wordSize << "/" << l << " found." << std::endl;
				return;
			}
//			for (uint ii = 0; ii < l - (next-s_idx); ii++)
//			{
//				array[c_idx++] = ' ';
//			}
			while (s_idx < next)
			{
				array[c_idx++] = str[s_idx++];
			}
			for (int ii = wordSize; ii < l; ii++)
			{
				array[c_idx++] = ' ';
			}
			s_idx += sep.length(); // skip the separator
			next = str.find(sep,s_idx);
		}
		// get the last one
		while (s_idx < (uint)str.length())
		{
			array[c_idx++] = str[s_idx++];
		}
		for (int ii = c_idx; ii % l != 0; ii++)
			array[c_idx++] = ' ';
	}

	/**
	 * Read a file into a string
	 */
	std::string readFile(std::string filename)
	{
	   const char* file = filename.c_str();
		std::ifstream t(file, std::ifstream::in);
		std::stringstream buffer;
		buffer << t.rdbuf();
		return buffer.str();
	}
}
