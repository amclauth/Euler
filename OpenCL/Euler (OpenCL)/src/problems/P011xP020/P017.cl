#pragma OPENCL EXTENSION cl_khr_fp64: enable

__kernel void brute(global int* answer, global int* array, int size )
{
	int idx = get_global_id(0);
	int count = 0;
	if (idx < 1000)
	{
		if (idx % 100 < 20)
		{
			count += array[idx % 100];
		}
		else
		{
			if (idx % 10 == 0)
			{
				count += array[idx % 100];
			}
			else
			{
				count += array[((int) ((idx % 100) / 10)) * 10];
				count += array[(int) (idx % 10)];
			}
		}
		if (idx >= 100)
		{
			count += array[(int) (idx / 100)];
			count += array[100];
			if (idx % 100 != 0)
			{
				count += array[99];
			}
		}
	}
	atomic_add(answer,count);	
}
   
/*
 */
__kernel void optimized( global int* answer, global int* array, local long* scratch, int size )
{
   
}