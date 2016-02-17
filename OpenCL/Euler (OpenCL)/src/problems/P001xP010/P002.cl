#pragma OPENCL EXTENSION cl_khr_fp64: enable
__kernel void brute( global int* answer )
{
   int n = get_global_id(0); // thread ID, starting at zero
   // have to use doubles because float doesn't offer enough precision
   // once we get to the higher order (20+ or so) Fibonacci numbers
   double sq5 = sqrt((double)5);
   int fib = (int)floor(( powr((double)(1 + sq5),n) - 
               pow((double)(1 - sq5),n) ) / 
             ( sq5 * powr((double)2,n) )+0.5);
   if (fib % 2 == 0)
      atomic_add(answer, fib);
}
