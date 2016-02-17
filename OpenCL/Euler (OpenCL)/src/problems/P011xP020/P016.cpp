#include "../../base/problem.h"

class P016: public Problem
{
	/**
	 * P016<br>
	 * 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
	 * What is the sum of the digits of the number 2^1000?
	 * Ans: 1366
	 */
	public:
		P016()
		{
			problem_number = 16;
			variations = 1;
		}
		~P016() {}

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
			size = 400;
			int array[400] = { 0 }; // 2n+1 * n+1
			array[398] = 1; // initialize with a zero at the end so addition index works out
			int initialVal = 0;

			cl->init("src/problems/P011xP020/P016.cl","brute");
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

		/**
		 * See the difference when using reduction for the final sum
		 */
		bool opt_setup()
		{
			size = 400;
			int array[400] = { 0 }; // 2n+1 * n+1
			array[398] = 1; // initialize with a zero at the end so addition index works out
			int initialVal = 0;

			cl->init("src/problems/P011xP020/P016.cl","optimized");
			cl->createReadWriteMemory(sizeof(int),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->createReadWriteMemory(sizeof(int)*size,&array_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*size,&array_mem,array);
			cl->setupOpenCLKernelArgs(4,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &array_mem,
					sizeof(long)*(1024), NULL,    // local scratch space
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
