/*
 * 
 */
__kernel void brute(global int* ans, global int* index, int size)
{
	int idx = get_global_id(0); 
	if (idx < size)
	{
		int a = idx % 10;
		idx = idx / 10;
		int b = idx % 10;
		idx = idx / 10;
		int c = idx % 10;
		idx = idx / 10;
		int d = idx % 10;
		
		if (c == 0 || a == 0 || (b == d && b == 0))
			return;
		
		int num1 = a*10+b;
		int den1 = c*10+d;
		if (num1 >= den1)
			return;
		
		int num2 = -1;
		int den2 = -1;
		
		if (b == d)
		{
			num2 = a;
			den2 = c;
		} 
		else if (a == c)
		{
			num2 = b;
			den2 = d;
		}
		else if (a == d)
		{
			num2 = b;
			den2 = c;
		}
		else if (b == c)
		{
			num2 = a;
			den2 = d;
		}
		
		if (num1*den2 == num2*den1)
		{
			//atomic_add(numerator,num2);
			//atomic_add(denominator,den2);
			ans[atomic_inc(index)] = num2*100+den2;
		}
	}
}



/*
 *	
 */
__kernel void optimized(global int* answer, int size)
{
   
}