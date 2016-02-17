#include "../../base/problem.h"
#include "../../util/basic.h"
#include "../../util/prime.h"

class P003: public Problem
{
	/**
	 * P003<br>
	 * The prime factors of 13195 are 5, 7, 13 and 29.<br>
	 * What is the largest prime factor of the number 600851475143?<br>
	 * Ans: 6857
	 */
	public:
		P003()
		{
			problem_number = 3;
			variations = 2;
		}
		~P003() {}

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

		cl_mem number_mem;
		/**
		 * Brute force version
		 * Just check every thread ID * 2 + 1 (all odd numbers) to see if it's prime, then
		 * if it's a divisor, do an atomic max on the answer
		 */
		bool brute_setup()
		{
			long number = 600851475143L;
			int initialVal = 0;

			cl->init("src/problems/P001xP010/P003.cl","brute");
         cl->createWriteOnlyMemory(sizeof(int),&answer_mem);
         cl->createReadOnlyMemory(sizeof(long),&number_mem);

			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->transferCPUObjectToGPU(sizeof(long),&number_mem,&number);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &number_mem,
					sizeof(cl_mem), &answer_mem);
			cl->waitForQueue(); // sync
			setThreads(sqrt(number)/2); // odds that are less than sqrt num
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
			clReleaseMemObject(number_mem);
			return true;
		}

		int brute()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}

		cl_mem prime_mem;

		/**
		 * Do the same basic thing, but this time compute the primes on the CPU and just
		 * run a single check to see if it's a divisor, then do an atomic check and set
		 */
		bool opt_setup()
		{
			long number = 600851475143L;
			int initialVal = 0;
			std::vector<int> *primes = prime::EratosthenesPrimesUpTo(sqrt(number));

			cl->init("src/problems/P001xP010/P003.cl","optimized");
			cl->createWriteOnlyMemory(sizeof(int),&answer_mem);
			cl->createReadOnlyMemory(sizeof(long),&number_mem);
			cl->createReadOnlyMemory(sizeof(int) * primes->size(),&prime_mem);

			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->transferCPUObjectToGPU(sizeof(long),&number_mem,&number);
			cl->transferCPUObjectToGPU(sizeof(int) * primes->size(),&prime_mem,primes->data());

			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &number_mem,
					sizeof(cl_mem), &prime_mem,
					sizeof(cl_mem), &answer_mem);

			cl->waitForQueue(); // sync

			setThreads(primes->size()); // check each prime
			delete(primes);
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
			clReleaseMemObject(prime_mem);
			clReleaseMemObject(number_mem);
			return true;
		}

		int optimized()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}
};
