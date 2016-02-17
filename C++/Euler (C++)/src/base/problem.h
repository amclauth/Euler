#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include <string>
#include <sstream>    // ostringstream

class Problem
{
   private:
      virtual std::string execute(int variation) = 0;

   protected:
      int problem_number;
      int variations;
      long executionTimeNs;

      template<typename T>
      std::string to_string(T value)
      {
         std::ostringstream os;
         os << value;
         return os.str();
      }

   public:
      void run(int variation); // 0 is always brute force and -1 is always the fastest
      int getProblemNumber()
      {
         return problem_number;
      }
      int getVariations()
      {
         return variations;
      }
      long getExecutionNs()
      {
         return executionTimeNs;
      }

      virtual ~Problem();
};

#endif
