package base;

import util.Stopwatch;


public abstract class Problem {
	
	protected abstract String execute(int variation);
	protected int problemNumber = Integer.valueOf(getClass().getSimpleName().substring(1));
	protected int variations;
	protected long executeTimeNs;
	
	public void run(int variation)
	{
		Stopwatch s = new Stopwatch();
		s.start();
		
		String answer = execute(variation);
		
		executeTimeNs = s.stop();
		if (!answer.equals(Config.INSTANCE.answer(problemNumber)))
		{
			System.out.print("---Problem: " + problemNumber);
			if (variation >= 0)
				System.out.print("_" + variation);
			System.out.println(" Expected (" + Config.INSTANCE.answer(problemNumber) + ") but got (" + answer + ")");
		} 
	}
	
	public int getProblemNumber()
	{
		return problemNumber;
	}
	
	public int getVariations()
	{
		return variations;
	}
	
	public long getExecuteTimeNs()
	{
		return executeTimeNs;
	}

}
