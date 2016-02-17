package util;

import java.math.BigInteger;
import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.List;

public class Basic
{

   /**
    * returns the sum from 1 to n
    * 
    * @param n
    * @return
    */
   public static int getNSum(int n)
   {
      return n * (n + 1) / 2;
   }

   /**
    * Returns the nth fibonacci number, starting with 0,1,1,2,3,5,...
    * 
    * @param n
    * @return
    */
   public static int getNthFibonacci(int n)
   {
      final double s5 = Math.sqrt(5);
      int fn = (int) ((Math.pow(1 + s5, n) - Math.pow(1 - s5, n)) / (Math.pow(
            2, n) * s5));
      return fn;
   }

   /**
    * Get a list of factor in the order they were discovered (should be smallest to largest 
    * and does include duplicates for orders of primes)
    * 
    * @param n
    * @return
    */
   public static List<Long> getPrimeFactors(long n)
   {
      List<Long> factors = new ArrayList<Long>();
      long factor = 2; // get the special case out of the way first
      while (n % factor == 0 && n >= factor)
      {
         factors.add(factor);
         n = n / factor;
      }
      factor++;
      while (n > 1)
      {
         while (n % factor != 0 && factor * factor <= n)
         {
            factor += 2;
         }
         if (factor * factor > n)
            factor = n;
         factors.add(factor);
         n = n / factor;
      }
      return factors;
   }
   
   /**
    * Get the list of prime factors using a list of primes to generate
    * @param n
    * @param primes
    * @return
    */
   public static List<Long> getPrimeFactors(long n, List<Integer> primes)
   {
      List<Long> factors = new ArrayList<Long>();
      
      int p_idx = 0;
      
      if (Long.valueOf(primes.get(primes.size() - 1)) * Long.valueOf(primes.get(primes.size() - 1)) < n)
      {
         System.out.println("Max prime " + primes.get(primes.size() - 1) + " is less than " + n + "^2");
         return null; // we may not have enough primes
      }
      
      while (n > 1)
      {
         while (n % primes.get(p_idx) == 0)
         {
            factors.add(Long.valueOf(primes.get(p_idx)));
            n = n / primes.get(p_idx);
         }
         p_idx++;
      }
      
      return factors;
   }

   /**
    * Get all the divisors for a number including mirrors.<br>
    * Almost certainly a faster way is getting the factors, then doing
    * combinations of n,n-1,n-2...n-n+1 and adding the uniques to the list. This
    * is the fastest implementation I've come up with so far (faster than
    * factoring and combining by 10x) ie: 12 = 1,2,3,4,6,12
    * 
    * @param num
    * @return
    */
   public static List<Long> getDivisors(long num)
   {
      List<Long> divisors = new ArrayList<Long>();
      // get all the initial divisors
      if (num == 0L)
      {
         divisors.add(0L);
         return divisors;
      }
      for (long ii = 1; ii * ii <= num; ii++)
      {
         if (num % ii == 0)
         {
            divisors.add(ii);
         }
      }
      // skip the duplicate at the square root
      int ii = divisors.size() - 1;
      if (divisors.get(ii) * divisors.get(ii) == num)
      {
         ii--;
      }
      // do simple division to add the mirrors in the right order.
      for (; ii >= 0; ii--)
      {
         divisors.add((num / divisors.get(ii)));
      }
      return divisors;
   }
   
   /**
    * Get the number of divisors from the factor list by using the power of
    * the primes for combinatorials. Not valid for 0 which returns an empty
    * list of factors.
    * @param factors
    * @return
    */
   public static long getNumberOfDivisorsFromFactors(List<Long> factors)
   {
      long answer = 1;
      if (factors.size() == 0)
         return 1;
      long previous = 0;
      int pCount = 0;
      
      for (int ii = 0; ii < factors.size(); ii++)
      {
         if (factors.get(ii).longValue() == previous)
         {
            pCount++;
         }
         else
         {
            answer *= pCount + 1;
            pCount = 1;
            previous = factors.get(ii).longValue();
         }
      }
      answer *= pCount + 1;
      return answer;
   }
   
   /**
    * The formula for a sum of divisors from factors is the multiplicative product of
    * (p^(n+1)-1)/(p-1) where p is the prime factor and n is the power of that prime
    * (number of repetitions). Not valid for 0. 
    * @param factors
    * @return
    */
   public static long getSumOfDivisorsFromFactors(List<Long> factors)
   {
      long previous = 0;
      int pCount = 0;
      long sum = 1;
      
      for (int ii = 0; ii < factors.size(); ii++)
      {
         if (factors.get(ii).longValue() == previous)
         {
            pCount++;
         } 
         else 
         {
            long j = previous;
            for (int jj = 0; jj < pCount; jj++)
            {
               j *= previous;
            }
            sum *= (j-1)/(previous-1);
            pCount = 1;
            previous = factors.get(ii).longValue();
         }
      }
      
      long j = previous;
      for (int jj = 0; jj < pCount; jj++)
      {
         j *= previous;
      }
      sum *= (j-1)/(previous-1);
      
      return sum;
   }

   /**
    * Reverse and return a long (look into faster shifting way to do this in
    * c++)
    * 
    * @param num
    * @return
    */
   public static long reverse(long num)
   {
      long n = num;
      long r = 0;
      while (n > 0)
      {
         r = r * 10 + n % 10;
         n = (n - n % 10) / 10;
      }
      return r;
   }

   /**
    * Reverse and return an int
    * 
    * @param num
    * @return
    */
   public static int reverse(int num)
   {
      int n = num;
      int r = 0;
      while (n > 0)
      {
         r = r * 10 + n % 10;
         n = (n - n % 10) / 10;
      }
      return r;
   }

   /**
    * Reverse and return a BigInteger
    * 
    * @param num
    * @return
    */
   public static BigInteger reverse(BigInteger num)
   {
      String l = reverse(num.toString());
      return new BigInteger(l);
   }

   /**
    * Reverse and return a string
    * 
    * @param s
    * @return
    */
   public static String reverse(String s)
   {
      return new StringBuilder(s).reverse().toString();
   }

   /**
    * Test a BigInteger for Palindrome-ness
    * 
    * @param num
    * @return
    */
   public static boolean isPalindrome(BigInteger num)
   {
      return isPalindrome(num.toString());
   }

   /**
    * Return whether a number is a palindrome or not. This is 4 times slower
    * than the int version
    * 
    * @param num
    * @return
    */
   public static boolean isPalindrome(String num)
   {
      for (int ii = 0; ii < num.length() / 2; ii++)
      {
         if (num.charAt(ii) != num.charAt(num.length() - 1 - ii))
            return false;
      }
      return true;
   }

   /**
    * Return whether a number is a palindrome or not. This is 4 times faster
    * than the string version
    * 
    * @param num
    * @return
    */
   public static boolean isPalindrome(int num)
   {
      int r = reverse(num);
      return r == num;
   }

   /**
    * Return whether a number is a palindrome or not. This is 4 times faster
    * than the string version
    * 
    * @param num
    * @return
    */
   public static boolean isPalindrome(long num)
   {
      long r = reverse(num);
      return r == num;
   }

   /**
    * Return the factorial of n. Gets too big pretty fast, though.
    * @param n
    * @return
    */
   public static long factorial(long n)
   {
      if (n == 0)
         return 1;
      long fact = n;
      for (long i = n - 1; i > 1; i--)
      {
         fact *= i;
      }
      return fact;
   }

   /**
    * An amicable number is a number where the sum of its divisors is a
    * different number ... whose divisors sum to be the original number. Sum of
    * divisors should not include the number itself.
    * 
    * @param num
    *           - the initial number
    * @return - -1 if there is not amicable number, or the amicable number
    */
   public static int getAmicableNumber(int num)
   {
      List<Long> d = getDivisors(num);
      int sum = 0;
      for (int ii = 0; ii < d.size() - 1; ii++)
      {
         sum += d.get(ii);
      }
      if (num == sum)
      {
         return -1; // the same number isn't a pair
      }
      d = getDivisors(sum);
      int sum2 = 0;
      for (int ii = 0; ii < d.size() - 1; ii++)
      {
         sum2 += d.get(ii);
      }
      if (sum2 == num)
      {
         return sum;
      }
      return -1;
   }
   
   /**
    * Check any number or list of numbers to see if 1-9 is contained
    * (may need to adjust this later for ranges or to include 0)
    * @param nums
    * @return
    */
   public static boolean isPandigital(int... nums)
   {
      int mask = 0;
      for (int ii = 0; ii < nums.length; ii++)
      {
         int n = nums[ii];
         while (n != 0)
         {
            int digit = n % 10;
            if (digit == 0)
               return false;
            
            mask |= (1 << (digit - 1));
            
            n = n/10;
         }
      }
      return mask == 0x01ff; // 1 1111 1111
   }
   
   /**
    * Check if a string is 1-9 pandigital
    * @param num
    * @return
    */
   public static boolean isPandigital(String num)
   {
   	for (char c = '1'; c <= '9'; c++)
   	{
   		if (num.indexOf(c) < 0)
   			return false;
   	}
   	return num.length() == 9;
   }
   
   /**
    * Finds the largest common factor to reduce by
    * @param num
    * @param den
    * @return the largest factor or -1
    */
   public static int reduce(int num, int den)
   {
   	List<Long> d1 = Basic.getDivisors(num);
   	List<Long> d2 = Basic.getDivisors(den);
   	for (int ii = d1.size() - 1; ii >= 0; ii--)
   	{
   		if (d2.contains(d1.get(ii)))
   		{
   			return d1.get(ii).intValue();
   		}
   	}
   	return -1;
   }
   
   /**
    * Determine if this is a particular n-gonal number. For a triangular number, for example
    * set n = 3 and num to the number to be tested
    * @param n - n-gonal (3 for triangular, 4 for square, 5 for pentagonal, etc)
    * @param num - the number to be tested
    * @return
    */
   public static boolean isNgonalNumber(int n, long num)
   {
      long b = (8*n - 16)*num + (n-4)*(n-4);
      double b_sqrt = Math.sqrt(b);
      if ((long)b_sqrt*(long)b_sqrt != b)
         return false;
      if (((long)b_sqrt + n - 4) % (2*n - 4) == 0)
         return true;
      return false;
   }
   
   /**
    * Get the idx'th n-gonal number. To get the third pentagonal number, use n=5, idx=3
    * @param n
    * @param idx
    * @return
    */
   public static long getNgonalNumber(int n, int idx)
   {
      return (idx*idx*(n-2)-idx*(n-4))/2;
   }

   /**
    * A triangle number is the number 1+2+3 for the third, +4 for the fourth, 
    * etc.
    * 1-indexed
    * 
    * @param n
    * @return
    */
   public static long getTriangleNumber(long n)
   {
      return n * (n + 1L) / 2L;
   }

   /**
    * Return true if val is a triangle number
    * @param val
    * @return
    */
   public static boolean isTriangleNumber(long val)
   {
      return isNgonalNumber(3,val);
   }
   
   /**
    * Return the nth pentagonal number
    * 1-indexed
    * @param n
    * @return
    */
   public static long getPentagonalNumber(long n)
   {
      return n * (3*n - 1)/2;
   }
   
   /**
    * Return true if val is a pentagonal number
    * @param val
    * @return
    */
   public static boolean isPentagonalNumber(long val)
   {
      return isNgonalNumber(5,val);
   }

   /**
    * Get the nth hexagonal number 
    * 1-indexed
    * @param n
    * @return
    */
   public static long getHexagonalNumber(long n)
   {
      return n * (2*n-1);
   }
   
   public static boolean isHexagonalNumber(long val)
   {
      return isNgonalNumber(6,val);
   }
   
   /**
    * Get the nth heptagonal number 
    * 1-indexed
    * @param n
    * @return
    */
   public static long getHeptagonalNumber(long n)
   {
      // n=n(5n−3)/2 1, 7, 18, 34, 55, ...
      return n * (5*n-3) / 2;
   }
   
   public static boolean isHeptagonalNumber(long val)
   {
      return isNgonalNumber(7,val);
   }
   
   /**
    * Get the nth octagonal number 
    * 1-indexed
    * @param n
    * @return
    */
   public static long getOctagonalNumber(long n)
   {
      // n=n(3n−2) 1, 8, 21, 40, 65, ...
      return n * (3*n-2);
   }
   
   public static boolean isOctagonalNumber(long val)
   {
      return isNgonalNumber(8,val);
   }

   /**
    * Return true if num is a perfect square
    * @param num
    * @return
    */
   public static boolean isSquare(long num)
   {
      double b_sqrt = Math.sqrt(num);
      if ((long)b_sqrt*(long)b_sqrt != num)
         return false;
      return true;
   }
   
   /**
    * Add two fractions together and return the numerator / denominator pair in an array
    * @param n1
    * @param d1
    * @param n2
    * @param d2
    * @return
    */
   public static int[] fractionCombine(int n1, int d1, int n2, int d2)
   {
      int n3 = n1*d2 + n2*d1;
      int d3 = d1*d2;
      int common = reduce(n3,d3);
      return new int[] {n3/common,d3/common};
   }
}
