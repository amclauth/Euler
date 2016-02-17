// try doing an add, and atomic adding to the array after a mem fence, so if we get
// 836 as an answer, add 3 to the next up and 8 to the one above that atomically
// then another mem fence

__kernel void brute( global int* answer, global int* array, int arr_size )
{
	int idx = get_global_id(0);
	if (idx < arr_size) // 0 to 199
	{
	   for (int ii = 2; ii <= 100; ii++) // initialized with 1
		{
		   // get the new value
		   int new = array[idx] * ii;
		   
		   // assign the value
		   array[idx] = new % 10;
		   barrier(CLK_GLOBAL_MEM_FENCE);
		   
		   // add the remaining digits
		   new = new / 10;
		   int jj = 1;
		   
		   while (new != 0 && idx - jj >= 0)
		   {
		   	int sum = atomic_add(&array[idx-jj], new % 10) + (new % 10);
		   	new = new / 10;
		   	while (sum >= 10)
		   	{
		   		atomic_sub(&array[idx-jj], 10);
		   		atomic_inc(&array[idx-jj-1]);
		   		sum -= 10;
		   	}
		   	jj++;
		   	
		   }		   
		   barrier(CLK_GLOBAL_MEM_FENCE);
		}
		
		atomic_add(answer,array[idx]);
	}
}


// other method, use a base of base 10 (10k, 100k, 1M, etc) that's a factor of the 
// max multiplier lower than the max int size, so in this case, at least 10k, at most
// 10M, then atomic add each digit at the end

__kernel void optimized( global int* answer, global int* array, int arr_size, int base )
{
	int idx = get_global_id(0);
	if (idx < arr_size) // 0 to 199
	{
	   for (int ii = 2; ii <= 100; ii++) // initialized with 1
		{
		   // get the new value
		   int new = array[idx] * ii;
		   
		   // assign the value
		   array[idx] = new % base;
		   barrier(CLK_GLOBAL_MEM_FENCE);
		   
		   // add the remaining digits
		   new = new / base;
		   int jj = 1;
		   
		   while (new != 0 && idx - jj >= 0)
		   {
		   	int sum = atomic_add(&array[idx-jj], new % base) + (new % base);
		   	new = new / base;
		   	while (sum >= base)
		   	{
		   		atomic_sub(&array[idx-jj], base);
		   		atomic_inc(&array[idx-jj-1]);
		   		sum -= base;
		   	}
		   	jj++;
		   	
		   }		   
		   barrier(CLK_GLOBAL_MEM_FENCE);
		}
		
		int num = array[idx];
		while (num != 0)
		{
			atomic_add(answer,num % 10);
			num = num / 10;
		}
	}
}

   
