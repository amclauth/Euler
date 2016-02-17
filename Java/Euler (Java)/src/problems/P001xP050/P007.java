package problems.P001xP050;

import util.Primes;
import base.Problem;

/**
 * P007<br>
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see
 * that the 6th prime is 13.<br>
 * What is the 10 001st prime number?<br>
 * Ans: 104743
 */
public class P007 extends Problem
{
   public P007()
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
            return getPrime() + "";
      }
      return null;
   }

   /**
    * This is the brute force attempt. Check every number for Primeness
    * 
    * @return
    */
   private int bruteForce()
   {
      int n = 0;
      int num = 2;
      while (n < 10001)
      {
         if (Primes.isPrime(num))
            n++;
         num++;
      }
      return num - 1;
   }

   private int getPrime()
   {
      return Primes.getNthPrime(10001);
   }
}
