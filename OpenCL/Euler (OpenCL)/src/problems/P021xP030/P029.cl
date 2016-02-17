#pragma OPENCL EXTENSION cl_khr_fp64: enable
__kernel void brute(global int* answer, global double* values, int size)
{
	int idx = get_global_id(0); // 0 to 99*99
	if (idx < size)
	{
		int a = idx % 99 + 2; // 2 to 100
		int b = idx / 99 + 2; // 2 to 100
		
		double val = pow(a*1.0,b*1.0);
		values[idx] = val;
		
		barrier(CLK_GLOBAL_MEM_FENCE);
		
		bool found = false;
		for (int ii = 0; ii < idx; ii++)
		{
			if (values[ii] == val)
			{
				found = true;
				break;
			}
		}
		if (!found)
		atomic_inc(answer);
	}
}

bool is_nth_power(int a, int n)
{
	int b = round(pow(a, 1.0 / n));
	int v = b;
	for (int ii = 2; ii <= n; ii++)
	{
		v *= b;
	}
	return v == a;
}

/*
 *	just try to see if we're a power first 
 * https://projecteuler.net/thread=29;page=3 // found dupes in jorgbrown's post
 */
__kernel void optimized(global int* answer, int size)
{
   int idx = get_global_id(0); // 0 to 99*99
	if (idx < size)
	{
		int a = idx % 99 + 2; // 2 to 100
		int b = idx / 99 + 2; // 2 to 100
		
		bool found = false;
		
		if (is_nth_power(a,2) && b <= 50)
			found = true;
		else if (is_nth_power(a,3) && (b <= 33 || (b%2 == 0 && b <= 66))) // cubes and b*3/2
			found = true;
		else if (is_nth_power(a,4) && (b <= 49 || (b%3 == 0 && b <= 75))) // squares, quads, and a^3/4 ^b*4/3
			found = true;
		else if (is_nth_power(a,5) && (b <= 20 || (b%2 == 0 && b <= 40) || (b%3 == 0 && b <= 60) || (b%4 == 0 && b <= 80))) 
			found = true;
		else if (is_nth_power(a,6) && (b <= 50 || (b%2 == 0 && b <= 66) || (b%5 == 0 && b <= 80)))
			found = true;
		
		if (found)
			atomic_dec(answer); // inc or dec made no real difference
	}
}