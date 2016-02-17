#pragma OPENCL EXTENSION cl_khr_fp64: enable

// TODO ... make sure /all/ processing is on the CL device

__kernel void brute(
                    global int* answer,
                    int size
                   )
{
   int id = get_global_id(0) + 1; // thread ID, starting at zero
   if (id <= size && (id % 3 == 0 || id % 5 == 0))
      atomic_add(answer, id);
}

__kernel void reduction(
                    global int* g_array,
                    int size,
                    int max
                   )
{
   int id = get_global_id(0);
   
   // ONLY BLOCKS PER WORK GROUP!
   barrier(CLK_GLOBAL_MEM_FENCE);
   
   for (int offset = size >> 1; offset > 0; offset >>= 1)
   {
      if (id < offset)
         g_array[id] = g_array[id] + g_array[id+offset];
      barrier(CLK_GLOBAL_MEM_FENCE);
   }
}

__kernel void reduction_2(
                    global int* g_array,
                    int size,
                    int max
                   )
{
   int id = get_global_id(0);
   if (((id + 1) % 3 == 0 || (id + 1) % 5 == 0) && (id+1) <= max)
      g_array[id] = id+1;
   else
      g_array[id] = 0;
   
   // ONLY BLOCKS PER WORK GROUP!
   barrier(CLK_GLOBAL_MEM_FENCE);
   
   for (int offset = size >> 1; offset > 0; offset >>= 1)
   {
      if (id < offset)
         g_array[id] = g_array[id] + g_array[id+offset];
      barrier(CLK_GLOBAL_MEM_FENCE);
   }
}
   
__kernel void reduction_3(
                    global int* answer,
                    local int* scratch,
                    int size
                   )
{
   int globalId = get_global_id(0);    // our global processing count, 0 indexed
   int localId = get_local_id(0);      // our local processing count, 0 indexed
   int localSize = get_local_size(0);  // the max number of local threads
                                       // 1002 on my local box
   
   // store our local array
   if (((globalId + 1) % 3 == 0 || (globalId + 1) % 5 == 0) && globalId + 1 <= size)
      scratch[localId] = globalId + 1;
   else
      scratch[localId] = 0;
   
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