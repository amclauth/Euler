#ifndef __ANSWERS_H__
#define __ANSWERS_H__

#include <vector>
#include <string>
#include <map>

class Answers
{
	private:
		std::map<int,std::string> answers;
		std::string filename;

	public:
		Answers(std::string filename);
		bool readFile();
		std::string getAnswer(int problem_number);
};

#endif
