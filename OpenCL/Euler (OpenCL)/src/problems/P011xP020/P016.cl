#pragma OPENCL EXTENSION cl_khr_fp64: enable

__kernel void brute(global int* answer, global int* array, int size )
{
	int idx = get_global_id(0);
	if (idx < size-1) // 0 to 398
	{
		for (int ii = 0; ii < 1000; ii++) // initialized with 2^0
		{
		   // get the new value
		   int new = (array[idx+1]*2/10) + array[idx]*2%10;
		   
		   barrier(CLK_GLOBAL_MEM_FENCE);
		   
		   // assign the value
		   array[idx] = new;
		   
		   barrier(CLK_GLOBAL_MEM_FENCE);
		}
		atomic_add(answer,array[idx]);
	}
}
   
/*
 */
__kernel void optimized( global int* answer, global int* array, local long* scratch, int size )
{
   int idx = get_global_id(0);
   int localId = get_local_id(0);      // our local processing count, 0 indexed
   int localSize = get_local_size(0);  // the max number of local threads
                                       // 1002 on my local box
                                       
	if (idx < size-1) // 0 to 398
	{
		for (int ii = 0; ii < 1000; ii++) // initialized with 2^0
		{
		   // get the new value
		   int new = (array[idx+1]*2/10) + array[idx]*2%10;
		   
		   barrier(CLK_LOCAL_MEM_FENCE);
		   
		   // assign the value
		   array[idx] = new;
		   
		   barrier(CLK_LOCAL_MEM_FENCE);
		}
	}
	
	// store our local array
   scratch[localId] = array[idx];
	
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