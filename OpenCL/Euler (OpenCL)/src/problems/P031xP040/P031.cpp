#include "../../base/problem.h"

class P031: public Problem
{
	/**
	 * P031<br>
	 * In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:
	 * 1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
	 * It is possible to make £2 in the following way:
	 * 1£1 + 150p + 220p + 15p + 12p + 31p
	 * How many different ways can £2 be made using any number of coins?
	 * Ans: 73682
	 */
	public:
		P031()
		{
			problem_number = 31;
			variations = 1;
		}
		~P031() {}

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
		cl_mem value_mem;

		/**
		 * Brute force version
		 *	All possible combinations of 1,.5,.2,.1,.05,.02 ... 2 is a special case and
		 *	.01 can always be used as filler. We don't include the max of each as that's
		 *	a singular special case (1 2, 2 1's, 4 .5's, etc). So we need to consider
		 *	1 -> 0,1 {2}
		 *	.5 -> 0,1,2,3 {4}
		 *	.2 -> 0,1,2,3,4,5,6,7,8,9 {10}
		 *	.1 -> {20}
		 *	.05 -> {40}
		 *	.02 -> {100}
		 *	6.4M combinations
		 */
		bool brute_setup()
		{
			size = 6400000;
			int initialVal = 7; // 0 of everything is in the combo,
			int value_arr[6] = {100, 50, 20, 10, 5, 2};

			cl->init("src/problems/P031xP040/P031.cl","brute");
         cl->createReadWriteMemory( sizeof(int),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
         cl->createReadWriteMemory( sizeof(int)*6,&value_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*6,&value_mem,value_arr);
         cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &value_mem,
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
			clReleaseMemObject(value_mem);
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
