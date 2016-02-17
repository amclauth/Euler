package problems.P026xP050;

import java.util.List;

import util.Primes;
import base.Problem;

/**
 * P035<br>
 * The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
 * There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
 * How many circular primes are there below one million?
 * Ans: 55 
 * @return
 */
public class P035 extends Problem
{
   public P035()
   {
      problemNumber = 35;
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
    * I think we can get the primes in an efficient way and then just test them all
    * @return
    */
   private long bruteForce()
   {
   	int total = 0;
   	List<Integer> primes = Primes.EratosthenesPrimesUpTo(1000000);
   	for (int p : primes)
   	{
   		int next = rotateRight(p);
   		boolean isCircular = true;
   		while (next != p)
   		{
   			if (!Primes.isPrime(next))
   			{
   				isCircular = false;
   				break;
   			}
   			next = rotateRight(next);
   		}
   		if (isCircular)
   		{
   			total++;
   		}
   	}
   	return total;
   }
   
   private int rotateRight(int num)
	{
		int i = num % 10;
		int j = (int) (num/10);
		int size = 1;
		while (j >= size)
			size *= 10;
		j += size * i;
		return j;
	}
   
   /**
    * Keeping track of which primes are good and bad didn't work well. Took almost a full 
    * second instead of 40ms. So instead, let's look at the digits. Ignore anything that
    * has an even number or a 5 in it
    * @return
    */
   private long faster()
   {
   	int total = 0;
   	List<Integer> primes = Primes.EratosthenesPrimesUpTo(1000000);
   	for (int p : primes)
   	{
   		if (p >= 10)
   		{
   			if (!checkDigits(p))
   				continue;
   		}
   		int next = rotateRight(p);
   		boolean isCircular = true;
   		while (next != p)
   		{
   			if (!Primes.isPrime(next))
   			{
   				isCircular = false;
   				break;
   			}
   			next = rotateRight(next);
   		}
   		if (isCircular)
   		{
   			total++;
   		}
   	}
   	return total;
   }
   
   private boolean checkDigits(int p)
   {
   	while (p != 0)
   	{
   		int n = p % 10;
   		if (n % 2 == 0 || n % 5 == 0)
   			return false;
   		p = p / 10;
   	}
   	return true;
   }
}
