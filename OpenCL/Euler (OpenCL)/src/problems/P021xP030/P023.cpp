#include "../../base/problem.h"

class P023: public Problem
{
	/**
	 * P023<br>
	 * A perfect number is a number for which the sum of its proper divisors is
	 * exactly equal to the number. For example, the sum of the proper divisors of
	 * 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
	 * A number n is called deficient if the sum of its proper divisors is less than
	 * n and it is called abundant if this sum exceeds n. As 12 is the smallest
	 * abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be
	 * written as the sum of two abundant numbers is 24. By mathematical analysis,
	 * it can be shown that all integers greater than 28123 can be written as the
	 * sum of two abundant numbers. However, this upper limit cannot be reduced any
	 * further by analysis even though it is known that the greatest number that
	 * cannot be expressed as the sum of two abundant numbers is less than this
	 * limit. Find the sum of all the positive integers which cannot be written as
	 * the sum of two abundant numbers. Ans: 4179871
	 */
	public:
		P023()
		{
			problem_number = 23;
			variations = 1;
		}
		~P023() {}

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
			size = 21283;
			int initialVal = 0;

			cl->init("src/problems/P021xP030/P023.cl","brute");
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
