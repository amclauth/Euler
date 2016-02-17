__kernel void brute(global int* answer, int size )
{
	long idx = get_global_id(0)*2 + 500001; // 500k to 999,999 odds being tested
	int num = idx;
	int count = 0;
	if (idx < size)
	{
		while (idx != 1)
		{
			if (idx & 1) // odd
			{
				idx = (3*idx+1)/2;
				count += 2;
			} else {
				idx = idx / 2;
				count++;
			}
		}
	}
	int ans = count*1000000 + num; // count is 12, answer is 865432: 12865432
	                                 // safe below 2000 or so counts
	atomic_max(answer, ans);
}
   
/*
 */
__kernel void optimized(global int* answer, global int* cache, int size )
{
	long idx = get_global_id(0)+1;
	int num = idx;
	int count = 0;
	if (idx < size)
	{
		while (idx != 1)
		{
			if (idx & 1) // odd
			{
				idx = (3*idx+1)/2;
				count += 2;
			} else {
				idx = idx / 2;
				count++;
			}
			if (idx < size && cache[idx] > 0)
			{
				// this one is done
				count += cache[idx];
				idx = 1;
			}
		}
		atomic_xchg(&cache[num], count);
		//cache[num] = count;
	}
	int ans = count*1000000 + num; // count is 12, answer is 865432: 12865432
	                                 // safe below 2000 or so counts
	atomic_max(answer, ans);
}