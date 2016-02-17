#include "../../base/problem.h"

class P019: public Problem
{
	/**
	 * P019<br>
	 * You are given the following information, but you may prefer to do some research for yourself.
	 * 1 Jan 1900 was a Monday.
	 * Thirty days has September,
	 * April, June and November.
	 * All the rest have thirty-one,
	 * Saving February alone,
	 * Which has twenty-eight, rain or shine.
	 * And on leap years, twenty-nine.
	 * A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
	 * How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
	 * Ans: 171
	 */
	public:
		P019()
		{
			problem_number = 19;
			variations = 1;
		}
		~P019() {}

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
		cl_mem array_mem;

		/**
		 * Brute force version
		 *
		 */
		bool brute_setup()
		{
			size = 12*1000;
			int array[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			int initialVal = 0;

			cl->init("src/problems/P011xP020/P019.cl","brute");
         cl->createReadWriteMemory(sizeof(int),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
         cl->createReadWriteMemory(sizeof(int)*12,&array_mem);
         cl->transferCPUObjectToGPU(sizeof(int)*12,&array_mem,array);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &array_mem);
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
		 * See the difference when using reduction for the final sum
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
