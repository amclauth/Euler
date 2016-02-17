#ifndef __TIMER_H__
#include "timer.h"
#endif

#include <iostream>    // cin, cout
#include <stdlib.h>    // vector
#include <sys/timeb.h>

// a timer class displaying times in ms
Timer::Timer()
{
   started = false;
   stopped = false;
   start_ns = 0L;
   stop_ns = 0L;
}

void Timer::start()
{
   started = true;
   stopped = false;
   clock_gettime(CLOCK_REALTIME, &ts);
   start_ns = ts.tv_sec * 1000000000L + ts.tv_nsec;
}

void Timer::stop()
{
   // simple null avoidance
   if (!started)
   {
      std::cout << "WARNING:: Timer was not started." << std::endl;
      start();
   }
   clock_gettime(CLOCK_REALTIME, &ts);
   stop_ns = ts.tv_sec * 1000000000L + ts.tv_nsec;
   stopped = true;
}

// clock duration in ns
long Timer::getDurationNs()
{
   if (!stopped)
   {
      stop();
   }

   if (stop_ns < start_ns)
   {
      stop_ns += 86400L * 1000000000L;
   }

   return stop_ns - start_ns;
}

