package base;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import problems.P051xP075.P070;
import util.Stopwatch;

public class Single {
	static Problem p = new P070();
	static int runs = 5;
	
	public static void main(String[] args) 
	{
		Config.INSTANCE.init();
		
		Stopwatch s = new Stopwatch();
		s.start("total");
		
		for (int v = 0; v < p.getVariations(); v++)
		{
			if (Config.INSTANCE.loglvl() > 1)
				System.out.println("   Variation " + v + "/" + p.getVariations());
			List<Long> runTimes = new ArrayList<Long>();
			List<Long> execTimes = new ArrayList<Long>();
			
			for (int ii = 0; ii < runs; ii++)
			{
				if (Config.INSTANCE.loglvl() > 1)
					System.out.println("      Iteration " + ii + "/" + runs);
				s.start("iter");
				p.run(v);
				runTimes.add(s.stop("iter"));
				execTimes.add(p.getExecuteTimeNs());
			}
			
			Collections.sort(runTimes);
			Collections.sort(execTimes);
			
			long runNs = runTimes.get((runs-1)/2);
			long execNs = execTimes.get((runs-1)/2);
			
			if (Config.INSTANCE.loglvl() > 0) // human readable
			{
				System.out.print("Problem: " + p.getProblemNumber());
				if (v >= 0)
					System.out.print("_" + v);
				System.out.print(", Run Time(ms): " + (runNs/1000000.0));
				System.out.println(", Exec Time(ms): " + (execNs/1000000.0));
			} else {
				System.out.print(p.getProblemNumber());
				if (v >= 0)
					System.out.print("_" + v);
				System.out.print("," + (runNs/1000000.0));
				System.out.println("," + (execNs/1000000.0));
			}
		}
		
		System.out.println();
		System.out.println("-- Total Time: " + Stopwatch.ppNanos(s.stop("total")));
	}
}
