bool isPandigital(int n)
{
   int mask = 0;
   while (n != 0)
   {
      int digit = n % 10;
      if (digit == 0)
         return false;

      mask |= (1 << (digit - 1));

      n = n/10;
   }
   return mask == 0x01ff; // 1 1111 1111
}

/*
 * Check every number to see 
 */
__kernel void brute(global int* answer, int size)
{
	int idx = get_global_id(0)+1; // 1 to 9999 
	if (idx < size)
	{
		int size = 0;
		int ii = 1;
		int num = 0;
		while (size < 9)
		{
			int n = idx * ii;
			int length = 1;
			while (n != 0)
			{
				size++;
				length *= 10;
				n = n / 10;
			}
			num = num * length + idx * ii++;
		}
		if (size != 9)
			return;
		if (isPandigital(num))
			atomic_max(answer,num);
	}
}


/*
 *	
 */
__kernel void optimized(global int* answer, int size)
{
	int idx = get_global_id(0); // 0 to 71
	if (idx < size)
	{
		int ii = idx;
		int num = 9000;
		
		int a = ii % 2 + 2; // 2 or 3
		ii = ii / 2;
		
		int b = ii % 6 + 2; // 2 - 7
		ii = ii / 6;
		
		int c = ii % 6 + 2; // 2 - 7
		
		num += a*100 + b*10 + c;
		
		num = num * 100000 + num*2;
		
		if (isPandigital(num))
			atomic_max(answer,num);
	}
}