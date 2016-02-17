// Try all the numbers, checking occasionally to see if we've got one.
__kernel void brute(global int* threadSize, global int* answer )
{
   int idx = get_global_id(0)+1; // thread ID plus one
   bool valid = true;
   while (valid)
   {
      for (int ii = 2; ii <= 20; ii++)
      {
         if (idx % ii != 0)
            valid = false;
      }
      if (valid) // found one that's divisible!
      {
	      atomic_min(answer, idx);
	      return;
   	}
   	// if it's larger than an int, we're too far
   	if (2147000000 - *threadSize < idx)
   	   return;
   	idx += *threadSize;
   	valid = true;
   }
}
   
// Search for just the prime coefficients, then multiply them together
__kernel void optimized(global int* primes, global int* count )
{
	int idx = get_global_id(0);
	if (idx >= *count)
		return;
		
	int prime = primes[idx];
	
	int max = pow(prime*1.0,(int) floor(log(20.0) / log(prime*1.0)));
	/*int max = prime;
	for (int ii = 1; ii <= 20; ii++)
	{
		int c = 1;
		int num = ii;
		while (num % prime == 0)
		{
		   c *= prime;
		   num = num / prime;
		}
		max = c > max ? c : max;
   }*/
   
   // set this variable because I can't multiply *answer *= max
   primes[idx] = max;
}