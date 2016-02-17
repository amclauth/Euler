#include "../../base/problem.h"
#include "../../util/basic.h"
#include <climits>

class P005: public Problem
{
	/**
	 * P005<br>
	 * 2520 is the smallest number that can be divided by each of the numbers from
	 * 1 to 10 without any remainder.
	 *
	 * What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
	 * Ans: 232792560
	 */
	public:
		P005()
		{
			problem_number = 5;
			variations = 2;
		}
		~P005() {}

		bool setup(int variation)
		{
			bool retval = false;
			cl = new CLKernel(kernelsize);
			switch (variation)
			{
				case 0:
					retval = brute_setup();
					break;
				case 1:
				case -1:
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
					retval = brute_teardown();
					break;
				case 1:
				case -1:
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
					brute();
					break;
				case 1:
				case -1:
					optimized();
					break;
				default:
					std::cout << "NOOP!" << std::endl;
					break;
			}
		}

	private:

		cl_mem thread_mem;
		/**
		 * Brute force version
		 * Check every single item to see if it's a palindrome!
		 */
		bool brute_setup()
		{
			int initialVal = INT_MAX;
			int count = 1000000; // how many threads to process at once ... just a WAG

			cl->init("src/problems/P001xP010/P005.cl","brute");
         cl->createWriteOnlyMemory(sizeof(int),&answer_mem);
         cl->createReadOnlyMemory(sizeof(int),&thread_mem);

			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->transferCPUObjectToGPU(sizeof(int),&thread_mem,&count);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &thread_mem,
					sizeof(cl_mem), &answer_mem);
			cl->waitForQueue(); // sync
			setThreads(count);
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
			answer = to_string(ans);
			clReleaseMemObject(answer_mem);
			clReleaseMemObject(thread_mem);
			return true;
		}

		int brute()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}

		cl_mem prime_mem;
		int count;

		/**
		 * All divisors together are 2, 3, 2,2, 5, 2,3, 7, 2,2,2, 3,3, 2,5,
		 * 11, 2,2,3, 13, 2,7, 3,5, 2,2,2,2 17, 2,3,3, 19, 2,2,5
		 * The answer is the largest number of "common" primes, so 4 2's, 2 3's,
		 * a single 5,7,11,13,17,19, all multiplied together. We can make it general
		 * by searching for each prime's coefficient.
		 */
		bool opt_setup()
		{
			int primes[] = {2,3,5,7,11,13,17,19};
			count = 8; // number of primes

			cl->init("src/problems/P001xP010/P005.cl","optimized");
			cl->createReadOnlyMemory(sizeof(int)*count,&prime_mem);
			cl->createReadOnlyMemory(sizeof(int),&thread_mem);

			cl->transferCPUObjectToGPU(sizeof(int)*count,&prime_mem,primes);
			cl->transferCPUObjectToGPU(sizeof(int),&thread_mem,&count);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &prime_mem,
					sizeof(cl_mem), &thread_mem);
			cl->waitForQueue(); // sync
			setThreads(count);
			return true;
		}

		bool opt_teardown()
		{
			int ans[8];
			if (!cl->transferGPUObjectToCPU(sizeof(int)*count, &prime_mem, &ans))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			int finalAns = 1;
			for (int ii = 0; ii < count; ii++)
				finalAns *= ans[ii];
			answer = to_string(finalAns);
			clReleaseMemObject(prime_mem);
			clReleaseMemObject(thread_mem);
			return true;
		}

		int optimized()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}
};
