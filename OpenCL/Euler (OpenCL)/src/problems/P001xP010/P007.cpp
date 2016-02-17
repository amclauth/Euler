#include "../../base/problem.h"
#include "../../util/basic.h"

class P007: public Problem
{
	/**
	 * P007<br>
	 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the
	 * 6th prime is 13.<br>
	 * What is the 10 001st prime number?<br>
	 * Ans: 104743
	 */
	public:
		P007()
		{
			problem_number = 7;
			variations = 1;
		}
		~P007() {}

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
		int arr_size;
		uint* primeFlagArray;

		/**
		 * Brute force version
		 * Check every number for primeness, storing in an array of bits. This uses a
		 * lot of atomic_or operations to achieve, but only conflicts a few times
		 * per 32 bit size. The bigger problem is simply dividing all the numbers out and
		 * transferring all the memory.
		 */
		bool brute_setup()
		{
			size = 130000;
			arr_size = size / 32 / 2 + 1;
			primeFlagArray = new uint[arr_size];
			for (int ii = 0; ii < arr_size; ii++)
			{
				primeFlagArray[ii] = 0;
			}


			cl->init("src/problems/P001xP010/P007.cl","brute");
         cl->createReadWriteMemory(sizeof(uint)*arr_size,&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(uint)*arr_size,&answer_mem,primeFlagArray);
			cl->setupOpenCLKernelArgs(2,
					sizeof(cl_mem), &answer_mem,
					sizeof(int), &size);         // the size
			cl->waitForQueue(); // sync
			setThreads(size);
			return true;
		}

		bool brute_teardown()
		{
			if (!cl->transferGPUObjectToCPU(sizeof(uint)*arr_size, &answer_mem, primeFlagArray))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			int idx = 0; // ignore 1 as a "prime", but factor 2 back in
			int ans = 0;
			for (int jj = 0; jj < size/32/2+1; jj++)
			{
				for (int ii = 0; ii < 32; ii++)
				{
					uint f = primeFlagArray[jj] & (0x1 << ii);
					if (f > 0)
					{
						f = 1;
						idx++;
						if (idx == 10001)
						{
//							std::cout << "Num = " << (jj*32*2 + 1 + ii*2) << std::endl;
							ans = jj*32*2+1 + ii*2;
							break;
						}
					}
					else
						f = 0;
//					std::cout << f;
				}
//				std::cout << std::endl;
			}
//			std::cout << idx << std::endl;
			answer = to_string(ans);
			clReleaseMemObject(answer_mem);
			delete primeFlagArray;
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
