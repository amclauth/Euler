#include "../../base/problem.h"
#include "../../util/basic.h"

#include <vector>
#include <string>
#include <sstream>
#include <cmath>

/**
 * P036<br>
 * The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.
 * Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
 * (Please note that the palindromic number, in either base, may not include leading zeros.)
 * Ans: 872187
 */
class P036: public Problem
{
   public:
      P036()
      {
         problem_number = 36;
         variations = 3;
      }
      ~P036()
      {
      }

      std::string execute(int variation)
      {
         switch (variation)
         {
            case 0:
               return to_string(bruteForce());
            case 1:
               return to_string(faster());
            case 2:
            case -1:
            	return to_string(fastest());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:

      /**
       * Check all numbers less than 1 million!
       */
      long bruteForce()
      {
         int total = 0;
         for (int ii = 1; ii < 1000000; ii++)
         {
            if (basic::isPalindrome(ii))
            {
               // get the base 2 representation
               std::ostringstream oss;
               int num = ii;
               while (num != 0)
               {
                  oss << (num % 2);
                  num = num / 2;
               }
               if (basic::isPalindrome(oss.str()))
               {
                  total += ii;
               }
            }
         }
         return total;
      }

      /**
       * Only need to check odd numbers because if it ends in a 0, it won't start with a 0, also
       * one million is 11110100001001000000 in base 2, a 20 digit number. Any base 2 palindrome
       * (or others) can be defined by only the first half of the palindrome. So we can use 10
       * digit numbers and create palindromes from them. This is only 512*2 numbers (times 2
       * because we have to check the 20 digit number and the 19 digit number as palindromes)
       */
      long faster()
      {
      	int total = 0;
         int arr[10] = {};
         arr[0] = 1;
         for (int ii = 0; ii < 512; ii++)
         {
            for (int jj = 2; jj < 10; jj++)
            {
               if (arr[jj-1] > 1)
               {
                  arr[jj]++;
                  arr[jj-1]-=2;
               }
            }
            int gsd = 0;
            for (int jj = 0; jj < 10; jj++)
            {
               if (arr[jj] == 1)
                  gsd = jj;
            }
            // we can have lots of palindromic numbers from, let's say, 101 as a base
            // 101101
            // 10101
            // 10100101
            // 101000000101, etc
            for (int kk = gsd; kk < 10; kk++)
            {
               // now get the decimal number. First, the lower half in order
                  int dec = 0;
                  int mult = 1;
                  int size = kk;
                  for (int jj = 0; jj <= size; jj++)
                  {
                     if (arr[jj] == 1)
                        dec += mult;
                     mult *= 2;
                  }
                  int dec19 = dec;
                  int dec20 = dec;
                  int multTmp = mult;
                  for (int jj = size; jj >= 0; jj--)
                  {
                     if (arr[jj] == 1)
                        dec20 += mult;
                     mult *= 2;
                  }
                  mult = multTmp;
                  for (int jj = size - 1; jj >= 0; jj--)
                  {
                     if (arr[jj] == 1)
                        dec19 += mult;
                     mult *= 2;
                  }
                  if (dec20 < 1000000)
                  {
                     if (basic::isPalindrome(dec20))
                     {
                        total += dec20;
                     }
                  }
                  if (basic::isPalindrome(dec19))
                  {
                     total += dec19;
                  }
            }

            arr[1]++;
         }
         return total;
      }

      /**
		 * Same as above, but discover the half rather than cycle through to find it
		 */
      long fastest()
		{
			int total = 0;
			for (int ii = 1; ii < 1024; ii+=2)
			{
				int bits[10] = { 0 };
				int l = 0;
				int n = ii;
				while (n != 0)
				{
					bits[l++] = n % 2;
					n = n/2;
				}

				for (int l2 = l; l2 <= 10; l2++) // add in zeros in between
				{
					int even = 0;
					int odd = 0;
					for (int jj = 0; jj < l2; jj++)
					{
						even = even * 2 + bits[jj];
					}
					odd = even / 2;
					for (int jj = l2-1; jj >= 0; jj--)
					{
						even = even * 2 + bits[jj];
						odd = odd * 2 + bits[jj];
					}

					if (basic::isPalindrome(even))
					{
						total += even;
					}
					if (basic::isPalindrome(odd))
					{
						total += odd;
					}
				}
			}
			return total;
		}
};
