#include "../../base/problem.h"
#include "../../util/prime.h"

/**
 * P010<br>
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.<br>
 * Find the sum of all the primes below two million.<br>
 * Ans: 142913828922
 */
class P010: public Problem
{
   public:
      P010()
      {
         problem_number = 10;
         variations = 2;
      }
      ~P010()
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
       * Just check every number!
       * @return
       */
      long bruteForce()
      {
         long sum = 0;
         for (int ii = 2; ii < 2000000; ii++)
         {
            if (prime::isPrime(ii))
               sum += ii;
         }
         return sum;
      }

      /**
       * Use the sieve of erosthenes and just add!
       * @return
       */
      long optimized()
      {
         long sum = 0;
         std::vector<int>* primes = prime::EratosthenesPrimesUpTo(2000000);
         for (std::vector<int>::iterator p = primes->begin(); p != primes->end(); ++p)
            sum += *p;
         delete primes;
         return sum;
      }
};
