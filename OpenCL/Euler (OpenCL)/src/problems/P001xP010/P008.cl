__kernel void brute(global int* answer, global int* digits, int size )
{
	int globalId = get_global_id(0);
	if (globalId < size-5)
	{
		int mult = 1;
	   for (int ii = globalId; ii < globalId + 5; ii++)
	   {
	   	mult *= digits[ii];
	   }
	   if (mult > 0)
	   {
	      atomic_max(answer, mult);
   	}
	}
}
   
__kernel void optimized(global int* answer, local int* scratch, int size )
{
	
}