__kernel void brute(global int* answer, global int* powers, int size)
{
	int idx = get_global_id(0) + 10; // 10 to 999999
	if (idx < 1000000)
	{
		int num = idx;
		int sum = 0;
		while (num != 0)
		{
			sum += powers[num % 10];
			num = num / 10;
		}
		if (idx == sum)
			atomic_add(answer, idx);
	}
}



/*
 *	
 */
__kernel void optimized(global int* answer, int size)
{
   int idx = get_global_id(0); // 0 to 99*99
	
}