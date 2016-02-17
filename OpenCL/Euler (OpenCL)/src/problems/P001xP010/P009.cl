__kernel void brute(global int* answer, int size )
{
	int globalId = get_global_id(0);
	if (globalId < size)
	{
		int a = globalId / 997 + 1;
		int b = globalId % 997 + 1;
		int c = 1000 - a - b;
		if (a*a + b*b == c*c)
			*answer = a*b*c; // only one, no atomic needed
	}
}
   
__kernel void optimized(global int* answer, int size )
{
	int globalId = get_global_id(0);
   if (globalId < size)
   {
		int a = globalId + 1; // 0 to 998
		int b = (500 * 1000 - 1000 * a) / (1000 - a);
	   int c = 1000 - a - b;
	   if (a*a + b*b == c*c && b > 0) // there's another answer at 920 with a negative b!
			*answer = a*b*c; // only one, no atomic needed
   }
}