#pragma OPENCL EXTENSION cl_khr_int64_base_atomics: enable

// barriers don't work across workgroups. Figure out how to structure with offsets so that everything is
// done locally in one workgroup.


// brute force, just load in all the names, bubble sort them (probably after converting to
// integers), then multiply to get their value and do atomic adds.
__kernel void brute(global long* answer, global char* array, global long* values, int arr_size, int word_len)
{
	int word = get_global_id(0); // 0 to arr_size
	int max = arr_size;
	
	if (word < max)
	{
		// first, we create val for sorting, base 27 because we can't decode a '0'
		// and it needs to be shifted so that all words "start" in the same index
		long val = 0;
		for (int ii = 0; ii < word_len; ii++)
		{
		   char c = array[word*word_len+ii];
		   val *= 27;
			if (c != ' ')
			{
				int v = c - 'A' + 1; // 1 to 26
				val += v;
			}
		}
		values[word] = val;
		
		barrier(CLK_GLOBAL_MEM_FENCE);
		
		// just look through all the data and count how many are beneath this number
		int my_idx = 1;
		for (int ii = 0; ii < max; ii++)
		{
			if (values[ii] < val)
			{
				my_idx++;
			}
		}
		
		// now add them all together with their index
		long newval = 0;
		while (val != 0)
		{
			newval += val % 27; // zero based vs 1 based
			val = val / 27;
		}
		newval = newval * my_idx;
		
		atomic_add(answer, newval);
	}
}

//http://www.bealto.com/gpu-sorting_parallel-bitonic-local.html


__kernel void parallelBitonic_Local(global long* in, int size)
{

		
		// now sort the values
		
		/*for (int length=1;length<thread_size;length<<=1)
	   {
	      bool direction = ((i & (length<<1)) != 0); // direction of sort: 0=asc, 1=desc
	      // Loop on comparison distance (between keys)
	      for (int inc=length;inc>0;inc>>=1)
	      {
	         int j = i ^ inc; // sibling to compare
	         long iData = values[i];
				long jData = values[j];
				bool smaller = (jData < iData) || ( jData == iData && j < i );
				bool swap = smaller ^ (j < i) ^ direction;
				barrier(CLK_GLOBAL_MEM_FENCE);
				values[i] = (swap)?jData:iData;
				barrier(CLK_GLOBAL_MEM_FENCE);
			}
		}*/
		
	int i = get_global_id(0); // index in workgroup

	if (i < 16)
	{
	   for (int length=1;length<16;length<<=1)
	   {
	      bool direction = ((i & (length<<1)) != 0); // direction of sort: 0=asc, 1=desc
	      // Loop on comparison distance (between keys)
	      for (int inc=length;inc>0;inc>>=1)
	      {
	         int j = i ^ inc; // sibling to compare
	         long iData = i >= size ? 999 : in[i];
				long jData = j >= size ? 999 : in[j];
				bool smaller = (jData < iData) || ( jData == iData && j < i );
				bool swap = smaller ^ (j < i) ^ direction;
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (i < size)
					in[i] = (swap)?jData:iData;
				barrier(CLK_GLOBAL_MEM_FENCE);
			}
		}
	}
}


// load the names in as an array of char[x] where x is the longest name (might have to guess)
// and first convert to numbers, then do a merge-sort (bitonic search?) in parallel, then get the final number
// by multiplication, and finally do a summation by reduction.
__kernel void optimized(global int* answer, global int* array, int size)
{
   int idx = get_global_id(0) + 1; // 1 to 9999
	if (idx < size) // 1 to 9999
	{
	   int sum = 1;
	   int ii;
	   for (ii = 2; ii*ii < idx; ii++)
	   {
	   	sum += idx % ii == 0 ? ii + idx / ii : 0;
	   }
	   if (ii*ii == idx)
	      sum += ii;
	   
		array[idx] = sum;
		
		barrier(CLK_GLOBAL_MEM_FENCE);
		
		if (array[array[idx]] == idx && array[idx] != idx)
			atomic_add(answer, idx);
	}
}