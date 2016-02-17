#pragma OPENCL EXTENSION cl_khr_int64_base_atomics: enable
// just go in order. We know the first numbers all start with 0 (9! of them),
// then 1, then 2, etc. Do a barrier, then on to the next number
__kernel void brute(global long* answer, local int* temp, local int* arr, local int* fac, int size)
{
	int idx = get_global_id(0); // 0 to 1000
	
	temp[0] = 0;
	
	int iter = 999999;
	if (idx < size)
	{
		arr[idx] = idx; // in order now
		
		// get the factorial values
		int val = 1;
		for (int ii = idx; ii > 1; ii--)
		{
			val = val * ii;
		}
		fac[idx] = val;
		barrier(CLK_LOCAL_MEM_FENCE);
		
		// find the indexes into the array
		long final = 0;
	
		for (int ii = 9; ii >= 0; ii--)
		{
			barrier(CLK_LOCAL_MEM_FENCE);
			if (fac[ii] * idx <= iter)
			{
				atomic_max(temp,idx);
			}
			barrier(CLK_LOCAL_MEM_FENCE);
			int num = temp[0];
			int current = arr[num];
			
			// shift
			if (idx >= num)
			{
				int val = arr[idx+1];
				barrier(CLK_LOCAL_MEM_FENCE);
				arr[idx] = val;
			}
			final = final * 10 + current;
			iter -= num * fac[ii];
			temp[0] = 0;
		}
		
		if (idx == 0)
			atomic_xchg(answer, final);
	}
	
	
	
}
   