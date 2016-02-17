bool isPalindromeInt(int num)
{
   int n = num;
   int r = 0;
   while (n > 0)
   {
      r = r * 10 + n % 10;
      n = (n - n % 10) / 10;
   }
      
   if (r == num)
   {
      return true;
   }
   return false;
}

bool isPalindromeArr(int* array, int size)
{
	for (int ii = 0; ii <= size/2; ii++)
	{
		if (array[ii] != array[size-ii-1])
			return false;
	}
	return true;
}

/*
 * Check every number to see 
 */
__kernel void brute(global int* answer, int size)
{
	int idx = get_global_id(0)+1; 
	if (idx < size)
	{
		int binary[20];
		if (!isPalindromeInt(idx))
			return;
		int num = idx;
		int ii = 0;
		while (num != 0)
		{
			binary[ii++] = num % 2;
			num = num / 2;
		}
		if (isPalindromeArr(binary, ii))
			atomic_add(answer,idx);
	}
}



/*
 *	
 */
__kernel void optimized(global int* answer, int size)
{
   int idx = get_global_id(0)*2+1; // 1 to 1023
	if (idx < 1024)
	{
		int bits[10] = { 0 };
		int l = 0;
		int n = idx;
		while (n != 0)
		{
			bits[l++] = n % 2;
			n = n/2;
		}

		for (int l2 = l; l2 <= 10; l2++) // add in zeros in between
		{
			int even = 0;
			int odd = 0;
			for (int jj = 0; jj < l2; jj++)
			{
				even = even * 2 + bits[jj];
			}
			odd = even / 2;
			for (int jj = l2-1; jj >= 0; jj--)
			{
				even = even * 2 + bits[jj];
				odd = odd * 2 + bits[jj];
			}

			if (isPalindromeInt(even))
			{
				atomic_add(answer,even);
			}
			if (isPalindromeInt(odd))
			{
				atomic_add(answer,odd);
			}
		}
	}
}