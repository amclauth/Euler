package problems.P001xP050;

import java.util.List;

import util.Basic;
import util.Primes;
import base.Problem;

/**
 * P003<br>
 * The prime factors of 13195 are 5, 7, 13 and 29.<br>
 * What is the largest prime factor of the number 600851475143 ?<br>
 * Ans: 6857
 * @return
 */
public class P003 extends Problem
{
   public P003()
   {
      variations = 2;
   }

   private long n = 600851475143L;

   @Override
   protected String execute(int variation)
   {
      switch (variation)
      {
         case 0:
         case -1:
            return bruteForce() + "";
         case 1:
            return primeTest() + "";
      }
      return null;
   }

   /**
    * Brute force (mostly). Start with 2, then 3, then 5, and just factor it
    * 
    * @return
    */
   private long bruteForce()
   {
      List<Long> factors = Basic.getPrimeFactors(n);
      return factors.get(factors.size() - 1);
   }

   /**
    * Check to see if decreasing primes are the right answer
    * 
    * @return
    */
   private long primeTest()
   {
      List<Integer> primes = Primes.EratosthenesPrimesUpTo((int) Math.sqrt(n));
      for (int ii = primes.size() - 1; ii >= 0; ii--)
      {
         if (n % primes.get(ii) == 0)
            return primes.get(ii);
      }
      return -1;
   }

}
