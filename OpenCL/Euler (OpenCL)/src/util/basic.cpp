#include "basic.h"

#include <string>

namespace basic
{
	/**
	 * Build a const char* out of the header (PRAGMA code), the function to compute
	 * value based on the thread id and store it in scratch[localId], and the operand
	 * (usually + or *) that will be used on the reduction algorithm.
	 */
   const char* reduction(const char* header, const char* threadValue, const char* operand)
   {
   	const char* program1 =
   	"__kernel void reduction( global int* answer, local int* scratch )\n"
   	"{\n"
		"	int globalId = get_global_id(0);    // our global processing count, 0 indexed\n"
		"	int localId = get_local_id(0);      // our local processing count, 0 indexed\n"
		"	int localSize = get_local_size(0);  // the max number of local threads\n"
		"													// 1002 on my local box\n"
		"\n";

   	// we could max out in localId, so use the second half of the array to do the
		// reduction (if reducing 1,2,3,4,5,6,7; do 7+3->3, 6+2->2, 5+1->1, then move down
		// to 4+2->2 3+1->1, then down again to 2+1->1, and we're done)

   	// start with the first power of two less than localsize
		// 1 bitshifted by the floor of the log2 of our localSize gets us the first
		// power of two less than local size
   	const char* program2 =
		"\n"
		"	barrier(CLK_LOCAL_MEM_FENCE);\n"
		"	for (int offset = 1 << (int)log2((float)localSize); offset > 0; offset >>= 1)\n"
		"	{\n"
		"		if ((localId >= offset) && (localId < offset * 2))\n"
		"			scratch[localId-offset] = scratch[localId-offset]";

   	// finish the operand, then barrier again (at the end of every set of operands)
   	// then finally do an atomic add across the workgroups
   	const char* program3 =
   	" scratch[localId];\n"
		"		barrier(CLK_LOCAL_MEM_FENCE);\n"
		"	}\n"
		"\n"
		"	if (localId == 0)\n"
		"	{\n"
		"		atomic_add(answer, scratch[0]);\n"
		"	}\n"
		"}";

   	// put together the kernel and return it as a const char*
   	std::string programStr = "" + std::string(header) + "\n" + program1 + threadValue + "\n" + program2 + operand + "\n" + program3;
   	return programStr.c_str();
   }
}
