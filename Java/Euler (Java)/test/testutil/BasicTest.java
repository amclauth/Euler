package testutil;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.junit.Test;

import util.Basic;

public class BasicTest {

	@Test
	public void test_n_sum()
	{
		int sum = 0;
		for (int ii = 0; ii < 100; ii++)
		{
			sum += ii;
			assertEquals(sum,Basic.getNSum(ii));
		}
	}
	
	@Test
	public void test_fibonacci()
	{
		// 0,1,1,2,3,5,8,...
		int a = 0;
		int b = 1;
		int fib = b;
		assertEquals(0,Basic.getNthFibonacci(0));
		assertEquals(1,Basic.getNthFibonacci(1));
		for (int ii = 2; ii < 20; ii++)
		{
			assertEquals(fib,Basic.getNthFibonacci(ii));
			a = b;
			b = fib;
			fib = a+b;
		}
	}
	
	@Test
	public void test_factors()
	{
		long n = 60;
		List<Long> factors = Basic.getPrimeFactors(n);
      assertEquals(4,factors.size());
		assertEquals(new Long(2),factors.get(0));
		assertEquals(new Long(2),factors.get(1));
		assertEquals(new Long(3),factors.get(2));
		assertEquals(new Long(5),factors.get(3));
	}
	
	@Test
   public void test_factors_primes()
   {
	   List<Integer> primes = new ArrayList<Integer>();
	   primes.add(2);
	   primes.add(3);
	   primes.add(5);
	   primes.add(7);
	   primes.add(11);
	   primes.add(13);
	   primes.add(17);
	   primes.add(23);
	   primes.add(29);
	   primes.add(31);
	   primes.add(37);
	   primes.add(41);
	   primes.add(43);
	   primes.add(47);
	   primes.add(53);
	   primes.add(59);
      long n = 60;
      List<Long> factors = Basic.getPrimeFactors(n, primes);
      assertEquals(4,factors.size());
      assertEquals(new Long(2),factors.get(0));
      assertEquals(new Long(2),factors.get(1));
      assertEquals(new Long(3),factors.get(2));
      assertEquals(new Long(5),factors.get(3));
   }
	
	@Test
	public void test_reverse()
	{
		int ni[] = {0,1,10,15,101,123,93487};
		int ri[] = {0,1,1,51,101,321,78439};
		for (int ii = 0; ii < ni.length; ii++)
		{
			assertEquals(ri[ii],Basic.reverse(ni[ii]));
		}
		
		long nl[] = {0,1,10,15,101,123,93487};
		long rl[] = {0,1,1,51,101,321,78439};
		for (int ii = 0; ii < nl.length; ii++)
		{
			assertEquals(rl[ii],Basic.reverse(nl[ii]));
		}
		
		String ns[] = {"0","1","10","101","123","93487"};
		String rs[] = {"0","1","01","101","321","78439"};
		for (int ii = 0; ii < ns.length; ii++)
		{
			assertEquals(rs[ii],Basic.reverse(ns[ii]));
		}
		
		BigInteger nb[] = {BigInteger.ZERO,BigInteger.ONE,BigInteger.valueOf(10L),
				BigInteger.valueOf(101L),BigInteger.valueOf(123L),
				BigInteger.valueOf(93487L)};
		BigInteger rb[] = {BigInteger.ZERO,BigInteger.ONE,BigInteger.ONE,
				BigInteger.valueOf(101L),BigInteger.valueOf(321L),
				BigInteger.valueOf(78439L)};
		for (int ii = 0; ii < nb.length; ii++)
		{
			assertEquals(rb[ii],Basic.reverse(nb[ii]));
		}
	}
	
	@Test
	public void test_palindrome()
	{
		assertTrue(Basic.isPalindrome(991199));
		assertTrue(Basic.isPalindrome(999));
		assertTrue(Basic.isPalindrome(1));
		assertFalse(Basic.isPalindrome(9911));
		assertFalse(Basic.isPalindrome(10));
		
		assertTrue(Basic.isPalindrome(991199L));
		assertTrue(Basic.isPalindrome(999L));
		assertTrue(Basic.isPalindrome(1L));
		assertFalse(Basic.isPalindrome(9911L));
		assertFalse(Basic.isPalindrome(10L));
		
		assertTrue(Basic.isPalindrome(BigInteger.valueOf(991199L)));
		assertTrue(Basic.isPalindrome(BigInteger.valueOf(999L)));
		assertTrue(Basic.isPalindrome(BigInteger.valueOf(1L)));
		assertFalse(Basic.isPalindrome(BigInteger.valueOf(9911L)));
		assertFalse(Basic.isPalindrome(BigInteger.valueOf(10L)));
		
		assertTrue(Basic.isPalindrome("991199"));
		assertTrue(Basic.isPalindrome("999"));
		assertTrue(Basic.isPalindrome("1"));
		assertFalse(Basic.isPalindrome("9911"));
		assertFalse(Basic.isPalindrome("10"));
	}
	
	@Test
	public void testTriangle()
	{
		int triangle = 0;
		for (int ii = 1; ii < 100; ii++)
		{
			triangle += ii;
			assertEquals(triangle, Basic.getTriangleNumber(ii));
		}
	}
	
	@Test
	public void testDivisors()
	{
		List<Long> divisors;
		divisors = Basic.getDivisors(1);
		assertEquals(1, divisors.size());
		assertEquals(1, divisors.get(0).longValue());

		divisors = Basic.getDivisors(30);
		assertEquals(8, divisors.size());
		assertEquals(1, divisors.get(0).longValue());
		assertEquals(2, divisors.get(1).longValue());
		assertEquals(3, divisors.get(2).longValue());
		assertEquals(5, divisors.get(3).longValue());
		assertEquals(6, divisors.get(4).longValue());
		assertEquals(10, divisors.get(5).longValue());
		assertEquals(15, divisors.get(6).longValue());
		assertEquals(30, divisors.get(7).longValue());
		
		divisors = Basic.getDivisors(25);
		assertEquals(3, divisors.size());
		assertEquals(1, divisors.get(0).longValue());
		assertEquals(5, divisors.get(1).longValue());
		assertEquals(25, divisors.get(2).longValue());
	}
	
	@Test
	public void testNumberOfDivisors()
	{
	   for (int ii = 2; ii < 100; ii++)
	   {
	      List<Long> divisors = Basic.getDivisors(ii);
         List<Long> factors = Basic.getPrimeFactors(ii);
         
         assertEquals(divisors.size(), Basic.getNumberOfDivisorsFromFactors(factors));
	   }
	}
	
	@Test
	public void testSumOfDivisorsFromFactors()
	{
	   for (int ii = 1; ii < 100; ii++)
	   {
   	   List<Long> divisors = Basic.getDivisors(ii);
   	   List<Long> factors = Basic.getPrimeFactors(ii);
   	   
   	   long sum = 0;
   	   for (Long l : divisors)
   	   {
   	      sum += l;
   	   }
   	   assertEquals(sum, Basic.getSumOfDivisorsFromFactors(factors));
	   }
	}
	
	@Test
	public void testFactorial()
	{
		long fac = 1;
		for (int ii = 1; ii < 20; ii++)
		{
			fac *= ii;
			assertEquals(fac, Basic.factorial(ii));
		}	
	}
	
	@Test
	public void testAmicable()
	{
	   assertEquals(220, Basic.getAmicableNumber(284));
	   assertEquals(284, Basic.getAmicableNumber(220));
	   assertEquals(-1, Basic.getAmicableNumber(8)); // divisors are 1,2,4 ... 7 is 1
	   assertEquals(-1, Basic.getAmicableNumber(6)); // divisors are 1,2,3 == 6
	}
	
	@Test 
	public void testPandigital()
	{
	   assertTrue(Basic.isPandigital(123465789));
	   assertTrue(Basic.isPandigital(978345621));
	   assertFalse(Basic.isPandigital(1203465789));
	   assertFalse(Basic.isPandigital(122465789));
	   assertFalse(Basic.isPandigital(12465789));
	   
	   assertTrue(Basic.isPandigital("123465789"));
      assertTrue(Basic.isPandigital("978345621"));
      assertFalse(Basic.isPandigital("1203465789"));
      assertFalse(Basic.isPandigital("122465789"));
      assertFalse(Basic.isPandigital("12465789"));
	}
	
	@Test
	public void testReduce()
	{
	   assertEquals(5, Basic.reduce(10, 15));
	   assertEquals(1, Basic.reduce(10, 13));
	}
	
	@Test
	public void testTriangular()
	{
	   int[] triangulars = {1, 3, 6, 10, 15, 21};
	   for (int ii = 0; ii < triangulars.length; ii++)
      {
         assertEquals(triangulars[ii], Basic.getTriangleNumber(ii+1));
      }
      for (int ii = 1; ii <= 21; ii++)
      {
         if (Arrays.binarySearch(triangulars, ii) >= 0)
         {
            assertTrue(ii + "", Basic.isTriangleNumber(ii));
            assertTrue(ii + "", Basic.isNgonalNumber(3, ii));
         }
         else
         {
            assertFalse(ii + "", Basic.isTriangleNumber(ii));
            assertFalse(ii + "", Basic.isNgonalNumber(3, ii));
         }
      }
	}
	
	@Test
	public void testPentagonal()
	{
	   long[] pentagonals = {1, 5, 12, 22, 35, 51, 70, 92, 117, 145};
	   for (int ii = 0; ii < pentagonals.length; ii++)
	   {
	      assertEquals(pentagonals[ii], Basic.getPentagonalNumber(ii+1));
	   }
	   for (long ii = 1; ii <= 145; ii++)
	   {
	      if (Arrays.binarySearch(pentagonals, ii) >= 0)
	      {
	         assertTrue(ii + "", Basic.isPentagonalNumber(ii));
	         assertTrue(ii + "", Basic.isNgonalNumber(5, ii));
	      }
	      else
	      {
	         assertFalse(ii + "", Basic.isPentagonalNumber(ii));
	         assertFalse(ii + "", Basic.isNgonalNumber(5, ii));
	      }
	   }
	}
	
	@Test
   public void testHexagonal()
   {
      long[] hexagonals = {1, 6, 15, 28, 45};
      for (int ii = 0; ii < hexagonals.length; ii++)
      {
         assertEquals(hexagonals[ii], Basic.getHexagonalNumber(ii+1));
      }
      for (long ii = 1; ii <= 45; ii++)
      {
         if (Arrays.binarySearch(hexagonals, ii) >= 0)
         {
            assertTrue(ii + "", Basic.isHexagonalNumber(ii));
            assertTrue(ii + "", Basic.isNgonalNumber(6, ii));
         }
         else
         {
            assertFalse(ii + "", Basic.isHexagonalNumber(ii));
            assertFalse(ii + "", Basic.isNgonalNumber(6, ii));
         }
      }
   }
	
	@Test
   public void testHeptagonal()
   {
      long[] heptagonals = {1, 7, 18, 34, 55};
      for (int ii = 0; ii < heptagonals.length; ii++)
      {
         assertEquals(heptagonals[ii], Basic.getHeptagonalNumber(ii+1));
      }
      for (long ii = 1; ii <= 55; ii++)
      {
         if (Arrays.binarySearch(heptagonals, ii) >= 0)
         {
            assertTrue(ii + "", Basic.isHeptagonalNumber(ii));
            assertTrue(ii + "", Basic.isNgonalNumber(7, ii));
         }
         else
         {
            assertFalse(ii + "", Basic.isHeptagonalNumber(ii));
            assertFalse(ii + "", Basic.isNgonalNumber(7, ii));
         }
      }
   }
	
	@Test
   public void testOctagonal()
   {
      long[] octagonals = {1, 8, 21, 40, 65};
      for (int ii = 0; ii < octagonals.length; ii++)
      {
         assertEquals(octagonals[ii], Basic.getOctagonalNumber(ii+1));
      }
      for (long ii = 1; ii <= 65; ii++)
      {
         if (Arrays.binarySearch(octagonals, ii) >= 0)
         {
            assertTrue(ii + "", Basic.isOctagonalNumber(ii));
            assertTrue(ii + "", Basic.isNgonalNumber(8, ii));
         }
         else
         {
            assertFalse(ii + "", Basic.isOctagonalNumber(ii));
            assertFalse(ii + "", Basic.isNgonalNumber(8, ii));
         }
      }
   }
	
	@Test
	public void testNgonal()
	{
	   for (int ii = 1; ii <= 20; ii++)
	   {
	      assertEquals("3-" + ii,Basic.getTriangleNumber(ii),Basic.getNgonalNumber(3, ii));
	      assertEquals("4-" + ii,ii*ii,Basic.getNgonalNumber(4, ii));
	      assertEquals("5-" + ii,Basic.getPentagonalNumber(ii),Basic.getNgonalNumber(5, ii));
	      assertEquals("6-" + ii,Basic.getHexagonalNumber(ii),Basic.getNgonalNumber(6, ii));
	      assertEquals("7-" + ii,Basic.getHeptagonalNumber(ii),Basic.getNgonalNumber(7, ii));
	      assertEquals("8-" + ii,Basic.getOctagonalNumber(ii),Basic.getNgonalNumber(8, ii));
	      
	      for (int jj = 3; jj <= 10; jj++)
	      {
	         assertTrue(Basic.isNgonalNumber(jj, Basic.getNgonalNumber(jj, ii)));
	      }
	   }
	   
	   for (int jj = 3; jj <= 10; jj++)
	   {
	      // generate the nGonals
	      Set<Integer> set = new HashSet<Integer>();
	      for (int ii = 1; ii <= 20; ii++)
	      {
	         set.add((int)Basic.getNgonalNumber(jj, ii));
	      }
	      for (int ii = 1; ii < 100; ii++)
	      {
	         if (set.contains(ii))
	         {
	            assertTrue(ii + " in " + jj + "-set",Basic.isNgonalNumber(jj, ii));
	         }
	         else
	         {
	            assertFalse(ii + " not in " + jj + "-set",Basic.isNgonalNumber(jj, ii));
	         }
	      }
	   }
	}
}
