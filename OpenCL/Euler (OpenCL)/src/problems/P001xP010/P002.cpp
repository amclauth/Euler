#include "../../base/problem.h"
#include "../../util/basic.h"

#include <iostream>
#include <string>

class P002: public Problem
{
	/**
	 * P002<br>
    * Each new term in the Fibonacci sequence is generated by adding the
    * previous two terms. By starting with 1 and 2, the first 10 terms will be:
    * 1,2,3,5,8,13,21,34,55,89
    * By considering the terms in the Fibonacci sequence whose values do not
    * exceed four million, find the sum of the even-valued terms.
	 * Ans: 4613732
	 */
	public:
		P002()
		{
			problem_number = 2;
			variations = 2;
		}
		~P002() {}

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
					retval = reduction_setup();
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
					retval = reduction_teardown();
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
					reduction();
					break;
				default:
					std::cout << "NOOP!" << std::endl;
					break;
			}
		}

	private:

		/**
		 * Brute force version
		 * Just check every thread ID (+1 since it's zero indexed) and compute the fibonacci number
		 * for that thread. Then check if it's even and if so, do an atomic add.
		 */
		bool brute_setup()
		{
			double sq5 = sqrt(5);
         double phi = 0.5 + 0.5*sq5;
         int N = floor(log(4000000.0 * sq5 + 0.5) / log(phi));
         cl->init("src/problems/P001xP010/P002.cl","brute");
         cl->createWriteOnlyMemory(sizeof(int),&answer_mem);
			int initialVal = 0;
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(1,
					sizeof(cl_mem), &answer_mem);
			cl->waitForQueue(); // sync
			setThreads(N);
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
		 * Reduction. Compute the fibonacci number, but use reduction to add them together.
		 * Use the reduction code in basic for this now.
		 */
		bool reduction_setup()
		{
         double sq5 = sqrt(5);
         double phi = 0.5 + 0.5*sq5;
         // one third of the needed numbers
         int N = floor(log(4000000.0 * sq5 + 0.5) / log(phi) / 3.0);

         const char* header = "#pragma OPENCL EXTENSION cl_khr_fp64: enable";
         const char* function =
         		"	int n = globalId*3;\n"
         		"	double sq5 = sqrt((double)5);\n"
         		"	int fib = (int)floor(( powr((double)(1 + sq5),n) -\n"
         		"					pow((double)(1 - sq5),n) ) /\n"
         		"				 ( sq5 * powr((double)2,n) )+0.5);\n"
         		"	scratch[localId] = fib;\n";
         const char* operand = "+";

         cl->init();
         cl->setupOpenCLKernelWithSource(basic::reduction(header, function, operand),"reduction");

			cl->createReadWriteMemory(sizeof(int),&answer_mem);
			int initialVal = 0;
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem, // the answer
					sizeof(int)*(1024), NULL);   // local scratch space
			cl->waitForQueue(); // sync
			setThreads(N);
			return true;
		}

		bool reduction_teardown()
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

		int reduction()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}
};
