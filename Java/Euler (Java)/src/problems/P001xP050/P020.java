package problems.P001xP050;

import java.math.BigInteger;

import base.Problem;

/**
 * P020<br>
 * n! means n  (n  1)  ...  3  2  1
 * For example, 10! = 10  9  ...  3  2  1 = 3628800,
 * and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
 * Find the sum of the digits in the number 100!
 * Ans: 648
 * @return
 */
public class P020 extends Problem
{	
	public P020()
	{
		problemNumber = 20;
		variations = 2; 
	}

	@Override
	protected String execute(int variation)
	{
		switch (variation)
		{
		case 0:
		case -1:
			return bruteForce() + "";
		case 1:
			return faster() + "";
		}
		return null;
	}

	/**
	 * 
	 * @return
	 */
	private int bruteForce()
	{
		int[] num = new int[200]; // WAG on size
		num[0] = 1;
		for (int ii = 2; ii <= 100; ii++)
		{
			int carry = 0;
			for (int jj = 0; jj < num.length; jj++)
			{
				num[jj] = num[jj]*ii + carry;
				carry = num[jj] / 10;
				num[jj] = num[jj] % 10;
			}
		}
		int sum = 0;
		for (int ii = 0; ii < num.length; ii++)
		{
			sum += num[ii];
		}
		return sum;
	}
	
	/**
	 * Big Decimal version
	 * @return
	 */
	private long faster()
	{
		BigInteger num = BigInteger.ONE;
		BigInteger sum = BigInteger.ZERO;
		for (int ii = 2; ii <= 100; ii++)
		{
			num = num.multiply(BigInteger.valueOf(ii));
		}
		
		BigInteger ten = BigInteger.valueOf(10);
		while (num.compareTo(BigInteger.ZERO) == 1)
		{
			sum = sum.add(num.mod(ten));
			num = num.divide(ten);
		}
		return sum.longValue();
	}

}
