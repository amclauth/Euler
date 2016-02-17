#include "../../base/problem.h"

#include <set>

class P034: public Problem
{
	/**
	 * P034<br>
	 * 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
	 * Find the sum of all numbers which are equal to the sum of the factorial of their digits.
	 * Note: as 1! = 1 and 2! = 2 are not sums they are not included.
	 * Ans: 40730
	 */
	public:
		P034()
		{
			problem_number = 34;
			variations = 1;
		}
		~P034() {}

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
		cl_mem fac_mem;

		/**
		 * Brute force version
		 *
		 */
		bool brute_setup()
		{
			size = 2540160;
			int initialVal = 0;
			int fac[10] = { 1, 1, 2, 3*2, 4*3*2, 5*4*3*2, 6*5*4*3*2, 7*6*5*4*3*2, 8*7*6*5*4*3*2, 9*8*7*6*5*4*3*2 };

			cl->init("src/problems/P031xP040/P034.cl","brute");
         cl->createReadWriteMemory( sizeof(int),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
         cl->createReadWriteMemory( sizeof(int)*10,&fac_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*10,&fac_mem,fac);
         cl->setupOpenCLKernelArgs(3,
         		sizeof(cl_mem), &answer_mem,
         		sizeof(cl_mem), &fac_mem,
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
			clReleaseMemObject(fac_mem);
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
			size = 9876-1234+1;
			int initialVal = 0;

			cl->init("src/problems/P031xP040/P032.cl","optimized");
			cl->createReadWriteMemory( sizeof(int),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem,
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
			return true;
		}

		int optimized()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}
};
