#include "discovery.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include "base/config.h"
#include "base/CLKernel.h"
#include "base/timer.h"


int main(int argc, char** argv)
{
   Timer* t = new Timer();
   t->start();

   const char *k_s = Config::Instance().getValue("kernelsize").c_str();
	int kernelsize = atoi(k_s);
   CLKernel* cl = new CLKernel(kernelsize);
   cl->discover();
   delete cl;

   t->stop();
   std::cout.precision(15);
   std::cout << "Time: " << t->getDurationNs()/1000000.0 << " (ms)" << std::endl;
}
