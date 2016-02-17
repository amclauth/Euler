// discovered my semaphores actually lock the warp. Not good.
__kernel void brute(global long* number, global int* answer )
{
   int n = get_global_id(0)*2+3; // thread ID, starting at 3 ...
   // assume that 2 is a trivial answer and any prime will be odd
   
   // check if it's prime ... this is the slowness
   for (int ii = 3; ii * ii <= n; ii += 2)
   {
      if (n % ii == 0)
         return;
   }
   
   if (*number % n == 0)
   {
   	atomic_max(answer,n);
   }
}

// Trying to load just the primes up here and then testing each of them
__kernel void optimized( global long* number, global int* primes, global int* answer )
{
   int n = get_global_id(0);
   
   if (*number % primes[n] == 0)
   {
   	atomic_max(answer, primes[n]);
   }
}