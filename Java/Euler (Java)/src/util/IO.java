package util;


public class IO {

	/**
	 * Reads a string into an array using the separator
	 * @param nums
	 * @param sep
	 * @return
	 */
	public static int[] readIntoArray(String nums, String sep) {
	   if (nums.length() == 0)
	      return new int[0];
	   
	   if (sep.length() == 0)
	   {
	      // special case ... doing a character split and don't want the "extra" one
	      int[] ans = new int[nums.length()];
	      nums.toCharArray();
	      for (int ii = 0; ii < nums.length(); ii++)
	      {
	         ans[ii] = nums.charAt(ii) - 48;
	      }
	      return ans;
	   }
	   
		String[] split = nums.split(sep);
		int[] ans = new int[split.length];
		
		for (int ii = 0; ii < split.length; ii++) {
			try {
				int num = Integer.valueOf(split[ii]);
				ans[ii] = num;
			} catch (NumberFormatException e) {
				// we're just skipping odd formatting
			}
		}
		return ans;
	}
}
