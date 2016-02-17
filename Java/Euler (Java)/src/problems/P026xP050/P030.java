package problems.P026xP050;

import java.util.ArrayList;
import java.util.List;

import base.Problem;

/**
 * P030<br>
 * Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:
 * 1634 = 1^4 + 6^4 + 3^4 + 4^4
 * 8208 = 864 + 2^4 + 0^4 + 8^4
 * 9474 = 9^4 + 4^4 + 7^4 + 4^4
 * As 1 = 1^4 is not a sum it is not included.
 * The sum of these numbers is 1634 + 8208 + 9474 = 19316.
 * Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
 * Ans: 443839
 * @return
 */
public class P030 extends Problem
{
   public P030()
   {
      problemNumber = 30;
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
    * Use all powers of five in an array and know that the upper limit is six digits that 
    * are nines (after six digits, the sum of powers can never be the same order as the
    * digit itself). Then just check every number.
    */
   private long bruteForce()
   {
      long rval = 0L;
      Integer[] pow = {0,1,2*2*2*2*2,3*3*3*3*3,4*4*4*4*4,5*5*5*5*5,6*6*6*6*6,
            7*7*7*7*7,8*8*8*8*8,9*9*9*9*9};
      int upper = (int) (6* Math.pow(9, 5));
      // ignoring non sums
      for (int ii = 10; ii < upper; ii++) {
         int num = ii;
         int sum = 0;
         while (num > 0) {
            sum += pow[num % 10];
            num = (int)(num / 10);
         }
         if (sum == ii) {
            rval += sum;
         }
      }
      return rval;
   }
   
   /**
    * Use combinations of the numbers ... this checks only that the sum of any number
    * uses all the numbers in the sum. For example 123's sum would be 276, we can see
    * easily that no combination of 1,2,3 equals 276, so we can move on and never consider
    * those again.
    */
   private long faster()
   {
      int rval = -1; // 1 is not included in the sum
      Integer[] pow = {0,1,2*2*2*2*2,3*3*3*3*3,4*4*4*4*4,5*5*5*5*5,6*6*6*6*6,
            7*7*7*7*7,8*8*8*8*8,9*9*9*9*9};

      for (int a = 0; a < 10; a++)
      {
         for (int b = a; b < 10; b++)
         {
            for (int c = b; c < 10; c++)
            {
               for (int d = c; d < 10; d++)
               {
                  for (int e = d; e < 10; e++)
                  {
                     for (int f = e; f < 10; f++)
                     {
                        // number is abcdef
                        int sum = pow[a] + pow[b] + pow[c] + pow[d] + pow[e] + pow[f];
                        int n = sum;
                        List<Integer> split = new ArrayList<Integer>();
                        while (n != 0)
                        {
                           split.add(n % 10);
                           n = n / 10;
                        }
                        // now check that a through f are in the array ... zeros can be anywhere
                        split.add(0);
                        int ai = split.indexOf(a);
                        if (ai >= 0)
                           split.set(ai, 0);
                        else
                           continue; // no a
                        
                        int bi = split.indexOf(b);
                        if (bi >= 0)
                           split.set(bi, 0);
                        else
                           continue; // no b
                        
                        int ci = split.indexOf(c);
                        if (ci >= 0)
                           split.set(ci, 0);
                        else
                           continue; // no c
                        
                        int di = split.indexOf(d);
                        if (di >= 0)
                           split.set(di, 0);
                        else
                           continue; // no d
                        
                        int ei = split.indexOf(e);
                        if (ei >= 0)
                           split.set(ei, 0);
                        else
                           continue; // no e
                        
                        int fi = split.indexOf(f);
                        if (fi >= 0)
                           split.set(fi, 0);
                        else
                           continue; // no f
                        
                        // if the list isn't all zero's now, it's not a match
                        boolean match = true;
                        for (int ii = 0; ii < split.size(); ii++)
                        {
                           if (split.get(ii) != 0)
                           {
                              match = false;
                              break;
                           }
                        }
                        if (match)
                        {
                           rval += sum;
                        }
                     }
                  }
               }
            }
         }
      }
      
      return rval;
   }

}
