#include <cstdlib>

// abstract class for problems
#include "problem.h"
#include <iostream>   // cout
#include "timer.h"
#include "config.h"

void Problem::run(int variation)
{
	kernelsize = atoi(Config::Instance().getValue("kernelsize").c_str());

	if (!setup(variation))
		std::cout << "ERROR:: Could not set up problem!" << std::endl;

	Timer* t = new Timer();
	t->start();

	execute(variation);

	t->stop();
	executionTimeNs = t->getDurationNs();

	if (!teardown(variation))
		std::cout << "ERROR:: Could not tear down problem!" << std::endl;

	if (answer != Config::Answer(problem_number))
	{
		std::cout << "---Problem: " << problem_number;
		if (variation >= 0)
			std::cout << "_" << variation << " ";
		std::cout << "::: Expected (" << Config::Answer(problem_number) << ") but got (" << answer << ")" << std::endl;
	}
}

Problem::~Problem() {}
