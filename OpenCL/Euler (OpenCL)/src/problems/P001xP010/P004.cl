// The hardest part of this is the indexing. We start with 100*100, then 100*101, etc
// all the way up to 100*999, and then 101*100, 101*101, etc.
__kernel void brute(global int* answer )
{
   int idx = get_global_id(0); // thread ID
   int idx1 = idx / 900 + 100;
   int idx2 = idx % 900 + 100;
   
   int num = idx1 * idx2;
   
   // now check if it's a palindrome
   int n = num;
   int r = 0;
   while (n > 0)
   {
      r = r * 10 + n % 10;
      n = (n - n % 10) / 10;
   }
   if (r == num) // it's a palindrome!
   {
   	atomic_max(answer, num);
   }
}