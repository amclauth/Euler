#include "../../base/problem.h"

#include <set>

class P039: public Problem
{
	/**
	 * P039<br>
	 * If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.
	 * {20,48,52}, {24,45,51}, {30,40,50}
	 * For which value of p <= 1000, is the number of solutions maximized?
	 * Ans: 840
	 */
	public:
		P039()
		{
			problem_number = 39;
			variations = 1;
		}
		~P039() {}

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
			size = 1000000;
			int initialVal[1000] = { 0 };

			cl->init("src/problems/P031xP040/P039.cl","brute");
         cl->createReadWriteMemory( sizeof(int)*1000,&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(int)*1000,&answer_mem,&initialVal);
         cl->setupOpenCLKernelArgs(2,
         		sizeof(cl_mem), &answer_mem,
					sizeof(int), &size);
			cl->waitForQueue(); // sync
			setThreads(size);
			return true;
		}

		bool brute_teardown()
		{
			int ans[1000];
			if (!cl->transferGPUObjectToCPU(sizeof(int)*1000, &answer_mem, ans))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			int max = 0;
			int sol = 0;
			for (int ii = 0; ii < 1000; ii++)
			{
				if (ans[ii] > max)
				{
					sol = ii;
					max = ans[ii];
				}
			}
			answer = to_string(sol);
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
			size = 71;
			int initialVal = 0;

			cl->init("src/problems/P031xP040/P039.cl","optimized");
			cl->createReadWriteMemory( sizeof(int),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem,
					sizeof(int), &size);
			cl->waitForQueue(); // sync
			setThreads(size);
			return true;
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
