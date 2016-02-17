#include "../../base/problem.h"
#include "../../util/basic.h"

#include <string>
#include <vector>
#include <map>

#include <iostream>

/**
 * P021<br>
 * Let d(n) be defined as the sum of proper divisors of n (numbers less than n
 * which divide evenly into n). If d(a) = b and d(b) = a, where a b, then a and
 * b are an amicable pair and each of a and b are called amicable numbers. For
 * example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55
 * and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71
 * and 142; so d(284) = 220. Evaluate the sum of all the amicable numbers under
 * 10000. Ans: 31626
 */
class P021: public Problem
{
   public:
      P021()
      {
         problem_number = 21;
         variations = 4;
      }
      ~P021()
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
               return to_string(cache());
            case 3:
            case -1:
               return to_string(sieve());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:

      /**
       *
       */
      int bruteForce()
      {
         int sum = 0;
         for (int ii = 0; ii < 10000; ii++)
         {
            int an = basic::getAmicableNumber(ii);
            if (an > 0)
               sum += an;
         }
         return sum;
      }

      /**
       * Only re-check numbers that are above the number we've checked ... adding
       * both sums immediately
       */
      long faster()
      {
         int sum = 0;
         std::vector<long>* divisors;
         for (int ii = 2; ii < 10000; ii++)
         {
            int nsum = 0;
            divisors = basic::getDivisors(ii);
            for (unsigned int jj = 0; jj < divisors->size() - 1; jj++)
            {
               nsum += divisors->at(jj);
            }
            if (nsum > ii)
            {
               int msum = 0;
               divisors = basic::getDivisors(nsum);
               for (unsigned int jj = 0; jj < divisors->size() - 1; jj++)
               {
                  msum += divisors->at(jj);
               }
               if (msum == ii)
               {
                  sum += ii + nsum;
               }
            }
         }
         return sum;
      }

      /**
       * Tried using prime factorization to get divisor sums, but that's actually
       * slower (by almost double). The cache also doesn't speed it up noticeably
       * (seems to slow it down, in fact).
       */
      long cache()
      {
         // List<Integer> primes = Primes.ErosPrimesUpTo(12000);
         std::map <int,int> cache;
         int total = 0;
         std::vector<long>* divisors;
         for (int ii = 2; ii < 10000; ii++)
         {
            int nsum = 0;
            if (cache.find(ii) == cache.end())
            {
               divisors = basic::getDivisors(ii);
               for (unsigned int jj = 0; jj < divisors->size() - 1; jj++)
               {
                  nsum += divisors-> at(jj);
               }

               cache[ii] = nsum;
            } else {
               nsum = cache[ii];
            }

            if (nsum > ii)
            {
               int msum = 0;
               if (cache.find(nsum) == cache.end())
               {
                  msum = 0;
                  divisors = basic::getDivisors(nsum);
                  for (unsigned int jj = 0; jj < divisors->size() - 1; jj++)
                  {
                     msum += divisors->at(jj);
                  }

                  cache[nsum] = msum;
               } else {
                  msum = cache[nsum];
               }

               if (msum == ii)
               {
                  total += ii + nsum;
               }
            }
         }
         return total;
      }

      /**
       * I wish I'd thought of this. Use a sieve to discover the divisor sums!
       */
      int sieve()
      {
         const int length = 10000;
         int divSum[length] = { }; // realized this will initialize to zero!

         // for each i
         for (int i = 1; i < length; i++)
         {
            // take j = 2i (so we know it's divisible), then keep adding i to j and to divSum[j]
            // so that all j's that are divisible by i*x have had i added to them. Doesn't include
            // the last number (itself)
            for (int j = i + i; j < length; j += i)
            {
               // d[1] = 0
               // d[2] = 1
               // d[3] = 1
               // d[4] = 1 + 2
               // d[5] = 1
               // d[6] = 1 + 2 + 3
               // d[7] = 1
               // d[8] = 1 + 2 +     4
               // d[9] = 1 +     3
               // d[10]= 1 + 2 +         5
               divSum[j] += i;
            }
         }

         int total = 0;
         // now, for every i, if divSum is within bounds, if it and it's reciprocal both are
         // equal, it's an amicable number combo! Add it twice (because we want the sum of
         // divisors not including itself, plus itself)
         for (int i = 1; i < length; i++)
         {
            if (divSum[i] < length && divSum[i] > i && divSum[divSum[i]] == i)
            {
               total += divSum[i] + i;
            }
         }

         return total;
      }
};
