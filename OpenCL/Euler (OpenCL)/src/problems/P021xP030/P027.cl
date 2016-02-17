
bool isPrime(int num)
{
	if (num % 2 == 0 || num <= 0)
		return false;
	for (int ii = 3; ii * ii <= num; ii += 2)
   {
      if (num % ii == 0)
         return false;
   }
   return true;
}

// n² + an + b, where |a| < 1000 and |b| < 1000
__kernel void brute(global int* answer, int size)
{
	int idx = get_global_id(0); // 0 to 999999
	if (idx < size)
	{
		int a = idx / 1000; // 0 to 999
		int b = idx % 1000; // 0 to 999
		
		int maxn = 0;
		int val = 0;
		for (int ii = 1; ii >= -1; ii -= 2)
		{
			for (int jj = 1; jj >= -1; jj -= 2)
			{
				int n = 0;
				while (isPrime(n*n + ii*a*n + jj*b))
				{
					n++;
				}
				
				if (n > maxn)
				{
					maxn = n;
					val = ii*a * jj*b;
				}
				
			}
		}
		int my_ans = val;
		my_ans += 10000000*maxn;
		if (maxn > 40) // looking for better than 40
			atomic_max(answer,my_ans);
	}
}


   
/*
 * 
 */
__kernel void optimized(global int* answer, global int* array, int size)
{
   
}