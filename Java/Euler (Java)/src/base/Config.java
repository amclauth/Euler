package base;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

public enum Config {
	INSTANCE;
	
	private final String configFile = "solver.cfg";
	
	Properties prop;
	int loglvl = 1;
	boolean onlyfastest = true;
	Map<Integer,String> answers;
	
	public void init()
	{
		prop = new Properties();
		answers = new HashMap<Integer,String>();
		if (!readConfig())
		{
			System.exit(0);
		}
	}
	
	/**
	 * Get the current log level
	 * @return
	 */
	public int loglvl()
	{
		return loglvl;
	}
	
	/**
	 * Return whether or not we should only test the optimized algorithm
	 * @return
	 */
	public boolean onlyfastest()
	{
	   return onlyfastest;
	}
	
	/**
	 * Get the answer for question n
	 * @param n
	 * @return
	 */
	public String answer(int n)
	{
		return answers.get(n);
	}
	
	private boolean readConfig()
	{
		try {
			prop.load(new FileInputStream(configFile));
		} catch (FileNotFoundException e) {
			System.out.println("ERROR :: No file found in at \"" + configFile + "\"");
			e.printStackTrace();
			return false;
		} catch (IOException e) {
			System.out.println("ERROR :: Could not read config file");
			e.printStackTrace();
			return false;
		}
		
		// check existance of log level
		if (prop.get("loglvl") == null)
		{
			System.out.println("ERROR :: loglvl not set in config file");
			return false;
		}
		try {
			loglvl = Integer.valueOf((String) prop.get("loglvl"));
		} catch (NumberFormatException e)
		{
			System.out.println("ERROR :: Could not parse log level \"" + prop.get("loglvl") + "\" into int");
			return false;
		}
		
		if (prop.get("onlyfastest") == null)
		{
		   System.out.println("ERROR :: onlyfastest not set in config file");
         return false;
      }
      try {
         onlyfastest = Integer.valueOf((String) prop.get("onlyfastest")) == 1;
      } catch (NumberFormatException e)
      {
         System.out.println("ERROR :: Could not parse onlyfastest \"" + prop.get("loglvl") + "\" into int");
         return false;
		}
		
		// check the answers are there
		Properties answerProp = new Properties();
		try {
			answerProp.load(new FileInputStream(prop.getProperty("answerfile")));
		} catch (FileNotFoundException e) {
			System.out.println("ERROR :: No answer file found in at \"" + configFile + "\"");
			e.printStackTrace();
			return false;
		} catch (IOException e) {
			System.out.println("ERROR :: Could not read config file 2");
			e.printStackTrace();
			return false;
		}
		
		// answers should be stored from 1 to size n
		for (int ii = 1; ii <= answerProp.size(); ii++)
		{
			if (answerProp.get(ii + "") == null)
			{
				System.out.println("ERROR :: answer " + ii + " not set in answer file");
				return false;
			}
			answers.put(ii, (String) answerProp.get(ii + ""));
		}
		
		return true;
	}	
}
