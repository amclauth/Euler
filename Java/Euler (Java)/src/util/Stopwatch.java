package util;

import java.util.HashMap;
import java.util.Map;

public class Stopwatch {
	
	private Map<String,Long> watches;

	public Stopwatch() {
		watches = new HashMap<String,Long>();
	}
	
	/**
	 * Clears the stopwatch and readies it for new input
	 */
	public void reset() {
		watches = new HashMap<String,Long>();
	}
	
	/**
	 * This is to use most simply ... start X number of watches, then stop them in order
	 * to get the times. IE: start() starts the first watch. start() again starts a
	 * second watch. stop() returns the time of the second watch. stop() again returns
	 * the time of the first watch. Inserts as key "0", "1", "2", "3", ...
	 * @return the nanosecond start time
	 */
	public long start() {
		return start(watches.size() + "");
	}
	
	/**
	 * Returns the duration at key size()-1. This is for simple starts and stops
	 * @return duration in nanoseconds
	 */
	public long stop() {
		return stop((watches.size() - 1) + "");
	}
	
	/**
	 * Start a stopwatch with a key (so you can start and stop multiple watches and know who they are)
	 * @param key
	 * @return the nanosecond start time
	 */
	public long start(String key) {
		Long start = System.nanoTime();
		watches.put(key, start);
		return start;
	}
	
	/**
	 * Stop a stopwatch with a particular key and return the duration in nanoseconds
	 * @param key
	 * @return duration in nanoseconds
	 */
	public long stop(String key) {
		Long stop = System.nanoTime();
		if (watches == null) {
			return -1L;
		}
		if (!watches.containsKey(key)) {
			return -1L;
		}
		return stop - watches.remove(key);
	}
	
	/**
	 * Stops the current stopwatch and pretty prints the result to the returned string
	 * @return
	 */
	public String pp() {
		return Stopwatch.pp(stop());
	}
	
	/**
	 * Pretty Print (Days Hours:Minutes:Seconds.MilliSeconds)
	 * Prints out only times that are required (ie: doesn't print days or hours if the time
	 * was measured in minutes).
	 * @param l
	 */
	public static String pp(Long nanoseconds) {
		if (nanoseconds == -1) {
			return "(Stopwatch Never Started)";
		}
		double ssep = nanoseconds / 1.0e9;
		int ms = (int)Math.round((ssep - Math.floor(ssep)) * 1000.0);
		int seconds = (int)Math.floor(ssep) % 60;
		int minutes = (((int)Math.floor(ssep) - seconds) / 60) % 60;
		int hours = (((int)Math.floor(ssep) - minutes * 60 - seconds) / 60 / 60) % 24;
		int days = ((int)Math.floor(ssep) - hours * 24 - minutes * 60 - seconds) / 60 / 60 / 24;
		
		String millis = ms < 10 ? "00" + ms : (ms < 100 ? "0" + ms : ms + ""); 
		String time = (seconds < 10 ? "0" + seconds : seconds) + "." + millis;
		String units = "S";
		if (minutes > 0 || hours > 0 || days > 0) {
			time = (minutes < 10 ? "0" + minutes : minutes) + ":" + time;
			units = "M:" + units;
		}
		if (hours > 0 || days > 0) {
			time = (hours < 10 ? "0" + hours : hours) + ":" + time;
			units = "H:" + units;
		}
		if (days > 0) {
			time = days + " " + time;
			units = "D " + units;
		}
		return time + " (" + units + ")";
	}
	
	/**
	 * Similar to ppNanos, but also prepends the seconds with zeros up to secondsBuffer length
	 * @param nanoseconds
	 * @param secondsBuffer
	 * @return
	 */
	public static String ppNanos(Long nanoseconds, int secondsBuffer) {
		String result = ppNanos(nanoseconds);
		int seconds = (int) (Math.floor(nanoseconds / 1E9));
		int div = 1;
		if (seconds == 0) {
			secondsBuffer--;
		}
		for (int ii = 0; ii < secondsBuffer; ii++) {
			if (seconds < div) {
				result = "0" + result;
			}
			div *= 10;
		}
		return result;
	}
	
	/**
	 * Return seconds unmodified, but nicely formatted in smaller intervals.
	 * @param nanoseconds
	 * @return
	 */
	public static String ppNanos(Long nanoseconds) {
		if (nanoseconds == -1) {
			return "(Stopwatch Never Started)";
		}
		int ns = (int) (nanoseconds % 1000);
		int us = (int) (((nanoseconds - ns) / 1000) % 1000);
		int ms = (int) (((nanoseconds - ns - us * 1000) / 1E6) % 1000);
		int seconds = (int) ((nanoseconds - ns - us * 1000 - ms * 1E6) / 1E9);
		StringBuffer nanos = new StringBuffer();
		
		nanos.append(seconds);
		nanos.append(".");
		nanos.append(ms < 100 ? (ms < 10 ? "00" : "0") : "");
		nanos.append(ms);
		nanos.append(",");
		nanos.append(us < 100 ? (us < 10 ? "00" : "0") : "");
		nanos.append(us);
		nanos.append(",");
		nanos.append(ns < 100 ? (ns < 10 ? "00" : "0") : "");
		nanos.append(ns);
		nanos.append(" (S)");
		
		return nanos.toString();
	}
}
