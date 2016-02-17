
__kernel void brute(global int* answer, global int* array, int size)
{
	int idx = get_global_id(0) + 1; // 1 to 9999
	if (idx < size) // 1 to 9999
	{
	   int sum = 0;
		for (int ii = 1; ii < idx; ii++)
		{
			sum += idx % ii == 0 ? ii : 0;
		}
		array[idx] = sum;
		
		barrier(CLK_GLOBAL_MEM_FENCE);
		
		if (array[array[idx]] == idx && array[idx] != idx)
			atomic_add(answer, idx);
	}
}
   
/*
 * Better divisor algorithm that only checks up to the sqrt
 */
__kernel void optimized(global int* answer, global int* array, int size)
{
   int idx = get_global_id(0) + 1; // 1 to 9999
	if (idx < size) // 1 to 9999
	{
	   int sum = 1;
	   int ii;
	   for (ii = 2; ii*ii < idx; ii++)
	   {
	   	sum += idx % ii == 0 ? ii + idx / ii : 0;
	   }
	   if (ii*ii == idx)
	      sum += ii;
	   
		array[idx] = sum;
		
		barrier(CLK_GLOBAL_MEM_FENCE);
		
		if (array[array[idx]] == idx && array[idx] != idx)
			atomic_add(answer, idx);
	}
}