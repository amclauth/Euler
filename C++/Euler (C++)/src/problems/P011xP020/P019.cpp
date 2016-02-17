#include "../../base/problem.h"
#include "../../util/io.h"

/**
 * P019<br>
 * You are given the following information, but you may prefer to do some research for yourself.
 * 1 Jan 1900 was a Monday.
 * Thirty days has September,
 * April, June and November.
 * All the rest have thirty-one,
 * Saving February alone,
 * Which has twenty-eight, rain or shine.
 * And on leap years, twenty-nine.
 * A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
 * How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
 * Ans: 171
 */
class P019: public Problem
{
	public:
		P019()
		{
			problem_number = 19;
			variations = 3;
		}
		~P019()
		{
		}

		std::string execute(int variation)
		{
			switch (variation)
			{
				case 0:
				case -1:
					return to_string(bruteForce());
				case 1:
					return "-1";
				case 2:
					return to_string(faster());
				default:
					return std::string("unavailable");
			}
			return NULL;
		}

	private:

		/**
		 * This has tricksy wording. We get that 1900 starts on a Monday but are asked to count from 1901.
		 */
		int bruteForce()
		{
			int dow = 1; // starts on Monday
			int sundays = 0;
			bool isLeapYear = false;

			int year = 1900;
			for (; year <= 2000; year++)
			{
				isLeapYear = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
				dow += 31; // january
				sundays += dow % 7 == 0 ? 1 : 0;
				dow += isLeapYear ? 29 : 28; // february
				sundays += dow % 7 == 0 ? 1 : 0;
				dow += 31; // march
				sundays += dow % 7 == 0 ? 1 : 0;
				dow += 30; // april
				sundays += dow % 7 == 0 ? 1 : 0;
				dow += 31; // may
				sundays += dow % 7 == 0 ? 1 : 0;
				dow += 30; // june
				sundays += dow % 7 == 0 ? 1 : 0;
				dow += 31; // july
				sundays += dow % 7 == 0 ? 1 : 0;
				dow += 31; // august
				sundays += dow % 7 == 0 ? 1 : 0;
				dow += 30; // september
				sundays += dow % 7 == 0 ? 1 : 0;
				dow += 31; // october
				sundays += dow % 7 == 0 ? 1 : 0;
				dow += 30; // november
				sundays += dow % 7 == 0 ? 1 : 0;
				if (year < 2000)
				{
					dow += 31; // december
					sundays += dow % 7 == 0 ? 1 : 0;
				}
				if (year == 1900)
					sundays = 0;
			}
			return sundays;
		}

		/**
		 * We know that 2000 is a leap year, so really it's just every 4 years in a cycle. 1900 wasn't a leap year
		 * so we know that 1901 starts in 365 days, or on a Tuesday. We can take every 4 years and add 365 or 366 % 7
		 * to it (1 or 2) once we know what each month's starting day is
		 */
		long faster()
		{
			int mArray[12];
			mArray[0] = 2;						// January starts on Tuesday
			mArray[1] = mArray[0] + 31%7; // February start
			mArray[2] = mArray[1] + 28%7; // March start
			mArray[3] = mArray[2] + 31%7;
			mArray[4] = mArray[3] + 30%7;
			mArray[5] = mArray[4] + 31%7;
			mArray[6] = mArray[5] + 30%7;
			mArray[7] = mArray[6] + 31%7;
			mArray[8] = mArray[7] + 31%7;
			mArray[9] = mArray[8] + 30%7;
			mArray[10] = mArray[9] + 31%7;
			mArray[11] = mArray[10] + 30%7;

			int sundays = 0;

			for (int month = 0; month < 12; month++)
			{
				if (mArray[month] % 7 == 0)
					sundays++;
			}

			for (int year = 2; year <= 100; year++) // 1902 to 2000 inclusive ... already added 1901
			{
				bool thisLeap = ((year % 4) == 0);
				bool lastLeap = (((year-1) % 4) == 0);
				for (int month = 0; month < 12; month++)
				{
					if (month >= 2)
					{
						if (thisLeap)
						{
							mArray[month] += 2;
						}
						else
						{
							mArray[month]++;
						}
					}
					else if (lastLeap)
					{
						mArray[month] += 2;
					}
					else
					{
						mArray[month]++;
					}

					if (mArray[month] % 7 == 0)
						sundays++;
				}
			}

			return sundays;
		}
};
