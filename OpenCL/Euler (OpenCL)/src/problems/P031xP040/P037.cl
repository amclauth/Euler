bool isPrime(int num)
{
	if (num % 2 == 0 && num != 2)
		return false;
	for (int ii = 3; ii*ii <= num; ii += 2)
	{
		if (num % ii == 0)
		{
			return false;
		}
	}
	if (num == 1)
		return false;
	return true;
}

/*
 * Check every number to see 
 */
__kernel void brute(global int* answer, int size)
{
	int idx = get_global_id(0)*2+11; 
	if (idx < 1000000)
	{
		if (isPrime(idx))
		{
			int n = 10;
			while (idx / n != 0)
			{
				if (!isPrime(idx / n) || !isPrime(idx % n))
					return;
				n *= 10;
			}
			atomic_add(answer,idx);
		}
		
	}
}



/*
 *	
 */
__kernel void optimized(global int* answer, int size)
{
}