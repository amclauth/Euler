#ifndef __COMBINATORICS_H__
#define __COMBINATORICS_H__

#include <vector>

//template <class T>
class Combinatorics
{
   protected:
      virtual void process(std::vector<int>* list) = 0;
      void permute(std::vector<int>* list);

   private:
      void permute(std::vector<int>* list, unsigned int k);

   public:
      virtual ~Combinatorics();
};

#endif
