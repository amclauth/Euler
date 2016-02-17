
#include "test.h"
#include "testBasic.cpp"
#include "testPrimes.cpp"
#include "testIO.cpp"

int main(void) {
	test *basic = new TestBasic();
	basic->run();
	delete basic;

	test *primes = new TestPrimes();
	primes->run();
	delete primes;

	test *io = new TestIO();
	io->run();
	delete io;
}
