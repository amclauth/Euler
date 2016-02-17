package problems.P026xP050;

import util.Basic;
import base.Problem;

/**
 * P033<br>
 * The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it 
 * may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by canceling the 9s.
 * We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
 * There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing 
 * two digits in the numerator and denominator.
 * If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
 * Ans: 100 
 * @return
 */
public class P033 extends Problem
{
   public P033()
   {
      problemNumber = 33;
      variations = 2;
   }

   @Override
   protected String execute(int variation)
   {
      switch (variation)
      {
         case 0:
            return bruteForce() + "";
         case -1:
         case 1:
            return faster() + "";
      }
      return null;
   }

   /**
    * Cycle through all numbers to see if they're non-trivial cancellations
    * @return
    */
   private long bruteForce()
   {
   	int numerator = 1;
   	int denominator = 1;
   	for (int num = 10; num <= 99; num++)
   	{
   		for (int den = num+1; den <= 99; den++)
   		{
   			// don't include powers of 10
   			if (num % 10 == 0 && den % 10 == 0)
   				continue;
   			int numA = num / 10;
   			int numB = num % 10;
   			int denA = den / 10;
   			int denB = den % 10;
   			if (
   					(numA == denA && num * denB == numB * den) ||
   					(numA == denB && num * denA == numB * den) ||
   					(numB == denA && num * denB == numA * den) ||
   					(numB == denB && num * denA == numA * den)
					)
   			{
   				numerator *= num;
   				denominator *= den;
   			}
   		}
   	}
   	return (long) (denominator / Basic.reduce(numerator, denominator));
   }
   
   /**
    * This problem can be reformulated as:
    * 1) ax/bx = a/b -or-
    * 2) ax/xb = a/b -or
    * 3) xa/bx = a/b -or
    * 4) xa/xb = a/b
    * 
    * So instead of searching 89*89 times, we can look for solutions to these individual problems:
    * 
    * 1) (10a+x)/(10b+x) = a/b => 10ab+xb = 10ab+xa => xa=xb => a=b (wrong because a must be less than b)
    * 2) (10a+x)/(10x+b) = a/b => 10ab+xb=10ax+ab => 9ab=10ax-bx => 9ab-9ax=ax-bx => 9a(b-x)=x(a-b)
    *    So since a < b, the RHS is negative, so b < x as well, so a < b < x < 10
    * 3) (10x+a)/(10b+x) = a/b => 10bx+ab=10ba+ax => 10bx-10ba=ax-ab => 9ab=10bx-ax => 9ab-9bx=bx-ax
    *    => 9b(a-x)=x(b-a), but we know that a<b, so the RHS must be positive, so a > x is implied. Also,
    *    we know that a!=x, b!=a otherwise, a=b=x, and we'd have a fraction of 1/1 which isn't allowed.
    *    => a-x=(xb-xa)/9b => a-x=xb/9b-xa/9b => a-x=x/9-xa/9b, but x can't be 9 since x < a < b < 10, 
    *    so x/9 is a fraction less than 1, and with x and a both less than b and x less than 9, xa/9b
    *    is also a fraction less than 1, but that would imply a-x is a fraction. Impossible
    * 4) (10x+a)/(10x+b) = a/b => 10ax+a^2=10bx+b^2 (wrong because a must be less than b)
    * 
    * So number 2 gives us the only solution. 
    * 
    * Continuing the solution:
    * a(b-x)=x(a-b)/9
    * LHS is an integer, so x(a-b) must be divisible by 9. Anything divisible by 9 is either a multiple of
    * 3, 6, or 9, but if x=3, then b=2 and a=1, but that doesn't create an integer on the RHS, so c must
    * be 6 or 9. With x as 6 or 9, (a-b) must be 3 or 6 (to make a multiple of 9). Let's reverse these so we 
    * can deal in positives and we have:
    * a(x-b)=x(b-a)/9
    * If x is 6, b-a (where a < b < c) must be 3 and the combos can only then be b=4 a=1 and b-5 a=2, and both
    * of those obviously fit the equation.
    * 
    * If x is 9, then we have a(9-b)=b-a => 9a-ab=b-a => 10a-ab=b => a=b/(10-b)
    * 
    * So while we could finish this with pen and paper, those are the only things left to /compute/, so let's
    * compute them
    * @return
    */
   private long faster()
   {
   	int numerator = 1;
   	int denominator = 1;
   	// form is ax/xb
   	// first add in a=1, b=4, c=6
   	numerator *= (10*1)+6;
   	denominator *= (10*6)+4;
   	// then add in a=2, b=5, c=6
   	numerator *= (10*2)+6;
   	denominator *= (10*6)+5;
   	// now we test for integer values where b < 9 and a could be 0, so 1<b<9
   	for (int b = 1; b < 9; b++)
   	{
   		double val = b/1.0/(10-b);
   		if (val == Math.floor(val))
   		{
   			int a = (int) val;
   			numerator *= (10*a)+9;
   			denominator *= (10*9)+b;
   		}
   	}
   	return (long) (denominator / Basic.reduce(numerator, denominator));
   }
}
