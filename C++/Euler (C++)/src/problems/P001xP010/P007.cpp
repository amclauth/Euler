#include <math.h>
#include <string>
#include <vector>

#include "../../util/prime.h"
#include "../../base/problem.h"

/**
 * P007<br>
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the
 * 6th prime is 13.<br>
 * What is the 10 001st prime number?<br>
 * Ans: 104743
 */
class P007: public Problem
{
   public:
      P007()
      {
         problem_number = 7;
         variations = 2;
      }
      ~P007()
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
               return to_string(getPrime());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:

      /**
       * This is the brute force attempt. Check every number for Primeness
       * @return
       */
      int bruteForce()
      {
         int n = 0;
         int num = 2;
         while (n < 10001)
         {
            if (prime::isPrime(num))
               n++;
            num++;
         }
         return num - 1;
      }

      int getPrime()
      {
         return prime::getNthPrime(10001);
      }

};
