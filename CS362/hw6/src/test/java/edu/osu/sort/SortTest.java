package edu.osu.sort;

import org.junit.*;
import static org.junit.Assert.*;
import java.util.*;

public class SortTest  
{
	private static final int NUM_TESTS = 100;
	private static final int UPPER_BOUND_LIST_SZIE = 1000;
	private static final int UPPER_BOUND_INT = 10000;
    private Random randSeed = new Random();
    private long seed = randSeed.nextLong();
    private static Random rand;

	@Before
	public void initRandom()
	{
    	System.out.println("Seed: " + seed);

    	rand = new Random(seed);
	}

    private static List<Integer> randomIntegerArray(int n)
    {
		int randSize = rand.nextInt(n);
		List<Integer> randArr = new ArrayList<Integer>(randSize);
		populateList(randArr,randSize);

		return randArr;
    }

    private static void populateList(List<Integer> list, int size)
    {
    	for(int i = 0; i < size; i++)
    	{
    		int num = rand.nextInt(UPPER_BOUND_INT + 1);
    		list.add(new Integer(num));
    	}
    }

    private void randTestSequence(List<Integer> original,List<Integer> sorted)
    {
    	assertTrue("The original and sorted lists are different sizes", original.size() == sorted.size());

    	if(sorted.size() > 1)
    	{
	    	int first = sorted.get(0).intValue();
	    	int last = sorted.get(sorted.size()-1).intValue();
	    	int middle = sorted.get(sorted.size()/2).intValue();

	    	assertTrue("arr[0] = " + first + " arr["+ (sorted.size()-1) +"] = " + last + " | " + first + " < " + last, first < last);
	    	assertTrue("arr[0] = " + first + " arr["+ ((sorted.size()-1)/2) +"] = " + middle + " | " + first + " < " + middle, first < middle);
	    	assertTrue("arr["+ ((sorted.size()-1)/2) +"] = " + middle + " arr["+ (sorted.size()-1) +"] = " + last + " | " + middle + " < " + last, middle < last);

	    	for(int i = 0; i < sorted.size(); i++)
	    	{
	    		assertNotNull("Null value in list", sorted.get(i));
	    		
    			if(sorted.get(i) == last)
    			{
    				for(int j = i; j < sorted.size(); j++)
    				{
    					assertTrue("The val at the last index is not the largest val in the list | arr["+ j +"] = " + sorted.get(j).intValue() +
	    				" arr["+(sorted.size()-1)+"] = " + last, sorted.get(j) == last);
    				}
    			}
    			else
    			{
    				assertTrue("The val at the last index is not the largest val in the list | arr["+ i +"] = " + sorted.get(i).intValue() +
	    			" arr["+(sorted.size()-1)+"] = " + last, sorted.get(i).intValue() < last);
    			}
	    	}
	    }
    }

    /*
    @Test // This test is an example template using an oracle
    public void randomTestExample() {
	int n_runs = 10;
	for(int i=0;i<n_runs;i++){
	    
	    // Generate a random array of size 10
	    List<Integer> sorted = randomIntegerArray(10);

	    // Copy the sorted array before sorting it 
	    List<Integer> original = new ArrayList(sorted);

	    // Sort it
	    Sort.sort(sorted);

	    // Test the result 
	    assertTrue(SortOracle.isSorted(original,sorted));
	}
    }
    
    */
    @Test
    public void randomTestOracle() 
    {    
    	for(int i = 0; i < NUM_TESTS; i++)
    	{
    		List<Integer> sorted = randomIntegerArray(UPPER_BOUND_LIST_SZIE + 1);
    		List<Integer> original = new ArrayList<Integer>(sorted);

    		Sort.sort(sorted);
    		assertTrue("According to the oracle, the list was not sorted", SortOracle.isSorted(original,sorted));
    		
    	}
    }

    @Test
    public void randomTestAssertion() 
    {    

    	for(int i = 0; i < NUM_TESTS; i++)
    	{
    		List<Integer> sorted = randomIntegerArray(UPPER_BOUND_LIST_SZIE + 1);
    		List<Integer> original = new ArrayList<Integer>(sorted);

    		Sort.sort(sorted);
    		randTestSequence(original,sorted);
    		
    	}

    }
}
