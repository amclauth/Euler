package problems.P001xP050;

import java.util.ArrayList;
import java.util.List;

import base.Problem;

/**
 * P008<br>
 * Find the greatest product of five consecutive digits in the 1000-digit
 * number.<br>
 * Ans: 40824
 */
public class P008 extends Problem
{
   public P008()
   {
      variations = 3;
      makeString();
   }

   @Override
   protected String execute(int variation)
   {
      switch (variation)
      {
         case 0:
            return bruteForce() + "";
         case 1:
            return optimizedBruteForce() + "";
         case -1:
         case 2:
            return optimizedBruteForceASCII() + "";
      }
      return null;
   }

   private char[] digits;

   /**
    * This is the brute force attempt. Just make a list of consecutive 5 numbers
    * and keep checking
    * 
    * @return
    */
   private int bruteForce()
   {
      List<Integer> fives = new ArrayList<Integer>(5);
      fives.add(Integer.valueOf(digits[0] + ""));
      fives.add(Integer.valueOf(digits[1] + ""));
      fives.add(Integer.valueOf(digits[2] + ""));
      fives.add(Integer.valueOf(digits[3] + ""));
      fives.add(Integer.valueOf(digits[4] + ""));
      int max = fives.get(0) * fives.get(1) * fives.get(2) * fives.get(3)
            * fives.get(4);
      for (int ii = 0; ii < digits.length; ii++)
      {
         fives.remove(0);
         fives.add(Integer.valueOf(digits[ii] + ""));
         int mult = fives.get(0) * fives.get(1) * fives.get(2) * fives.get(3)
               * fives.get(4);
         if (mult > max)
            max = mult;
      }
      return max;
   }

   /**
    * Make a couple additions here ... don't use lists (use an array) and only
    * check values that have five consecutive digits with no zero in them.
    * Instead of multiplying all five digits, divide out the oldest and multiply
    * in the newest.
    * 
    * @return
    */
   private int optimizedBruteForce()
   {
      int[] fives = new int[5];
      int idx = 0;
      int size = 0;
      int max = 0;
      int mult = 1;
      for (int ii = 0; ii < digits.length; ii++)
      {
         int cur = Integer.valueOf(digits[ii] + "");
         if (cur == 0)
         {
            // start over
            size = 0;
            idx = 0;
            mult = 1;
         }
         else if (size < 5)
         {
            fives[idx++] = cur;
            mult *= cur;
            size++;
         }
         else
         {
            idx = (idx + 1) % 5;
            mult = mult / fives[idx] * cur;
            fives[idx] = cur;
            if (mult > max)
               max = mult;
         }
      }
      return max;
   }

   /**
    * only addition here is to use the fact that chars are ascii values, so for
    * integers, we can just subtract 48 from the char rather than do a
    * conversion to an int
    * 
    * @return
    */
   private int optimizedBruteForceASCII()
   {
      int[] fives = new int[5];
      int idx = 0;
      int size = 0;
      int max = 0;
      int mult = 1;
      for (int ii = 0; ii < digits.length; ii++)
      {
         int cur = (int) digits[ii] - 48;
         if (cur == 0)
         {
            // start over
            size = 0;
            idx = 0;
            mult = 1;
         }
         else if (size < 5)
         {
            fives[idx++] = cur;
            mult *= cur;
            size++;
         }
         else
         {
            idx = (idx + 1) % 5;
            mult = mult / fives[idx] * cur;
            fives[idx] = cur;
            if (mult > max)
               max = mult;
         }
      }
      return max;
   }

   private void makeString()
   {
      String[] s_arr = new String[20];
      s_arr[0] = "73167176531330624919225119674426574742355349194934";
      s_arr[1] = "96983520312774506326239578318016984801869478851843";
      s_arr[2] = "85861560789112949495459501737958331952853208805511";
      s_arr[3] = "12540698747158523863050715693290963295227443043557";
      s_arr[4] = "66896648950445244523161731856403098711121722383113";
      s_arr[5] = "62229893423380308135336276614282806444486645238749";
      s_arr[6] = "30358907296290491560440772390713810515859307960866";
      s_arr[7] = "70172427121883998797908792274921901699720888093776";
      s_arr[8] = "65727333001053367881220235421809751254540594752243";
      s_arr[9] = "52584907711670556013604839586446706324415722155397";
      s_arr[10] = "53697817977846174064955149290862569321978468622482";
      s_arr[11] = "83972241375657056057490261407972968652414535100474";
      s_arr[12] = "82166370484403199890008895243450658541227588666881";
      s_arr[13] = "16427171479924442928230863465674813919123162824586";
      s_arr[14] = "17866458359124566529476545682848912883142607690042";
      s_arr[15] = "24219022671055626321111109370544217506941658960408";
      s_arr[16] = "07198403850962455444362981230987879927244284909188";
      s_arr[17] = "84580156166097919133875499200524063689912560717606";
      s_arr[18] = "05886116467109405077541002256983155200055935729725";
      s_arr[19] = "71636269561882670428252483600823257530420752963450";

      String input = "";
      for (int ii = 0; ii < s_arr.length; ii++)
         input += s_arr[ii];

      digits = input.toCharArray();
   }

}
