package problems.P001xP050;

import java.math.BigInteger;

import base.Problem;

/**
 * P016<br>
 * 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
 * What is the sum of the digits of the number 2^1000?
 * Ans: 1366
 * @return
 */
public class P016 extends Problem
{	
	public P016()
	{
		problemNumber = 16;
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
	 * Actually multiply it out into an array
	 * @return
	 */
	private int bruteForce()
	{
		int[] array = new int[400]; 
		array[0] = 1;
		
		for (int ii = 0; ii < 1000; ii++)
		{
			int carry = 0;
			for (int jj = 0; jj < array.length; jj++)
			{
				int n = array[jj] * 2 + carry;
				if (n > 9)
				{
					array[jj] = n % 10;
					carry = n / 10;
				} else {
					array[jj] = n;
					carry = 0;
				}
			}
		}
		int total = 0;
		for (int ii = 0; ii < array.length; ii++)
		{
			total += array[ii];
		}
		return total;
	}
	
	/**
	 * Just use BigInteger
	 * @return
	 */
	private int faster()
	{
		BigInteger val = BigInteger.ONE.shiftLeft(1000);
		int sum = 0;
		for (char c : val.toString().toCharArray())
		{
			sum += Character.getNumericValue(c);
		}
		return sum;
	}

}
