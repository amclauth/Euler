package util;

import java.util.List;

import base.Problem;

/**
 * A class that does permutations and combinations
 * @author andymac
 * @param <E>
 *
 */
public abstract class Combinatorics<E> extends Problem {

   /**
    * Permute a list to give all permutations. Uses abstract function
    * process to process intermediate results rather than preserving
    * an entire list. 
    * @param arr
    * @return 
    */
   protected void permute(List<E> arr)
   {
      permute(arr, 0);
   }
   
   private void permute(List<E> arr, int k)
   {
      if (k >= arr.size())
      {
         process(arr);
      }
      for (int i = k; i < arr.size(); i++)
      {
         java.util.Collections.swap(arr, i, k);
         permute(arr, k + 1);
         java.util.Collections.swap(arr, k, i);
      }
   }
   
   protected abstract void process(List<E> arr);
}
