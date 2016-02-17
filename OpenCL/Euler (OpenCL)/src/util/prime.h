#ifndef __PRIME_H__
#define __PRIME_H__

#include <vector>

namespace prime
{
   /**
    * Quick check for primeness of small numbers
    * @param num
    * @return
    */
   bool isPrime(int num);

   /**
    * Uses the sieve of Eratosthenes and assumes that there are ~ n/ln(n) primes less than n
    * So the nth prime is approximately n ln n. n ln n is less than the prime, though, so
    * use the greater approximation: n ln n + n ln ln n
    * @param n
    * @return
    */
   int getNthPrime(int n);

   /**
    * Doing a Sieve of Eratosthenes
    * @param n
    * @return
    */
   std::vector<int>* EratosthenesPrimesUpTo(int n);

}

#endif
