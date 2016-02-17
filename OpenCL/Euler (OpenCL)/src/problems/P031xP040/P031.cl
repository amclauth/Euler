__kernel void brute(global int* answer, global int* values, int size)
{
	int idx = get_global_id(0); // 0 to millions
	if (idx < size)
	{
		int val = 0;
		int ii = 0;
		
		val += values[ii++] * (idx % 2);
		idx = idx / 2;
		
		val += values[ii++] * (idx % 4);
		idx = idx / 4;
		
		val += values[ii++] * (idx % 10);
		idx = idx / 10;
		
		val += values[ii++] * (idx % 20);
		idx = idx / 20;
		
		val += values[ii++] * (idx % 40);
		idx = idx / 40;
		
		val += values[ii++] * (idx % 100);
		
		if (val <= 200) // can be suplemented with .01's.
			atomic_inc(answer);
	}
}



/*
 *	
 */
__kernel void optimized(global int* answer, int size)
{
   int idx = get_global_id(0); // 0 to 99*99
	
}