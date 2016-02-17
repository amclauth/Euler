
#include "test.h"
#include "testBasic.cpp"

int main(void) {
	test *basic = new TestBasic();
	basic->run();
	delete basic;
}
