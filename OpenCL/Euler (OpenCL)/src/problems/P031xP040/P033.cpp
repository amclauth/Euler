#include "../../base/problem.h"

#include <set>

class P033: public Problem
{
	/**
	 * P033<br>
	 * The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it
	 * may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by canceling the 9s.
	 * We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
	 * There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing
	 * two digits in the numerator and denominator.
	 * If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
	 * Ans: 100
	 */
	public:
		P033()
		{
			problem_number = 33;
			variations = 1;
		}
		~P033() {}

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
		cl_mem size_mem;

		/**
		 * Brute force version
		 *
		 */
		bool brute_setup()
		{
			size = 10000;
			int initialVal = 0;

			cl->init("src/problems/P031xP040/P033.cl","brute");
         cl->createReadWriteMemory( sizeof(int)*50,&answer_mem);
         cl->createReadWriteMemory( sizeof(int),&size_mem);
         cl->transferCPUObjectToGPU(sizeof(int),&size_mem,&initialVal);
         cl->setupOpenCLKernelArgs(3,
         		sizeof(cl_mem), &answer_mem,
         		sizeof(cl_mem), &size_mem,
					sizeof(int), &size);
			cl->waitForQueue(); // sync
			setThreads(size);
			return true;
		}

		bool brute_teardown()
		{
			int ans[50];
			if (!cl->transferGPUObjectToCPU(sizeof(int)*50, &answer_mem, ans))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			int size;
			if (!cl->transferGPUObjectToCPU(sizeof(int), &size_mem, &size))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}

			int num = 1;
			int den = 1;

			for (int ii = 0; ii < size; ii++)
			{
				num *= ans[ii] / 100;
				den *= ans[ii] % 100;
			}

			for (int ii = num; ii >= 2; ii--)
			{
				if (ii > num)
				{
					ii = num+1;
					continue;
				}
				if (den % ii == 0 && num % ii == 0)
				{
					den = den / ii;
					num = num / ii;
				}
			}

			answer = to_string(den);
			clReleaseMemObject(answer_mem);
			clReleaseMemObject(size_mem);
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
