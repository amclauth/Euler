package problems.P001xP050;

import util.IO;
import base.Problem;

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
 * @return
 */
public class P018 extends Problem
{	
	public P018()
	{
		problemNumber = 18;
		variations = 2; 
	}

	@Override
	protected String execute(int variation)
	{
		switch (variation)
		{
		case 0:
			return bruteForce() + "";
		case 1:
		case -1:
			return faster() + "";
		}
		return null;
	}

	/**
	 * Like the direction choosing problem in problem 15
	 * @return
	 */
	private int bruteForce()
	{
		int[][] triangle = new int[15][15];
		
		int ii = 0;
		triangle[ii++] = IO.readIntoArray("75", " ");
		triangle[ii++] = IO.readIntoArray("95 64", " ");
		triangle[ii++] = IO.readIntoArray("17 47 82", " ");
		triangle[ii++] = IO.readIntoArray("18 35 87 10", " ");
		triangle[ii++] = IO.readIntoArray("20 04 82 47 65", " ");
		triangle[ii++] = IO.readIntoArray("19 01 23 75 03 34", " ");
		triangle[ii++] = IO.readIntoArray("88 02 77 73 07 63 67", " ");
		triangle[ii++] = IO.readIntoArray("99 65 04 28 06 16 70 92", " ");
		triangle[ii++] = IO.readIntoArray("41 41 26 56 83 40 80 70 33", " ");
		triangle[ii++] = IO.readIntoArray("41 48 72 33 47 32 37 16 94 29", " ");
		triangle[ii++] = IO.readIntoArray("53 71 44 65 25 43 91 52 97 51 14", " ");
		triangle[ii++] = IO.readIntoArray("70 11 33 28 77 73 17 78 39 68 17 57", " ");
		triangle[ii++] = IO.readIntoArray("91 71 52 38 17 14 91 43 58 50 27 29 48", " ");
		triangle[ii++] = IO.readIntoArray("63 66 04 68 89 53 67 30 73 16 69 87 40 31", " ");
		triangle[ii++] = IO.readIntoArray("04 62 98 27 23 09 70 98 73 93 38 53 60 04 23", " ");
		
		return follow(triangle, 0, 0, 0);
	}
	
	private int follow(int[][] triangle, int ii, int jj, int num)
	{
		if (ii == triangle.length)
		{
			return num; // done!
		}
		
		int n1 = triangle[ii][jj] + follow(triangle, ii+1, jj, num);
		int n2 = triangle[ii][jj] + follow(triangle, ii+1, jj+1, num);
		return n1 > n2 ? n1 : n2;
	}
	
	/**
	 * recurse up the triangle. Take the highest of the two branch points at each bottom choice and save it in the row 
	 * above, then those two to the row above that, etc. The total ends up in the top.
	 * @return
	 */
	private long faster()
	{
		int[][] triangle = new int[15][15];
		
		int ii = 0;
		triangle[ii++] = IO.readIntoArray("75", " ");
		triangle[ii++] = IO.readIntoArray("95 64", " ");
		triangle[ii++] = IO.readIntoArray("17 47 82", " ");
		triangle[ii++] = IO.readIntoArray("18 35 87 10", " ");
		triangle[ii++] = IO.readIntoArray("20 04 82 47 65", " ");
		triangle[ii++] = IO.readIntoArray("19 01 23 75 03 34", " ");
		triangle[ii++] = IO.readIntoArray("88 02 77 73 07 63 67", " ");
		triangle[ii++] = IO.readIntoArray("99 65 04 28 06 16 70 92", " ");
		triangle[ii++] = IO.readIntoArray("41 41 26 56 83 40 80 70 33", " ");
		triangle[ii++] = IO.readIntoArray("41 48 72 33 47 32 37 16 94 29", " ");
		triangle[ii++] = IO.readIntoArray("53 71 44 65 25 43 91 52 97 51 14", " ");
		triangle[ii++] = IO.readIntoArray("70 11 33 28 77 73 17 78 39 68 17 57", " ");
		triangle[ii++] = IO.readIntoArray("91 71 52 38 17 14 91 43 58 50 27 29 48", " ");
		triangle[ii++] = IO.readIntoArray("63 66 04 68 89 53 67 30 73 16 69 87 40 31", " ");
		triangle[ii++] = IO.readIntoArray("04 62 98 27 23 09 70 98 73 93 38 53 60 04 23", " ");
		
		for (ii = triangle.length - 1; ii > 0; ii--) {
			for (int jj = 0; jj < triangle[ii-1].length; jj++) {
				triangle[ii-1][jj] = 
						triangle[ii][jj] > triangle[ii][jj+1] ?
								triangle[ii-1][jj] + triangle[ii][jj] :
								triangle[ii-1][jj] + triangle[ii][jj+1];
			}
		}
		
		return triangle[0][0];
	}

}
