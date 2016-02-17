
__kernel void brute(global int* answer, global int* array, int size)
{
	int idx = get_global_id(0) + 1; // 1 to 9999
	if (idx < size-1) // 1 to 21283
	{
		// use the faster divisors algorithm
	   int sum = 1;
	   int ii;
	   for (ii = 2; ii*ii < idx; ii++)
	   {
	   	sum += idx % ii == 0 ? ii + idx / ii : 0;
	   }
	   if (ii*ii == idx)
	      sum += ii;
	   
		array[idx] = sum > idx ? sum : 0;
		
		barrier(CLK_GLOBAL_MEM_FENCE);
		
		bool found = false;
		for (int ii = 1; ii < idx; ii++)
		{
			if (array[ii] > 0 && array[idx - ii] > 0)
			{
				found = true;
				break;
			}
		} 
		if (!found)
		{
			atomic_add(answer, idx);
		}
	}
}
   