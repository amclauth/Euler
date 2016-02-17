package problems.P001xP050;

import base.Problem;

/**
 * P009<br>
 * A Pythagorean triplet is a set of three natural numbers, a b c, for which,<br>
 * a^2 + b^2 = c^2<br>
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.<br>
 * There exists exactly one Pythagorean triplet for which a + b + c = 1000.<br>
 * Find the product abc.<br>
 * Ans: 31875000
 */
public class P009 extends Problem
{
   public P009()
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
    * Just check every set of numbers!
    * 
    * @return
    */
   private int bruteForce()
   {
      // doing pure brute force
      for (int ii = 1; ii < 1000; ii++)
      {
         // jj must be > ii and less than 1000-ii (actually, less than
         // 1000 - ii - jj - 1 since kk must be > jj)
         for (int jj = ii + 1; jj < 1000 - ii; jj++)
         {
            int kk = 1000 - ii - jj;
            if (ii * ii + jj * jj == kk * kk)
            {
               return ii * jj * kk;
            }
         }
      }
      return -1;
   }

   /**
    * We might not have to hunt for out second term: ii^2 + x^2 = (1000-ii-x)^2
    * = 1000^2 + ii^2 + x^2 - 2000ii - 2000x - 2ii*x 
    * 0 = 1000^2 - 2000ii - 2000x * - 2iix 2000ii - 1000^2
    *  = -x(2000 - 2ii) 1000^2 - 2000ii / 2000 - 2ii
    *  = x * 500*1000 - 1000
    *  ii / 1000 - ii = x
    * 
    * @return
    */
   private int optimized()
   {
      for (int a = 1; a < 1000; a++)
      {
         int b = (500 * 1000 - 1000 * a) / (1000 - a);
         int c = 1000 - a - b;
         if (a * a + b * b == c * c)
         {
            return a*b*c;
         }
      }
      return -1;
   }
}
