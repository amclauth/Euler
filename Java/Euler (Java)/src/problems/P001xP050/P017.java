package problems.P001xP050;

import java.util.HashMap;
import java.util.Map;

import base.Problem;

/**
 * P017<br>
 * If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
 * If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
 * NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen)
 * contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
 * Ans: 21124 
 * @return
 */
public class P017 extends Problem
{	
	public P017()
	{
		problemNumber = 17;
		variations = 2; 
	}

	@Override
	protected String execute(int variation)
	{
		switch (variation)
		{
		case 0:
			return bruteForce() + "";
		case 1:
		case -1:
			return faster() + "";
		}
		return null;
	}

	/**
	 * Programatically write everything out
	 * @return
	 */
	private long bruteForce()
	{
		Map<Integer,String> special = new HashMap<Integer,String>();
		special.put(0,"");
		special.put(1,"one");
		special.put(2,"two");
		special.put(3,"three");
		special.put(4,"four");
		special.put(5,"five");
		special.put(6,"six");
		special.put(7,"seven");
		special.put(8,"eight");
		special.put(9,"nine");
		special.put(10,"ten");
		special.put(11,"eleven");
		special.put(12,"twelve");
		special.put(13,"thirteen");
		special.put(14,"fourteen");
		special.put(15,"fifteen");
		special.put(16,"sixteen");
		special.put(17,"seventeen");
		special.put(18,"eighteen");
		special.put(19,"nineteen");
		special.put(20,"twenty");
		special.put(30,"thirty");
		special.put(40,"forty");
		special.put(50,"fifty");
		special.put(60,"sixty");
		special.put(70,"seventy");
		special.put(80,"eighty");
		special.put(90,"ninety");
		
		
		long count = 0;
		String s = "";
		
		for (int ii = 1; ii < 1000; ii++) {
			if (ii % 100 < 20) {
				count += special.get(ii % 100).length();
				s = special.get(ii % 100);
			} else {
				if (ii % 10 == 0) {
					count += special.get(ii % 100).length();
					s = special.get(ii % 100);
				} else {
					count += special.get(((int)((ii % 100) / 10))*10).length();
					count += special.get((int)(ii % 10)).length();
					s = special.get(((int)((ii % 100) / 10))*10) + "-" + special.get((int)(ii % 10));
				}
			}
			if (ii >= 100) {
				count += special.get((int)(ii / 100)).length();
				count += (new String("hundred")).length();
				if (ii % 100 != 0) {
					count += (new String("and")).length();
					s = "and " + s;
				}
				s = special.get((int)(ii / 100)) + " " + "hundred" + " " + s;
			}
//			System.out.println(s + ": " + count);
			
		}
		count += (new String("onethousand")).length();
		
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
	 * the "hundred" occurring 900 times, the "and" occurring 9*99 times (not on the even hundreds), and the 
	 * sum total of 1-100 occurring 9 times plus the characters for "one thousand"
	 * @return
	 */
	private long faster()
	{
		int ones = 3+3+5+4+4+3+5+5+4;
		int teens = 3+6+6+8+8+7+7+9+8+8;
		int tens = 8*ones + 10*(6+6+5+5+5+7+6+6);
		int pre_hundred = ones + teens + tens;
		int hundreds = 100*ones + 7*900 + 3*9*99 + pre_hundred*9;
		int one_thousand = 11;
		return pre_hundred + hundreds + one_thousand;
	}

}
