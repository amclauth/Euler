package problems.P001xP050;

import util.Basic;
import base.Problem;

/**
 * P001<br>
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we
 * get 3, 5, 6 and 9. The sum of these multiples is 23.<br>
 * Find the sum of all the multiples of 3 or 5 below 1000.<br>
 * Ans: 233168
 */
public class P001 extends Problem
{
   public P001()
   {
      variations = 3;
   }

   @Override
   protected String execute(int variation)
   {
      switch (variation)
      {
         case 0:
            return bruteForce() + "";
         case 1:
            return multiples() + "";
         case 2:
         case -1:
            return closedForm() + "";
      }
      return null;
   }

   private final int max = 999; // use 999999 for a better differentiator

   /**
    * This is the brute force attempt. Just check all the numbers below 1000 to
    * see if they're divisible. Should be fast enough.
    * 
    * @return
    */
   private int bruteForce()
   {
      int start = 1;
      int sum = 0;
      for (int ii = start; ii <= max; ii++)
      {
         if (ii % 3 == 0 || ii % 5 == 0)
         {
            sum += ii;
         }
      }
      return sum;
   }

   /**
    * A slightly faster implementation. We don't check every single number, but
    * don't have an easy way to skip previously added numbers, so we should
    * subtract them out
    * 
    * @return
    */
   private int multiples()
   {
      int sum = 0;
      for (int ii = 1; ii <= max / 3; ii += 1)
         sum += ii * 3;
      for (int ii = 1; ii <= max / 5; ii += 1)
         sum += ii * 5;
      for (int ii = 1; ii <= max / 15; ii += 1)
         sum -= ii * 15;
      return sum;
   }

   /**
    * We know that we can find a sum from 1 to n, so let's add the sums of 3's
    * and 5's, then subtract the sum of their common denominators, 15's.
    * 
    * @return
    */
   private int closedForm()
   {
      int high3 = max / 3;
      int high5 = max / 5;
      int high15 = max / 15;

      int total = 0;
      // add the 3's
      total += 3 * Basic.getNSum(high3);
      total += 5 * Basic.getNSum(high5);
      total -= 15 * Basic.getNSum(high15);

      return total;
   }

}
