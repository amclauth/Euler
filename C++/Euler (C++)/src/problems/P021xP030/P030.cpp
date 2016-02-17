#include "../../base/problem.h"

#include <vector>
#include <algorithm>
#include <cmath>

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
 */
class P030: public Problem
{
   public:
      P030()
      {
         problem_number = 30;
         variations = 2;
      }
      ~P030()
      {
      }

      std::string execute(int variation)
      {
         switch (variation)
         {
            case 0:
               return to_string(bruteForce());
            case -1:
            case 1:
               return to_string(faster());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:

      /**
       * Use all powers of five in an array and know that the upper limit is six digits that
       * are nines (after six digits, the sum of powers can never be the same order as the
       * digit itself). Then just check every number.
       */
      long bruteForce()
      {
         long rval = 0L;
         int powers[] = {0,1,2*2*2*2*2,3*3*3*3*3,4*4*4*4*4,5*5*5*5*5,6*6*6*6*6,
               7*7*7*7*7,8*8*8*8*8,9*9*9*9*9};
         int upper = (int)pow(9,5) * 6;
         // ignoring non sums
         for (int ii = 10; ii < upper; ii++) {
            int num = ii;
            int sum = 0;
            while (num > 0) {
               sum += powers[num % 10];
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
      long faster()
      {
         int rval = -1; // 1 is not included in the sum
         int pow[] = {0,1,2*2*2*2*2,3*3*3*3*3,4*4*4*4*4,5*5*5*5*5,6*6*6*6*6,
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
                           std::vector<int> split;
                           while (n != 0)
                           {
                              split.push_back(n % 10);
                              n = n / 10;
                           }
                           // now check that a through f are in the array ... zeros can be anywhere
                           split.push_back(0);

                           std::vector<int>::iterator it = std::find(split.begin(), split.end(), a);
                           if (it != split.end())
                              *it = 0;
                           else
                              continue; // no a

                           it = std::find(split.begin(), split.end(), b);
                           if (it != split.end())
                              *it = 0;
                           else
                              continue; // no b

                           it = std::find(split.begin(), split.end(), c);
                           if (it != split.end())
                              *it = 0;
                           else
                              continue; // no c

                           it = std::find(split.begin(), split.end(), d);
                           if (it != split.end())
                              *it = 0;
                           else
                              continue; // no d

                           it = std::find(split.begin(), split.end(), e);
                           if (it != split.end())
                              *it = 0;
                           else
                              continue; // no e

                           it = std::find(split.begin(), split.end(), f);
                           if (it != split.end())
                              *it = 0;
                           else
                              continue; // no f

                           // if the list isn't all zero's now, it's not a match
                           bool match = true;
                           for (unsigned int ii = 0; ii < split.size(); ii++)
                           {
                              if (split[ii] != 0)
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
};
