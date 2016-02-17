package util;

import java.util.ArrayList;
import java.util.List;

public class Primes {
	
	/**
	 * Quick check for primeness of small numbers
	 * @param num
	 * @return
	 */
	public static boolean isPrime(int num)
	{
		if (num <= 1)
			return false;
		if (num % 2 == 0 && num != 2)
			return false;
		for (int ii = 3; ii * ii <= num; ii +=2)
		{
			if (num % ii == 0)
				return false;
		}
		return true;
	}
	
	/**
	 * Uses the sieve of Eratosthenes and assumes that there are ~ n/ln(n) primes less than n
	 * So the nth prime is approximately n ln n. n ln n is less than the prime, though, so 
	 * use the greater approximation: n ln n + n ln ln n
	 * @param n
	 * @return
	 */
	public static int getNthPrime(int n)
	{
		double lnn = Math.log(n);
		double max = n * (lnn + Math.log(lnn));
		List<Integer> primes = EratosthenesPrimesUpTo((int) max);
		if (n <= primes.size())
		{
			return primes.get(n-1);
		}
		return -1;
	}
	
	/**
	 * Doing a Sieve of Eratosthenes
	 * @param n
	 * @return
	 */
	public static List<Integer> EratosthenesPrimesUpTo(int n)
	{
		boolean[] is_composite = new boolean[(n - 2) >> 1]; // booleans of all odd numbers
		// upper bound for primes is approximately 1.25506 * n / ln(n)
		List<Integer> results = new ArrayList<Integer>((int) Math.ceil(1.25506 * n / Math.log(n)));
		results.add(2); // add 2 since we're ignoring evens
		for (int ii = 0; ii < is_composite.length; ii++) // check all odds
		{
			if (!is_composite[ii]) // if it's not known, we need to check it
			{
				results.add(2 * ii + 3);
				// changing indexes to use only odd numbers
				for (long j = 4L * ii * ii + 12L * ii + 9; j < 2 * is_composite.length + 3; j += 4 * ii + 6) 
				{
					is_composite[(int) (j - 3L >> 1)] = true;
				}
			}
		}
		return results;
	}
	
	/**
	 * Add the next prime number to this series. Assumes 2 and 3 are already in the list
	 * @param primes
	 */
	public static void addNextPrime(List<Integer> primes)
	{
	   int next = primes.get(primes.size() - 1);
	   boolean found = false;
	   while (!found)
	   {
	      next += 2;
	      found = true;
	      for (int p : primes)
	      {
	         if (next % p == 0)
	         {
	            found = false;
	            break;
	         }
	      }
	      if (found)
	      {
	         primes.add(next);
	         return;
	      }
	   }
	}
}
