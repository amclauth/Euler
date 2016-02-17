package problems.P001xP050;

import base.Problem;

/**
 * P006<br>
 * The sum of the squares of the first ten natural numbers is,<br>
 * 1^2 + 2^2 + ... + 10^2 = 385<br>
 * The square of the sum of the first ten natural numbers is,<br>
 * (1 + 2 + ... + 10)^2 = 55^2 = 3025<br>
 * Hence the difference between the sum of the squares of the first ten natural
 * numbers and the square of the sum is 3025 - 385 = 2640. <br>
 * Find the difference between the sum of the squares of the first one hundred
 * natural numbers and the square of the sum. Ans: 25164150
 */
public class P006 extends Problem
{
   public P006()
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
            return formula() + "";
      }
      return null;
   }

   /**
    * This is the brute force attempt. Simply count and apply.
    * 
    * @return
    */
   private int bruteForce()
   {
      // find the sum of squares
      int sum = 0;
      int square = 0;
      for (int ii = 1; ii <= 100; ii++)
      {
         sum += ii * ii;
         square += ii;
      }
      square *= square;
      return square - sum;
   }

   /**
    * We know the formula for sums from 1 to n, and I looked up the formula for
    * sums from 1^2 to n^2. It is n/6*(2n+1)*(n+1). This can also be solved for
    * and proved via induction that it is correct.
    * 
    * @return
    */
   private int formula()
   {
      int n = 100;
      int square = n * (n + 1) / 2;
      int sum = n * (2 * n + 1) * (n + 1) / 6;
      return square * square - sum;
   }
}
