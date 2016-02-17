package testutil;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.ArrayList;
import java.util.List;

import org.junit.Test;

import util.Primes;

public class PrimeTest {

	@Test
	public void testPrimeGeneration()
	{
		List<Integer> primes = new ArrayList<Integer>();
		primes.add(2);
		primes.add(3);
		primes.add(5);
		primes.add(7);
		primes.add(11);
		primes.add(13);
		primes.add(17);
		primes.add(19);
		
		List<Integer> pN = new ArrayList<Integer>();
		pN.add(2);
		pN.add(3);
		for (int ii = 0; ii < primes.size() - 2; ii++)
		   Primes.addNextPrime(pN);
		
		List<Integer> pE = Primes.EratosthenesPrimesUpTo(20);
		
		assertEquals(primes.size(),pE.size());
		assertEquals(primes.size(),pN.size());
		
		for (int ii = 0; ii < primes.size(); ii++)
		{
			assertEquals(primes.get(ii),pE.get(ii));
			assertEquals(primes.get(ii),pN.get(ii));
			assertTrue(Primes.isPrime(pE.get(ii)));
			assertTrue(Primes.isPrime(pN.get(ii)));
		}
	}
	
	@Test
	public void nthPrimeTest()
	{
		List<Integer> primes = Primes.EratosthenesPrimesUpTo(10000);
		for (int ii = 10; ii < primes.size(); ii++)
		{
			// first prime is primes.get(0)
			assertEquals(primes.get(ii-1).intValue(),Primes.getNthPrime(ii));
		}
	}
}
