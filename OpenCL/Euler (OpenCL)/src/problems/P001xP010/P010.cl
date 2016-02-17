#pragma OPENCL EXTENSION cl_khr_fp64: enable
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics: enable

__kernel void brute(global long* answer, int size )
{
	int globalId = get_global_id(0);
	int num = globalId * 2 + 1; // all odd numbers
	if (num < size)
	{
		bool found = false;
		for (int ii = 3; ii *ii <= num; ii += 2)
		{
			if (num % ii == 0)
			{
				found = true;
			}
		} 
		if (!found) // prime!
		{
			atomic_add(answer, num);
		}
	}
}
   
__kernel void optimized(global long* answer, local long* scratch, int size)
{
   int globalId = get_global_id(0);    // our global processing count, 0 indexed
   int localId = get_local_id(0);      // our local processing count, 0 indexed
   int localSize = get_local_size(0);  // the max number of local threads
                                       // 1002 on my local box
   
   int num = globalId * 2 + 1; // all odd numbers
	if (num < size)
	{
		num = globalId * 2 + 1; // all odd numbers
		bool found = false;
		for (int ii = 3; ii * ii <= num; ii += 2)
		{
			if (num % ii == 0)
			{
				found = true;
				num = 0;
			}
		} 
	} else {
		num = 0;
	}
   // store our local array
   scratch[localId] = num;
   
   barrier(CLK_LOCAL_MEM_FENCE);
   // we could max out in localId, so use the second half of the array to do the
   // reduction (if reducing 1,2,3,4,5,6,7; do 7+3->3, 6+2->2, 5+1->1, then move down
   // to 4+2->2 3+1->1, then down again to 2+1->1, and we're done)
   
   // start with the first power of two less than localsize
   // 1 bitshifted by the floor of the log2 of our localSize gets us the first
   // power of two less than local size
   for (int offset = 1 << (int)log2((double)localSize); offset > 0; offset >>= 1)
   {
      if ((localId >= offset) && (localId < offset * 2))
         scratch[localId-offset] = scratch[localId-offset] + scratch[localId];
      barrier(CLK_LOCAL_MEM_FENCE);
   }  
   
   // now we have to add all the workgroups to the answer
   if (localId == 0)
   {
      atomic_add(answer, scratch[0]);
   }
}