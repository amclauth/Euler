bool isPrime(int num)
{
	if (num % 2 == 0)
		return false;
	for (int ii = 3; ii *ii <= num; ii += 2)
	{
		if (num % ii == 0)
		{
			return false;
		}
	}
	return true;
} 

int rotateRight(int num)
{
   int i = num % 10;
   int j = (int) (num/10);
   int size = 1;
   while (j >= size)
      size *= 10;
   j += size * i;
   return j;
}
/*
 * Check every number to see 
 */
__kernel void brute(global int* answer, int size)
{
	int idx = get_global_id(0)+2; 
	if (idx < size)
	{
		int num = idx;
		if (isPrime(num))
		{
			num = rotateRight(num);
			while (num != idx)
			{
				if (!isPrime(num))
				{
					return;
				}
				num = rotateRight(num);
			}
			atomic_inc(answer);
		}
	}
}

bool checkDigits(int p)
{
   while (p != 0)
   {
      int n = p % 10;
      if (n % 2 == 0 || n % 5 == 0)
         return false;
      p = p / 10;
   }
   return true;
}

/*
 *	
 */
__kernel void optimized(global int* answer, int size)
{
   int idx = get_global_id(0)+2; 
	if (idx < size && checkDigits(idx))
	{
		int num = idx;
		if (isPrime(num))
		{
			num = rotateRight(num);
			while (num != idx)
			{
				if (!isPrime(num))
				{
					return;
				}
				num = rotateRight(num);
			}
			atomic_inc(answer);
		}
	}
}