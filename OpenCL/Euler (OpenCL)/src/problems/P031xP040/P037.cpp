#include "../../base/problem.h"

#include <set>

class P037: public Problem
{
	/**
	 * P037<br>
	 * The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right,
	 * and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
	 * Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
	 * NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
	 * Ans: 748317
	 */
	public:
		P037()
		{
			problem_number = 37;
			variations = 1;
		}
		~P037() {}

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
			size = 500000;
			int initialVal = 0;

			cl->init("src/problems/P031xP040/P037.cl","brute");
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
			size = 511;
			int initialVal = 0;

			cl->init("src/problems/P031xP040/P037.cl","optimized");
			cl->createReadWriteMemory( sizeof(int),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem,
					sizeof(int), &size);
			cl->waitForQueue(); // sync
			setThreads(size);
			return true;
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
