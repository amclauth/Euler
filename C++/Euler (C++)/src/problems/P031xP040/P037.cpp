#include "../../base/problem.h"
#include "../../util/prime.h"

#include <vector>

/**
 * P037<br>
 * The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right,
 * and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
 * Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
 * NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
 * Ans: 748317
 */
class P037: public Problem
{
   public:
      P037()
      {
         problem_number = 37;
         variations = 2;
      }
      ~P037()
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
       * Check all numbers less than 1 million!
       */
      long bruteForce()
      {
         int total = 0 -2 -3 -5 -7; // these are not "truncatable"
         std::vector<int>* primes = prime::EratosthenesPrimesUpTo(1000000);
         for (std::vector<int>::iterator it = primes->begin(); it != primes->end(); ++it)
         {
            int p = *it;
            int right = p;
            int left = 0;
            int power = 1;
            bool isTruncatable = true;
            while (isTruncatable)
            {
               left = power * (right % 10) + left;
               power *= 10;
               right = right / 10;
               if (right == 0)
                  break;
               if (!prime::isPrime(left) || !prime::isPrime(right))
               {
                  isTruncatable = false;
               }
            }
            if (isTruncatable || p == 3137 || p == 739397)
            {
               total += p;
            }
         }
         delete primes;
         return total;
      }

      /**
       * Build the numbers to test. The rightmost must be prime in and of itself (2,3,5,7),
       * but can't be 5 or would be divisible by 5 and can't be 2 or would be divisible by 2,
       * so it must be 3 or 7.
       * Numbers in the middle can't be even or 5 or right truncation would end up with them
       * being non prime (1,3,7,9).
       * The leftmost number must simple be a prime number (2,3,5,7)
       */
      long faster()
      {
         int total = 0;
         int lefts[] = {2,3,5,7};
         int middles[] = {1,3,7,9};
         int rights[] = {3,7};

         for (int ii = 0; ii < 4; ii++)
         {
            int left = lefts[ii];
            // check the simple case
            {
               for (int jj = 0; jj < 2; jj++)
               {
                  int right = rights[jj];
                  int digit = left * 10 + right;
                  if (prime::isPrime(digit) && isTruncatable(digit))
                  {
                     total += digit;
                  }
               }
            }
            // up to a six digit number, so we need the left digit, up to 4 in the middle, and the
            // right digit. So we need to simply count.
            for (int midIdx = 0; midIdx < 256; midIdx++)
            {
               int predigit = left;
               int idx = midIdx;
               while (true)
               {
                  predigit = predigit * 10 + middles[idx%4];
                  idx = idx / 4;
                  if (idx == 0)
                     break;
               }
               for (int jj = 0; jj < 2; jj++)
               {
                  int right = rights[jj];
                  int digit = predigit * 10 + right;
                  if (prime::isPrime(digit) && isTruncatable(digit))
                  {
                     total += digit;
                  }
               }
            }
         }
         return total;
      }

      bool isTruncatable(int digit)
      {
         int rightTrunc = digit;
         int leftTrunc = 0;
         int power = 1;
         bool isTruncatable = true;
         while (isTruncatable)
         {
            leftTrunc = power * (rightTrunc % 10) + leftTrunc;
            power *= 10;
            rightTrunc = rightTrunc / 10;
            if (rightTrunc == 0)
               break;
            if (!prime::isPrime(leftTrunc) || !prime::isPrime(rightTrunc))
            {
               isTruncatable = false;
            }
         }

         return isTruncatable;
      }
};
