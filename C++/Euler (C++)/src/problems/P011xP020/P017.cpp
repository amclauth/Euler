#include "../../base/problem.h"


/**
 * P017<br>
 * If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
 * If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
 * NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen)
 * contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
 * Ans: 21124
 */
class P017: public Problem
{
	public:
		P017()
		{
			problem_number = 17;
			variations = 2;
		}
		~P017()
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
		 * Programatically write everything out
		 * @return
		 */
		long bruteForce()
		{
			std::string special[91]; // just need zero through ninety
			special[0] = "";
			special[1] = "one";
			special[2] = "two";
			special[3] = "three";
			special[4] = "four";
			special[5] = "five";
			special[6] = "six";
			special[7] = "seven";
			special[8] = "eight";
			special[9] = "nine";
			special[10] = "ten";
			special[11] = "eleven";
			special[12] = "twelve";
			special[13] = "thirteen";
			special[14] = "fourteen";
			special[15] = "fifteen";
			special[16] = "sixteen";
			special[17] = "seventeen";
			special[18] = "eighteen";
			special[19] = "nineteen";
			special[20] = "twenty";
			special[30] = "thirty";
			special[40] = "forty";
			special[50] = "fifty";
			special[60] = "sixty";
			special[70] = "seventy";
			special[80] = "eighty";
			special[90] = "ninety";

			long count = 0;
			std::string s = "";

			for (int ii = 1; ii < 1000; ii++)
			{
				if (ii % 100 < 20)
				{
					count += special[ii % 100].length();
					s = special[ii % 100];
				}
				else
				{
					if (ii % 10 == 0)
					{
						count += special[ii % 100].length();
						s = special[ii % 100];
					}
					else
					{
						count += special[((int) ((ii % 100) / 10)) * 10].length();
						count += special[(int) (ii % 10)].length();
						s = special[((int) ((ii % 100) / 10)) * 10] + "-" + special[(int) (ii % 10)];
					}
				}
				if (ii >= 100)
				{
					count += special[(int) (ii / 100)].length();
					count += (std::string("hundred")).length();
					if (ii % 100 != 0)
					{
						count += (std::string("and")).length();
						s = "and " + s;
					}
					s = special[(int) (ii / 100)] + " " + "hundred" + " " + s;
				}
				//			System.out.println(s + ": " + count);

			}
			count += (std::string("onethousand")).length();

			return count;
		}

		/**
		 * Numbers 1-9 are 3+3+5+4+4+3+5+5+4 = 36
		 * Numbers 11-19 are oddballs, so explicitly, 3+6+6+8+8+7+7+9+8+8
		 * twenty
		 * thirty
		 * forty
		 * fifty
		 * sixty
		 * seventy
		 * eighty
		 * ninety
		 * Numbers 20-99 then have the ones repeated for each, plus ten instances of each prefix
		 * Numbers 100-999 we have the ones each occurring 100 times (one hundred 100 times, two hundred 100 times),
		 * the "hundred" occurring 900 times, the "and" occurring 9*99 times (not on the exact hundreds), and the
		 * sum total of 1-100 occurring 9 times plus the characters for "one thousand"
		 * @return
		 */
		long faster()
		{
			int ones = 3 + 3 + 5 + 4 + 4 + 3 + 5 + 5 + 4;
			int teens = 3 + 6 + 6 + 8 + 8 + 7 + 7 + 9 + 8 + 8;
			int tens = 8 * ones + 10 * (6 + 6 + 5 + 5 + 5 + 7 + 6 + 6);
			int pre_hundred = ones + teens + tens;
			int hundreds = 100 * ones + 7 * 900 + 3 * 9 * 99 + pre_hundred * 9;
			int one_thousand = 11;
			return pre_hundred + hundreds + one_thousand;
		}
};
