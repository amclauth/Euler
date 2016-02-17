#include <iostream>
#include <string>

#include "../util/io.h"
#include "test.h"

class TestIO: public test
{
	public:

		void run()
		{
			test_readIntoArray();
			if (passed)
			{
				std::cout << "IO Test:: SUCCESS! All tests passed." << std::endl;
			}
			else
			{
				std::cout << "IO Test:: !!!FAILURE!!! Tests failed." << std::endl;
			}
		}

	private:

		void test_readIntoArray()
		{
			std::vector<int>* array;

			array = io::readIntoArray("", " ");
			assertEquals((size_t) 0, array->size(), __func__, "array 0");

			array = io::readIntoArray("10", " ");
			assertEquals((size_t) 1, array->size(), __func__, "array 1");
			assertEquals(10, array->at(0), __func__, "array 1");

			array = io::readIntoArray("10 1111 12 13 4 15", " ");
			assertEquals((size_t) 6, array->size(), __func__, "array 2");
			assertEquals(10, array->at(0), __func__, "array 2");
			assertEquals(1111, array->at(1), __func__, "array 2");
			assertEquals(12, array->at(2), __func__, "array 2");
			assertEquals(13, array->at(3), __func__, "array 2");
			assertEquals(4, array->at(4), __func__, "array 2");
			assertEquals(15, array->at(5), __func__, "array 2");

			array = io::readIntoArray("10, 1111, 12, 13, 4, 15", ", ");
			assertEquals((size_t) 6, array->size(), __func__, "array 3");
			assertEquals(10, array->at(0), __func__, "array 3");
			assertEquals(1111, array->at(1), __func__, "array 3");
			assertEquals(12, array->at(2), __func__, "array 3");
			assertEquals(13, array->at(3), __func__, "array 3");
			assertEquals(4, array->at(4), __func__, "array 3");
			assertEquals(15, array->at(5), __func__, "array 3");

			array = io::readIntoArray("102", "");
			assertEquals((size_t) 3, array->size(), __func__, "array 4");
			assertEquals(1, array->at(0), __func__, "array 4");
			assertEquals(0, array->at(1), __func__, "array 4");
			assertEquals(2, array->at(2), __func__, "array 4");
		}
};
