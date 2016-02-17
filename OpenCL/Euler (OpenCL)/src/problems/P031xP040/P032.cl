bool isPandigital(int nums[], int length)
{
   int mask = 0;
   for (int ii = 0; ii < length; ii++)
   {
      int n = nums[ii];
      while (n != 0)
      {
         int digit = n % 10;
         if (digit == 0)
            return false;

         mask |= (1 << (digit - 1));

         n = n/10;
      }
   }
   return mask == 0x01ff; // 1 1111 1111
}

/*
 * Check every number to see if it's pandigital and if it's a multiple.
 * Unfortunately, there are duplicates here, so we also need to check
 * if this product can be produced other ways that are pandigital.
 */
__kernel void brute(global int* array_index, global int* products, int size)
{
	int idx = get_global_id(0) + 123456789; // 123456789 to 987654321
	if (idx <= 987654321)
	{
		int num = idx;
		// check if pandigital
		
		// start with p{4}
		int p = idx % 10000;
		num = num / 10000;
		
		for (int ii = 10; ii <= 100; ii *= 10) // get 1x4 and 2x3, don't need 3x2 and 4x1 then
		{
			int b = num % ii;
			int a = num / ii;
			if (a * b == p)
			{
				int array[3];
				array[0] = p;
				array[1] = a;
				array[2] = b;
				if (isPandigital(array, 3)) // if pandigital
				{
					//atomic_add(answer,p);
					products[atomic_inc(array_index)] = p; // then return products
					break;
				}
			}
		}
	}
}



/*
 *	
 */
__kernel void optimized(global int* answer, int size)
{
   int idx = get_global_id(0) + 1234; // 1234 to 9876
   int array[3];
   
	if (idx <= 9876)
	{
		// find divisors
		array[0] = idx;
		
		for (int jj = 2; jj*jj < idx; jj++) // second half is repeats and sqrt is duplicated
		{
			if (idx % jj != 0)
				continue;
			array[1] = jj;
			array[2] = idx / jj;
		
			if (isPandigital(array,3))
			{
				atomic_add(answer,idx);
				break;
			}
		}
	}
}