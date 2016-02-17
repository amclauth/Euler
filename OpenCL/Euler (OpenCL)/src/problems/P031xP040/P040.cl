/*
 * Check every number to see 
 */
__kernel void brute(global int* answer, int size)
{
	int digits[] = {9, 90*2, 900*3, 9000*4, 90000*5, 900000*6};
	
	int idx = get_global_id(0); // 0 to 5 
	if (idx < size) // 6
	{
		int n = 1;
		for (int ii = 0; ii < idx; ii++)
		{
			n *= 10;
		}
		int ii = 0;
      int base = 1;
      int digitsPerNumber = 1;
      while (n > digits[ii])
      {
         n -= digits[ii++];
         base *= 10;
         digitsPerNumber++;
      }
      int numberOrder = (n-1) / digitsPerNumber + 1;
      int digitOrder = digitsPerNumber - (n-1) % digitsPerNumber - 1;
      int number = base + numberOrder - 1;
      for (int jj = 0; jj < digitOrder; jj++)
         number = number / 10;
      answer[idx] = number % 10;
      //return number % 10;
	}
}


/*
 *	
 */
__kernel void optimized(global int* answer, int size)
{
	
}