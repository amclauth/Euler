#ifndef __TIMER_H__
#define __TIMER_H__

#include <time.h>      // clock
#include <sys/time.h>  // timeofday

class Timer
{
   private:
      long start_ns, stop_ns;
      timespec ts;
      bool started, stopped;

   public:
      Timer();
      void start();
      void stop();
      /**
       * Get wall duration in ns
       */
      long getDurationNs(); // ns
};

#endif
