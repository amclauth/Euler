#include "../../base/problem.h"

/**
 * P015<br>
 * Starting in the top left corner of a 22 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.<br>
 * How many such routes are there through a 2020 grid?<br>
 * Ans: 137846528820
 */
class P015: public Problem
{
	public:
		P015()
		{
			problem_number = 15;
			variations = 3;
		}
		~P015()
		{
		}

		std::string execute(int variation)
		{
			switch (variation)
			{
				case 0:
					return to_string(bruteForce());
				case 1:
					return to_string(pascals());
				case 2:
				case -1:
					return to_string(factorial());
				default:
					return std::string("unavailable");
			}
			return NULL;
		}

	private:

		/**
		 * This is literally Pascal's triangle, so let's follow it explicitly. Easiest to think of it
		 * in an array of
		 * 1 1 1
		 * 1 . .
		 * 1 . . (as the example)
		 *
		 * But I don't want to have to rotate that, so instead, I'll make a grid like:
		 *     1            1            1            1            1
		 *   . . .        1 1 1        1 1 1        1 1 1        1 1 1
		 * . . . . . -> . . . . . -> 1 2 3 2 1 -> 1 2 3 2 1 -> 1 2 3 2 1
		 *   . . .        . . .        . . .        6 7 6        6 7 6
		 *     .            .            .            .           19
		 * This is 3*2-1 in size
		 */
		long pascals()
		{
			int width = 21; // because normally 1 indexed
			int size = width * 2 - 1; // grid size
			long grid[size][size];

			// set up the boundary conditions
			for (int ii = 0; ii < size; ii++)
			{
				for (int jj = 0; jj < size; jj++)
				{
					grid[ii][jj] = 0L;
				}
			}
			for (int ii = 0; ii < width; ii++)
			{
				// middle is at column width-1
				grid[ii][width - 1 + ii] = 1L;
				grid[ii][width - 1 - ii] = 1L;
			}

			// with boundary conditions and checking for existing data, we can run the whole square
			for (int ii = 1; ii < size; ii++)
			{
				for (int jj = 1; jj < size - 1; jj++)
				{
					long left = grid[ii - 1][jj - 1];
					long right = grid[ii - 1][jj + 1];
					if (left > 0 && right > 0)
					{
						grid[ii][jj] = left + right;
					}
				}
			}
			return grid[size - 1][width - 1];
		}

		// takes a /long/ time ... about 35 minutes per run!
		long bruteForce()
		{
			return follow(20, 20, 0, 0, 0);
		}

		long follow(int height, int width, int x, int y, long num)
		{
			// this assumes possible paths are only right or down
			if ((x == width) && (y == height))
			{
				return num + 1;
			}
			if (x < width)
			{
				num = follow(height, width, x + 1, y, num);
			}
			if (y < height)
			{
				num = follow(height, width, x, y + 1, num);
			}
			return num;
		}

		/**
		 * Using Combinatorics. we want n choose k, which ends up (in this case) being
		 * ((2n)!)/(n!)^2 since paths are always 2n in length and we have up to n of any
		 * direction in them.
		 * @return
		 */
		long factorial()
		{
			int size = 20;
			long num = 1L;

			for (int ii = 0; ii < size; ii++)
			{
				num *= (2 * size) - ii;
				num /= ii + 1;
			}
			return num;
		}
};
