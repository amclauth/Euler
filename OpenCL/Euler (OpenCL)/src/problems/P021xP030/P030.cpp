#include "../../base/problem.h"

class P030: public Problem
{
	/**
	 * P030<br>
	 * Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:
	 * 1634 = 1^4 + 6^4 + 3^4 + 4^4
	 * 8208 = 864 + 2^4 + 0^4 + 8^4
	 * 9474 = 9^4 + 4^4 + 7^4 + 4^4
	 * As 1 = 1^4 is not a sum it is not included.
	 * The sum of these numbers is 1634 + 8208 + 9474 = 19316.
	 * Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
	 * Ans: 443839
	 */
	public:
		P030()
		{
			problem_number = 30;
			variations = 1;
		}
		~P030() {}

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
		cl_mem power_mem;

		/**
		 * Brute force version
		 *
		 */
		bool brute_setup()
		{
			size = 1000000-10;
			int initialVal = 0;
			int value_arr[10] = {0,1,2*2*2*2*2,3*3*3*3*3,4*4*4*4*4,5*5*5*5*5,6*6*6*6*6,
               7*7*7*7*7,8*8*8*8*8,9*9*9*9*9};

			cl->init("src/problems/P021xP030/P030.cl","brute");
         cl->createReadWriteMemory( sizeof(int),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
         cl->createReadWriteMemory( sizeof(int)*10,&power_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*10,&power_mem,value_arr);
         cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &power_mem,
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
			clReleaseMemObject(power_mem);
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
