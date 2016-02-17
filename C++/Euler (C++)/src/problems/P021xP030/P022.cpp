#include "../../base/problem.h"
#include "../../util/io.h"

#include <vector>
#include <algorithm>
#include <set>

/**
 * P022 Using names.txt (right click and 'Save Link/Target As...'), a 46K text
 * file containing over five-thousand first names, begin by sorting it into
 * alphabetical order. Then working out the alphabetical value for each name,
 * multiply this value by its alphabetical position in the list to obtain a name
 * score. For example, when the list is sorted into alphabetical order, COLIN,
 * which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So,
 * COLIN would obtain a score of 938 * 53 = 49714. What is the total of all the
 * name scores in the file? Ans: 871198282
 */
class P022: public Problem
{
   public:
      P022()
      {
         problem_number = 22;
         variations = 3;
      }
      ~P022()
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
            case 2:
            case -1:
               return to_string(faster());
            default:
               return std::string("unavailable");
         }
         return NULL;
      }

   private:

      // use std::sort with a function to sort alphabetically using strcmp
      /**
       * Just read in the file, use std::sort and add to the total
       */
      long bruteForce()
      {
      	long sum = 0;
      	std::string file = io::readFile("data/names.txt");
      	std::vector<std::string>* names = io::readIntoStringArray(file, "\",\"");

      	// strip quotes off first and last elements
      	names->at(0) = names->at(0).replace(0,1,"");
      	int len = (*(names->end()-1)).length();
      	(*(names->end()-1)).replace(len-1,len,"");

      	std::sort(names->begin(),names->end());

      	int idx = 0;
      	for (std::vector<std::string>::iterator it = names->begin(); it != names->end(); ++it)
         {
            std::string name = *it;
            int namecount = 0;
            for (unsigned int ii = 0; ii < name.length(); ii++)
            {
               int n = name[ii] - 'A' + 1;
               namecount += n;
            }
            sum += namecount * (idx++ + 1);
         }

			return sum;
      }

      /**
       * Not much I can upgrade here. Try using a pre-sorted set for the names?
       */
      long faster()
      {
         long sum = 0;
         std::string file = io::readFile("data/names.txt");
         // erase the first and last quotes
         file.erase(0,1);
         file.erase(file.size() - 1);
         std::set<std::string>* sorted = io::readIntoStringSet(file, "\",\"");

         int idx = 0;
         for (std::set<std::string>::iterator it = sorted->begin(); it != sorted->end(); ++it)
         {
            std::string name = *it;

            int namecount = 0;
            for (unsigned int ii = 0; ii < name.length(); ii++)
            {
               int n = name[ii] - 'A' + 1;
               namecount += n;
            }
            sum += namecount * (idx++ + 1);
         }

			return sum;
      }
};
