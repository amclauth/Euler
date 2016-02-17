package problems.P026xP050;

import java.util.List;

import util.Primes;
import base.Problem;

/**
 * P037<br>
 * The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, 
 * and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
 * Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
 * NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
 * Ans: 748317 
 * @return
 */
public class P037 extends Problem
{
   public P037()
   {
      problemNumber = 37;
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
    * Check all numbers!
    * @return
    */
   private long bruteForce()
   {
   	int total = 0 -2 -3 -5 -7; // these are not "truncatable"
   	List<Integer> primes = Primes.EratosthenesPrimesUpTo(1000000);
   	for (int p : primes)
   	{
   		int right = p;
   		int left = 0;
   		int power = 1;
   		boolean isTruncatable = true;
   		while (isTruncatable)
   		{
   			left = power * (right % 10) + left;
   			power *= 10;
   			right = right / 10;
   			if (right == 0)
   				break;
   			if (!Primes.isPrime(left) || !Primes.isPrime(right))
   			{
   				isTruncatable = false;
   			}
   		}
   		if (isTruncatable)
   			total += p;
   	}
   	return total;
   }
   
   /**
    * Build the numbers to test. The rightmost must be prime in and of itself (2,3,5,7),
    * but can't be 5 or would be divisible by 5 and can't be 2 or would be divisible by 2,
    * so it must be 3 or 7.
    * Numbers in the middle can't be even or 5 or right truncation would end up with them
    * being non prime (1,3,7,9). 
    * The leftmost number must simple be a prime number (2,3,5,7) 
    * @return
    */
   private long faster()
   {
   	int total = 0;
   	int[] lefts = new int[]{2,3,5,7};
   	int[] middles = new int[]{1,3,7,9};
   	int[] rights = new int[]{3,7};
   	
   	for (int left : lefts)
   	{
   		// check the simple case
   		{
   			for (int right : rights)
   			{
   				int digit = left * 10 + right;
   				if (Primes.isPrime(digit) && isTruncatable(digit))
		   		{
		   			total += digit;
		   		}
   			}
   		}
   		// up to a six digit number, so we need the left digit, up to 4 in the middle, and the
   		// right digit. So we need to simply count.
   		for (int midIdx = 0; midIdx < 256; midIdx++)
   		{
   			int predigit = left;
   			int idx = midIdx;
   			while (true)
   			{
   				predigit = predigit * 10 + middles[idx%4];
   				idx = idx / 4;
   				if (idx == 0)
   					break;
   			}
				for (int right : rights)
				{
					int digit = predigit * 10 + right;
		   		if (Primes.isPrime(digit) && isTruncatable(digit))
		   		{
		   			total += digit;
		   		}
				}
			}
   	}
   	return total;
   }
   
   private boolean isTruncatable(int digit)
   {
   	int rightTrunc = digit;
		int leftTrunc = 0;
		int power = 1;
		boolean isTruncatable = true;
		while (isTruncatable)
		{
			leftTrunc = power * (rightTrunc % 10) + leftTrunc;
			power *= 10;
			rightTrunc = rightTrunc / 10;
			if (rightTrunc == 0)
				break;
			if (!Primes.isPrime(leftTrunc) || !Primes.isPrime(rightTrunc))
			{
				isTruncatable = false;
			}
		}
		
		return isTruncatable;
   }
}
