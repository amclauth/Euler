#include "../../base/problem.h"

class P009: public Problem
{
	/**
	 * P009<br>
	 * A Pythagorean triplet is a set of three natural numbers, a  b  c, for which,<br>
	 * a^2 + b^2 = c^2<br>
	 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.<br>
	 * There exists exactly one Pythagorean triplet for which a + b + c = 1000.<br>
	 * Find the product abc.<br>
	 * Ans: 31875000
	 */
	public:
		P009()
		{
			problem_number = 9;
			variations = 2;
		}
		~P009() {}

		bool setup(int variation)
		{
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

		int digits[1000];
		int size;

		/**
		 * Brute force version
		 * Check every combination of 2 sides of the triangle. ~1M possibilities
		 */
		bool brute_setup()
		{
			// 1 to 998 for each (because if a is 998, b and c both have to be 1
			size = 997*997;

			cl->init("src/problems/P001xP010/P009.cl","brute");
         cl->createWriteOnlyMemory(sizeof(int),&answer_mem);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem,
					sizeof(int), &size);         // the size
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
			return true;
		}

		int brute()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}

		/**
		 * We might not have to hunt for out second term:
       * ii^2 + x^2 = (1000-ii-x)^2 = 1000^2 + ii^2 + x^2 - 2000ii - 2000x - 2ii*x
       * 0 = 1000^2 - 2000ii - 2000x - 2iix
       * 2000ii - 1000^2 = -x(2000 - 2ii)
       * 1000^2 - 2000ii / 2000 - 2ii = x
       * 500*1000 - 1000ii / 1000 - ii = x
		 */
		bool opt_setup()
		{
			size = 997;

			cl->init("src/problems/P001xP010/P009.cl","optimized");
			cl->createWriteOnlyMemory(sizeof(int),&answer_mem);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem,
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
