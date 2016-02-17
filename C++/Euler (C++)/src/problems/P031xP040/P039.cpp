#include "../../base/problem.h"

/**
 * P039<br>
 * If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.
 * {20,48,52}, {24,45,51}, {30,40,50}
 * For which value of p <= 1000, is the number of solutions maximized?
 * Ans: 840
 */
class P039: public Problem
{
   public:
      P039()
      {
         problem_number = 39;
         variations = 2;
      }
      ~P039()
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
       * Check all possible values to see if they're triangles
       */
      long bruteForce()
      {
         int max = 0;
         int p = 0;
         for (int ii = 3; ii <= 1000; ii++)
         {
            int count = 0;
            for (int a = 1; a <= ii-2; a++)
            {
               for (int b = 1; b <= ii-a-1; b++)
               {
                  int c = ii - a - b;
                  if (a*a+b*b == c*c)
                  {
                     // this is a solution!
                     count++;
                  }
               }
            }
            if (count > max)
            {
               p = ii;
               max = count;
            }
         }
         return p;
      }

      /**
       * Check only values that /can/ solve the a^2 + b^2 = c^2 equation. Also, for the perimeter,
       * we know that if a and b are even, then c will be even and p will be even. If a and b are
       * odd, then c will be even and p will be even, if one is even and the other is odd, c will
       * be odd and p will be even. So we only need to check even numbers of p.
       */
      long faster()
      {
         int max = 0;
         int maxnum = 0;
         for (int size = 4; size <= 1000; size+=2)
         {
            int count = 0;
            for (int a = 1; a <= size - 2; a++)
            {
               // we can increase b by an amount related to c ...
               // a^2 + b^2 = c^2
               // a + b + c = p
               // a^2 + b^2 = (p - b - a)^2
               // a^2 + b^2 = p^2 - pb - pa - pb + b^2 + ba - pa + ab + a^2
               // 0 = p^2 - pb - pa + 2ba
               // (2pa - p^2) / (2a - 2p) = b;
               int b = (2*size*a - size*size) / (2*a - 2*size);
               int c = size - a - b;
               if (b < 1 || c < 1)
                  continue;
               int left = a*a + b*b;
               int right = c*c;
               if (left == right)
               {
                  count++;
               }
            }
            if (count > max)
            {
               max = count;
               maxnum = size;
            }
         }
         return maxnum;
      }
};
