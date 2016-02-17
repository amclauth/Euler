#include "../../base/problem.h"

#include <cmath>

/**
 * P025<br>
 * The Fibonacci sequence is defined by the recurrence relation:
 * Fn = Fn1 + Fn2, where F1 = 1 and F2 = 1.
 * Hence the first 12 terms will be:
 * F1 = 1
 * F2 = 1
 * F3 = 2
 * F4 = 3
 * F5 = 5
 * F6 = 8
 * F7 = 13
 * F8 = 21
 * F9 = 34
 * F10 = 55
 * F11 = 89
 * F12 = 144
 * The 12th term, F12, is the first term to contain three digits.
 * What is the first term in the Fibonacci sequence to contain 1000 digits?
 * Ans: 4782
 */
class P025: public Problem
{
   public:
      P025()
      {
         problem_number = 25;
         variations = 2;
      }
      ~P025()
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
               return to_string(faster());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:

      /**
       * Do fibonnaci in arrays to do long number addition
       */
      long bruteForce()
      {
         // initialize the fibonacci numbers in arrays
         int prev[1000] = {};
         int next[1000] = {};
         int tmp[1000] = {};
         prev[0] = 1;
         next[0] = 1;
         int count = 2; // 1 and 2 are both 1
         while (next[999] == 0)
         {
            for (int ii = 0; ii < 1000; ii++)
            {
               tmp[ii] = prev[ii];
               prev[ii] = next[ii];
            }
            count++;
            for (int ii = 0; ii < 1000; ii++)
            {
               next[ii] += tmp[ii];
               while (next[ii] >= 10)
               {
                  next[ii+1]++;
                  next[ii] -= 10;
               }
            }
         }
         return count;
      }

      /**
       * the nth fibonnaci is (phi^n - pho^n)/sqrt(5) where phi is (1+sqrt(5))/2 and
       * pho is (1-sqrt(5))/2. It can also be represented as the nearest number to
       * phi^n/sqrt(5). So we simply need the first n where that answer is >= 10^1000:
       * log10(phi^n/sqrt(5) = 1000
       * log10(phi^n) - log10(sqrt(5)) = 1000
       * n log10(phi) - log10(sqrt(5)) = 1000
       * n = (1000 + log10(sqrt(5))) / log10(phi)
       */
      long faster()
      {
         double phi = (1+sqrt(5))/2.0;

         int num = (int) ((999.0 + log10(sqrt(5))) / log10(phi) + 0.5);
         return num;
      }
};
