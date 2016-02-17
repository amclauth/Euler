#include "../../base/problem.h"

class P017: public Problem
{
	/**
	 * P017<br>
	 * If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
	 * If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
	 * NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen)
	 * contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
	 * Ans: 21124
	 */
	public:
		P017()
		{
			problem_number = 17;
			variations = 1;
		}
		~P017() {}

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
			size = 1000;
			int array[101] = { 0 }; // 2n+1 * n+1
			getLengthArray(array);
			int initialVal = 0;

			cl->init("src/problems/P011xP020/P017.cl","brute");
         cl->createReadWriteMemory(sizeof(int),&answer_mem);
         cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
         cl->createReadWriteMemory(sizeof(int)*101,&array_mem);
         cl->transferCPUObjectToGPU(sizeof(int)*101,&array_mem,array);
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
			ans += std::string("onethousand").length();
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

		void getLengthArray(int* array)
		{
			array[0] = std::string("").length();
			array[1] = std::string("one").length();
			array[2] = std::string("two").length();
			array[3] = std::string("three").length();
			array[4] = std::string("four").length();
			array[5] = std::string("five").length();
			array[6] = std::string("six").length();
			array[7] = std::string("seven").length();
			array[8] = std::string("eight").length();
			array[9] = std::string("nine").length();
			array[10] = std::string("ten").length();
			array[11] = std::string("eleven").length();
			array[12] = std::string("twelve").length();
			array[13] = std::string("thirteen").length();
			array[14] = std::string("fourteen").length();
			array[15] = std::string("fifteen").length();
			array[16] = std::string("sixteen").length();
			array[17] = std::string("seventeen").length();
			array[18] = std::string("eighteen").length();
			array[19] = std::string("nineteen").length();
			array[20] = std::string("twenty").length();
			array[30] = std::string("thirty").length();
			array[40] = std::string("forty").length();
			array[50] = std::string("fifty").length();
			array[60] = std::string("sixty").length();
			array[70] = std::string("seventy").length();
			array[80] = std::string("eighty").length();
			array[90] = std::string("ninety").length();
			array[99] = std::string("and").length(); // special 1
			array[100] = std::string("hundred").length(); // special 2
		}
};
