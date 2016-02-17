#include "../../base/problem.h"

#include <set>

class P032: public Problem
{
	/**
	 * P032<br>
	 * We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once;
	 * for example, the 5-digit number, 15234, is 1 through 5 pandigital.
	 * The product 7254 is unusual, as the identity, 39  186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.
	 * Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
	 * HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
	 * Ans: 45228
	 */
	public:
		P032()
		{
			problem_number = 32;
			variations = 2;
		}
		~P032() {}

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
			size = 987654321 - 123456789 + 1;
			int initialVal = 0;

			cl->init("src/problems/P031xP040/P032.cl","brute");
         cl->createReadWriteMemory( sizeof(int),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
         cl->createReadWriteMemory( sizeof(int)*20,&array_mem);
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
			int values[20];
			if (!cl->transferGPUObjectToCPU(sizeof(int)*20, &array_mem, values))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			std::set<int>* products = new std::set<int>();
			int sum = 0;
			for (int ii = 0; ii < ans; ii++)
			{
				if(products->insert(values[ii]).second)
				{
					sum += values[ii];
				}
			}
			delete products;
			answer = to_string(sum);
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
