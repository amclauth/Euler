#include "../../base/problem.h"

#include <string>

/**
 * P009<br>
 * A Pythagorean triplet is a set of three natural numbers, a  b  c, for which,<br>
 * a^2 + b^2 = c^2<br>
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.<br>
 * There exists exactly one Pythagorean triplet for which a + b + c = 1000.<br>
 * Find the product abc.<br>
 * Ans: 31875000
 */
class P009: public Problem
{
   public:
      P009()
      {
         problem_number = 9;
         variations = 2;
      }
      ~P009()
      {
      }

      std::string execute(int variation)
      {
         switch (variation)
         {
            case 0:
               return to_string(bruteForce());
            case 1:
            case -1:
               return to_string(optimized());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:

      /**
       * Just check every set of numbers!
       * @return
       */
      int bruteForce()
      {
         // doing pure brute force
         for (int ii = 1; ii < 1000; ii++)
         {
            // jj must be > ii and less than 1000-ii (actually, less than
            // 1000 - ii - jj - 1 since kk must be > jj)
            for (int jj = ii + 1; jj < 1000 - ii; jj++)
            {
               int kk = 1000 - ii - jj;
               if (ii * ii + jj * jj == kk * kk)
               {
                  return ii * jj * kk;
               }
            }
         }
         return -1;
      }

      /**
       * We might not have to hunt for out second term:
       * ii^2 + x^2 = (1000-ii-x)^2 = 1000^2 + ii^2 + x^2 - 2000ii - 2000x - 2ii*x
       * 0 = 1000^2 - 2000ii - 2000x - 2iix
       * 2000ii - 1000^2 = -x(2000 - 2ii)
       * 1000^2 - 2000ii / 2000 - 2ii = x
       * 500*1000 - 1000ii / 1000 - ii = x
       * @return
       */
      int optimized()
      {
         for (int ii = 1; ii < 1000; ii++)
         {
            int jj = (500 * 1000 - 1000 * ii) / (1000 - ii);
            int kk = 1000 - ii - jj;
            if (ii * ii + jj * jj == kk * kk)
            {
               return ii * jj * kk;
            }
         }
         return -1;
      }
};
