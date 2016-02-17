package problems.P001xP050;

import java.util.ArrayList;
import java.util.List;

import util.Basic;
import base.Problem;

/**
 * P023<br>
 * A perfect number is a number for which the sum of its proper divisors is
 * exactly equal to the number. For example, the sum of the proper divisors of
 * 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
 * A number n is called deficient if the sum of its proper divisors is less than
 * n and it is called abundant if this sum exceeds n. As 12 is the smallest
 * abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be
 * written as the sum of two abundant numbers is 24. By mathematical analysis,
 * it can be shown that all integers greater than 28123 can be written as the
 * sum of two abundant numbers. However, this upper limit cannot be reduced any
 * further by analysis even though it is known that the greatest number that
 * cannot be expressed as the sum of two abundant numbers is less than this
 * limit. Find the sum of all the positive integers which cannot be written as
 * the sum of two abundant numbers. Ans: 4179871
 * 
 * @return
 */
public class P023 extends Problem
{
   public P023()
   {
      problemNumber = 23;
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
    * Try to use boolean arrays to keep track of which numbers are abundant, then 
    * which numbers can be sums of them.
    * @return
    */
   private long bruteForce()
   {
      final int size = 28123;
      
      long sum = 0;
      boolean[] abundant = new boolean[size]; // defaults to false
      boolean[] expressable = new boolean[size]; // defaults to false
      for (int ii = 0; ii < size; ii++)
      {
         long num = 0;
         for (Long l : Basic.getDivisors(ii))
         {
            num += l;
         }
         if (num > ii + ii)
         {
            abundant[ii] = true;
         }
      }
      
      for (int ii = 0; ii < size; ii++)
      {
         for (int jj = ii; jj < size - ii; jj++)
         {
            if (abundant[ii] && abundant[jj])
            {
               expressable[ii+jj] = true;
            }
         }
      }
      
      for (int ii = 0; ii < size; ii++)
      {
         if (!expressable[ii])
         {
            sum += ii;
         }
      }
      
      return sum;
   }
   


   /**
    * Since there are not so many abundant number, use a list and only
    * iterate over those in the list!
    * @return
    */
   private long faster()
   {
      final int size = 28123;

      List<Integer> abundants = new ArrayList<Integer>();
      for (int ii = 12; ii < size - 12; ii++)
      {
         long sum = 0;
         for (Long l : Basic.getDivisors(ii))
         {
            sum += l;
         }
         if (sum > ii + ii)
         {
            abundants.add(ii);
         }
      }

      // tried using a set here, but /most/ numbers are expressable, and
      // the set operation itself adds a lot. Plus, checking the non-set
      // later takes longer.
      boolean[] expressable = new boolean[size];
      for (int ii = 0; ii < abundants.size(); ii++)
      {
         for (int jj = 0; jj <= ii; jj++)
         {
            int n = abundants.get(ii) + abundants.get(jj);
            if (n < size)
               expressable[n] = true;
            else
               break;
         }
      }
      
      long sum = 0;
      for (int ii = 0; ii < size; ii++)
      {
         if (!expressable[ii])
            sum += ii;
      }
      return sum;
   }
}
