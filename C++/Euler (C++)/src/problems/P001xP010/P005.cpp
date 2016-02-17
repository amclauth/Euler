#include <math.h>
#include <string>
#include <vector>

#include "../../util/basic.h"
#include "../../base/problem.h"

/**
 * P005<br>
 * 2520 is the smallest number that can be divided by each of the numbers from
 * 1 to 10 without any remainder.
 *
 * What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
 * Ans: 232792560
 */
class P005: public Problem
{
   public:
      P005()
      {
         problem_number = 5;
         variations = 3;
      }
      ~P005()
      {
      }

      std::string execute(int variation)
      {
         switch (variation)
         {
            case 0:
               return to_string(bruteForce());
            case 1:
               return to_string(factors());
            case -1:
            case 2:
               return to_string(primeFactors());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:

      /**
       * This is the brute force attempt. Check every number starting with 1
       * @return
       */
      int bruteForce()
      {
         bool found = false;
         int num = 1;
         while (!found)
         {
            found = true;
            for (int ii = 2; ii <= 20; ii++)
            {
               found &= num % ii == 0;
               if (!found)
                  continue;
            }
            num++;
         }
         return num - 1;
      }

      /**
       * Factorize each number between 1 and 20. Combine to one common total factorization
       * and multiply!
       * @return
       */
      int factors()
      {
         int factors[20];
         int miniFactors[20];
         // first, initialize ... max prime is 19
         for (int ii = 0; ii <= 19; ii++)
            factors[ii] = 0;
         for (int ii = 2; ii <= 20; ii++)
         {
            // initialize a sub-list
            for (int jj = 0; jj <= 19; jj++)
               miniFactors[jj] = 0;
            std::vector<long>* f = basic::factors(ii);

            // add factors to miniFactors
            for (std::vector<long>::iterator it = f->begin(); it != f->end(); ++it)
               miniFactors[*it]++;

            // now compare to existing factors
            for (int jj = 0; jj <= 19; jj++)
               if (miniFactors[jj] > factors[jj])
                  factors[jj] = miniFactors[jj];
         }

         // now multiply
         int num = 1;
         for (int ii = 2; ii <= 19; ii++)
         {
            for (int jj = 0; jj < factors[ii]; jj++)
               num *= ii;
         }

         return num;
      }

      /**
       * Use math. Create a list of prime numbers (in this case, simple enough that we don't have
       * to use the primesupto functions). Create a second list to be the power of each prime
       * represented. EG: since 2^4 = 16, and 2 is the 0th prime in our list, a[0]=4. Initialize
       * this list of powers at 1 since we have every prime number under 20 in our list. Then
       * figure out what the largest power of each prime must be. We can find this by checking
       * the log to the base of that prime of our highest number. So what power of 2 is the
       * lowest power of 2 that would represent 20? 4. For 3? 3. Etc. We don't need to check
       * any primes lower than the sqrt(20) since there won't be more than one of those.
       * @return
       */
      int primeFactors()
      {
         int N = 1;
         double limit = sqrt(20);
         int p[8] =
         { 2, 3, 5, 7, 11, 13, 17, 19 };
         int a[8];
         for (int ii = 0; ii < 8; ii++)
            a[ii] = 1;
         for (int ii = 0; ii < 8; ii++)
         {
            a[ii] = 1;
            if (p[ii] <= limit)
               a[ii] = (int) floor(log(20) / log(p[ii]));
            N = N * (int) pow(p[ii], a[ii]);
         }
         return N;
      }

};
