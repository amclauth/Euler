__kernel void brute(global int* answer, global int* digits, int size )
{
	int idx = get_global_id(0);
	if (idx < size)
	{
		int sum = 0;
		for (int ii = 0; ii < 100; ii++)
		{
			sum += digits[idx + ii*50];
		}
		answer[idx] = sum;
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
	if (idx == 0)
	{
		for (int ii = 48; ii >= 0; ii--)
		{
			int tens = answer[ii+1]/10;
			int ones = answer[ii+1] % 10;
			answer[ii] += tens;
			answer[ii+1] = ones;
		}	
	}
}
   
/*
 */
__kernel void optimized(global int* answer, global int* digits, int size )
{
	int idx = get_global_id(0);
	if (idx < size)
	{
		int sum = 0;
		for (int ii = 0; ii < 100; ii++)
			sum += digits[idx + ii*8];
		answer[idx] = sum;
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
	if (idx == 0)
	{
		int base = 10000000;
		for (int ii = 6; ii >= 0; ii--)
		{
			int tens = answer[ii+1]/base;
			int ones = answer[ii+1] % base;
			answer[ii] += tens;
			answer[ii+1] = ones;
		}	
	}
}