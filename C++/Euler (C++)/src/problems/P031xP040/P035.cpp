#include "../../base/problem.h"
#include "../../util/prime.h"

#include <vector>

/**
 * P035<br>
 * The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
 * There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
 * How many circular primes are there below one million?
 * Ans: 55
 */
class P035: public Problem
{
   public:
      P035()
      {
         problem_number = 35;
         variations = 2;
      }
      ~P035()
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
       * I think we can get the primes in an efficient way and then just test them all
       */
      long bruteForce()
      {
         int total = 0;
         std::vector<int>* primes = prime::EratosthenesPrimesUpTo(1000000);
         for (std::vector<int>::iterator it = primes->begin(); it != primes->end(); ++it)
         {
            int p = *it;
            int next = rotateRight(p);
            bool isCircular = true;
            while (next != p)
            {
               if (!prime::isPrime(next))
               {
                  isCircular = false;
                  break;
               }
               next = rotateRight(next);
            }
            if (isCircular)
            {
               total++;
            }
         }
         delete primes;
         return total;
      }

      int rotateRight(int num)
      {
         int i = num % 10;
         int j = (int) (num/10);
         int size = 1;
         while (j >= size)
            size *= 10;
         j += size * i;
         return j;
      }

      /**
       * Keeping track of which primes are good and bad didn't work well. Took almost a full
       * second instead of 40ms. So instead, let's look at the digits. Ignore anything that
       * has an even number or a 5 in it
       */
      long faster()
      {
         int total = 0;
         std::vector<int>* primes = prime::EratosthenesPrimesUpTo(1000000);
         for (std::vector<int>::iterator it = primes->begin(); it != primes->end(); ++it)
         {
            int p = *it;
            if (p >= 10)
            {
               if (!checkDigits(p))
                  continue;
            }
            int next = rotateRight(p);
            bool isCircular = true;
            while (next != p)
            {
               if (!prime::isPrime(next))
               {
                  isCircular = false;
                  break;
               }
               next = rotateRight(next);
            }
            if (isCircular)
            {
               total++;
            }
         }
         delete primes;
         return total;
      }

      bool checkDigits(int p)
      {
         while (p != 0)
         {
            int n = p % 10;
            if (n % 2 == 0 || n % 5 == 0)
               return false;
            p = p / 10;
         }
         return true;
      }
};
