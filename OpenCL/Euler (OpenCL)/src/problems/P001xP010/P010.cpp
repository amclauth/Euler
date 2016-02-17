#include "../../base/problem.h"

class P010: public Problem
{
	/**
	 * P010<br>
	 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.<br>
	 * Find the sum of all the primes below two million.<br>
	 * Ans: 142913828922
	 */
	public:
		P010()
		{
			problem_number = 10;
			variations = 2;
		}
		~P010() {}

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

		/**
		 * Brute force version
		 * Check every number to see if it's prime, then atomic add it
		 */
		bool brute_setup()
		{
			// 1 to 998 for each (because if a is 998, b and c both have to be 1
			size = 2000000;
			long initialVal = 1; // we will find "1" to be prime and skip 2, so need to offset

			cl->init("src/problems/P001xP010/P010.cl","brute");
         cl->createWriteOnlyMemory(sizeof(long),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(long),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem,
					sizeof(int), &size);         // the size
			cl->waitForQueue(); // sync
			setThreads(size/2-1);
			return true;
		}

		bool brute_teardown()
		{
			long ans;
			if (!cl->transferGPUObjectToCPU(sizeof(long), &answer_mem, &ans))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
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
		 * Same way to figure out if we're prime, but then do a reduction to add
		 */
		bool opt_setup()
		{
			size = 2000000;
			long initialVal = 1; // we will find "1" to be prime and skip 2, so need to offset

			cl->init("src/problems/P001xP010/P010.cl","optimized");
			cl->createWriteOnlyMemory(sizeof(long),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(long),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(long)*(1024), NULL,    // local scratch space
					sizeof(int), &size);         // the size
			cl->waitForQueue(); // sync
			setThreads(size/2-1);
			return true;
		}

		bool opt_teardown()
		{
			long ans;
			if (!cl->transferGPUObjectToCPU(sizeof(long), &answer_mem, &ans))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			answer = to_string(ans);
			clReleaseMemObject(answer_mem);
			return true;
		}

		int optimized()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}
};
