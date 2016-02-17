#include "../../base/problem.h"

class P024: public Problem
{
	/**
	 * P024<br>
	 * A permutation is an ordered arrangement of objects. For example, 3124 is one
	 * possible permutation of the digits 1, 2, 3 and 4. If all of the permutations
	 * are listed numerically or alphabetically, we call it lexicographic order. The
	 * lexicographic permutations of 0, 1 and 2 are: 012 021 102 120 201 210 What is
	 * the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7,
	 * 8 and 9?
	 *
	 * Ans: 2783915460
	 */
	public:
		P024()
		{
			problem_number = 24;
			variations = 1;
		}
		~P024() {}

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
		 * We know that for flipping the 1st digit, there is 1 permutations
		 * For the 2nd digit, there are 2 permutations
		 * For the 3rd digit, there are 3 numbers * 2 permutations
		 * For the 4th, 4 numbers * that previous 3*2, etc.
		 */
		bool brute_setup()
		{
			size = 10;
			long initialVal = 0;

			cl->init("src/problems/P021xP030/P024.cl","brute");
         cl->createReadWriteMemory(sizeof(long),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(long),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(5,
					sizeof(cl_mem), &answer_mem,
					sizeof(int), NULL,
					sizeof(int)*10, NULL,
					sizeof(int)*10, NULL,
					sizeof(int), &size);
			cl->waitForQueue(); // sync
			setThreads(size);
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
