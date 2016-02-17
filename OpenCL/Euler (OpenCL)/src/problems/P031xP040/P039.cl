/*
 * Check every number to see 
 */
__kernel void brute(global int* answer, int size)
{
	int idx = get_global_id(0); // 0 to 1000000 
	if (idx < size)
	{
		int a = idx % 1000;
		int b = idx / 1000;
		for (int ii = 1000; ii >= 3; ii--)
		{
			int c = ii - a - b;
			if (c < 0)
				return;
				
			if (a*a + b*b == c*c)
			{
				atomic_inc(&answer[ii]);
			}
		}
	}
}


/*
 *	
 */
__kernel void optimized(global int* answer, int size)
{
	
}