package problems.P001xP050;

import java.util.ArrayList;
import java.util.List;

import util.Basic;
import base.Problem;

/**
 * P024<br>
 * A permutation is an ordered arrangement of objects. For example, 3124 is one
 * possible permutation of the digits 1, 2, 3 and 4. If all of the permutations
 * are listed numerically or alphabetically, we call it lexicographic order. The
 * lexicographic permutations of 0, 1 and 2 are: 012 021 102 120 201 210 What is
 * the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7,
 * 8 and 9? 
 * 
 * Ans: 2783915460
 * 
 * @return
 */
public class P024 extends Problem
{
   public P024()
   {
      problemNumber = 24;
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
    * Check all the numbers and see if they contain all the digits. Guaranteed
    * to be ordered this way. Takes a /long/ time.
    * 
    * @return
    */
   private long bruteForce()
   {
      int count = 0;
      for (long ii = 123456789; ii <= 9876543210L; ii++) {
         if (containsAll(ii)) {
            count++;
            if (count == 1000000) {
               return ii;
            }
         }
      }
      return 0;
   }
   
   @SuppressWarnings("unused")
   private boolean containsAll(String n)
   {
      for (char ii = '1'; ii <= '9'; ii++)
      {
         if (!(n.indexOf(ii) >= 0))
         {
            return false;
         }
      }
      if (n.length() < 10 || n.indexOf('0') >= 0)
         return true;
      return false;
   }

   // check if a number contains all digits. Probably faster to convert to a string and do contains, though.
   private boolean containsAll(long n) {
      boolean[] nums = {false,false,false,false,false,false,false,false,false,false};
      if (n < 1000000000L) {
         nums[0] = true; // 0 is the first number then!
      }
      while (n >= 1) {
         nums[(int)(n % 10)] = true;
         n = (int)(n/10);
      }
      for (int ii = 0; ii < nums.length; ii++) {
         if (!nums[ii])
            return false;
      }
      return true;
   }

   /**
    * We know that there are n! permutations for any combination of numbers, so 
    * we can search for the first number by asking "what is the greatest number
    * that fits in the equations x*9! <= 1000000. We then have the difference
    * between 1000000 and x*9! number of permutations away from the 0th 
    * permutation to find. Then it's x2*8! < 1000000 - x*9!, etc.
    * 
    * @return
    */
   private long faster()
   {
      List<Integer> digits = new ArrayList<Integer>();
      for (int ii = 0; ii < 10; ii++) {
         digits.add(ii);
      }
      long num = 0;
      int goal = 1000000;
      while (digits.size() > 0) {
         for (int ii = 0; ii < 10; ii++) {
            long fac = Basic.factorial(digits.size() - 1);
            if ((ii + 1) * fac >= goal) {
               goal -= ii * fac;
               num = num * 10 + digits.remove(ii);
               break;
            }
         }
      }
      
      return num;
   }

}
