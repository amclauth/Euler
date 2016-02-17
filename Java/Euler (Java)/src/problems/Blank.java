package problems;

import base.Problem;

/**
 * Blank<br>
 * Ans: 
 * @return
 */
public class Blank extends Problem
{	
	public Blank()
	{
		problemNumber = 0;
		variations = 2; 
	}

	@Override
	protected String execute(int variation)
	{
		switch (variation)
		{
		case 0:
			return bruteForce() + "";
		case 1:
		case -1:
			return faster() + "";
		}
		return null;
	}

	/**
	 * 
	 * @return
	 */
	private long bruteForce()
	{
		return 0L;
	}
	
	/**
	 * 
	 * @return
	 */
	private long faster()
	{
		return -1L;
	}

}
