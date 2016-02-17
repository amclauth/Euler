__kernel void brute( global int* answer, global int* daysInMonth )
{
	int idx = get_global_id(0);
	int year = idx/12 + 1; // 1901 to 2000
	int month = idx % 12; // 0 to 11
	if (year < 101)
	{
		int leapDays = (year-1) / 4;
		if (month > 1 && year % 4 == 0)
			leapDays++;
		int day = 365*year + leapDays;
		for (int ii = 0; ii < month; ii++)
		{
			day += daysInMonth[ii];
		}
		// day is now number of days since monday, jan 1 1900
		// assume day of week = 0 on Monday
		if (day % 7 == 6)
		{
			atomic_inc(answer);
		}
	}
}
   
/*
 */
__kernel void optimized( global int* answer, global int* array, local long* scratch, int size )
{
   
}