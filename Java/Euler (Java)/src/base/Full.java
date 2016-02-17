package base;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import util.Stopwatch;

public class Full {
   
   private final static int numProblemsSolved = 50;
	
	@SuppressWarnings("unchecked")
   private static void initProblems()
	{
	   for (int ii = 1; ii <= numProblemsSolved; ii++)
	   {
	      String name = ii + "";
	      while (name.length() < 3)
	      {
	         name = "0" + name;
	      }
	      name = "P" + name;
	      int bucket = 10;
	      while (ii > bucket)
	         bucket += 10;
	      name = "xP0" + bucket + "." + name;
	      bucket = bucket - 10 + 1;
	      name = bucket + name;
	      if (bucket < 10)
	         name = "0" + name;
	      name = "problems.P0" + name;
	      try
         {
            problems.add((Class<? extends Problem>) Class.forName(name));
         }
         catch (ClassNotFoundException e)
         {
            System.out.println("ERROR :: No class for " + name);
            e.printStackTrace();
         }
	   }
	}
	
	private static List<Class<? extends Problem>> problems = new ArrayList<Class<? extends Problem>>();
	
	public static void main(String[] args) 
	{
		Config.INSTANCE.init();
		boolean onlyfastest = Config.INSTANCE.onlyfastest();
		
		initProblems();
		
		Stopwatch s = new Stopwatch();
		s.start("total");
		Long runTotal = 0L;
		Long execTotal = 0L;
		
		for (Class<? extends Problem> pClass : problems)
		{
			Problem p;
			try {
				p = pClass.newInstance();
			} catch (InstantiationException e) {
				System.out.println("ERROR :: Could not instantiate class " + pClass.getSimpleName());
				e.printStackTrace();
				return;
			} catch (IllegalAccessException e) {
				System.out.println("ERROR :: Could not access class " + pClass.getSimpleName());
				e.printStackTrace();
				return;
			}
			
			int pnum_min = -1;
			int pnum_max = 0;
			if (!onlyfastest)
			{
			   pnum_min = 0;
			   pnum_max = p.getVariations();
			}
			
			for (int pnum = pnum_min; pnum < pnum_max; pnum++)
			{
			   List<Long> runTimes = new ArrayList<Long>();
	         List<Long> execTimes = new ArrayList<Long>();
	         
   			for (int ii = 0; ii < 5; ii++)
   			{
   				s.start("iter");
   				p.run(pnum);
   				runTimes.add(s.stop("iter"));
   				execTimes.add(p.getExecuteTimeNs());
   			}
   			
   			Collections.sort(runTimes);
   			Collections.sort(execTimes);
   			
   			long runNs = runTimes.get(2);
   			long execNs = execTimes.get(2);
   			runTotal += runNs;
   			execTotal += execNs;
   			
   			if (Config.INSTANCE.loglvl() > 0) // human readable
   			{
   				System.out.print("Problem: " + p.getProblemNumber());
   				if (!onlyfastest)
   				   System.out.print("." + pnum);
   				System.out.print(", Run Time(ms): " + (runNs/1000000.0));
   				System.out.println(", Exec Time(ms): " + (execNs/1000000.0));
   			} else {
   				System.out.print(p.getProblemNumber());
   				if (!onlyfastest)
                  System.out.print("." + pnum);
   				System.out.print("," + (runNs/1000000.0));
   				System.out.println("," + (execNs/1000000.0));
   			}
			}
		}
		
		System.out.println();
		System.out.println("-- Total Run Time(ms)::  " + (runTotal / 1000000.0));
		System.out.println("-- Total Exec Time(ms):: " + (execTotal) / 1000000.0);
		System.out.println("-- Total Time(ms)::      " + (s.stop("total") / 1000000.0));
	}
}
