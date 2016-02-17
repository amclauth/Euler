__kernel void brute(global int* answer, int size)
{
	int idx = (get_global_id(0)+1)*2+1; // 3 to 1001 by 2's
	if (idx <= 1001)
	{
		// n^2
      // n^2 - (n-1)
      // n^2 - 2(n-1)
      // n^2 - 3(n-1)
      int val = idx*idx;
      val += idx*idx - (idx-1);
      val += idx*idx - 2*(idx-1);
      val += idx*idx - 3*(idx-1);
		atomic_add(answer,val);
	}
}

/*
 * 
 */
__kernel void optimized(global int* answer, int size)
{
   // add all four diagonals immediately in a longer for loop, but less atomics
   int idx = get_global_id(0); // 0 to 3
	if (idx < size)
	{
		int val = 0;
		for (int ii = 3; ii <= 1001; ii+=2)
		{
			val += ii*ii - idx*(ii-1);
		}
		atomic_add(answer,val);
	}
}