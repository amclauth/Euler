#pragma OPENCL EXTENSION cl_khr_fp64: enable

__kernel void brute(global int* square, global int* sum, int size )
{
	int globalId = get_global_id(0);    // our global processing count, 0 indexed

   int idx = globalId + 1; // thread ID plus one
   if (globalId < size)
   {
	   atomic_add(square, idx*idx);
	   atomic_add(sum, idx);
	}
}
   
__kernel void optimized(global int* answer, local int* scratch, int size )
{
	int globalId = get_global_id(0);    // our global processing count, 0 indexed
   int localId = get_local_id(0);      // our local processing count, 0 indexed
   int localSize = get_local_size(0);  // the max number of local threads
                                       // 1002 on my local box
   int idx = globalId + 1; // thread ID plus one
   int _square = idx*idx;
   int _sum = idx;
   
   // store our local array
   if (globalId < size)
   {
   	scratch[localId*2] = _square;
   	scratch[localId*2+1] = _sum;
   } 
   else
   {
   	scratch[localId*2] = 0;
   	scratch[localId*2+1] = 0;
   } 
   
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
      {
         scratch[localId*2-offset*2] = scratch[localId*2-offset*2] + scratch[localId*2];
         scratch[localId*2+1-offset*2] = scratch[localId*2+1-offset*2] + scratch[localId*2+1];
      }
      barrier(CLK_LOCAL_MEM_FENCE);
   }  
   
   // now we have to add all the workgroups to the answer
   if (localId == 0)
   {
      atomic_add(answer, scratch[1]*scratch[1] - scratch[0]);
   }
}