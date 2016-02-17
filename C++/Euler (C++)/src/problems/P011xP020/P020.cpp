#include "../../base/problem.h"

#include <vector>
#include <iostream>

/**
 * P020<br>
 * n! means n  (n  1)  ...  3  2  1
 * For example, 10! = 10  9  ...  3  2  1 = 3628800,
 * and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
 * Find the sum of the digits in the number 100!
 * Ans: 648
 */
class P020: public Problem
{
   public:
      P020()
      {
         problem_number = 20;
         variations = 3;
      }
      ~P020()
      {
      }

      std::string execute(int variation)
      {
         switch (variation)
         {
            case 0:
               return to_string(bruteForce());
            case 1:
            	return "-1";
            case -1:
            case 2:
               return to_string(faster());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:

      /**
       *
       */
      int bruteForce()
      {
         int size = 200; // WAG on size
         int num[size]; // WAG on size
         for (int ii = 0; ii < size; ii++)
         {
            num[ii] = 0;
         }
         num[0] = 1;
         for (int ii = 2; ii <= 100; ii++)
         {
            int carry = 0;
            for (int jj = 0; jj < size; jj++)
            {
               num[jj] = num[jj] * ii + carry;
               carry = num[jj] / 10;
               num[jj] = num[jj] % 10;
            }
         }
         int sum = 0;
         for (int ii = size -1 ; ii >= 0; ii--)
         {
            sum += num[ii];
//            std::cout << num[ii];
         }
//         std::cout << std::endl;
         return sum;
      }

      /**
       * Try with a vector to only use needed space
       */
      long faster()
      {
         std::vector<int> array;
         array.push_back(1); // array[0] will be lsb
         for (int ii = 2; ii <= 100; ii++)
         {
            int carry = 0;
            for (unsigned int jj = 0; jj < array.size(); jj++)
            {
               int n = array.at(jj) * ii + carry;
               if (n > 9)
               {
                  array.at(jj) = n % 10;
                  carry = n / 10;
               }
               else
               {
                  array.at(jj) = n;
                  carry = 0;
               }
            }
            while (carry > 0)
            {
               array.push_back(carry % 10);
               carry = carry / 10;
            }
         }
         int total = 0;
         for (unsigned int ii = 0; ii < array.size(); ii++)
         {
            total += array.at(ii);
         }
         return total;
      }
};
