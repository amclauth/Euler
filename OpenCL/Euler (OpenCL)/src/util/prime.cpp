#include "prime.h"
#include <math.h>
#include <climits>
#include <iostream>

namespace prime
{
   /**
    * Quick check for primeness of small numbers
    * @param num
    * @return
    */
   bool isPrime(int num)
   {
      if (num <= 1)
         return false;
      if (num % 2 == 0 && num != 2)
         return false;
      for (int ii = 3; ii * ii <= num; ii += 2)
      {
         if (num % ii == 0)
            return false;
      }
      return true;
   }

   /**
    * Uses the sieve of Eratosthenes and assumes that there are ~ n/ln(n) primes less than n
    * So the nth prime is approximately n ln n. n ln n is less than the prime, though, so
    * use the greater approximation: n ln n + n ln ln n
    * @param n
    * @return
    */
   int getNthPrime(int n)
   {
      double lnn = log(n);
      double max = n * (lnn + log(lnn));
      std::vector<int>* primes = EratosthenesPrimesUpTo((int) max);
      if (n <= (int) primes->size())
      {
         int val = primes->at(n - 1);
         delete primes;
         return val;
      }
      delete primes;
      return -1;
   }

   /**
    * Doing a Sieve of Eratosthenes
    * @param n
    * @return
    */
   std::vector<int>* EratosthenesPrimesUpTo(int n)
   {
      int size = (n - 2) >> 1;
      bool is_composite[size]; // booleans of all odd numbers
      for (int ii = 0; ii < size; ii++)
         is_composite[ii] = false;
      std::vector<int>* results = new std::vector<int>();
      results->push_back(2); // add 2 since we're ignoring evens
      for (int ii = 0; ii < size; ii++) // check all odds
      {
         if (!is_composite[ii]) // if it's not known, we need to check it
         {
            results->push_back(2 * ii + 3);
            // changing indexes to use only odd numbers
            for (long j = 4L * ii * ii + 12L * ii + 9; j < 2 * size + 3; j += 4 * ii + 6)
            {
               is_composite[(int) ((j - 3L) >> 1)] = true;
            }
         }
      }
      return results;
   }
}
