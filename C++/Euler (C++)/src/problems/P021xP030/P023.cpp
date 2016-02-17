#include "../../base/problem.h"
#include "../../util/basic.h"

#include <vector>

/**
 * P023<br>
 * A perfect number is a number for which the sum of its proper divisors is
 * exactly equal to the number. For example, the sum of the proper divisors of
 * 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
 * A number n is called deficient if the sum of its proper divisors is less than
 * n and it is called abundant if this sum exceeds n. As 12 is the smallest
 * abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be
 * written as the sum of two abundant numbers is 24. By mathematical analysis,
 * it can be shown that all integers greater than 28123 can be written as the
 * sum of two abundant numbers. However, this upper limit cannot be reduced any
 * further by analysis even though it is known that the greatest number that
 * cannot be expressed as the sum of two abundant numbers is less than this
 * limit. Find the sum of all the positive integers which cannot be written as
 * the sum of two abundant numbers. Ans: 4179871
 */
class P023: public Problem
{
   public:
      P023()
      {
         problem_number = 23;
         variations = 2;
      }
      ~P023()
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
       * Try to use boolean arrays to keep track of which numbers are abundant, then
       * which numbers can be sums of them.
       */
      long bruteForce()
      {
         const int size = 28123;

         long sum = 0;
         bool abundant[28123] = {false};
         bool expressable[28123] = {false};
         for (int ii = 0; ii < size; ii++)
         {
            long num = 0;
            std::vector<long>* divisors = basic::getDivisors(ii);
            for (std::vector<long>::iterator it = divisors->begin(); it != divisors->end(); ++it)
            {
               num += *it;
            }
            if (num > ii + ii)
            {
               abundant[ii] = true;
            }
            delete divisors;
         }

         for (int ii = 0; ii < size; ii++)
         {
            for (int jj = ii; jj < size - ii; jj++)
            {
               if (abundant[ii] && abundant[jj])
               {
                  expressable[ii+jj] = true;
               }
            }
         }

         for (int ii = 0; ii < size; ii++)
         {
            if (!expressable[ii])
            {
               sum += ii;
            }
         }

         return sum;
      }

      /**
       * Since there are not so many abundant number, use a list and only
       * iterate over those in the list!
       */
      long faster()
      {
         const int size = 28123;

         std::vector<long>* abundants = new std::vector<long>();
         for (int ii = 12; ii < size - 12; ii++)
         {
            long sum = 0;
            std::vector<long>* divisors = basic::getDivisors(ii);
            for (std::vector<long>::iterator it = divisors->begin(); it != divisors->end(); ++it)
            {
               sum += *it;
            }
            if (sum > ii + ii)
            {
               abundants->push_back(ii);
            }
            delete divisors;
         }

         // tried using a set here, but /most/ numbers are expressable, and
         // the set operation itself adds a lot. Plus, checking the non-set
         // later takes longer.
         bool expressable[size] = {false};
         for (unsigned int ii = 0; ii < abundants->size(); ii++)
         {
            for (unsigned int jj = 0; jj <= ii; jj++)
            {
               int n = abundants->at(ii) + abundants->at(jj);
               if (n < size)
                  expressable[n] = true;
               else
                  break;
            }
         }

         long sum = 0;
         for (int ii = 0; ii < size; ii++)
         {
            if (!expressable[ii])
               sum += ii;
         }
         return sum;
      }
};
