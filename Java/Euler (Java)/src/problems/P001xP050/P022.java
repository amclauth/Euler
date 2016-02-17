package problems.P001xP050;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import base.Problem;

/**
 * P022 Using names.txt (right click and 'Save Link/Target As...'), a 46K text
 * file containing over five-thousand first names, begin by sorting it into
 * alphabetical order. Then working out the alphabetical value for each name,
 * multiply this value by its alphabetical position in the list to obtain a name
 * score. For example, when the list is sorted into alphabetical order, COLIN,
 * which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So,
 * COLIN would obtain a score of 938 * 53 = 49714. What is the total of all the
 * name scores in the file? Ans: 871198282
 * 
 * @return
 */
public class P022 extends Problem {
	public P022() {
		problemNumber = 22;
		variations = 2;
	}

	@Override
	protected String execute(int variation) {
		switch (variation) {
		case 0:
			return bruteForce() + "";
		case 1:
		case -1:
			return faster() + "";
		}
		return null;
	}

	/**
	 * Just read in the file, use collections.sort (mergesort) and add to the total
	 * @return
	 */
	private long bruteForce() {
		List<String> names = new ArrayList<String>();
		try {
			InputStream in = new FileInputStream("data/names.txt");
			Reader reader = new InputStreamReader(in, Charset.defaultCharset());
			Reader buffer = new BufferedReader(reader);
			int r = 0;
			String name = "";
			while ((r = buffer.read()) != -1) {
				char c = (char) r;
				if (c == '"') {
					continue;
				}
				if (c == ',') {
					names.add(name);
					name = "";
				} else {
					name += c;
				}
			}
			names.add(name);
			in.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

		Collections.sort(names);

		long sum = 0;
		for (int ii = 0; ii < names.size(); ii++) {
			char[] chars = names.get(ii).toCharArray();
			int namecount = 0;
			for (char c : chars) {
				int n = c - 'A' + 1;
				namecount += n;
			}
			sum += namecount * (ii + 1);
		}
		return sum;
	}

	/**
	 * Not much I can upgrade here. Use the newer "readAllBytes" and string.split instead
	 * of reading char by char.
	 * @return
	 */
	private long faster() {
		List<String> names = new ArrayList<String>();
		byte[] encoded = null;
		try {
			encoded = Files.readAllBytes(Paths.get("data/names.txt"));
		} catch (IOException e) {
			e.printStackTrace();
		}
		String file = new String(encoded, Charset.defaultCharset());
		file = file.replace("\"", "");
		names.addAll(Arrays.asList(file.split(",")));
		Collections.sort(names);

		long sum = 0;
		for (int ii = 0; ii < names.size(); ii++) {
			int namecount = 0;
			for (char c : names.get(ii).toCharArray()) {
				int n = c - 'A' + 1;
				namecount += n;
			}
			sum += namecount * (ii + 1);
		}
		return sum;
	}

}
