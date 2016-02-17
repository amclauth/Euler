#include "../../base/problem.h"

class P027: public Problem
{
	/**
	 * P027<br>
	 * Euler published the remarkable quadratic formula:
	 * n² + n + 41
	 * It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39. However,
	 * when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41, 41² + 41 + 41 is clearly divisible by 41.
	 * Using computers, the incredible formula  n²  79n + 1601 was discovered, which produces 80 primes for the consecutive values n = 0 to 79.
	 * The product of the coefficients, 79 and 1601, is 126479.
	 * Considering quadratics of the form:
	 * n² + an + b, where |a|  1000 and |b|  1000
	 * where |n| is the modulus/absolute value of n
	 * e.g. |11| = 11 and |4| = 4
	 * Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive
	 * values of n, starting with n = 0.
	 * Ans: -59231
	 */
	public:
		P027()
		{
			problem_number = 27;
			variations = 1;
		}
		~P027() {}

		bool setup(int variation)
		{
			bool retval = false;
			cl = new CLKernel(kernelsize);
			switch (variation)
			{
				case 0:
				case -1:
					retval = brute_setup();
					break;
				case 1:
					retval = opt_setup();
					break;
				default:
					retval = false;
			}
			return retval;
		}

		bool teardown(int variation)
		{
			bool retval = false;
			switch (variation)
			{
				case 0:
				case -1:
					retval = brute_teardown();
					break;
				case 1:
					retval =opt_teardown();
					break;
				default:
					retval = false;
			}
			cl->releaseKernel();
			return retval;
		}

		void execute(int variation)
		{
			switch (variation)
			{
				case 0:
				case -1:
					brute();
					break;
				case 1:
					optimized();
					break;
				default:
					std::cout << "NOOP!" << std::endl;
					break;
			}
		}

	private:

		int size;

		/**
		 * Brute force version
		 *
		 */
		bool brute_setup()
		{
			size = 1000000;
			int initialVal = 0;

			cl->init("src/problems/P021xP030/P027.cl","brute");
         cl->createReadWriteMemory( sizeof(int),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
         cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem,
					sizeof(int), &size);
			cl->waitForQueue(); // sync
			setThreads(size);
			return true;
		}

		bool brute_teardown()
		{
			int ans;
			if (!cl->transferGPUObjectToCPU(sizeof(int), &answer_mem, &ans))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			ans = ans % 10000000;
			if (ans > 1000000)
			{
				ans = ans - 10000000;
			}
			answer = to_string(ans);
			clReleaseMemObject(answer_mem);
			return true;
		}

		int brute()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}

		/**
		 *
		 */
		bool opt_setup()
		{

			return true;
		}

		bool opt_teardown()
		{

			return true;
		}

		int optimized()
		{

			return 0;
		}
};
