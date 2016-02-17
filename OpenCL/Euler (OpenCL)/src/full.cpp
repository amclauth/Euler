//============================================================================
// Name        : full.cpp
// Author      : Andrew McLauthlin
// Version     : 0.1
// Description : Project Euler, full run.
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <algorithm>  // sort
#include "base/config.h"
#include "base/problem.h"
#include "base/timer.h"
#include "problems/P001xP010/P001.cpp"
#include "problems/P001xP010/P002.cpp"
#include "problems/P001xP010/P003.cpp"
#include "problems/P001xP010/P004.cpp"
#include "problems/P001xP010/P005.cpp"
#include "problems/P001xP010/P006.cpp"
#include "problems/P001xP010/P007.cpp"
#include "problems/P001xP010/P008.cpp"
#include "problems/P001xP010/P009.cpp"
#include "problems/P001xP010/P010.cpp"
#include "problems/P011xP020/P011.cpp"
#include "problems/P011xP020/P012.cpp"
#include "problems/P011xP020/P013.cpp"
#include "problems/P011xP020/P014.cpp"
#include "problems/P011xP020/P015.cpp"
#include "problems/P011xP020/P016.cpp"
#include "problems/P011xP020/P017.cpp"
#include "problems/P011xP020/P018.cpp"
#include "problems/P011xP020/P019.cpp"
#include "problems/P011xP020/P020.cpp"
#include "problems/P021xP030/P021.cpp"
#include "problems/P021xP030/P022.cpp"
#include "problems/P021xP030/P023.cpp"
#include "problems/P021xP030/P024.cpp"
#include "problems/P021xP030/P025.cpp"
#include "problems/P021xP030/P026.cpp"
#include "problems/P021xP030/P027.cpp"
#include "problems/P021xP030/P028.cpp"
#include "problems/P021xP030/P029.cpp"
#include "problems/P021xP030/P030.cpp"
#include "problems/P031xP040/P031.cpp"
#include "problems/P031xP040/P032.cpp"
#include "problems/P031xP040/P033.cpp"
#include "problems/P031xP040/P034.cpp"
#include "problems/P031xP040/P035.cpp"
#include "problems/P031xP040/P036.cpp"
#include "problems/P031xP040/P037.cpp"
#include "problems/P031xP040/P038.cpp"
#include "problems/P031xP040/P039.cpp"
#include "problems/P031xP040/P040.cpp"

void initProblems(std::vector<Problem*> & problems)
{
   problems.push_back(new P001());
   problems.push_back(new P002());
   problems.push_back(new P003());
   problems.push_back(new P004());
   problems.push_back(new P005());
   problems.push_back(new P006());
   problems.push_back(new P007());
   problems.push_back(new P008());
   problems.push_back(new P009());
   problems.push_back(new P010());
   problems.push_back(new P011());
   problems.push_back(new P012());
   problems.push_back(new P013());
   problems.push_back(new P014());
   problems.push_back(new P015());
   problems.push_back(new P016());
   problems.push_back(new P017());
   problems.push_back(new P018());
   problems.push_back(new P019());
   problems.push_back(new P020());
   problems.push_back(new P021());
   problems.push_back(new P022());
   problems.push_back(new P023());
   problems.push_back(new P024());
   problems.push_back(new P025());
   problems.push_back(new P026());
   problems.push_back(new P027());
   problems.push_back(new P028());
   problems.push_back(new P029());
   problems.push_back(new P030());
   problems.push_back(new P031());
   problems.push_back(new P032());
   problems.push_back(new P033());
   problems.push_back(new P034());
   problems.push_back(new P035());
   problems.push_back(new P036());
   problems.push_back(new P037());
   problems.push_back(new P038());
   problems.push_back(new P039());
   problems.push_back(new P040());
}

int main(void) {
	Config::Instance(); // intialize config
	bool onlyfastest = Config::ONLYFASTEST();
	std::vector<Problem*> problems;
	initProblems(problems);

	// Set up the timer
	Timer *t = new Timer();
	t->start();
	long runTotal = 0;
	long execTotal = 0;

	Timer *t2 = new Timer();

	for (unsigned int ii = 0; ii < problems.size(); ii++)
	{
		Problem *p = problems.at(ii);
		long runTimes[5];
		long execTimes[5];

		int pnum_min = -1;
		int pnum_max = 0;
		if (!onlyfastest)
		{
			pnum_min = 0;
			pnum_max = p->getVariations();
		}

		for (int pnum = pnum_min; pnum < pnum_max; pnum++)
		{
			for (int ii = 0; ii < 5; ii++)
			{
				t2->start();
				p->run(pnum);
				t2->stop();
				runTimes[ii] = t2->getDurationNs();
				execTimes[ii] = p->getExecutionNs();
			}

			std::sort(&runTimes[0], &runTimes[0]+5);
			std::sort(&execTimes[0], &execTimes[0]+5);
			long runNs = runTimes[2];
			long execNs = execTimes[2];
			runTotal += runNs;
			execTotal += execNs;

			std::cout.precision(15);
			if (Config::LOGLVL() > 0) // human readable
			{
				std::cout << "Problem: " << p->getProblemNumber();
				if (!onlyfastest)
					std::cout << "." << pnum;
				std::cout << ", Run Time (ms): " << (runNs / 1000000.0);
				std::cout << ", Exec Time (ms): " << (execNs / 1000000.0) << std::endl;
			}
			else
			{
				std::cout << p->getProblemNumber();
				if (!onlyfastest)
					std::cout << "." << pnum;
				std::cout << "," << (runNs / 1000000.0);
				std::cout << "," << (execNs / 1000000.0) << std::endl;
			}
		}

		// Get the execution time
		t->stop();
	}

	while (!problems.empty())
	{
		delete problems.back();
		problems.pop_back();
	}
	std::cout << std::endl;
	std::cout.precision(15);
	std::cout << "-- Total Run Time(ms):  " << (runTotal / 1000000.0) << std::endl;
	std::cout << "-- Total Exec Time(ms): " << (execTotal / 1000000.0) << std::endl;
	std::cout << "-- Total Time(ms):      " << (t->getDurationNs() / 1000000.0) << std::endl;
	return EXIT_SUCCESS;
}
