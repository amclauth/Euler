package problems.P001xP050;

import base.Problem;

/**
 * P011<br>
 * In the 2020 grid below, four numbers along a diagonal line have been marked in red.<br>
 * The product of these numbers is 26  63  78  14 = 1788696.<br>
 * What is the greatest product of four adjacent numbers in the same direction (up, down, left, right, or diagonally) in the 20x20 grid?<br>
 * Ans: 70600674
 */
public class P011 extends Problem
{	
	public P011()
	{
		variations = 2;
		makeString();
	}

	@Override
	protected String execute(int variation)
	{
		switch (variation)
		{
		case 0:
			return bruteForce() + "";
		case -1:
		case 1:
			return optimizedBruteForce() + "";
		}
		return null;
	}
	
	private char[][] digits = new char[20][60];

	/**
	 * This is the brute force attempt. Just make a list of consecutive 4 numbers and 
	 * keep checking. Very similar to problem 7
	 * @return
	 */
	private int bruteForce()
	{
		int max = 0;
		int mult = 0;
		int cur = 0;
		// first check all horizontal values
		for (int ii = 0; ii < 20; ii++)
			for (int jj = 0; jj < 17; jj++)
			{
				mult = 1;
				for (int kk = 0; kk < 4; kk++)
				{
					cur = (int)(digits[ii][jj*3+kk*3]-48)*10 + 
							(int)(digits[ii][jj*3+1+kk*3]-48);
					mult *= cur;
				}
				if (mult > max)
					max = mult;
			}
		// then all vertical values
		for (int ii = 0; ii < 17; ii++)
			for (int jj = 0; jj < 20; jj++)
			{
				mult = 1;
				for (int kk = 0; kk < 4; kk++)
				{
					cur = (int)(digits[ii+kk][jj*3]-48)*10 + 
							(int)(digits[ii][jj*3+1]-48);
					mult *= cur;
				}
				if (mult > max)
					max = mult;
			}
		// then forward diagonals
		for (int ii = 0; ii < 17; ii++)
			for (int jj = 0; jj < 17; jj++)
			{
				mult = 1;
				for (int kk = 0; kk < 4; kk++)
				{
					cur = (int)(digits[ii+kk][jj*3+kk*3]-48)*10 + 
							(int)(digits[ii+kk][jj*3+1+kk*3]-48);
					mult *= cur;
				}
				if (mult > max)
					max = mult;
			}
		// then backward diagonals
		for (int ii = 0; ii < 17; ii++)
			for (int jj = 4; jj < 20; jj++)
			{
				mult = 1;
				for (int kk = 0; kk < 4; kk++)
				{
					cur = (int)(digits[ii+kk][jj*3-kk*3]-48)*10 + 
							(int)(digits[ii+kk][jj*3+1-kk*3]-48);
					mult *= cur;
				}
				if (mult > max)
					max = mult;
			}
		return max;
	}
	
	/**
	 * Make a couple additions here ... use an array of ints, skip any that center around zero,
	 * and use only one loop through the entire list (rather than back tracking). Expand
	 * the matrix to include 0 buffers.
	 * @return
	 */
	private int optimizedBruteForce()
	{
		// first, convert everything so we aren't doing a bunch of extra conversions
		int[][] numbers = new int[20][20];
		for (int ii = 0; ii < 20; ii++)
			for (int jj = 0; jj < 20; jj++)
				numbers[ii][jj] = ((int)digits[ii][jj*3]-48)*10 +
										((int)digits[ii][jj*3+1]-48);
		
		int max = 0, ans = 0;
		for (int ii = 0; ii < 20; ii++)
		{
			for (int jj = 0; jj < 20; jj++)
			{
				if (numbers[ii][jj] == 0)
					continue;
				if (ii+3 < 20)
				{
					ans = numbers[ii][jj] * numbers[ii+1][jj] * numbers[ii+2][jj] * numbers[ii+3][jj];
					max = ans > max ? ans : max;
				}
				if (jj+3 < 20)
				{
					ans  = numbers[ii][jj] * numbers[ii][jj+1] * numbers[ii][jj+2] * numbers[ii][jj+3];
					max = ans > max ? ans : max;
				}
				if (ii+3 < 20 && jj+3 < 20)
				{
					ans = numbers[ii][jj] * numbers[ii+1][jj+1] * numbers[ii+2][jj+2] * numbers[ii+3][jj+3];
					max = ans > max ? ans : max;
				}
				if (ii+3 < 20 && jj-3 >= 0)
				{
					ans = numbers[ii][jj] * numbers[ii+1][jj-1] * numbers[ii+2][jj-2] * numbers[ii+3][jj-3];
					max = ans > max ? ans : max;
				}	
			}
		}
		return max;
	}
	
	private void makeString() 
	{
		String[] s_arr = new String[20];
   	s_arr[0] = "08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08";
   	s_arr[1] = "49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00";
   	s_arr[2] = "81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65";
   	s_arr[3] = "52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91";
   	s_arr[4] = "22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80";
   	s_arr[5] = "24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50";
   	s_arr[6] = "32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70";
   	s_arr[7] = "67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21";
   	s_arr[8] = "24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72";
   	s_arr[9] = "21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95";
   	s_arr[10] = "78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92";
   	s_arr[11] = "16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57";
   	s_arr[12] = "86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58";
   	s_arr[13] = "19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40";
   	s_arr[14] = "04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66";
   	s_arr[15] = "88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69";
   	s_arr[16] = "04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36";
   	s_arr[17] = "20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16";
   	s_arr[18] = "20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54";
   	s_arr[19] = "01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48";
   	
   	for (int ii = 0; ii < s_arr.length; ii++)
   		digits[ii] = s_arr[ii].toCharArray();
	}

}
