#include <string>
#include "../../base/problem.h"
#include "../../util/basic.h"

/**
 * P001<br>
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.<br>
 * Find the sum of all the multiples of 3 or 5 below 1000.<br>
 * Ans: 233168
 */
class P001: public Problem
{
   public:
      P001()
      {
         problem_number = 1;
         variations = 3;
      }
      ~P001()
      {
      }

      std::string execute(int variation)
      {
         switch (variation)
         {
            case 0:
               return to_string(brute());
            case 1:
               return to_string(multiples());
            case 2:
            case -1:
               return to_string(closedForm());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:
      const static int max = 999; // use 999999 for a better differentiator of times

      int brute()
      {
         int start = 1;
         int sum = 0;
         for (int ii = start; ii <= max; ii++)
         {
            if (ii % 3 == 0 || ii % 5 == 0)
            {
               sum += ii;
            }
         }
         return sum;
      }

      /**
       * A slightly faster implementation. We don't check every single number, but don't have an easy way to skip previously added numbers.
       * @return
       */
      int multiples()
      {
         int sum = 0;
         for (int ii = 5; ii <= max; ii += 5)
         {
            sum += ii;
         }
         for (int ii = 3; ii <= max; ii += 3)
         {
            if (ii % 5 != 0)
            {
               sum += ii;
            }
         }
         return sum;
      }

      /**
       * Note that the sum from 1 to n is n(n+1)/2. In this case, we sum from 3 to 1000, or better yet,
       * from 3*(1 -> 333), as well as from 5*(1 -> 199) {note ... < 1000). Then we subtract items that are multiples.
       * That's 15, 30, 45, etc ... or 15*(1 -> 66). To make this more adaptable, we'll compute the highest
       * number
       */
      int closedForm()
      {
         int high_3 = max / 3;
         int high_5 = max / 5;
         int high_15 = max / 15;

         int total = 0;
         // add the 3's
         total += 3 * basic::n_sum(high_3);
         // add the 5's
         total += 5 * basic::n_sum(high_5);
         // subtract the 15's
         total += -15 * basic::n_sum(high_15);
         return total;
      }
};
