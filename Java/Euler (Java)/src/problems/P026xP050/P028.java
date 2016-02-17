package problems.P026xP050;

import base.Problem;

/**
 * P028<br>
 * Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:
 * 21 22 23 24 25
 * 20  7  8  9 10
 * 19  6  1  2 11
 * 18  5  4  3 12
 * 17 16 15 14 13
 * It can be verified that the sum of the numbers on the diagonals is 101.
 * What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
 * Ans: 669171001
 * @return
 */
public class P028 extends Problem
{
   public P028()
   {
      problemNumber = 28;
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
    * Build the array and then add it up!
    * 
    * @return
    */
   private long bruteForce()
   {
      int[][] array = new int[1001][1001];
      // start at the center, (500,500)
      int x = 500;
      int y = 500;
      int n = 1;
      array[x][y] = n++;
      for (int idx = 1; idx < 501; idx++)
      {
         // move to the right
         array[++x][y] = n++; 
         // move down
         for (int ii = 0; ii < idx*2-1; ii++)
         {
            array[x][--y] = n++;
         }
         // move left
         for (int ii = 0; ii < idx*2; ii++)
         {
            array[--x][y] = n++;
         }
         // move up
         for (int ii = 0; ii < idx*2; ii++)
         {
            array[x][++y] = n++;
         }
         // move right
         for (int ii = 0; ii < idx*2; ii++)
         {
            array[++x][y] = n++;
         }
      }
      // add it all up!
      long sum = -1; // 1 will be counted twice
      for (int ii = 0; ii < 1001; ii++)
      {
         sum += array[ii][ii];
         sum += array[ii][1000-ii];
      }
      return sum;
   }
   
   /**
    * We start with the center block of 1. Then, we notice that (unsurprisingly because
    * we're building a square), one corner is always the perfect square of an odd number
    * that increases by two each time. 1, 9, 25, etc. This is because the first square is
    * size 1, the second is size 8, the next is size 16, the next 24, 32, etc. A side 
    * increases its length by 2 each time we cycle out, so the largest corner number is
    * really the /area/ of the interior, which is the length of a side squared.
    * The other corners simply are subtractions from that highest number by the size of
    * the spiral we're currently on by n-1 each. And a 1001 spiral means we're on layer 500 
    * of the spiral so we just need to count. 
    */
   private long faster()
   {
      long sum = 1L;
      // skip 1 since it's obviously 1
      for (int ii = 3; ii <= 1001; ii+=2) {
         // sum of the corners is
         // n^2
         // n^2 - (n-1)
         // n^2 - 2(n-1)
         // n^2 - 3(n-1)
         // totaling 4n^2-6n+6
         sum += 4*ii*ii - 6*ii + 6;
      }
      return sum;
   }

}
