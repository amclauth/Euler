#include <iostream>
#include <string>
#include <stdlib.h>

#include "../util/basic.h"
#include "test.h"

class TestBasic: public test
{
	public:

		void run()
		{
			test_n_sum();
			test_fibonacci();
			test_factors();
			test_reverse();
			test_palindrome();
			test_getDivisors();
			test_triangle();
			test_factorial();
			test_amicable();
			test_pandigital();
			test_reduce();
			if (passed)
			{
				std::cout << "BasicTest:: SUCCESS! All tests passed." << std::endl;
			}
			else
			{
				std::cout << "BasicTest:: !!!FAILURE!!! Tests failed." << std::endl;
			}
		}

	private:

		void test_n_sum()
		{
			int sum = 0;
			for (int ii = 0; ii < 100; ii++)
			{
				sum += ii;
				assertEquals(sum, basic::n_sum(ii), __func__, ii + "");
			}
		}

		void test_fibonacci()
		{
			// 0,1,1,2,3,5,8,...
			int a = 0;
			int b = 1;
			int fib = b;
			assertEquals(0, basic::fibonacci(0), __func__, "0 value");
			assertEquals(1, basic::fibonacci(1), __func__, "1 value");
			for (int ii = 2; ii < 20; ii++)
			{
				assertEquals(fib, basic::fibonacci(ii), __func__, ii + "");
				a = b;
				b = fib;
				fib = a + b;
			}
		}

		void test_factors()
		{
			long n = 60;
			// factors: 2,2,3,5
			// divisors: 1,2,3,4,5,6,10,12,15,20,30,60
			std::vector<long>* factors = basic::factors(n);
			assertEquals(2L, factors->at(0), __func__, "2");
			assertEquals(2L, factors->at(1), __func__, "2_2");
			assertEquals(3L, factors->at(2), __func__, "3");
			assertEquals(5L, factors->at(3), __func__, "5");
			assertEquals((std::vector<long>::size_type) 4, factors->size(), __func__, "size");

			assertEquals(12L, basic::getNumberOfDivisorsFromFactors(factors), __func__, "num");
			assertEquals(168L, basic::getSumOfDivisorsFromFactors(factors), __func__, "sum");
		}

		void test_reverse()
		{
			int ni[] = { 0, 1, 10, 15, 101, 123, 93487 };
			int ri[] = { 0, 1, 1, 51, 101, 321, 78439 };
			for (int ii = 0; ii < 7; ii++)
			{
				assertEquals(ri[ii], basic::reverse(ni[ii]), __func__, "reverse int");
			}

			long nl[] = { 0, 1, 10, 15, 101, 123, 93487 };
			long rl[] = { 0, 1, 1, 51, 101, 321, 78439 };
			for (int ii = 0; ii < 7; ii++)
			{
				assertEquals(rl[ii], basic::reverse(nl[ii]), __func__, "reverse long");
			}

			std::string reversible = "reversible";
			std::string elbisrever = basic::reverse(reversible);
			assertEquals(std::string("reversible"), reversible, __func__, "reverse string immutable");
			assertEquals(std::string("elbisrever"), elbisrever, __func__, "reversed string");
		}

		void test_palindrome()
		{
			assertTrue(basic::isPalindrome(991199), __func__, "1");
			assertTrue(basic::isPalindrome(999), __func__, "2");
			assertTrue(basic::isPalindrome(1), __func__, "3");
			assertFalse(basic::isPalindrome(9911), __func__, "4");
			assertFalse(basic::isPalindrome(10), __func__, "5");

			assertTrue(basic::isPalindrome(991199L), __func__, "6");
			assertTrue(basic::isPalindrome(999L), __func__, "7");
			assertTrue(basic::isPalindrome(1L), __func__, "8");
			assertFalse(basic::isPalindrome(9911L), __func__, "9");
			assertFalse(basic::isPalindrome(10L), __func__, "10");

			assertTrue(basic::isPalindrome("991199"), __func__, "11");
         assertTrue(basic::isPalindrome("999"), __func__, "12");
         assertTrue(basic::isPalindrome("1"), __func__, "13");
         assertFalse(basic::isPalindrome("9911"), __func__, "14");
         assertFalse(basic::isPalindrome("10"), __func__, "15");
		}

		void test_getDivisors()
		{
			std::vector<long>* divisors;
			divisors = basic::getDivisors(1);
			assertTrue(1 == divisors->size(), __func__, "1 size");
			assertEquals((long) 1, divisors->at(0), __func__, "1 element 0");

			divisors = basic::getDivisors(30);
			assertTrue(8 == divisors->size(), __func__, "30 size");
			assertEquals((long) 1, divisors->at(0), __func__, "element 0");
			assertEquals((long) 2, divisors->at(1), __func__, "element 1");
			assertEquals((long) 3, divisors->at(2), __func__, "element 2");
			assertEquals((long) 5, divisors->at(3), __func__, "element 3");
			assertEquals((long) 6, divisors->at(4), __func__, "element 4");
			assertEquals((long) 10, divisors->at(5), __func__, "element 5");
			assertEquals((long) 15, divisors->at(6), __func__, "element 6");
			assertEquals((long) 30, divisors->at(7), __func__, "element 7");

			divisors = basic::getDivisors(25);
			assertTrue(3 == divisors->size(), __func__, "25 size");
			assertEquals((long) 1, divisors->at(0), __func__, "element 0");
			assertEquals((long) 5, divisors->at(1), __func__, "element 1");
			assertEquals((long) 25, divisors->at(2), __func__, "element 2");
		}

		void test_triangle()
		{
			long triangle = 0;
			for (int ii = 1; ii < 10; ii++)
			{
				triangle += ii;
				assertEquals(triangle, basic::getTriangle(ii), __func__, "triangle " + to_string(ii));
			}
		}


      void test_factorial()
      {
         long fac = 1;
         for (int ii = 1; ii < 20; ii++)
         {
            fac *= ii;
            assertEquals(fac, basic::factorial(ii), __func__, "factorial " + to_string(ii));
         }
      }

      void test_amicable()
      {
         assertEquals(220, basic::getAmicableNumber(284), __func__, "284");
         assertEquals(284, basic::getAmicableNumber(220), __func__, "220");
         assertEquals(-1, basic::getAmicableNumber(8), __func__, "8"); // divisors are 1,2,4 ... 7 is 1
         assertEquals(-1, basic::getAmicableNumber(6), __func__, "6"); // divisors are 1,2,3 == 6
      }

      void test_pandigital()
      {
         int one[] = {1,2,3,4,5,6,7,8,9};
         int two[] = {978635412};
         int three[] = {98765,4321};
         int four[] = {1,1,2,3,4,5,6,7,8,9};
         int five[] = {97863,54120};
         int six[] = {98765,431};
         assertTrue(basic::isPandigital(one,9), __func__, "int array 1");
         assertTrue(basic::isPandigital(two,1), __func__, "int array 2");
         assertTrue(basic::isPandigital(three,2), __func__, "int array 3");
         assertFalse(basic::isPandigital(four,10), __func__, "int array 1");
         assertFalse(basic::isPandigital(five,2), __func__, "int array 2");
         assertFalse(basic::isPandigital(six,2), __func__, "int array 3");

         assertTrue(basic::isPandigital("123465789"), __func__, "string array 1");
         assertTrue(basic::isPandigital("978645321"), __func__, "string array 1");
         assertFalse(basic::isPandigital("123346789"), __func__, "string array 1");
         assertFalse(basic::isPandigital("1230465789"), __func__, "string array 1");
      }

      void test_reduce()
      {
         assertEquals(5, basic::reduce(10,15), __func__, "reduce 10,15");
         assertEquals(1, basic::reduce(10,13), __func__, "reduce 10,13");
      }
};
