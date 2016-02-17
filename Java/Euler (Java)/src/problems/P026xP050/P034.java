package problems.P026xP050;

import java.util.Arrays;

import base.Problem;

/**
 * P034<br>
 * 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
 * Find the sum of all numbers which are equal to the sum of the factorial of their digits.
 * Note: as 1! = 1 and 2! = 2 are not sums they are not included.
 * Ans: 40730 
 * @return
 */
public class P034 extends Problem
{
   public P034()
   {
      problemNumber = 34;
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
    * We need an upper bound to define this problem. 9! is 362880. 7*9! is 2540160,
 	 * so 9999999 cannot be included in this, but 7 digit numbers less than 2540160
 	 * can still be represented. Any 8 digit number is then larger than 8*9!, so no
 	 * 8 digit numbers or higher can be included.
    * @return
    */
   private long bruteForce()
   {
   	int total = 0;
   	int[] facts = new int[10];
   	facts[0] = 1;
   	for (int idx = 1; idx < 10; idx++)
   	{
   		facts[idx] = facts[idx-1] * idx;
   	}
   	for (int num = 3; num <= 2540160; num++)
   	{
   		int ii = num;
   		int sum = 0;
   		while (ii != 0)
   		{
   			sum += facts[ii % 10];
   			ii = ii / 10;
   		}
   		if (sum == num)
   		{
   			total += sum;
   		}
   	}
   	return total;
   }
   
   /**
    * We only care about combinations of numbers. 145 is correct, but we don't
    * have to then also check 514, 415, etc.
    * @return
    */
   private long faster()
   {
   	int total = -3; // remove 0, 1, and 2
   	int[] facts = new int[10];
   	facts[0] = 1;
   	for (int idx = 1; idx < 10; idx++)
   	{
   		facts[idx] = facts[idx-1] * idx;
   	}
   	int[] nums = {0,0,0,0,0,0,0};
   	// this will go up to 299999 (which also includes 9999992), which is too far, but
   	// the easiest limit to set overall
   	for (nums[0] = 0; nums[0] <= 2; nums[0]++)
   	{
   		for (nums[1] = nums[0]; nums[1] <= 9; nums[1]++)
   		{
   			for (nums[2] = nums[1]; nums[2] <= 9; nums[2]++)
   			{
   				for (nums[3] = nums[2]; nums[3] <= 9; nums[3]++)
      			{
   					for (nums[4] = nums[3]; nums[4] <= 9; nums[4]++)
   	   			{
   						for (nums[5] = nums[4]; nums[5] <= 9; nums[5]++)
   		   			{
   							for (nums[6] = nums[5]; nums[6] <= 9; nums[6]++)
   			   			{
   			   				// nums are now in sorted order
   								int sum = 0;
   								int zeros = 0;
   								for (int ii = 0; ii < nums.length; ii++)
   								{
   									sum += facts[nums[ii]];
   									if (nums[ii] == 0)
   									{
   										zeros++;
   									}
   								}
   								// any number of zeros could be included
   								for (int z = 0; z <= zeros; z++)
   								{
   									int[] newnum = new int[nums.length];
      								int idx = 0;
      								int mySum = sum - z;
      								int myZeros = 0;
      								while (mySum != 0)
      								{
      									newnum[idx++] = mySum % 10;
      									if (mySum % 10 == 0)
      									{
      										myZeros++;
      									}
      									mySum = mySum / 10;
      								}
      								// check if the number of zeros we're factoring out, plus the 
      								// number in the answer is equal to the total zeros in the array
      								if (myZeros + z != zeros)
      								{
      									continue;
      								}
      								Arrays.sort(newnum);
      								boolean found = true;
      								for (int ii = 0; ii < nums.length; ii++)
      								{
      									if (newnum[ii] != nums[ii])
      									{
      										found = false;
      										break;
      									}
      								}
      								if (found)
      								{
      									total += sum - z;
      								}
   								}
   			   			}
   		   			}
   	   			}
      			}
   			}
   		}
   	}
   	
   	return total;
   }
}
