__kernel void brute(global int* answer, global int* digits, int size )
{
	int globalId = get_global_id(0);
	int ii = globalId / 20;
	int jj = globalId % 20;
	
	int horiz = 1;
	int verti = 1;
	int diag1 = 1;
	int diag2 = 1;
	for (int n = 0; n < 4; n++)
	{
		horiz *= digits[ii*20     + jj+n];
		verti *= digits[(ii+n)*20 + jj];
		diag1 *= digits[(ii+n)*20 + jj+n];
		diag2 *= digits[(ii+3-n)*20 + jj+n];
	}
	int max = horiz > verti ? horiz : verti;
	int max2 = diag2 > diag2 ? diag1 : diag2;
	max = max > max2 ? max : max2;
	atomic_max(answer,max);
}
   
__kernel void optimized(global long* answer, local long* scratch, int size)
{
}