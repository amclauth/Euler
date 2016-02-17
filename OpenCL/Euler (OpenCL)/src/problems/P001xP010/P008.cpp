#include "../../base/problem.h"

class P008: public Problem
{
	/**
	 * P008<br>
	 * Find the greatest product of five consecutive digits in the 1000-digit number.<br>
	 * Ans: 40824
	 */
	public:
		P008()
		{
			problem_number = 8;
			variations = 1;
		}
		~P008() {}

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

		int digits[1000];
		cl_mem digit_mem;
		int size;

		/**
		 * Brute force version
		 * Check every number for primeness, storing in an array of bits. This uses a
		 * lot of atomic_or operations to achieve, but only conflicts a few times
		 * per 32 bit size. The bigger problem is simply dividing all the numbers out and
		 * transferring all the memory.
		 */
		bool brute_setup()
		{
			size = 1000;
			makeString();
			int initialVal = 0;

			cl->init("src/problems/P001xP010/P008.cl","brute");
         cl->createReadOnlyMemory(sizeof(int)*size,&digit_mem);
         cl->createReadWriteMemory(sizeof(int),&answer_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*size,&digit_mem,digits);
			cl->transferCPUObjectToGPU(sizeof(int),&answer_mem,&initialVal);
			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &digit_mem,
					sizeof(int), &size);         // the size
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
			clReleaseMemObject(digit_mem);
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

		void makeString()
		{
			std::string number = "73167176531330624919225119674426574742355349194934"
					"96983520312774506326239578318016984801869478851843"
					"85861560789112949495459501737958331952853208805511"
					"12540698747158523863050715693290963295227443043557"
					"66896648950445244523161731856403098711121722383113"
					"62229893423380308135336276614282806444486645238749"
					"30358907296290491560440772390713810515859307960866"
					"70172427121883998797908792274921901699720888093776"
					"65727333001053367881220235421809751254540594752243"
					"52584907711670556013604839586446706324415722155397"
					"53697817977846174064955149290862569321978468622482"
					"83972241375657056057490261407972968652414535100474"
					"82166370484403199890008895243450658541227588666881"
					"16427171479924442928230863465674813919123162824586"
					"17866458359124566529476545682848912883142607690042"
					"24219022671055626321111109370544217506941658960408"
					"07198403850962455444362981230987879927244284909188"
					"84580156166097919133875499200524063689912560717606"
					"05886116467109405077541002256983155200055935729725"
					"71636269561882670428252483600823257530420752963450";
			for (uint ii = 0; ii < number.length(); ii++)
			{
				digits[ii] = number.at(ii) - '0';
			}
		}
};
