#include <math.h>
#include <string>
#include <vector>

#include "../../util/basic.h"
#include "../../base/problem.h"

/**
 * P004<br>
 * A palindromic number reads the same both ways. The largest palindrome made<br>
 * from the product of two 2-digit numbers is 9009 = 91 99.<br>
 * Find the largest palindrome made from the product of two 3-digit numbers.<br>
 * Ans: 906609
 */
class P004: public Problem
{
   public:
      P004()
      {
         problem_number = 4;
         variations = 2;
      }
      ~P004()
      {
      }

      std::string execute(int variation)
      {
         switch (variation)
         {
            case 0:
               return to_string(brute());
            case -1:
            case 1:
               return to_string(decreasingSearch());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:

      /**
       * This is the brute force attempt. Just multiply all 3 digit numbers and
       * check if they're palindromic
       * @return
       */
      int brute()
      {
         int max = 0;
         for (int n1 = 100; n1 < 1000; n1++)
         {
            for (int n2 = 100; n2 < 1000; n2++)
            {
               int ans = n1 * n2;
               if (basic::isPalindrome(ans) && ans > max)
                  max = ans;
            }
         }
         return max;
      }

      /**
       * Check to see if decreasing numbers are the answer
       * @return
       */
      int decreasingSearch()
      {
         int lb = 100 * 100;
         int ub = 999 * 999;

         for (int ii = ub; ii >= lb; ii--)
         {
            // check if it's a palindrome
            if (basic::isPalindrome(ii))
            {
               // check if it's factorable
               if (isThreesMultiple(ii) != 0)
                  return ii;
            }
         }
         return 0;
      }

      /**
       * if we find a factor of three digits, the other multiple (because of our bounds)
       * must also be three digits. We start at the square root
       * of the number since it can't be lower and be a multiple.
       * @param num
       * @return
       */
      int isThreesMultiple(int num)
      {
         int factor = (int) sqrt(num);
         while (factor < 1000)
         {
            if (num / factor <= 100)
               return 0; // always less than 3 digits as factor increases
            if (num % factor == 0)
            {
               return factor;
            }
            factor++;
         }
         return 0;
      }

};
