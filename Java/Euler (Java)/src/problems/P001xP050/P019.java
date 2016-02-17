package problems.P001xP050;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import base.Problem;

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
 * @return
 */
public class P019 extends Problem
{	
	public P019()
	{
		problemNumber = 19;
		variations = 2; 
	}

	@Override
	protected String execute(int variation)
	{
		switch (variation)
		{
		case 0:
		case -1:
			return bruteForce() + "";
		case 1:
			return faster() + "";
		}
		return null;
	}

	/**
	 * This has tricksy wording. We get that 1900 starts on a Monday but are asked to count from 1901.
	 * @return
	 */
	private int bruteForce()
	{
		int dow = 1; // starts on Monday
		int sundays = 0;
		boolean isLeapYear = false;
		
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
	 * Try using the Calendar format
	 * @return
	 */
	private int faster()
	{
		String date = "01 January 1901"; // first sunday
		DateFormat formatter;
		Date d = null;
		formatter = new SimpleDateFormat("dd MMMM yyyy");
		try {
			d = formatter.parse(date);
		} catch (ParseException e) {
			e.printStackTrace();
		}
		Calendar cal = Calendar.getInstance();
		cal.setTime(d);
		int count = 0;
		
		while (cal.get(Calendar.YEAR) < 2001) {
			if (cal.get(Calendar.DAY_OF_WEEK) == Calendar.SUNDAY) {
				count++;
			}
			cal.add(Calendar.MONTH, 1);
		}
		
		return count;
	}

}
