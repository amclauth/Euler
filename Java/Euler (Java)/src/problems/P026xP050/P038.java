package problems.P026xP050;

import util.Basic;
import base.Problem;

/**
 * P038<br>
 * Take the number 192 and multiply it by each of 1, 2, and 3:
 * 192  1 = 192
 * 192  2 = 384
 * 192  3 = 576
 * By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)
 * The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated 
 * product of 9 and (1,2,3,4,5).
 * What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) where n  1?
 * Ans: 932718654 
 * @return
 */
public class P038 extends Problem
{
   public P038()
   {
      problemNumber = 38;
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
    * Check all numbers! Don't need to check past 4 digit numbers because n must be
    * greater than 1. If 4, we'd have two 4 digit numbers (or a 4 and 5 digit!), if 
    * 5, we'd have a minimum of two five digit numbers, which is too large.
    * @return
    */
   private long bruteForce()
   {
   	long max = 0;
   	for (int num = 1; num < 10000; num++)
   	{
   		String pan = "";
   		for (int ii = 1; ii < 10; ii++)
   		{
   			pan += ii * num;
   			if (pan.length() > 9)
   				break;
   			else if (pan.length() == 9)
   			{
   				if (Basic.isPandigital(pan))
   				{
   					long pan_l = Long.valueOf(pan);
   					if (pan_l > max)
   					{
   						max = pan_l;
   					}
   				}
   			}
   		}
   	}
   	return max;
   }
   
   /**
    * This one bears looking at more closely. We know the answer is greater than 918273645, so
    * the number must start with a 9 (since it'll get multiplied by 1). A two digit number (90->99)
    * will be a two digit number followed by three digit numbers for either 8 or 11 digits. A
    * three digit number will be a three digit followed by four digit numbers, meaning 7 or 11 digits.
    * A four digit number will be four followed by five digits. Anything over four digits can't repeat.
    * So we're looking for a number that starts with 9, is a 4 digit number, and uses n=(1..2).
    * 
    * Two times any number starting with 9 will result in an 18 or 19 as the first digits of the next
    * sequence. Obviously anything over 18 won't work (since we already have a 9), so our number now must
    * be less than 9500 and cannot contain a 1 or 8.
    * 
    * We can't use any 94xx numbers because that would result in a 188.. We're now down to 9[2-3][2-7][2-7]
    * 
    * We want the highest possible, so we could count down and the first number we find that works would
    * be it, because it's the number times 1 first 
    * @return
    */
   private long faster()
   {
   	int total = 0;
   	// starting is 9376
   	for (int a : new int[] {3,2})
   	{
   		for (int b : new int[] {7,6,5,4,3,2})
   		{
   			if (b == a)
   				continue;
   			for (int c : new int[] {7,6,5,4,3,2})
   			{
   				if (c == b || c == a)
   					continue;
   				int digit = 9000 + 100*a + 10*b + c;
   				if (Basic.isPandigital(digit,digit*2))
   				{
   					return Long.valueOf(digit) * 100000L + digit*2;
   				}
   			}
   		}
   	}
   	return total;
   }
}
