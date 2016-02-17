// answers to problems

#ifndef __ANSWERS_H__
#include "answers.h"
#endif

#include <iostream> // for istringstream
#include <fstream>  // for ifstream
#include <sstream>  // for getline
#include <cstdlib>   // for strtol

Answers::Answers(std::string filename)
{
	this->filename = filename;
}

std::string Answers::getAnswer(int problem_number)
{
	std::map<int,std::string>::iterator itr = answers.find(problem_number);
	if (itr != answers.end())
		return itr->second;
	return "";
}

bool Answers::readFile()
{
	std::ifstream file(filename.c_str());
	if (!file)
	{
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	file.close();

	std::string line;
	// we should get them in order
	int num = 1;

	while (std::getline(fileStream, line))
	{
		std::istringstream lineStream(line);
		std::string key;
		if (std::getline(lineStream,key,'='))
		{
			std::string value;
			if (std::getline(lineStream,value))
			{
				// have key and value
				const char *s = key.c_str();
				char *t;
				long l = std::strtol(s, &t, 10);
				if (s != t) {
					answers[l] = value;
					if (l != num++)
					{
						std::cout << "Got answer " << l << " instead of " << (num -1) << std::endl;
						return false;
					}
				}
			}
		}
	}
	return true;
}
