#include "../../base/problem.h"

#include <set>

class P040: public Problem
{
	/**
	 * P040<br>
	 * An irrational decimal fraction is created by concatenating the positive integers:
	 * 0.123456789101112131415161718192021...
	 * It can be seen that the 12th digit of the fractional part is 1.
	 * If dn represents the nth digit of the fractional part, find the value of the following expression.
	 * d1 x d10 x d100 x d1000 x d10000 x d100000 x d1000000
	 * Ans: 210
	 */
	public:
		P040()
		{
			problem_number = 40;
			variations = 1;
		}
		~P040() {}

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
			size = 6;
			int initialVal[6] = { 0 };

			cl->init("src/problems/P031xP040/P040.cl","brute");
         cl->createReadWriteMemory( sizeof(int)*6,&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(int)*6,&answer_mem,&initialVal);
         cl->setupOpenCLKernelArgs(2,
         		sizeof(cl_mem), &answer_mem,
					sizeof(int), &size);
			cl->waitForQueue(); // sync
			setThreads(size);
			return true;
		}

		bool brute_teardown()
		{
			int ans[6];
			if (!cl->transferGPUObjectToCPU(sizeof(int)*6, &answer_mem, ans))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			int final = 1;
			for (int ii = 0; ii < 6; ii++)
			{
				final *= ans[ii];
			}
			answer = to_string(final);
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
