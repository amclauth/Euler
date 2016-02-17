#include "../../base/problem.h"

#include <iostream>
#include <string>

class P001: public Problem
{
	/**
	 * P001<br>
	 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.<br>
	 * Find the sum of all the multiples of 3 or 5 below 1000.<br>
	 * Ans: 233168
	 */
	public:
		P001()
		{
			problem_number = 1;
			variations = 4;
			max = 999;
		}
		~P001() {}

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
					retval = reduction_1_setup();
					break;
				case 2:
					retval = reduction_2_setup();
					break;
				case -1:
				case 3:
					retval = reduction_3_setup();
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
					retval = reduction_1_teardown();
					break;
				case 2:
					retval = reduction_2_teardown();
					break;
				case -1:
				case 3:
					retval = reduction_3_teardown();
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
					reduction_1();
					break;
				case 2:
					reduction_2();
					break;
				case -1:
				case 3:
					reduction_3();
					break;
				default:
					std::cout << "NOOP!" << std::endl;
					break;
			}
		}

	private:

		int max;

		/**
		 * Brute force version
		 * Just check every thread ID (+1 since it's zero indexed) and see if it's
		 * mod3 or mod5. If so, atomically add it to the answer
		 */
		bool brute_setup()
		{
			cl->init("src/problems/P001xP010/P001.cl","brute");
			cl->createWriteOnlyMemory(sizeof(int),&answer_mem);
			int initialVal = 0;
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem,
					sizeof(int),&max);
			cl->waitForQueue(); // sync
			setThreads(max);
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
		 * Reduction 1
		 * Use reduction on the GPU, initializing all the data at the CPU and using barriers on
		 * the GPU. Problem is, barriers only flush at the workgroup level, so this is only
		 * safe up to that level.
		 */
		bool reduction_1_setup()
		{
			int size2 = 2;
			while (size2 < max)
				size2 <<= 1; // get it to be a power of 2
			int input[size2];
			for (int ii = 0; ii < max; ii++)
				if ((ii+1) % 3 == 0 || (ii+1) % 5 == 0)
				{
					input[ii] = ii+1;
				} else {
					input[ii] = 0;
				}
			for (int ii = max; ii < size2; ii++)
				input[ii] = 0;

			cl->init("src/problems/P001xP010/P001.cl","reduction");
			cl->createReadWriteMemory(sizeof(int)*size2,&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*size2,&answer_mem,input);
			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(int),&size2,
					sizeof(int),&max);
			cl->waitForQueue(); // sync
			setThreads(size2);
			return true;
		}

		bool reduction_1_teardown()
		{
			int ans;
			if (!cl->transferGPUObjectToCPU(sizeof(int), &answer_mem, &ans)) // store the answer in the first element
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			answer = to_string(ans);
			clReleaseMemObject(answer_mem);
			return true;
		}

		int reduction_1()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}

		/**
		 * Reduction 2
		 * Re-try reduction, but this time do everything on the GPU. Still has a 'per-workgroup' problem
		 */
		bool reduction_2_setup()
		{
			int size2 = 2;
			while (size2 < max)
				size2 <<= 1; // get it to be a power of 2

			cl->init("src/problems/P001xP010/P001.cl","reduction_2");
			cl->createReadWriteMemory(sizeof(int)*size2,&answer_mem);
			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(int),&size2,
					sizeof(int),&max);
			cl->waitForQueue(); // sync
			setThreads(size2);
			return true;
		}

		bool reduction_2_teardown()
		{
			int ans;
			if (!cl->transferGPUObjectToCPU(sizeof(int), &answer_mem, &ans)) // store the answer in the first element
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			answer = to_string(ans);
			clReleaseMemObject(answer_mem);
			return true;
		}

		int reduction_2()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}

		/**
		 * Reduction 3
		 * This time, build it to handle load across multiple workgroups, and while
		 * we're at it, use local memory on each of the workgroups to do a local
		 * reduction, then atomically add the reduced workgroups back together
		 * at the end.
		 */
		bool reduction_3_setup()
		{
			cl->init("src/problems/P001xP010/P001.cl","reduction_3");
			cl->createReadWriteMemory(sizeof(int),&answer_mem);
			int initialVal = 0;
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem, // the answer
					sizeof(int)*(1024), NULL,    // local scratch space
					sizeof(int), &max);          // the size
			cl->waitForQueue(); // sync
			setThreads(max);
			return true;
		}

		bool reduction_3_teardown()
		{
			int ans;
			if (!cl->transferGPUObjectToCPU(sizeof(int), &answer_mem, &ans)) // store the answer
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			answer = to_string(ans);
			clReleaseMemObject(answer_mem);
			return true;
		}

		int reduction_3()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}
};
