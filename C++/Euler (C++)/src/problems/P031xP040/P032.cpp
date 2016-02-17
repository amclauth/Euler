#include "../../base/problem.h"
#include "../../util/combinatorics.h"
#include "../../util/basic.h"

#include <vector>
#include <set>

/**
 * P032<br>
 * We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once;
 * for example, the 5-digit number, 15234, is 1 through 5 pandigital.
 * The product 7254 is unusual, as the identity, 39  186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.
 * Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
 * HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
 * Ans: 45228
 */
class P032: public Problem, Combinatorics
{
   public:
      P032()
      {
         products = NULL;
         problem_number = 32;
         variations = 2;
      }
      ~P032()
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

      std::set<int>* products;
      /**
       * Check all permutations for a, b, and c!
       */
      long bruteForce()
      {
         products = new std::set<int>();
         std::vector<int> nums;
         for (int ii = 1; ii <= 9; ii++)
         {
            nums.push_back(ii);
         }
         permute(&nums);
         int total = 0;
         for (std::set<int>::iterator it = products->begin(); it != products->end(); ++it)
         {
            total += *it;
         }
         delete products;
         return total;
      }

      /**
       * We know the multiplicands must either be 1x4, 2x3, 3x2, or 4x1 in length to
       * produce a correctly numbered output. We know the output must be 4 in length,
       * so we can iterate through 1234 to 9876 and check if divisors of those numbers
       * together with the solution contain a pandigital. We can check for
       * pandigiality with a bitmask of the deconstructed integer
       */
      long faster()
      {
         products = new std::set<int>();
         for (int product = 1234; product <= 9876; product++)
         {
            std::vector<long>* divisors = basic::getDivisors(product);
            for (int ii = 0; ii < divisors->size() / 2.0; ii++)
            {
               int d1 = divisors->at(ii);
               int d2 = divisors->at(divisors->size() - 1 - ii);
               int solution[] = {product,d1,d2};
               if (basic::isPandigital(solution,3))
               {
                  products->insert(product);
                  break;
               }
            }
            delete divisors;
         }

         int total = 0;
         for (std::set<int>::iterator it = products->begin(); it != products->end(); ++it)
         {
            total += *it;
         }
         delete products;
         return total;
      }

      void process(std::vector<int>* arr)
      {
         // try combinations of a * b = c
         for (int ii = 1; ii < 5; ii++)
         {
            int a = 0;
            for (int kk = 0; kk < ii; kk++)
            {
               a *= 10;
               a += arr->at(kk);
            }
            for (int jj = 5 - ii; jj < 4; jj++)
            {
               int b = 0;
               for (int kk = ii; kk < jj + ii; kk++)
               {
                  b *= 10;
                  b += arr->at(kk);
               }

               int c = 0;
               for (unsigned int kk = ii + jj; kk < arr->size(); kk++)
               {
                  c *= 10;
                  c += arr->at(kk);
               }

               if (a * b == c)
               {
                  products->insert(c);
               }

               if (a * b > c)
               {
                  break;
               }
            }
         }
      }
};
