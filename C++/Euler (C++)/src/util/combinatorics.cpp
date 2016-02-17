#ifndef __COMBINATORICS_H__
#include "combinatorics.h"
#endif

#include <algorithm>

void Combinatorics::permute(std::vector<int>* list)
{
   permute(list,0);
}

void Combinatorics::permute(std::vector<int>* list, unsigned int k)
{
   if (k >= list->size())
   {
      process(list);
   }

   for (unsigned int i = k; i < list->size(); i++)
   {
      std::iter_swap(list->begin() + i,list->begin() + k);
      permute(list, k + 1);
      std::iter_swap(list->begin() + k,list->begin() + i);
   }
}

Combinatorics::~Combinatorics()
{
}
