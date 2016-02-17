//============================================================================
// Name        : Euler.cpp
// Author      : Andrew McLauthlin
// Version     : 0.1
// Description : Single problem run in Project Euler
//============================================================================

#include <stdlib.h>
#include <algorithm>  // sort
#include <iostream>

#include "base/config.h"
#include "base/timer.h"
//#include "problems/P001xP010/P009.cpp"
//#include "problems/P011xP020/P020.cpp"
//#include "problems/P021xP030/P029.cpp"
#include "problems/P031xP040/P037.cpp"

int main(void)
{
   Config::Instance(); // initialize config
   Problem *p = new P037(); // initialize the problem space

   // Set up the timer
   Timer *t = new Timer();
   t->start();

   Timer *t2 = new Timer();

   for (int v = 0; v < p->getVariations(); v++)
   {
      long runTimes[5];
      long execTimes[5];

      if (Config::LOGLVL() > 1)
         std::cout << "   Variation " << v << "/" << p->getVariations() << std::endl;

      for (int ii = 0; ii < 5; ii++)
      {
         t2->start();
         p->run(v);
         t2->stop();
         runTimes[ii] = t2->getDurationNs();
         execTimes[ii] = p->getExecutionNs();
      }

      std::sort(&runTimes[0], &runTimes[5]);
      std::sort(&execTimes[0], &execTimes[5]);
      long runNs = runTimes[2];
      long execNs = execTimes[2];

      std::cout.precision(15);
      if (Config::LOGLVL() > 0) // human readable
      {
         std::cout << "Problem: " << p->getProblemNumber();
         if (v >= 0)
            std::cout << "_" << v;
         std::cout << ", Run Time (ms): " << (runNs / 1000000.0);
         std::cout << ", Exec Time (ms): " << (execNs / 1000000.0) << std::endl;
      }
      else
      {
         std::cout << p->getProblemNumber();
         if (v >= 0)
            std::cout << "_" << p->getProblemNumber();
         std::cout << "," << (runNs / 1000000.0);
         std::cout << "," << (execNs / 1000000.0) << std::endl;
      }
   }

   // Get the execution time
   t->stop();

   std::cout << std::endl;
   std::cout.precision(15);
   std::cout << "-- Total Execution Time(ms): " << (t->getDurationNs() / 1000000.0) << std::endl;
   delete p; // clean up
   delete t;
   delete t2;
   return EXIT_SUCCESS;
}
