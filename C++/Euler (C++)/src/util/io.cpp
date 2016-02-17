#include "io.h"

#include <stdlib.h>
#include <fstream>
#include <sstream>

namespace io
{
	/**
	 * Reads a string into an array using the separator
	 * @param nums
	 * @param sep
	 * @return
	 */
	std::vector<int>* readIntoArray(std::string nums, std::string sep)
	{
		std::vector<int>* ans = new std::vector<int>();
		if (sep.length() == 0)
		{
			// special case ... split to character array first
			for (unsigned int ii = 0; ii < nums.size(); ii++)
			{
				ans->push_back(nums[ii] - '0');
			}
		}
		else
		{
			int idx = 0;
			int end = nums.find(sep, idx);
			while (end != (int)std::string::npos)
			{
				ans->push_back(atoi(nums.substr(idx, end - idx).c_str()));
				idx = end + sep.size();
				end = nums.find(sep, idx);
			}
			// get the last one on the end
			if (idx < (int)nums.size() && idx >= 0)
			{
				ans->push_back(atoi(nums.substr(idx, nums.size() - idx).c_str()));
			}
		}

		return ans;
	}

	/**
    * Reads a string into an array using the separator
    * @param nums
    * @param sep
    * @return
    */
   std::set<int>* readIntoSet(std::string nums, std::string sep)
   {
      std::set<int>* ans = new std::set<int>();
      if (sep.length() == 0)
      {
         // special case ... split to character array first
         for (unsigned int ii = 0; ii < nums.size(); ii++)
         {
            ans->insert(nums[ii] - '0');
         }
      }
      else
      {
         int idx = 0;
         int end = nums.find(sep, idx);
         while (end != (int)std::string::npos)
         {
            ans->insert(atoi(nums.substr(idx, end - idx).c_str()));
            idx = end + sep.size();
            end = nums.find(sep, idx);
         }
         // get the last one on the end
         if (idx < (int)nums.size() && idx >= 0)
         {
            ans->insert(atoi(nums.substr(idx, nums.size() - idx).c_str()));
         }
      }

      return ans;
   }

	/**
	 * Reads a string into an array using the separator
	 * @param nums
	 * @param sep
	 * @return
	 */
	std::vector<std::string>* readIntoStringArray(std::string nums, std::string sep)
	{
		std::vector<std::string>* ans = new std::vector<std::string>();
		if (sep.length() == 0)
		{
			// special case ... split to character array first
			for (unsigned int ii = 0; ii < nums.size(); ii++)
			{
				ans->push_back(std::string(1,nums[ii]));
			}
		}
		else
		{
			int idx = 0;
			int end = nums.find(sep, idx);
			while (end != (int)std::string::npos)
			{
				ans->push_back(nums.substr(idx, end - idx));
				idx = end + sep.size();
				end = nums.find(sep, idx);
			}
			// get the last one on the end
			if (idx < (int)nums.size() && idx >= 0)
			{
				ans->push_back(nums.substr(idx, nums.size() - idx));
			}
		}

		return ans;
	}

	/**
    * Reads a string into an array using the separator
    * @param nums
    * @param sep
    * @return
    */
   std::set<std::string>* readIntoStringSet(std::string nums, std::string sep)
   {
      std::set<std::string>* ans = new std::set<std::string>();
      if (sep.length() == 0)
      {
         // special case ... split to character array first
         for (unsigned int ii = 0; ii < nums.size(); ii++)
         {
            ans->insert(std::string(1,nums[ii]));
         }
      }
      else
      {
         int idx = 0;
         int end = nums.find(sep, idx);
         while (end != (int)std::string::npos)
         {
            ans->insert(nums.substr(idx, end - idx));
            idx = end + sep.size();
            end = nums.find(sep, idx);
         }
         // get the last one on the end
         if (idx < (int)nums.size() && idx >= 0)
         {
            ans->insert(nums.substr(idx, nums.size() - idx));
         }
      }

      return ans;
   }

	/**
	 * Read a file into a string
	 */
	std::string readFile(std::string filename)
	{
	   const char* file = filename.c_str();
		std::ifstream t(file, std::ifstream::in);
		std::stringstream buffer;
		buffer << t.rdbuf();
		return buffer.str();
	}
}
