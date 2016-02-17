
// assume each is n-1 long (max allowable for 1/n), then check n-1th remainder against further divisions until a match
__kernel void brute(global int* answer, int size)
{
	int idx = get_global_id(0)+1; // 1 to 1000
	if (idx < size)
	{
		int rest = 1;
		int r0;
		for (int ii = 0; ii < idx; ii++)
		{
			rest = (rest * 10) % idx;
		}
		r0 = rest;
		int count = 1;
		rest = (rest * 10) % idx;
		while (rest != r0)
		{
			rest = (rest * 10) % idx;
			count++;
		}
		atomic_max(answer,count*10000 + idx);
	}
}
   
/*
 * Better divisor algorithm that only checks up to the sqrt
 */
__kernel void optimized(global int* answer, global int* array, int size)
{
   
}