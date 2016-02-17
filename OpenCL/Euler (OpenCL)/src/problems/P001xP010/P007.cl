__kernel void brute(global uint* nums, int size )
{
	int globalId = get_global_id(0);
	int num = globalId*2 + 1;    // our global processing count, odds starting with 1

	if (num < size)
	{
	   bool found = false;
	   for (int ii = 3; ii*ii <= num; ii+=2)
	   {
	   	if (num % ii == 0)
	   	{
	      	found = true;
	      	break;
	     	}
	   }
	   if (!found)
	   {
	   	int idx = globalId / 32; // 32 bit uint
	   	uint flag = 0x1 << (globalId % 32);
	      
	      atomic_or(&nums[idx], flag);
	   }
	}
}
   
__kernel void optimized(global int* answer, local int* scratch, int size )
{
	
}