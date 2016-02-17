__kernel void brute(global long* answer, global long* array, int size )
{
	// array is a "2d" array of size+1 x size+1 elements for the dots in the grid
	int idx = get_global_id(0) + 1; // we will auto-insert 1's on the side of the rows
	if (idx <= size)
	{
		int row = 1 * (size+1); // start with row 1, row 0 is auto-populated
		int prev_row = 0;
		for (int ii = 0; ii < 2*size+1; ii++) // there are n+1 + n "dots" on each grid
		{
		   array[row + idx] = array[prev_row + idx] + array[prev_row + idx - 1];
		   prev_row = row;
		   row += size+1;
		   barrier(CLK_GLOBAL_MEM_FENCE);
		}
	}
	*answer = array[(size+1)*2*size + size];
}
   
/*
 */
__kernel void optimized(global int* answer, global int* cache, int size )
{
	
}