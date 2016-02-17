package problems.P001xP050;

import java.util.List;

import util.Primes;
import base.Problem;

/**
 * P010<br>
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.<br>
 * Find the sum of all the primes below two million.<br>
 * Ans: 142913828922
 */
public class P010 extends Problem
{
   public P010()
   {
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
            return optimized() + "";
      }
      return null;
   }

   /**
    * Just check every number!
    * 
    * @return
    */
   private long bruteForce()
   {
      long sum = 0;
      for (int ii = 2; ii < 2000000; ii++)
      {
         if (Primes.isPrime(ii))
            sum += ii;
      }
      return sum;
   }

   /**
    * Use the sieve of erosthenes and just add!
    * 
    * @return
    */
   private long optimized()
   {
      long sum = 0;
      List<Integer> primes = Primes.EratosthenesPrimesUpTo(2000000);
      for (int p : primes)
         sum += p;
      return sum;
   }
}
