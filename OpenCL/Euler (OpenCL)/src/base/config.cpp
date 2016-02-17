#ifndef __CONFIG_H__
#include "config.h"
#endif

#include <iostream> // for istringstream, cout
#include <fstream>  // for ifstream
#include <sstream>  // for getline
#include <cstdlib>  // for exit

Config::Config()
{
	if (!readConfig())
	{
		std::cout << "ERROR :: Could not open " << CONFIGFILE << std::endl;
		std::exit(0);
	}
	answers = new Answers(answerFile);
	if (!answers->readFile())
	{
		std::cout << "ERROR :: Could not generate answers file." << std::endl;
		std::exit(0);
	}
}

bool Config::readConfig()
{
	std::ifstream file(CONFIGFILE);
	if (!file)
	{
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	file.close();

	std::string line;
	int setVals = 0;

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
				values[key] = value;
				if (key == std::string("answerfile"))
				{
					answerFile = value;
					setVals++;
				}
				else if (key == std::string("loglvl"))
				{
					const char *s = value.c_str();
					char *t;
					long l = strtol(s, &t, 10);
					if (s != t) {
						loglvl = l;
						setVals++;
					} else {
						std::cout << "ERROR :: Could not set loglevel from " << value << std::endl;
						std::exit(0);
					}
				}
				else if (key == std::string("onlyfastest"))
				{
					const char *s = value.c_str();
					char *t;
					long l = strtol(s, &t, 10);
					if (s != t) {
						onlyfastest = l == 1;
						setVals++;
					} else {
						std::cout << "ERROR :: Could not set onlyfastest from " << value << std::endl;
						std::exit(0);
					}
				}
			}
		}
	}

	// make sure we have a config file and answers file
	if (setVals < 3)
	{
		std::cout << "ERROR :: Did not get one of answerfile, loglvl, onlyfastest" << std::endl;
		std::exit(0);
	}
	return true;
}

std::string Config::getValue(std::string key)
{
	std::map<std::string,std::string>::iterator itr = values.find(key);
	if (itr != values.end())
		return itr->second;
	return NULL;
}
