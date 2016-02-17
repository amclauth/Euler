#include <iostream>
#include <string>

#include "../util/basic.h"
#include "test.h"

class TestBasic: public test
{
	public:

		void run()
		{
			test_reduction_string();
			if (passed)
			{
				std::cout << "SUCCESS! All tests passed." << std::endl;
			} else {
				std::cout << "!!!FAILURE!!! Tests failed." << std::endl;
			}
		}

	private:

		void test_reduction_string()
		{
			const char * program = basic::reduction(std::string("header").c_str(),
					std::string("value").c_str(),
					std::string("operand").c_str());
			assertEquals('h',program[0],__func__);
			assertNotEquals('1',program[0],__func__);
			assertEquals('e',program[1],__func__);
			assertEquals('a',program[2],__func__);
			assertEquals('d',program[3],__func__);
			assertEquals('e',program[4],__func__);
			assertEquals('r',program[5],__func__);
			assertEquals('\n',program[6],__func__);
			assertEquals('_',program[7],__func__);
		}
};
