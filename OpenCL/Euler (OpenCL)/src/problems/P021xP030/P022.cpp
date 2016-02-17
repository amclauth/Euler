#include "../../base/problem.h"
#include "../../util/io.h"
#include <math.h>

class P022: public Problem
{
	/**
	 * P022 Using names.txt (right click and 'Save Link/Target As...'), a 46K text
	 * file containing over five-thousand first names, begin by sorting it into
	 * alphabetical order. Then working out the alphabetical value for each name,
	 * multiply this value by its alphabetical position in the list to obtain a name
	 * score. For example, when the list is sorted into alphabetical order, COLIN,
	 * which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So,
	 * COLIN would obtain a score of 938 * 53 = 49714. What is the total of all the
	 * name scores in the file? Ans: 871198282
	 */
	public:
		P022()
		{
			problem_number = 22;
			variations = 1;
		}
		~P022() {}

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

		int array_size, word_size;
		cl_mem array_mem, value_mem;

		/**
		 * Brute force version
		 * 5163 names, max name length = 11
		 */
		bool brute_setup()
		{
			word_size = 11;
			array_size = 5163;
			long initialVal = 0;

			char array[5163*11];
			std::string file = io::readFile("data/names.txt");
			// erase the first and last quotes
			file.erase(0,1);
			file.erase(file.size() - 1);
			io::readIntoCharArray(array,file, "\",\"",11);

			cl->init("src/problems/P021xP030/P022.cl","brute");
         cl->createReadWriteMemory(sizeof(long),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(long),&answer_mem,&initialVal);
         cl->createReadWriteMemory(sizeof(char)*array_size*word_size,&array_mem);
         cl->transferCPUObjectToGPU(sizeof(char)*array_size*word_size,&array_mem,array);
         cl->createReadWriteMemory(sizeof(long)*array_size,&value_mem);
			cl->setupOpenCLKernelArgs(5,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &array_mem,
					sizeof(cl_mem), &value_mem,
					sizeof(int), &array_size,
					sizeof(int), &word_size);
			cl->waitForQueue(); // sync
			setThreads(array_size);
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
			clReleaseMemObject(value_mem);
			return true;
		}

		int brute()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}

		/**
		 * Only check up to the sqrt of the number for divisors
		 */
		bool opt_setup()
		{
			long array[16] = {1,5,3,4,2,6,10,8,9,7,14,13,12,11,16,15};
			int size = 16;

			cl->init("src/problems/P021xP030/P022.cl","parallelBitonic_Local");
			cl->createReadWriteMemory(sizeof(long)*size,&array_mem);
			cl->transferCPUObjectToGPU(sizeof(long)*size,&array_mem,array);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &array_mem,
					sizeof(int), &size);
			cl->waitForQueue(); // sync
			setThreads(16);
			return true;
		}

		bool opt_teardown()
		{
			int size = 16;
			long ans[16];
			if (!cl->transferGPUObjectToCPU(sizeof(long)*size, &array_mem, &ans))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			for (int ii = 0; ii < size; ii++)
			{
				std::cout << ans[ii] << " ";
			}
			std::cout << std::endl;
			answer = to_string(ans);
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
