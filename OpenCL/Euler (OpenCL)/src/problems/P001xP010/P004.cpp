#include "../../base/problem.h"
#include "../../util/basic.h"

class P004: public Problem
{
	/**
	 * P004<br>
	 * A palindromic number reads the same both ways. The largest palindrome made<br>
	 * from the product of two 2-digit numbers is 9009 = 91 99.<br>
	 * Find the largest palindrome made from the product of two 3-digit numbers.<br>
	 * Ans: 906609
	 */
	public:
		P004()
		{
			problem_number = 4;
			variations = 1;
		}
		~P004() {}

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
				default:
					std::cout << "NOOP!" << std::endl;
					break;
			}
		}

	private:

		/**
		 * Brute force version
		 * Check every single item to see if it's a palindrome!
		 */
		bool brute_setup()
		{
			int initialVal = 0;
			int count = 900*900; // 100->999 * 100->999

			cl->init("src/problems/P001xP010/P004.cl","brute");
         cl->createWriteOnlyMemory(sizeof(int),&answer_mem);

			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(1,
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
			return true;
		}

		int brute()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}
};
