#include "../../base/problem.h"

class P021: public Problem
{
	/**
	 * P021<br>
	 * Let d(n) be defined as the sum of proper divisors of n (numbers less than n
	 * which divide evenly into n). If d(a) = b and d(b) = a, where a b, then a and
	 * b are an amicable pair and each of a and b are called amicable numbers. For
	 * example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55
	 * and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71
	 * and 142; so d(284) = 220. Evaluate the sum of all the amicable numbers under
	 * 10000. Ans: 31626
	 */
	public:
		P021()
		{
			problem_number = 21;
			variations = 2;
		}
		~P021() {}

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
		cl_mem array_mem;

		/**
		 * Brute force version
		 *
		 */
		bool brute_setup()
		{
			size = 10000;
			int initialVal = 0;

			cl->init("src/problems/P021xP030/P021.cl","brute");
         cl->createReadWriteMemory(sizeof(int),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
         cl->createReadWriteMemory(sizeof(int)*size,&array_mem);
			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &array_mem,
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
			clReleaseMemObject(array_mem);
			return true;
		}

		int brute()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}

		/**
		 * Only check up to the sqrt of the number for divisors
		 */
		bool opt_setup()
		{
			size = 10000;
			int initialVal = 0;

			cl->init("src/problems/P021xP030/P021.cl","optimized");
			cl->createReadWriteMemory(sizeof(int),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->createReadWriteMemory(sizeof(int)*size,&array_mem);
			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &array_mem,
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
			answer = to_string(ans);
			clReleaseMemObject(answer_mem);
			clReleaseMemObject(array_mem);
			return true;
		}

		int optimized()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}
};
