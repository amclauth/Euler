#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include <CL/cl.h>
#include <cmath>
#include <iostream>
#include <sstream>    // ostringstream
#include <string>

#include "config.h"
#include "CLKernel.h"

class CLKernel;

class Problem
{
	private:
		virtual void execute(int variation) = 0;
		virtual bool setup(int variation) = 0;
		virtual bool teardown(int variation) = 0;

	protected:
		int problem_number;
		int variations;
		long executionTimeNs;
		std::string answer;
		cl_mem answer_mem;

		long kernelsize, threadsize;
		CLKernel* cl;

		template <typename T>
		std::string to_string(T value)
		{
			std::ostringstream os;
			os << value;
			return os.str();
		}

		void setThreads(long numThreads)
		{
			threadsize = ceil(numThreads * 1.0 / kernelsize) * kernelsize;
		}

	public:
		void run(int variation); // 0 is always brute force and -1 is always the fastest
		int getProblemNumber() { return problem_number; }
		int getVariations() { return variations; }
		long getExecutionNs() { return executionTimeNs; }

		virtual ~Problem();
};

#endif
