#include "../../base/problem.h"

#include <cmath>

/**
 * P031<br>
 * In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:
 * 1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
 * It is possible to make £2 in the following way:
 * 1£1 + 150p + 220p + 15p + 12p + 31p
 * How many different ways can £2 be made using any number of coins?
 * Ans: 73682
 */
class P031: public Problem
{
   public:
      P031()
      {
         problem_number = 31;
         variations = 3;
      }
      ~P031()
      {
      }

      std::string execute(int variation)
      {
         switch (variation)
         {
            case 0:
               return to_string(bruteForce());
            case 1:
               return to_string(faster());
            case -1:
            case 2:
               return to_string(dynamic());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:

      /**
       * Just start with L2, then fill in any number of the rest, finishing with
       * as many p as are necessary to finish out the group
       */
      long bruteForce()
      {
         int amount = 200;
         int combos = 0;
         int values[] = {200, 100, 50, 20, 10, 5, 2, 1};
         for (int a = 0; values[0] * a <= amount; a++)
         {
            int sum = a*values[0];
            for (int b = 0; values[1] * b + sum <= amount; b++)
            {
               sum += b * values[1];
               for (int c = 0; values[2] * c + sum <= amount; c++)
               {
                  sum += c * values[2];
                  for (int d = 0; values[3] * d + sum <= amount; d++)
                  {
                     sum += d * values[3];
                     for (int e = 0; values[4] * e + sum <= amount; e++)
                     {
                        sum += e * values[4];
                        for (int f = 0; values[5] * f + sum <= amount; f++)
                        {
                           sum += f * values[5];
                           for (int g = 0; values[6] * g + sum <= amount; g++)
                           {
                              combos++;
                              // pence is simply left over ... don't even need to know how many
                           }
                           sum -= f * values[5];
                        }
                        sum -= e * values[4];
                     }
                     sum -= d * values[3];
                  }
                  sum -= c * values[2];
               }
               sum -= b * values[1];
            }
         }
         return combos;
      }

      /**
       * Recurse!
       */
      long faster()
      {
         double values[] = {1,2,5,10,20,50,100,200};
         return parse(values,0,7,0,200);
      }

      long parse(double values[], int current, int idx, long counter, int total) {
         int inputCurrent = current;
         if (idx == -1)
            return counter;
         int max = (int) (round((total - current) * 1.0 / values[idx]));
         for (int ii = max; ii >= 0; ii--) {
            current = (int) (round(inputCurrent + ii * values[idx]));
            if (current == total) {
               counter++;
               // escape from over-checking the final index
               if (idx == 0) {
                  return counter;
               }
            } else {
               counter = parse(values,current,idx-1,counter,total);
            }
         }
         return counter;
      }

      /**
       * Dynamic programming version. Much faster!
       * @return
       */
      int dynamic() {
         int coins[] = {1, 2, 5, 10, 20, 50, 100, 200};
         int ways[200+1] = {};
         ways[0] = 1;

         for(int i = 0; i < 8; i++)
            for(int j = coins[i]; j <= 200; j++)
               ways[j] += ways[j - coins[i]];

         return ways[200];
      }
};
