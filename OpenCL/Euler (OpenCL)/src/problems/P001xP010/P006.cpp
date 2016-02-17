#include "../../base/problem.h"
#include "../../util/basic.h"

class P006: public Problem
{
	/**
	 * P006<br>
	 * The sum of the squares of the first ten natural numbers is,<br>
	 * 1^2 + 2^2 + ... + 10^2 = 385<br>
	 * The square of the sum of the first ten natural numbers is,<br>
	 * (1 + 2 + ... + 10)^2 = 55^2 = 3025<br>
	 * Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 - 385 = 2640.
	 * <br>Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
	 * Ans: 25164150
	 */
	public:
		P006()
		{
			problem_number = 6;
			variations = 2;
		}
		~P006() {}

		int size;

		bool setup(int variation)
		{
			size = 100;
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

		cl_mem answer2_mem;

		/**
		 * Brute force version
		 * Simply generate the sums and then add them together on the CPU
		 */
		bool brute_setup()
		{
			int initalVal = 0;

			cl->init("src/problems/P001xP010/P006.cl","brute");
         cl->createReadWriteMemory(sizeof(int),&answer_mem);
         cl->createReadWriteMemory(sizeof(int),&answer2_mem);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initalVal);
			cl->transferCPUObjectToGPU(sizeof(int),&answer2_mem,&initalVal);
			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &answer2_mem,
					sizeof(int), &size);         // the size
			cl->waitForQueue(); // sync
			setThreads(size);
			return true;
		}

		bool brute_teardown()
		{
			int ans1, ans2;
			if (!cl->transferGPUObjectToCPU(sizeof(int), &answer_mem, &ans1))
			{
				std::cout << "ERROR:: Could not read answer 1 from GPU!" << std::endl;
				return false;
			}
			if (!cl->transferGPUObjectToCPU(sizeof(int), &answer2_mem, &ans2))
			{
				std::cout << "ERROR:: Could not read answer 2 from GPU!" << std::endl;
				return false;
			}
			answer = to_string(ans2*ans2 - ans1);
			clReleaseMemObject(answer_mem);
			clReleaseMemObject(answer2_mem);
			return true;
		}

		int brute()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}

		/**
		 * Do this with reduction, all the way down to the final answer
		 */
		bool opt_setup()
		{
			int initalVal = 0;

			cl->init("src/problems/P001xP010/P006.cl","optimized");
			cl->createReadWriteMemory(sizeof(int),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initalVal);
			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(int)*(size*2), NULL,    // local scratch space
					sizeof(int), &size);         // the size
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
