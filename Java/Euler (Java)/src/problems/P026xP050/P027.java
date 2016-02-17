package problems.P026xP050;

import java.util.List;

import util.Primes;
import base.Problem;

/**
 * P027<br>
 * Euler published the remarkable quadratic formula:
 * n² + n + 41
 * It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39. However, 
 * when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41, 41² + 41 + 41 is clearly divisible by 41.
 * Using computers, the incredible formula  n²  79n + 1601 was discovered, which produces 80 primes for the consecutive values n = 0 to 79.
 * The product of the coefficients, 79 and 1601, is 126479.
 * Considering quadratics of the form:
 * n² + an + b, where |a|  1000 and |b|  1000
 * where |n| is the modulus/absolute value of n
 * e.g. |11| = 11 and |4| = 4
 * Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive 
 * values of n, starting with n = 0.
 * Ans: -59231 
 * @return
 */
public class P027 extends Problem
{
   public P027()
   {
      problemNumber = 27;
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
    * Just test them all!
    * 
    * @return
    */
   private long bruteForce()
   {
      int max = 0;
      int mult = 0;
      for (int a = -999; a < 1000; a++)
      {
         for (int b = -999; b < 1000; b++)
         {
            int count = 0;
            int n = 0;
            while (Primes.isPrime(n*n + a*n + b))
            {
               count++;
               n++;
            }
            if (count > max)
            {
               max = count;
               mult = a*b;
            }
         }
      }
      return mult;
   }
   
   /**
    * First, we know that b must be prime and positive because when n == 0, we still
    * must have a prime number. Secondly, instead of testing a large list of primes,
    * we know that the largest prime is less than 80^2 + 80*999 + 999 (87319), so we
    * can generate a list of primes up to that number and see if it's contained. 
    * (This idea didn't work out ... isPrime is much faster for small primes than
    * testing contains on all of those primes)
    * We also know
    * that for n=1, 1+a+b must be prime, and since b is odd, a must be odd (adding one) to
    * keep the solution odd. We also know that a+b must be greater than zero, so a must be
    * a minimum of -b+2 (plus 2 because a must remain odd)
    * @return
    */
   private int faster()
   {
      List<Integer> primes = Primes.EratosthenesPrimesUpTo(1010);
      
      int max = 0;
      int mult = 0;
      
      int b = primes.get(0);
      for (int idx = 1; b < 1000; idx++)
      {
         
         for (int a = -b + 2; a < 1000; a+=2)
         {
            int count = 0;
            int n = 0;
            while (Primes.isPrime(n*n + a*n + b))
            {
               count++;
               n++;
            }
            if (count > max)
            {
               max = count;
               mult = a*b;
            }
         }
         b = primes.get(idx);
      }
      return mult;
   }

}
