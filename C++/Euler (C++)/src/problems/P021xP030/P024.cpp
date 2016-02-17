#include "../../base/problem.h"
#include "../../util/basic.h"

#include <vector>

/**
 * P024<br>
 * A permutation is an ordered arrangement of objects. For example, 3124 is one
 * possible permutation of the digits 1, 2, 3 and 4. If all of the permutations
 * are listed numerically or alphabetically, we call it lexicographic order. The
 * lexicographic permutations of 0, 1 and 2 are: 012 021 102 120 201 210 What is
 * the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7,
 * 8 and 9?
 *
 * Ans: 2783915460
 */
class P024: public Problem
{
   public:
      P024()
      {
         problem_number = 24;
         variations = 2;
      }
      ~P024()
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
       * Check all the numbers and see if they contain all the digits. Guaranteed
       * to be ordered this way. Takes a /long/ time. (136s)
       */
      long bruteForce()
      {
         int count = 0;
         for (long ii = 123456789; ii <= 9876543210L; ii++) {
            if (containsAll(ii)) {
               count++;
               if (count == 1000000) {
                  return ii;
               }
            }
         }
         return 0;
      }

      // check if a number contains all digits.
      bool containsAll(long n) {
         bool nums[10] = {false,false,false,false,false,false,false,false,false,false};
         if (n < 1000000000L) {
            nums[0] = true; // 0 is the first number then!
         }
         while (n >= 1) {
            nums[(int)(n % 10)] = true;
            n = (int)(n/10);
         }
         for (int ii = 0; ii < 10; ii++) {
            if (!nums[ii])
               return false;
         }
         return true;
      }

      /**
       * We know that there are n! permutations for any combination of numbers, so
       * we can search for the first number by asking "what is the greatest number
       * that fits in the equations x*9! <= 1000000. We then have the difference
       * between 1000000 and x*9! number of permutations away from the 0th
       * permutation to find. Then it's x2*8! < 1000000 - x*9!, etc.
       *
       */
      long faster()
      {
         std::vector<int>* digits = new std::vector<int>();
         for (int ii = 0; ii < 10; ii++) {
            digits->push_back(ii);
         }
         long facts[10] = { 0 };
         for (int ii = 0; ii < 10; ii++)
         {
         	facts[ii] = basic::factorial(ii);
         }
         long num = 0;
         int goal = 1000000;
         while (digits->size() > 0) {
            for (int ii = 0; ii < 10; ii++) {
            	long fac = facts[digits->size() - 1];
               if ((ii + 1) * fac >= goal) {
                  goal -= ii * fac;
                  num = num * 10 + digits->at(ii);
                  digits->erase(digits->begin() + ii);
                  break;
               }
            }
         }
         delete digits;

         return num;
      }
};
