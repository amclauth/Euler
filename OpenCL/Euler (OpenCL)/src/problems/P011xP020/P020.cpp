#include "../../base/problem.h"

class P020: public Problem
{
	/**
	 * P020<br>
	 * n! means n  (n  1)  ...  3  2  1
	 * For example, 10! = 10  9  ...  3  2  1 = 3628800,
	 * and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
	 * Find the sum of the digits in the number 100!
	 * Ans: 648
	 */
	public:
		P020()
		{
			problem_number = 20;
			variations = 2;
		}
		~P020() {}

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

		int size;
		cl_mem array_mem;

		/**
		 * Brute force version
		 *
		 */
		bool brute_setup()
		{
			size = 200;
			int array[200] = { 0 };
			array[size-1] = 1;
			int initialVal = 0;

			cl->init("src/problems/P011xP020/P020.cl","brute");
			cl->createReadWriteMemory(sizeof(int),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->createReadWriteMemory(sizeof(int)*size,&array_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*size,&array_mem,array);
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

		int base;
		/**
		 * Use a base of 10M
		 */
		bool opt_setup()
		{
			size = 100;
			base = 10000000;
			int array[200] = { 0 };
			array[size-1] = 1;
			int initialVal = 0;

			cl->init("src/problems/P011xP020/P020.cl","optimized");
			cl->createReadWriteMemory(sizeof(int),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->createReadWriteMemory(sizeof(int)*size,&array_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*size,&array_mem,array);
			cl->setupOpenCLKernelArgs(4,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &array_mem,
					sizeof(int), &size,
					sizeof(int), &base);
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
			clReleaseMemObject(array_mem);
			return true;
		}

		int optimized()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}
};
