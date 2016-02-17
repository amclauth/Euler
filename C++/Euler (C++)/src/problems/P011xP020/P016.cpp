#include "../../base/problem.h"

#include <vector>

/**
 * P016<br>
 * 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
 * What is the sum of the digits of the number 2^1000?
 * Ans: 1366
 */
class P016: public Problem
{
	public:
		P016()
		{
			problem_number = 16;
			variations = 3;
		}
		~P016()
		{
		}

		std::string execute(int variation)
		{
			switch (variation)
			{
				case 0:
					return to_string(bruteForce());
				case 1:
					return "-1";
				case 2:
				case -1:
					return to_string(faster());
				default:
					return std::string("unavailable");
			}
			return NULL;
		}

	private:

		/**
		 * Actually multiply it out into an array
		 */
		int bruteForce()
		{
			int arr_size = 400;
			int array[arr_size];
			for (int ii = 0; ii < arr_size; ii++)
			{
				array[ii] = 0;
			}
			array[0] = 1;

			for (int ii = 0; ii < 1000; ii++)
			{
				int carry = 0;
				for (int jj = 0; jj < arr_size; jj++)
				{
					int n = array[jj] * 2 + carry;
					if (n > 9)
					{
						array[jj] = n % 10;
						carry = n / 10;
					}
					else
					{
						array[jj] = n;
						carry = 0;
					}
				}
			}
			int total = 0;
			for (int ii = 0; ii < arr_size; ii++)
			{
				total += array[ii];
			}
			return total;
		}

		/**
		 * Use a vector to allocate space and do multiplications only as needed
		 */
		int faster()
		{
			std::vector<int> array;
			array.push_back(1); // 2^0
			for (int ii = 1; ii <= 1000; ii++)
			{
				int carry = 0;
				for (unsigned int jj = 0; jj < array.size(); jj++)
				{
					int n = array.at(jj) * 2 + carry;
					if (n > 9)
					{
						array.at(jj) = n % 10;
						carry = n / 10;
					}
					else
					{
						array.at(jj) = n;
						carry = 0;
					}
				}
				if (carry > 0)
					array.push_back(carry);
			}
			int total = 0;
			for (unsigned int ii = 0; ii < array.size(); ii++)
			{
				total += array.at(ii);
			}
			return total;
		}
};
