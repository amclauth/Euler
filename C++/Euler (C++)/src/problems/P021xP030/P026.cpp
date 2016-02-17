#include "../../base/problem.h"
#include "../../util/prime.h"

#include <set>
#include <vector>

/**
 * P026<br>
 * A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:
 * 1/2   =  0.5
 * 1/3   =  0.(3)
 * 1/4   =  0.25
 * 1/5   =  0.2
 * 1/6   =  0.1(6)
 * 1/7   =  0.(142857)
 * 1/8   =  0.125
 * 1/9   =  0.(1)
 * 1/10  =  0.1
 * Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.
 * Find the value of d  1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
 * Ans: 983
 */
class P026: public Problem
{
   public:
      P026()
      {
         problem_number = 26;
         variations = 2;
      }
      ~P026()
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
       * Look for the first repeating remainder, since that remainder will tell us the length of
       * repetition of the decimal for a 1/x number
       */
      long bruteForce()
      {
         int greatest = 0;
         int longest = 0;
         for (int divisor = 2; divisor < 1000; divisor++) {
            std::set<int>* remainders = new std::set<int>();
            int n = 1;
            while (n != 0) {
               bool found = false;
               while (divisor > n)
               {
                  n *= 10;
                  std::set<int>::iterator loc = remainders->find(n); //std::find(remainders->begin(), remainders->end(), n);
                  if (loc != remainders->end())
                  {
                     int count = remainders->size() - *loc;
                     if (count > greatest)
                     {
                        greatest = count;
                        longest = divisor;
                     }
                     found = true;
                     break;
                  }
                  remainders->insert(n);
               }
               if (found)
               {
                  break;
               }
               int d = n / divisor;
               n = n - d * divisor;
            }
            delete remainders;
         }
         return longest;
      }

      /**
       * We know that any multiple of a divisor has the same number of repeating decimals. So we only need
       * to check prime numbers (since there's also only one "greatest" per the question, there's only one
       * maximum here, no multiples ... we could use that to limit the search from 500 to 1000, but I'll keep
       * this more general).
       *
       * From Wikipedia, we know that the period of the repeating decimal of 1/p where p is a prime is equal
       * to the order of 10 % p
       */
      long faster()
      {
         std::vector<int>* primes = prime::EratosthenesPrimesUpTo(1000);

         int greatestLength = 0;
         int longest = 0;
         for (int idx = primes->size() - 1; idx >= 0; idx--)
         {
            int divisor = primes->at(idx);
            if (greatestLength > 0 && divisor - 1 < greatestLength)
            {
               // done because the largest it can get is p-1 now
               break;
            }
            // d is the order of 999....999 where a cycle is first produced, so
            // rather than trying 10^99 or more, we can do long division by
            // nines rather than tens
            int d = 1;
            int n = 9;
            while (n != 0)
            {
               if (divisor > n)
               {
                  n = n*10 + 9;
                  d++;
                  continue;
               }
               n = n % divisor;
            }
            if (d > greatestLength)
            {
               greatestLength = d;
               longest = divisor;
            }
         }

         delete primes;
         return longest;
      }
};
