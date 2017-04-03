package edu.osu.cs362;

import java.util.Arrays;

import static org.junit.Assert.*;
import org.junit.Test;


/*
B# = test input block
Q# = output to assert (in the absence of input to partition)
*/

public class WarmupTest  {

    @Test
    public void testFindIntegerExample() {

		int result = WarmUp.findInteger(new int[] { 1, 2, 3, 4, 5 }, 100);
		assertEquals(result, -1);

		for (int i = 1; i < 5; i++) {
			int result2 = WarmUp.findInteger(new int[] { 1, 2, 3, 4, 5 }, i + 1);
			assertEquals("findInteger(new int[]{1,2,3,4,5}," + i + ")", result2, i);
		}
	}

	/*
	function: lastZero()
	input: int[] arr
	B1 - null
	B2 - empty
	B3 - array with a single zero
		B3_1 - zero at arr[0]
		B3_2 - zero at arr[arr.length-1]
		B3_3 - zero not at arr[0] or arr[arr.length-1]
	B4 - array with multiple zeroes
	B5 - array without a zero
	*/
	@Test
	public void testLastZeroNull()
	{
		boolean failed = false;

		try
		{
			int result = WarmUp.lastZero(null);
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			failed = true;
		}

		assertTrue("Expected an ArrayIndexOutOfBoundsException", failed);
	}

	@Test
	public void testLastZeroEmptyArr()
	{
		try
		{
			int result = WarmUp.lastZero(new int[] {});
			assertEquals("No zero should be found in an empty array",-1,result);
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastZeroAtFirstIndex()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = i;
		}

		try
		{	
			int result = WarmUp.lastZero(arr);
			assertEquals("Zero was not found at arr[0]",0,result);
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastZeroAtLastIndex()
	{
		int[] arr = new int[10];

		for(int i = arr.length-1; i <= 0; i--)
		{
			arr[i] = i;
		}

		try
		{
			int result = WarmUp.lastZero(arr);
			assertEquals("Zero was not found at arr[arr.length-1]",arr.length-1,result);
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastZeroAtMiddleIndex()
	{
		int[] arr = new int[10];

		for(int i = 1; i < arr.length; i++)
		{
			if(i == (arr.length / 2))
			{
				arr[i] = 0;
			}
			else
			{
				arr[i] = i;
			}
		}

		try
		{
			int result = WarmUp.lastZero(arr);
			assertEquals("Zero was not found at arr[arr.length/2]",(arr.length/2),result);
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastZeroMultipleZeroes()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			if((i + 1) % 2 == 0)
			{
				arr[i] = 0;
			}
			else
			{
				arr[i] = i + 1;
			}
		}

		try
		{
			int result = WarmUp.lastZero(arr);
			assertEquals("Zero was not found at arr[arr.length-1]",arr.length-1,result);
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastZeroNoZeroes()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = i+1;
		}

		try
		{
			int result = WarmUp.lastZero(arr);
			assertEquals("A zero should not have been found",-1,result);
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	function: last()
	input = int[] arr, int toFind
	B1 - null
	B2 - empty array, toFind = *
	B3 - array with a single toFind value
		B3_1 - toFind at arr[0]
		B3_2 - toFind at arr[arr.length-1]
		B3_3 - toFind not at arr[0] or arr[arr.length-1]
	B4 - array with multiple toFind values
	B5 - array without a toFind value
	B6 - toFind is too large
	B7 - toFind is too small
	*/
	@Test
	public void testLastNull()
	{
		int val = 42;

		try
		{
			int result = WarmUp.last(null,val);
			assertEquals("A null value passed as the array should return -1",-1,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastEmptyArr()
	{
		int val = 42;

		try
		{
			int result = WarmUp.last(new int[] {},val);
			assertEquals("toFind should be found in an empty array",-1,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastMatchAtFirstIndex()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = i;
		}

		try
		{	
			int result = WarmUp.last(arr,arr[0]);
			assertEquals("toFind was not found at arr[0]",0,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastMatchAtLastIndex()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = i;
		}

		try
		{
			int result = WarmUp.last(arr,arr[arr.length-1]);
			assertEquals("toFind was not found at arr[arr.length-1]",arr.length-1,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastMatchAtMiddleIndex()
	{
		int val = 42;
		int[] arr = new int[10];

		for(int i = 1; i < arr.length; i++)
		{
			if(i == (arr.length / 2))
			{
				arr[i] = val;
			}
			else
			{
				arr[i] = i;
			}
		}

		try
		{
			int result = WarmUp.last(arr,val);
			assertEquals("toFind was not found at arr[arr.length/2]",(arr.length/2),result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastMultipleMatches()
	{
		int val = 42;
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			if((i + 1) % 2 == 0)
			{
				arr[i] = val;
			}
			else
			{
				arr[i] = i;
			}
		}

		try
		{
			int result = WarmUp.last(arr,val);
			assertEquals("toFind was not found at arr[arr.length-1]",arr.length-1,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastNoMatch()
	{
		int val = 42;
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = i;
		}

		try
		{
			int result = WarmUp.last(arr,val);
			assertEquals("toFind should not have been found",-1,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastToFindTooLarge()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = i;
		}

		try
		{
			int result = WarmUp.last(arr,Integer.MAX_VALUE + 1);
			assertEquals("toFind should not have been found",-1,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testLastToFindTooSmall()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = i;
		}

		try
		{
			int result = WarmUp.last(arr,Integer.MIN_VALUE - 1);
			assertEquals("toFind should not have been found",-1,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}



	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	function: positive()
	input = int[] arr
	B1 - arr is null
	B2 - arr is empty
	B3 - arr contains only positive numbers
	B4 - arr contains only negative numbers
	B5 - arr contains only zeroes
	*/

	@Test
	public void testPositiveNull()
	{
		boolean failed = false;

		try
		{
			int result = WarmUp.positive(null);
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			failed = true;
		}

		assertTrue("Expected an ArrayIndexOutOfBoundsException", failed);
	}

	@Test
	public void testPositiveEmpty()
	{
		try
		{
			int result = WarmUp.positive(new int[] {});
			assertEquals("There should be no positive numbers in an empty array",0,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

	}

	@Test
	public void testPositiveWithAllPosNums()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = i + 1;
		}

		try
		{
			int result = WarmUp.positive(arr);
			assertEquals("There should be arr.length positive numbers", arr.length,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

	}

	@Test
	public void testPositiveWithAllNegNums()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = i * -1;
		}

		try
		{
			int result = WarmUp.positive(arr);
			assertEquals("There should be no positive numbers", 0,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

	}

	@Test
	public void testPositiveNoPosOrNegNums()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = 0;
		}

		try
		{
			int result = WarmUp.positive(arr);
			assertEquals("There should be no positive numbers", 0,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	function: oddOrPos()
	input = int[] arr
	B1 - arr is null
	B2 - arr is empty
	B3 - arr contains only odd numbers
		B3_1 - all numbers are positive
		B3_2 - all numbers are negative
	B4 - arr contains only even numbers
		B4_1 - all numbers are positive
		B4_2 - all numbers are negative
	B5 - arr contains only zeroes
	*/
	
	@Test
	public void testOddOrPosNull()
	{
		boolean failed = false;

		try
		{
			int result = WarmUp.oddOrPos(null);
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			failed = true;
		}

		assertTrue("Expected an ArrayIndexOutOfBoundsException", failed);
	}

	@Test
	public void testOddOrPosEmpty()
	{
		try
		{
			int result = WarmUp.positive(new int[] {});
			assertEquals("There should be no odd and/or positive numbers in an empty array",0,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testOddOrPosWithOddPosNums()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = (2 * i) + 1;
		}

		try
		{
			int result = WarmUp.oddOrPos(arr);
			assertEquals("There should be arr.length positive odd numbers", arr.length,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testOddOrPosWithOddNegNums()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = -((2 * i) + 1);
		}

		try
		{
			int result = WarmUp.oddOrPos(arr);
			assertEquals("There should be arr.length negative odd numbers", arr.length,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testOddOrPosWithEvenPosNums()
	{
		int[] arr = new int[10];
		arr[0] = 42;

		for(int i = 1; i < arr.length; i++)
		{
			arr[i] = 2 * i;
		}

		try
		{
			int result = WarmUp.oddOrPos(arr);
			assertEquals("There should be arr.length positive even numbers", arr.length,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testOddOrPosWithEvenNegNums()
	{
		int[] arr = new int[10];
		arr[0] = -42;

		for(int i = 1; i < arr.length; i++)
		{
			arr[i] = -(2 * i);
		}

		try
		{
			int result = WarmUp.oddOrPos(arr);
			assertEquals("There should be no odd or positive numbers", 0,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}


	@Test
	public void testOddOrPosOnlyZeroes()
	{
		int[] arr = new int[10];

		for(int i = 0; i < arr.length; i++)
		{
			arr[i] = 0;
		}

		try
		{
			int result = WarmUp.oddOrPos(arr);
			assertEquals("Zero is even and neither positive nor negative", 0, result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}
}