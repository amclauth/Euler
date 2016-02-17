#include "basic.h"

#include <math.h>
#include <algorithm>

namespace basic
{
   /**
    * returns the sum from 1 to n
    */
   int n_sum(int n)
   {
      return n * (n + 1) / 2;
   }

   /**
    * Returns the nth fibonacci number, starting with 0,1,1,2,3,5,...
    */
   int fibonacci(int n)
   {
      const double s5 = sqrt(5);
      int fn = (pow(1 + s5, n) - pow(1 - s5, n)) / (pow(2, n) * s5);
      return fn;
   }

   /**
    * Get an (unsorted) list of factor in the order they were discovered
    */
   std::vector<long>* factors(long n)
   {
      std::vector<long> *factors = new std::vector<long>();
      long factor = 2;
      while (n > 1)
      {
         while (n % factor != 0 && factor * factor <= n)
         {
            if (factor > 2)
               factor += 2;
            else
               factor++;
         }
         if (factor * factor > n)
            factor = n;
         factors->push_back(factor);
         n = n / factor;
      }
      return factors;
   }

   /**
    * Get all the divisors for a number including mirrors.<br>
    * Almost certainly a faster way is getting the factors, then
    * doing combinations of n,n-1,n-2...n-n+1 and adding the
    * uniques to the list. This is the fastest implementation I've
    * come up with so far (faster than factoring and combining by 10x)
    * ie: 12 = 1,2,3,4,6,12
    * @param num
    * @return
    */
   std::vector<long>* getDivisors(long num)
   {
      std::vector<long> *divisors = new std::vector<long>();
      // get all the initial divisors
      if (num == 0)
      {
         divisors->push_back(0);
         return divisors;
      }
      for (long ii = 1; ii*ii <= num; ii++)
      {
         if (num % ii == 0)
         {
            divisors->push_back(ii);
         }
      }
      // skip the duplicate at the square root
      int ii = divisors->size() - 1;
      if (divisors->at(ii)*divisors->at(ii) == num)
      {
         ii--;
      }
      // do simple division to add the mirrors in the right order.
      for (; ii >= 0; ii--)
      {
         divisors->push_back((num / divisors->at(ii)));
      }
      return divisors;
   }

   /**
    * Get the number of divisors from the factor list by using the power of
    * the primes for combinatorials. Not valid for 0 which returns an empty
    * list of factors.
    */
   long getNumberOfDivisorsFromFactors(std::vector<long>* factors)
   {
      long answer = 1;
      if (factors->size() == 0)
         return 1;
      long previous = 0;
      int pCount = 0;

      for (unsigned int ii = 0; ii < factors->size(); ii++)
      {
         // use unchecked for speed
         if (factors->at(ii) == previous)
         {
            pCount++;
         }
         else
         {
            answer *= pCount + 1;
            pCount = 1;
            previous = factors->at(ii);
         }
      }
      answer *= pCount + 1;
      return answer;
   }

   /**
    * The formula for a sum of divisors from factors is the multiplicative product of
    * (p^(n+1)-1)/(p-1) where p is the prime factor and n is the power of that prime
    * (number of repetitions). Not valid for 0.
    */
   long getSumOfDivisorsFromFactors(std::vector<long>* factors)
   {
      long previous = 0;
      int pCount = 0;
      long sum = 1;

      for (unsigned int ii = 0; ii < factors->size(); ii++)
      {
         if (factors->at(ii) == previous)
         {
            pCount++;
         }
         else
         {
            long j = previous;
            for (int jj = 0; jj < pCount; jj++)
            {
               j *= previous;
            }
            sum *= (j-1)/(previous-1);
            pCount = 1;
            previous = factors->at(ii);
         }
      }

      long j = previous;
      for (int jj = 0; jj < pCount; jj++)
      {
         j *= previous;
      }
      sum *= (j-1)/(previous-1);

      return sum;
   }

   /**
    * Reverse and return a long (look into faster shifting way to do this
    * in c++)
    * @param num
    * @return
    */
   long reverse(long num)
   {
      long n = num;
      long r = 0;
      while (n > 0)
      {
         r = r * 10 + n % 10;
         n = (n - n % 10) / 10;
      }
      return r;
   }

   /**
    * Reverse and return an int
    * @param num
    * @return
    */
   int reverse(int num)
   {
      int n = num;
      int r = 0;
      while (n > 0)
      {
         r = r * 10 + n % 10;
         n = (n - n % 10) / 10;
      }
      return r;
   }

   /**
    * Reverse and return a string
    *
    * @param s
    * @return
    */
   std::string reverse(std::string s)
   {
      std::reverse(s.begin(), s.end());
      return s;
   }

   /**
    * Return whether a number is a palindrome or not
    * @param num
    * @return
    */
   bool isPalindrome(long num)
   {
      long r = reverse(num);
      if (r == num)
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   /**
    * Return whether a number is a palindrome or not
    * @param num
    * @return
    */
   bool isPalindrome(int num)
   {
      int r = reverse(num);
      if (r == num)
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   bool isPalindrome(std::string num)
   {
      const char* buffer = num.c_str();
      for (unsigned int ii = 0; ii < num.length() / 2; ii++)
      {
         if (buffer[ii] != buffer[num.length() - 1 - ii])
            return false;
      }
      return true;
   }

   /**
    * A triangle number is the number 1+2+3 for the third, +4 for the fourth, etc.
    * @param n
    * @return
    */
   long getTriangle(int n)
   {
      return n * (n + 1L) / 2L;
   }

   /**
    * Return the factorial of n. Gets too big pretty fast
    */
   long factorial(long n)
   {
      if (n == 0)
         return 1;
      long fact = n;
      for (long i = n - 1; i > 1; i--)
      {
         fact *= i;
      }
      return fact;
   }

   /**
    * An amicable number is a number where the sum of its divisors is a
    * different number ... whose divisors sum to be the original number. Sum of
    * divisors should not include the number itself.
    *
    * @param num - the initial number
    * @return - -1 if there is not amicable number, or the amicable number
    */
   int getAmicableNumber(int num)
   {
      std::vector<long>* d = getDivisors(num);
      int sum = 0;
      for (unsigned int ii = 0; ii < d->size() - 1; ii++)
      {
         sum += d->at(ii);
      }
      if (num == sum)
      {
         return -1; // the same number isn't a pair
      }
      d = getDivisors(sum);
      int sum2 = 0;
      for (unsigned int ii = 0; ii < d->size() - 1; ii++)
      {
         sum2 += d->at(ii);
      }
      if (sum2 == num)
      {
         return sum;
      }
      return -1;
   }

   /**
    * Check any number or list of numbers to see if 1-9 is contained
    * (may need to adjust this later for ranges or to include 0)
    * @param nums
    * @return
    */
   bool isPandigital(int nums[], int length)
   {
      int mask = 0;
      for (int ii = 0; ii < length; ii++)
      {
         int n = nums[ii];
         while (n != 0)
         {
            int digit = n % 10;
            if (digit == 0)
               return false;

            mask |= (1 << (digit - 1));

            n = n/10;
         }
      }
      return mask == 0x01ff; // 1 1111 1111
   }

   /**
    * Check if a string is 1-9 pandigital
    * @param num
    * @return
    */
   bool isPandigital(std::string num)
   {
      for (char c = '1'; c <= '9'; c++)
      {
         if (num.find_first_of(c) == num.npos)
            return false;
      }
      return num.length() == 9;
   }

   /**
    * Finds the largest common factor to reduce by
    * @param num
    * @param den
    * @return the largest factor or -1
    */
   int reduce(int num, int den)
   {
      std::vector<long>* d1 = getDivisors(num);
      std::vector<long>* d2 = getDivisors(den);
      for (unsigned int ii = d1->size() - 1; ii >= 0; ii--)
      {
         if (std::find(d2->begin(), d2->end(), d1->at(ii)) != d2->end())
         {
            return d1->at(ii);
         }
      }
      return -1;
   }
}
