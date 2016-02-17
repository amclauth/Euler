#ifndef __HELPER_H__
#define __HELPER_H__

#include <vector>
#include <string>

namespace basic
{
   // Sum a number from 1 to n
   int n_sum(int n);

   // Return the nth Fibonacci number (starting with 0,1,1,2,3,5,...)
   int fibonacci(int n);

   // Get an (unsorted) list of factor in the order they were discovered
   std::vector<long>* factors(long n);

   // get all the divisors for a number including mirrors
   std::vector<long>* getDivisors(long num);

   // get the number of divisors from a list of factors
   long getNumberOfDivisorsFromFactors(std::vector<long>* factors);

   // get the sum of the divisors from a list of factors
   long getSumOfDivisorsFromFactors(std::vector<long>* factors);

   // reverse num
   long reverse(long num);

   // reverse num
   int reverse(int num);

   // reverse string
   std::string reverse(std::string s);

   // return true if num is a palindrome
   bool isPalindrome(long num);

   // return true if num is a palindrome
   bool isPalindrome(int num);

   // return true if num is a palindrome
   bool isPalindrome(std::string num);

   // get the nth triangle number
   long getTriangle(int n);

   // get the factorial of n
   long factorial(long n);

   // return the amicable number, or -1 if there isn't one
   int getAmicableNumber(int num);

   // check if a set of numbers is 1-9 pandigital
   bool isPandigital(int nums[], int length);

   // check if a string is 1-9 pandigital
   bool isPandigital(std::string num);

   // return the largest common factor or -1 if none
   int reduce(int num, int den);
}

#endif
