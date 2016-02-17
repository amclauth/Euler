int getDivisors(int n)
{
	int divisors = 1;
	int ii;
	// had to do the sqrt thing here or I run out of resources!
	for (ii = 2; ii*ii < n; ii++)
	{
	   if (n % ii == 0)
	      divisors++;
	}
	divisors = divisors * 2;
	if (ii*ii == n)
	   divisors--;
	   
	return divisors;
}

__kernel void brute(global int* answer )
{
	int n = get_global_id(0)+1;
	// get the triangle number
	int triang = n*(n+1)/2;
	int divisors = getDivisors(triang);
	if (divisors > 500)
		atomic_min(answer, triang);
}
   
/* we know that the triangle numbers are n(n+1)/2. We also know that n and n+1 have no factors
 * in common, so similarly, n and (n+1)/2 would have no factors in common (except "1"), so we
 * can multiply the factors of each together.
 */
__kernel void optimized(global int* answer)
{
	int n = get_global_id(0)+1;
	int triang = n*(n+1)/2;
	int count = 0;
	if (n % 2 == 0)
   {
      // even ... do the division on the ii number
      count = getDivisors(n / 2) * getDivisors(n + 1);
   }
   else
   {
      // odd ... do the division on the ii+1 number
      count = getDivisors(n) * getDivisors((n + 1) / 2);
   }
   if (count > 500)
   	atomic_min(answer, triang);
}