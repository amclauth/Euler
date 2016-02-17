/*
 * 
 */
__kernel void brute(global int* answer, global int* fac, int size)
{
	int idx = get_global_id(0); 
	if (idx < size && idx > 2)
	{
		int num = idx;
		int sum = 0;
		while (num != 0)
		{
			sum += fac[num % 10];
			num = num / 10;
		}
		if (sum == idx)
			atomic_add(answer,idx);
	}
}



/*
 *	
 */
__kernel void optimized(global int* answer, int size)
{
   
}