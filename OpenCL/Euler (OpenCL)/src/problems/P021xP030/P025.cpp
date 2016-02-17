#include "../../base/problem.h"

class P025: public Problem
{
	/**
	 * P025<br>
	 * The Fibonacci sequence is defined by the recurrence relation:
	 * Fn = Fn1 + Fn2, where F1 = 1 and F2 = 1.
	 * Hence the first 12 terms will be:
	 * F1 = 1
	 * F2 = 1
	 * F3 = 2
	 * F4 = 3
	 * F5 = 5
	 * F6 = 8
	 * F7 = 13
	 * F8 = 21
	 * F9 = 34
	 * F10 = 55
	 * F11 = 89
	 * F12 = 144
	 * The 12th term, F12, is the first term to contain three digits.
	 * What is the first term in the Fibonacci sequence to contain 1000 digits?
	 * Ans: 4782
	 */
	public:
		P025()
		{
			problem_number = 25;
			variations = 1;
		}
		~P025() {}

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
		cl_mem prev_mem, cur_mem;

		/**
		 * Brute force version
		 *
		 */
		bool brute_setup()
		{
			size = 1000;
			int initialVal = 0;
			int prev[1000] = { 0 };
			int cur[1000] = { 0 };
			cur[999] = 1;
			prev[999] = 1;

			cl->init("src/problems/P021xP030/P025.cl","brute");
         cl->createReadWriteMemory( sizeof(int),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
         cl->createReadWriteMemory( sizeof(int)*size,&prev_mem);
         cl->transferCPUObjectToGPU(sizeof(int)*size,&prev_mem,prev);
         cl->createReadWriteMemory( sizeof(int)*size,&cur_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*size,&cur_mem,cur);
			cl->setupOpenCLKernelArgs(4,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &prev_mem,
					sizeof(cl_mem), &cur_mem,
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
			clReleaseMemObject(prev_mem);
			clReleaseMemObject(cur_mem);
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
