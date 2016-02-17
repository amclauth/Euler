#include <string>
#include <vector>

#include "../../base/problem.h"

/**
 * P008<br>
 * Find the greatest product of five consecutive digits in the 1000-digit number.<br>
 * Ans: 40824
 */
class P008: public Problem
{
   public:
      P008()
      {
         problem_number = 8;
         variations = 2;
         makeString();
      }
      ~P008()
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
               return to_string(optimizedBruteForce());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:

      char digits[1000];

      /**
       * This is the brute force attempt. Just make a list of consecutive 5 numbers and
       * keep checking
       * @return
       */
      int bruteForce()
      {
         std::vector<int> fives;
         fives.push_back(digits[0] - '0');
         fives.push_back(digits[1] - '0');
         fives.push_back(digits[2] - '0');
         fives.push_back(digits[3] - '0');
         fives.push_back(digits[4] - '0');
         int max = fives[0] * fives[1] * fives[2] * fives[3] * fives[4];
         for (int ii = 0; ii < 1000; ii++)
         {
            fives.erase(fives.begin());
            fives.push_back(digits[ii] - '0');
            int mult = fives[0] * fives[1] * fives[2] * fives[3] * fives[4];
            if (mult > max)
               max = mult;
         }
         return max;
      }

      /**
       * Make a couple additions here ... don't use lists (use an array) and only check
       * values that have five consecutive digits with no zero in them. Instead of
       * multiplying all five digits, divide out the oldest and multiply in the newest.
       * @return
       */
      int optimizedBruteForce()
      {
         int fives[5] = { };
         int idx = 0;
         int size = 0;
         int max = 0;
         int mult = 1;
         for (int ii = 0; ii < 1000; ii++)
         {
            int cur = digits[ii] - '0';
            if (cur == 0)
            {
               // start over
               size = 0;
               idx = 0;
               mult = 1;
            }
            else if (size < 5)
            {
               fives[idx++] = cur;
               mult *= cur;
               size++;
            }
            else
            {
               idx = (idx + 1) % 5;
               mult = mult / fives[idx] * cur;
               fives[idx] = cur;
               if (mult > max)
                  max = mult;
            }
         }
         return max;
      }

      void makeString()
      {
         std::string number = "73167176531330624919225119674426574742355349194934"
               "96983520312774506326239578318016984801869478851843"
               "85861560789112949495459501737958331952853208805511"
               "12540698747158523863050715693290963295227443043557"
               "66896648950445244523161731856403098711121722383113"
               "62229893423380308135336276614282806444486645238749"
               "30358907296290491560440772390713810515859307960866"
               "70172427121883998797908792274921901699720888093776"
               "65727333001053367881220235421809751254540594752243"
               "52584907711670556013604839586446706324415722155397"
               "53697817977846174064955149290862569321978468622482"
               "83972241375657056057490261407972968652414535100474"
               "82166370484403199890008895243450658541227588666881"
               "16427171479924442928230863465674813919123162824586"
               "17866458359124566529476545682848912883142607690042"
               "24219022671055626321111109370544217506941658960408"
               "07198403850962455444362981230987879927244284909188"
               "84580156166097919133875499200524063689912560717606"
               "05886116467109405077541002256983155200055935729725"
               "71636269561882670428252483600823257530420752963450";
         number.copy(digits, 1000);
      }

};
