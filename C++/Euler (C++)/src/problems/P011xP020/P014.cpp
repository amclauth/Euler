#include "../../base/problem.h"
#include <iostream>

#include <vector>

/**
 * P014<br>
 * The following iterative sequence is defined for the set of positive integers:
 * n -> n/2 (n is even)
 * n -> 3n + 1 (n is odd)
 * Using the rule above and starting with 13, we generate the following sequence:
 * 13  40  20  10  5  16  8  4  2  1
 * It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem),
 * it is thought that all starting numbers finish at 1.
 * Which starting number, under one million, produces the longest chain?
 * NOTE: Once the chain starts the terms are allowed to go above one million.
 * Ans: 837799
 */
class P014: public Problem
{
	public:
		P014()
		{
			problem_number = 14;
			variations = 2;
		}
		~P014()
		{
		}

		std::string execute(int variation)
		{
			switch (variation)
			{
				case 0:
					return to_string(bruteForce());
				case 1:
				case -1:
					return to_string(faster());
				default:
					return std::string("unavailable");
			}
			return NULL;
		}

	private:

		/**
		 *
		 */
		int bruteForce()
		{
			int longest = 0;
			int length = 0;
			for (int ii = 999999; ii >= 500000; ii -= 2)
			{ // anything below 500000 is already in this list because of n/2
				long num = ii;
				int chainlength = 0;

				while (num != 1)
				{
					if (num % 2 == 0)
					{
						num = num / 2;
					} else
					{
						num = 3 * num + 1;
					}
					chainlength++;
				}
				if (chainlength > length)
				{
					longest = ii;
					length = chainlength;
				}
			}
			return longest;
		}

		/**
		 * Set up a cache where we can look up previous numbers
		 */
		int faster()
		{
			int max = 1000000;
			int length = 0;
			int longest = 0;

			std::vector<int> cache;
			//Initialize cache
			for (int ii = 0; ii < max+1; ii++)
			{
				cache.push_back(-1);
			}
			cache.at(1) = 1;

			// anything under 500000 will show up in the list from n/2 finding it
			for (int ii = 2; ii <= max; ii++)
			{
				int n = getLength(cache, ii);
				cache.at(ii) = n;
				if (n > length)
				{
					length = n;
					longest = ii;
				}
			}
			return longest;
		}

		// tried storing intermediate results, but numbers went well beyond the int level for
		// n, blowing out the cache size, making searching a simple array very, very hard.
		int getLength(std::vector<int>& cache, long n)
		{
			if (n <= 1000000 && cache.at(n) > 0)
			return cache.at(n);

			if (n % 2 == 0)
			return getLength(cache, n/2) + 1;

			return getLength(cache, n*3+1) + 1;
		}
};
