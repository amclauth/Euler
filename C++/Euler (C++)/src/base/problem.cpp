// abstract class for problems
#ifndef __PROBLEM_H__
#include "problem.h"
#endif

#include <iostream>   // cout
#include "timer.h"
#include "config.h"

void Problem::run(int variation)
{
   Timer* t = new Timer();
   t->start();

   std::string answer = execute(variation);

   t->stop();
   executionTimeNs = t->getDurationNs();

   if (answer != Config::Answer(problem_number))
   {
      std::cout << "---Problem: " << problem_number;
      if (variation >= 0)
         std::cout << "_" << variation << " ";
      std::cout << " ::: Expected (" << Config::Answer(problem_number) << ") but got (" << answer << ")" << std::endl;
   }
}

Problem::~Problem()
{
}
