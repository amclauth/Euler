package problems.P026xP050;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import util.Basic;
import util.Combinatorics;

/**
 * P032<br>
 * We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; 
 * for example, the 5-digit number, 15234, is 1 through 5 pandigital.
 * The product 7254 is unusual, as the identity, 39  186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.
 * Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
 * HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
 * Ans: 45228 
 * @return
 */
public class P032 extends Combinatorics<Integer>
{
   private static Set<Integer> products;
   
   public P032()
   {
      problemNumber = 32;
      variations = 2;
   }

   @Override
   protected String execute(int variation)
   {
      switch (variation)
      {
         case 0:
            return bruteForce() + "";
         case -1:
         case 1:
            return faster() + "";
      }
      return null;
   }

   /**
    * Check all permutations for a, b, and c!
    * @return
    */
   private long bruteForce()
   {
      products = new HashSet<Integer>();
      List<Integer> nums = new ArrayList<Integer>();
      for (int ii = 1; ii <= 9; ii++)
      {
         nums.add(ii);
      }
      permute(nums);
      int total = 0;
      for (int p : products)
      {
         total += p;
      }
      return total;
   }
   
   /**
    * We know the multiplicands must either be 1x4, 2x3, 3x2, or 4x1 in length to 
    * produce a correctly numbered output. We know the output must be 4 in length,
    * so we can iterate through 1234 to 9876 and check if divisors of those numbers
    * together with the solution contain a pandigital. We can check for
    * pandigiality with a bitmask of the deconstructed integer
    */
   private long faster()
   {
      products = new HashSet<Integer>();
      for (int product = 1234; product <= 9876; product++)
      {
         List<Long> divisors = Basic.getDivisors(product);
         for (int ii = 0; ii < divisors.size() / 2.0; ii++)
         {
            int d1 = divisors.get(ii).intValue();
            int d2 = divisors.get(divisors.size() - 1 - ii).intValue();
            if (Basic.isPandigital(product,d1,d2))
            {
               products.add(product);
               break;
            }
         }
      }
      
      int total = 0;
      for (int p : products)
      {
         total += p;
      }
      return total;
   }

   @Override
   protected void process(List<Integer> arr)
   {
      // try combinations of a * b = c
      for (int ii = 1; ii < 5; ii++)
      {
         int a = 0;
         for (int kk = 0; kk < ii; kk++)
         {
            a *= 10;
            a += arr.get(kk);
         }
         for (int jj = 5 - ii; jj < 4; jj++)
         {
            int b = 0;
            for (int kk = ii; kk < jj + ii; kk++)
            {
               b *= 10;
               b += arr.get(kk);
            }
            
            int c = 0;
            for (int kk = ii + jj; kk < arr.size(); kk++)
            {
               c *= 10;
               c += arr.get(kk);
            }
            
            if (a * b == c)
            {
               products.add(c);
            }
            
            if (a * b > c)
            {
               break;
            }
         }
      }
   }
}
