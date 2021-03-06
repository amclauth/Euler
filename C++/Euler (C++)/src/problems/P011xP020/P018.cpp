#include "../../base/problem.h"
#include "../../util/io.h"

/**
 * P018<br>
 * By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
 * 3
 * 7 4
 * 2 4 6
 * 8 5 9 3
 * That is, 3 + 7 + 4 + 9 = 23.
 * Find the maximum total from top to bottom of the triangle below:
 * NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However,
 * Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
 * Ans: 1074
 */
class P018: public Problem
{
	public:
		P018()
		{
			problem_number = 18;
			variations = 2;
		}
		~P018()
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
		 * Like the direction choosing problem in problem 15
		 */
		int bruteForce()
		{
			std::vector<std::vector<int> > triangle;

			triangle.push_back(*io::readIntoArray("75", " "));
			triangle.push_back(*io::readIntoArray("95 64", " "));
			triangle.push_back(*io::readIntoArray("17 47 82", " "));
			triangle.push_back(*io::readIntoArray("18 35 87 10", " "));
			triangle.push_back(*io::readIntoArray("20 04 82 47 65", " "));
			triangle.push_back(*io::readIntoArray("19 01 23 75 03 34", " "));
			triangle.push_back(*io::readIntoArray("88 02 77 73 07 63 67", " "));
			triangle.push_back(*io::readIntoArray("99 65 04 28 06 16 70 92", " "));
			triangle.push_back(*io::readIntoArray("41 41 26 56 83 40 80 70 33", " "));
			triangle.push_back(*io::readIntoArray("41 48 72 33 47 32 37 16 94 29", " "));
			triangle.push_back(*io::readIntoArray("53 71 44 65 25 43 91 52 97 51 14", " "));
			triangle.push_back(*io::readIntoArray("70 11 33 28 77 73 17 78 39 68 17 57", " "));
			triangle.push_back(*io::readIntoArray("91 71 52 38 17 14 91 43 58 50 27 29 48", " "));
			triangle.push_back(*io::readIntoArray("63 66 04 68 89 53 67 30 73 16 69 87 40 31", " "));
			triangle.push_back(*io::readIntoArray("04 62 98 27 23 09 70 98 73 93 38 53 60 04 23", " "));

			return follow(triangle, 0, 0, 0);
		}

		int follow(std::vector<std::vector<int> >& triangle, unsigned int ii, unsigned int jj, int num)
		{
			if (ii == triangle.size())
			{
				return num; // done!
			}

			int n1 = triangle.at(ii).at(jj) + follow(triangle, ii + 1, jj, num);
			int n2 = triangle.at(ii).at(jj) + follow(triangle, ii + 1, jj + 1, num);
			return n1 > n2 ? n1 : n2;
		}

		/**
		 * recurse up the triangle. Take the highest of the two branch points at each bottom choice and save it in the row
		 * above, then those two to the row above that, etc. The total ends up in the top.
		 */
		long faster()
		{
			std::vector<std::vector<int> > triangle;

			triangle.push_back(*io::readIntoArray("75", " "));
			triangle.push_back(*io::readIntoArray("95 64", " "));
			triangle.push_back(*io::readIntoArray("17 47 82", " "));
			triangle.push_back(*io::readIntoArray("18 35 87 10", " "));
			triangle.push_back(*io::readIntoArray("20 04 82 47 65", " "));
			triangle.push_back(*io::readIntoArray("19 01 23 75 03 34", " "));
			triangle.push_back(*io::readIntoArray("88 02 77 73 07 63 67", " "));
			triangle.push_back(*io::readIntoArray("99 65 04 28 06 16 70 92", " "));
			triangle.push_back(*io::readIntoArray("41 41 26 56 83 40 80 70 33", " "));
			triangle.push_back(*io::readIntoArray("41 48 72 33 47 32 37 16 94 29", " "));
			triangle.push_back(*io::readIntoArray("53 71 44 65 25 43 91 52 97 51 14", " "));
			triangle.push_back(*io::readIntoArray("70 11 33 28 77 73 17 78 39 68 17 57", " "));
			triangle.push_back(*io::readIntoArray("91 71 52 38 17 14 91 43 58 50 27 29 48", " "));
			triangle.push_back(*io::readIntoArray("63 66 04 68 89 53 67 30 73 16 69 87 40 31", " "));
			triangle.push_back(*io::readIntoArray("04 62 98 27 23 09 70 98 73 93 38 53 60 04 23", " "));

			for (int ii = triangle.size() - 1; ii > 0; ii--)
			{
				for (unsigned int jj = 0; jj < triangle[ii - 1].size(); jj++)
				{
					triangle.at(ii - 1).at(jj) =
							triangle.at(ii).at(jj) > triangle.at(ii).at(jj + 1) ?
									triangle.at(ii - 1).at(jj) + triangle.at(ii).at(jj) :
									triangle.at(ii - 1).at(jj) + triangle.at(ii).at(jj + 1);
				}
			}

			return triangle.at(0).at(0);
		}
};
