#include "../../base/problem.h"

class P014: public Problem
{
	/**
	 * P014<br>
	 * The following iterative sequence is defined for the set of positive integers:
	 * n -> n/2 (n is even)
	 * n -> 3n + 1 (n is odd)
	 * Using the rule above and starting with 13, we generate the following sequence:
	 * 13  40  20  10  5  16  8  4  2  1
	 * It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem),
	 * it is thought that all starting numbers finish at 1.
	 * Which starting number, under one million, produces the longest chain?
	 * NOTE: Once the chain starts the terms are allowed to go above one million.
	 * Ans: 837799
	 */
	public:
		P014()
		{
			problem_number = 14;
			variations = 2;
		}
		~P014() {}

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

		int size;
		cl_mem cache_mem;

		/**
		 * Brute force version
		 *
		 */
		bool brute_setup()
		{
			size = 999999;
			int initialVal = 0;

			cl->init("src/problems/P011xP020/P014.cl","brute");
         cl->createReadWriteMemory(sizeof(int),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem,
					sizeof(int), &size);
			cl->waitForQueue(); // sync
			setThreads((size+1)/4); // odds above 500k
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
			ans = ans % 1000000; // get rid of the count
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
		 * Try to do the same thing, but in a base of 10M rather than 10
		 */
		bool opt_setup()
		{
			size = 999999;
			int initialVal = 0;
			int cacheVals[1000000] = { 0 };

			cl->init("src/problems/P011xP020/P014.cl","optimized");
			cl->createReadWriteMemory(sizeof(int),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->createReadWriteMemory(sizeof(int)*1000000,&cache_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*1000000,&cache_mem,cacheVals);
			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &cache_mem,
					sizeof(int), &size);
			cl->waitForQueue(); // sync
			setThreads(size);
			return true;
		}

		bool opt_teardown()
		{
			int ans;
			if (!cl->transferGPUObjectToCPU(sizeof(int), &answer_mem, &ans))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			ans = ans % 1000000; // get rid of the count
			answer = to_string(ans);
			clReleaseMemObject(answer_mem);
			clReleaseMemObject(cache_mem);
			return true;
		}

		int optimized()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}
};
