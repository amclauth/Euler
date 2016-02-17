#include <math.h>
#include <string>
#include <vector>

#include "../../util/basic.h"
#include "../../base/problem.h"
#include "../../util/prime.h"

/**
 * P003<br>
 * The prime factors of 13195 are 5, 7, 13 and 29.<br>
 * What is the largest prime factor of the number 600851475143 ?<br>
 * Ans: 6857
 */
class P003: public Problem
{
   public:
      P003()
      {
         problem_number = 3;
         variations = 2;
      }
      ~P003()
      {
      }

      std::string execute(int variation)
      {
         switch (variation)
         {
            case 0:
            case -1:
               return to_string(brute());
            case 1:
               return to_string(primeTest());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:
      static const long n = 600851475143L;

      // factor the number, starting with 2's, then 3's, and on up. The last
      // factor is the largest.
      long brute()
      {
         return (basic::factors(n))->back();
      }

      int primeTest()
      {
         std::vector<int>* primes = prime::EratosthenesPrimesUpTo(sqrt(n));
         for (unsigned int ii = primes->size() - 1; ii >= 0; ii--)
         {
            if (n % primes->at(ii) == 0)
            {
            	int retVal = primes->at(ii);
            	delete primes;
               return retVal;
            }
         }
         delete primes;
         return -1;
      }

};
