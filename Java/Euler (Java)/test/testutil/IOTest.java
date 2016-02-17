package testutil;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import util.IO;

public class IOTest {

	@Test
	public void test_ReadIntoArray()
	{
	   int[] array;

      array = IO.readIntoArray("", " ");
      assertEquals(0,array.length);

      array = IO.readIntoArray("10", " ");
      assertEquals(1,array.length);
      assertEquals(10, array[0]);

      array = IO.readIntoArray("10 1111 12 13 4 15", " ");
      assertEquals(6,array.length);
      assertEquals(10, array[0]);
      assertEquals(1111, array[1]);
      assertEquals(12, array[2]);
      assertEquals(13, array[3]);
      assertEquals(4, array[4]);
      assertEquals(15, array[5]);
      
      array = IO.readIntoArray("10, 1111, 12, 13, 4, 15", ", ");
      assertEquals(6,array.length);
      assertEquals(10, array[0]);
      assertEquals(1111, array[1]);
      assertEquals(12, array[2]);
      assertEquals(13, array[3]);
      assertEquals(4, array[4]);
      assertEquals(15, array[5]);

      array = IO.readIntoArray("102", "");
      assertEquals(3,array.length);
      assertEquals(1, array[0]);
      assertEquals(0, array[1]);
      assertEquals(2, array[2]);
	}
}
