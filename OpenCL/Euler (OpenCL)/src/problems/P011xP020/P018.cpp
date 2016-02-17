#include "../../base/problem.h"

class P018: public Problem
{
	/**
	 * P018<br>
	 * By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
	 * 3
	 * 7 4
	 * 2 4 6
	 * 8 5 9 3
	 * That is, 3 + 7 + 4 + 9 = 23.
	 * Find the maximum total from top to bottom of the triangle below:
	 * NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However,
	 * Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
	 * Ans: 1074
	 */
	public:
		P018()
		{
			problem_number = 18;
			variations = 2;
		}
		~P018() {}

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
		bool opt_setup()
		{
			size = 14;
			int array[120] = { 0 };
			getArray(array);
			int initialVal = 0;

			cl->init("src/problems/P011xP020/P018.cl","optimized");
			cl->createReadWriteMemory(sizeof(int),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->createReadWriteMemory(sizeof(int)*120,&array_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*120,&array_mem,array);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &array_mem);
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

		/**
		 * See the difference when using reduction for the final sum
		 */
		bool brute_setup()
		{
			size = 16384;
			int array[120] = { 0 };
			getArray(array);
			int initialVal = 0;

			cl->init("src/problems/P011xP020/P018.cl","brute");
			cl->createReadWriteMemory(sizeof(int),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->createReadWriteMemory(sizeof(int)*120,&array_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*120,&array_mem,array);
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

		void getArray(int* array)
		{
			int ii = 0;
			std::string nums[15];
			nums[ii++] = std::string(" 75");
			nums[ii++] = std::string(" 95 64");
			nums[ii++] = std::string(" 17 47 82");
			nums[ii++] = std::string(" 18 35 87 10");
			nums[ii++] = std::string(" 20 04 82 47 65");
			nums[ii++] = std::string(" 19 01 23 75 03 34");
			nums[ii++] = std::string(" 88 02 77 73 07 63 67");
			nums[ii++] = std::string(" 99 65 04 28 06 16 70 92");
			nums[ii++] = std::string(" 41 41 26 56 83 40 80 70 33");
			nums[ii++] = std::string(" 41 48 72 33 47 32 37 16 94 29");
			nums[ii++] = std::string(" 53 71 44 65 25 43 91 52 97 51 14");
			nums[ii++] = std::string(" 70 11 33 28 77 73 17 78 39 68 17 57");
			nums[ii++] = std::string(" 91 71 52 38 17 14 91 43 58 50 27 29 48");
			nums[ii++] = std::string(" 63 66 04 68 89 53 67 30 73 16 69 87 40 31");
			nums[ii++] = std::string(" 04 62 98 27 23 09 70 98 73 93 38 53 60 04 23");

			// 120 numbers: 15*(15+1)/2
			unsigned int idx = 0;
			for (ii = 0; ii < 15; ii++)
			{
				for (unsigned int jj = 0; jj < nums[ii].length(); jj += 3)
				{
					int n = (nums[ii][jj+1] - '0')*10 + nums[ii][jj+2] - '0';
					array[idx++] = n;
				}
			}
		}
};
