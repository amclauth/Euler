__kernel void optimized( global int* answer, global int* array )
{
	int idx = get_global_id(0);
	for (int ii = 13; ii >= 0; ii--)
	{
		int cur_row = ii; 
		if (idx <= cur_row)
		{
			int cur_idx = cur_row*(cur_row+1)/2; // 1=1, 2=3, 3=6, 4=10
			int nex_idx = cur_idx + cur_row + 1;
			
			// this spot in the array should be updated with the higher of the two
			// values beneath it
			int v1 = array[nex_idx + idx];
			int v2 = array[nex_idx + idx + 1];
			int cur = array[cur_idx + idx];
			cur += v1 > v2 ? v1 : v2;
			barrier(CLK_GLOBAL_MEM_FENCE);
			
			array[cur_idx + idx] = cur;
			barrier(CLK_GLOBAL_MEM_FENCE);
		}
	}
	if (idx == 0)
	{
	   *answer = array[0];
	}
}
   
/*
 */
__kernel void brute( global int* answer, global int* array, int size )
{
   int idx = get_global_id(0);
   int count = 0;
	int loc = 0;
	int row_size = 1;
	count += array[loc];
   for (int ii = 0; ii < 14; ii++)
   {
   	int branch = idx % 2;
   	idx = idx / 2;
   	loc += row_size + branch;
   	count += array[loc];
   	row_size++;
   }
   atomic_max(answer,count);
}