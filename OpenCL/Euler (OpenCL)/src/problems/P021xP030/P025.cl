
__kernel void brute(global int* answer, global int* prev, global int* cur, int size)
{
	int idx = get_global_id(0); // 0 to 999
	if (idx < size) // 0 to 999
	{
		int counter = 2; // f1 = 1, f2 = 1, f3 = 2 ... first calculated value is f3
		while (cur[0] == 0)
		{
			int mine = prev[idx] + cur[idx];
			int newPrev = cur[idx];
			barrier(CLK_GLOBAL_MEM_FENCE);
			prev[idx] = newPrev;
			cur[idx] = mine;
			barrier(CLK_GLOBAL_MEM_FENCE);
			/*while (mine > 9)
			{
				int excess = mine / 10;
				atomic_add(&cur[idx-1],excess);
				atomic_sub(&cur[idx],excess*10);
				barrier(CLK_GLOBAL_MEM_FENCE);
				mine = cur[idx];
			}*/
			if (idx == 0)
			{
				for (int ii = 999; ii >= 0; ii--)
				{
					if (cur[ii] > 9)
					{
						cur[ii-1] += cur[ii]/10;
						cur[ii] = cur[ii] % 10;
					}
				}
			}
			counter++;
			barrier(CLK_GLOBAL_MEM_FENCE);
		}
		if (idx == 0)
			atomic_xchg(answer,counter);
	}
}
   
/*
 * Better divisor algorithm that only checks up to the sqrt
 */
__kernel void optimized(global int* answer, global int* array, int size)
{
   
}