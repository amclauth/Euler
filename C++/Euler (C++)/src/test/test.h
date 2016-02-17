/*
 * test.h
 *
 *  Created on: Nov 19, 2013
 *      Author: andymac
 */

#ifndef TEST_H_
#define TEST_H_

#include <iostream>
#include <sstream>
#include <string>

class test
{
	public:
		test();
		virtual ~test();

		virtual void run() = 0;

	protected:
		bool passed;
		template<typename T>
		std::string to_string(T value)
		{
			std::ostringstream os;
			os << value;
			return os.str();
		}

		/**
		 * Assert that a and b are equal. Uses == operator and types must be the same.
		 * @param a expected value
		 * @param b given value
		 * @param func function name
		 * @param opt optional argument (for identification)
		 */
		template<class T>
		bool assertEquals(T a, T b, std::string func, std::string opt = "")
		{
			if (a != b)
			{
				std::cout << "ERROR ::: Expected \"" << a << "\", but received \""
						<< b << "\" in function " << func << ". " << opt;
				std::cout << std::endl;
				passed = false;
			}
			return a == b;
		}

		/**
		 * Assert that a is true
		 * @param a given value
		 * @param func function name
		 * @param opt optional argument (for identification)
		 */
		bool assertTrue(bool a, std::string func, std::string opt = "")
		{
			if (!a)
			{
				std::cout << "ERROR ::: assert is false in function " << func << ". " << opt;
				std::cout << std::endl;
				passed = false;
			}
			return a;
		}

		/**
		 * Assert that a is false
		 * @param a given value
		 * @param func function name
		 * @param opt optional argument (for identification)
		 */
		bool assertFalse(bool a, std::string func, std::string opt = "")
		{
			if (a)
				{
					std::cout << "ERROR ::: assert is true in function " << func << ". " << opt;
					std::cout << std::endl;
					passed = false;
				}
				return !a;
		}
};

#endif /* TEST_H_ */
