package problems.P026xP050;

import util.Basic;
import base.Problem;

/**
 * P036<br>
 * The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.
 * Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
 * (Please note that the palindromic number, in either base, may not include leading zeros.)
 * Ans: 872187
 * @return
 */
public class P036 extends Problem
{
   public P036()
   {
      problemNumber = 36;
      variations = 2;
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
            return faster() + "";
      }
      return null;
   }

   /**
    * Check all numbers less than 1 million!
    * @return
    */
   private long bruteForce()
   {
   	int total = 0;
   	for (int ii = 1; ii < 1000000; ii++)
   	{
   		if (Basic.isPalindrome(ii))
   		{
	   		// get the base 2 representation
	   		String b2 = "";
	   		int num = ii;
	   		while (num != 0)
	   		{
	   			b2 = b2 + (num % 2);
	   			num = num / 2;
	   		}
	   		if (Basic.isPalindrome(b2))
	   		{
	   			total += ii;
	   		}
   		}
   	}
   	return total;
   }
   
   /**
    * Only need to check odd numbers because if it ends in a 0, it won't start with a 0, also
    * one million is 11110100001001000000 in base 2, a 20 digit number. Any base 2 palindrome
    * (or others) can be defined by only the first half of the palindrome. So we can use 10
    * digit numbers and create palindromes from them. This is only 512*2 numbers (times 2
    * because we have to check the 20 digit number and the 19 digit number as palindromes)
    * @return
    */
   private long faster()
   {
   	int total = 0;
   	int[] arr = new int[10];
   	arr[0] = 1;
   	for (int ii = 0; ii < 512; ii++)
   	{
   		for (int jj = 2; jj < arr.length; jj++)
   		{
   			if (arr[jj-1] > 1)
   			{
   				arr[jj]++;
   				arr[jj-1]-=2;
   			}
   		}
   		int gsd = 0;
   		for (int jj = 0; jj < arr.length; jj++)
   		{
   			if (arr[jj] == 1)
   				gsd = jj;
   		}
   		// we can have lots of palindromic numbers from, let's say, 101 as a base
   		// 101101
   		// 10101
   		// 10100101
   		// 101000000101, etc
   		for (int kk = gsd; kk < arr.length; kk++)
   		{
   			// now get the decimal number. First, the lower half in order
   	   		int dec = 0;
   	   		int mult = 1;
   	   		int size = kk;
   	   		for (int jj = 0; jj <= size; jj++)
   	   		{
   	   			if (arr[jj] == 1)
   	   				dec += mult;
   	   			mult *= 2;
   	   		}
   	   		int dec19 = dec;
   	   		int dec20 = dec;
   	   		int multTmp = mult;
   	   		for (int jj = size; jj >= 0; jj--)
   	   		{
   	   			if (arr[jj] == 1)
   	   				dec20 += mult;
   	   			mult *= 2;
   	   		}
   	   		mult = multTmp;
   	   		for (int jj = size - 1; jj >= 0; jj--)
   	   		{
   	   			if (arr[jj] == 1)
   	   				dec19 += mult;
   	   			mult *= 2;
   	   		}
   	   		if (dec20 < 1000000)
   	   		{
   	   			if (Basic.isPalindrome(dec20))
   	   			{
   	   				total += dec20;
   	   			}
   	   		}
   	   		if (Basic.isPalindrome(dec19))
   	   		{
   	   			total += dec19;
   	   		}
   		}
   		
   		arr[1]++;
   	}
   	return total;
   }
}
