#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <math.h>

#include "../util/prime.h"
#include "test.h"
#include "../base/timer.h"

class TestPrimes: public test
{
	public:

		void run()
		{
			testPrimeGeneration();
			testPrimeGenSpeed();
			nthPrimeTest();
			if (passed)
			{
				std::cout << "PrimeTest:: SUCCESS! All tests passed." << std::endl;
			} else {
				std::cout << "PrimeTest:: !!!FAILURE!!! Tests failed." << std::endl;
			}
		}

	private:

		static const bool print = false;

		void testPrimeGeneration()
		{
			std::vector<int> primes;
			primes.push_back(2);
			primes.push_back(3);
			primes.push_back(5);
			primes.push_back(7);
			primes.push_back(11);
			primes.push_back(13);
			primes.push_back(17);
			primes.push_back(19);

			std::vector<int>* pE = prime::EratosthenesPrimesUpTo(20);
			std::vector<int>* pO = prime::OptimizedBrutePrimesUpTo(20);
			std::vector<int>* pB = prime::BrutePrimesUpTo(20);
			assertEquals(primes.size(),pE->size(),__func__,"ErosPrimes");
			assertEquals(primes.size(),pO->size(),__func__,"Optimized Primes");
			assertEquals(primes.size(),pB->size(),__func__,"Brute Primes");

			for (unsigned int ii = 0; ii < primes.size(); ii++)
			{
				assertEquals(primes[ii],pE->at(ii),__func__,"Eros");
				assertEquals(primes[ii],pO->at(ii),__func__,"Optimized");
				assertEquals(primes[ii],pB->at(ii),__func__,"Brute");
				assertTrue(prime::isPrime(primes[ii]),__func__,"Prime " + to_string(primes[ii]));
			}
			delete pE;
			delete pO;
			delete pB;
		}

		void testPrimeGenSpeed()
		{
			int max = (int) sqrt(INT_MAX);
			int min = 3;

			Timer *t = new Timer();

			if (print) std::cout << "idx,Eros,Opt,Brute" << std::endl;
			for (int ii = min; ii < max; ii += (ii < 1000 ? (ii < 100 ? 1 : 10) : 1000))
			{
				t->start();
				std::vector<int>* pE = prime::EratosthenesPrimesUpTo(ii);
				t->stop();
				if (print) std::cout << ii << "," << t->getDurationNs() << ",";

				t->start();
				std::vector<int>* pO = prime::OptimizedBrutePrimesUpTo(ii);
				t->stop();
				if (print) std::cout << t->getDurationNs() << ",";

				t->start();
				std::vector<int>* pB = prime::BrutePrimesUpTo(ii);
				t->stop();
				if (print) std::cout << t->getDurationNs() << std::endl;

				assertEquals(pE->size(),pO->size(),__func__,"PE vs PO Size");
				assertEquals(pE->size(),pB->size(),__func__,"PE vs PB Size");

				assertEquals(pE->back(),pO->back(),__func__,"PE end vs PO end");
				assertEquals(pE->back(),pB->back(),__func__,"PE end vs PB end");

				delete pE;
				delete pO;
				delete pB;
			}
		}

		void nthPrimeTest()
		{
			std::vector<int>* primes = prime::EratosthenesPrimesUpTo(10000);
			for (unsigned int ii = 10; ii < primes->size(); ii++)
			{
				// first prime is primes.get(0)
				assertEquals(primes->at(ii-1),prime::getNthPrime(ii),__func__);
			}
			delete primes;
		}
};
