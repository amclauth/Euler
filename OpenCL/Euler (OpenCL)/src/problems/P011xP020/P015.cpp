#include "../../base/problem.h"

class P015: public Problem
{
	/**
	 * P015<br>
	 * Starting in the top left corner of a 22 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.<br>
	 * How many such routes are there through a 2020 grid?<br>
	 * Ans: 137846528820
	 */
	public:
		P015()
		{
			problem_number = 15;
			variations = 1;
		}
		~P015() {}

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
			size = 20;
			long array[861] = { 0 }; // 2n+1 * n+1
			for (int ii = 0; ii < 2*size + 1; ii++)
			{
				array[ii * (size+1)] = 1;
			}
			long initialVal = 0;

			cl->init("src/problems/P011xP020/P015.cl","brute");
         cl->createReadWriteMemory(sizeof(long),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(long),&answer_mem,&initialVal);
         cl->createReadWriteMemory(sizeof(long)*(2*size+1)*(size+1),&array_mem);
         cl->transferCPUObjectToGPU(sizeof(long)*(2*size+1)*(size+1),&array_mem,array);
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
