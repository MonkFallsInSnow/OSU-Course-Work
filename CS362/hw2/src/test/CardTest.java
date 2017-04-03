package edu.osu.cs362;

import java.util.List;
import java.util.ArrayList;

import static org.junit.Assert.*;
import org.junit.Test;
import static org.hamcrest.CoreMatchers.*;
import static org.junit.matchers.JUnitMatchers.*;


/*
B# = test input block
Q# = output to assert (in the absence of input to partition)
*/

public class CardTest
{

	/*
	function: Card()
	input = Face face, Suit suit
	B1 - valid parameters
	...invalid parameters produce compilation errors
	*/ 

	@Test
	public void testCard()
	{
		Card.Face expectedFace = Card.Face.TWO;
		Card.Suit expectedSuit = Card.Suit.CLUB;

		try
		{
			Card card = new Card(expectedFace,expectedSuit);
			assertNotNull("Card obj should not be null",card);
			assertEquals("Card face should be 2",expectedFace,card.face);
			assertEquals("Card suit should be clubs",expectedSuit,card.suit);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	function: equals()
	input = Object o
	B1 - o is a card object
		B1_1 - o is a shallow copy
		B1_2 - o is a deep copy
		B1_3 - o is not a copy of the calling object
	B2 - o is not a card object
	*/

	@Test public void testEqualsShallowCopy()
	{
		Card card = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card cardCopy = card;

		try
		{
			boolean result = card.equals(cardCopy);
			assertTrue("Shallow copies should be equal",result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test public void testEqualsDeepCopy()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = new Card(Card.Face.TWO,Card.Suit.CLUB);

		try
		{
			boolean result = card1.equals(card2);
			assertTrue("Deep copies should be equal",result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test public void testEqualsNotEqual()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = new Card(Card.Face.ACE,Card.Suit.SPADE);

		try
		{
			boolean result = card1.equals(card2);
			assertFalse("The 2 of clubs and the Ace of spades should not be equal",result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test public void testEqualsNotACard()
	{
		Card card = new Card(Card.Face.TWO,Card.Suit.CLUB);
		String str = "not a card";

		try
		{
			boolean result = card.equals(str);
			assertFalse("A card should not be equal to a string",result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	function: toString()
	input = none
	Q1 - assert the correct string was produced
	*/

	@Test
	public void testToString()
	{
		Card card = new Card(Card.Face.TWO,Card.Suit.CLUB);

		try
		{
			String result = card.toString();
			String expected = "TWOCLUB";
			assertEquals("Inaccurate string representation of the calling object",expected,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	function: newDeck()
	input = none
	Q1 - assert deck was created
	Q2 - assert deck has proper card count
	Q3 - assert deck has all required faces and suits
	*/

	@Test
	public void testNewDeck()
	{
		final int DECK_SIZE = 52;
		List<Card> list = new ArrayList<Card>();
		List<Card> deck = new ArrayList<Card>();

		try
		{
			deck = Card.newDeck();
			assertNotNull("A deck was not created",deck);
			assertEquals("The deck has less than 52 cards",DECK_SIZE,deck.size());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		Card.Face faces[] = Card.Face.values();
		Card.Suit suits[] = Card.Suit.values();

		for(Card.Suit suit : suits)
		{
			for(Card.Face face : faces)
			{
				list.add(new Card(face,suit));
			}
		}

		assertArrayEquals("Not all faces and suits are represented in this deck",list.toArray(),deck.toArray());
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------


	/*
	function: isVisible()
	input = none
	Q1 - asset card is not visible by default
	*/

	@Test
	public void testIsVisibleDefault()
	{
		Card card = new Card(Card.Face.ACE,Card.Suit.SPADE);

		try
		{
			boolean result = card.isVisible();
			assertFalse("Card should not be visible by deafault",result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	function: setVisible()
	input = boolean b
	B1 - b is true
	B2 - b is false
	*/

	@Test
	public void testSetVisibleTrue()
	{
		Card card = new Card(Card.Face.ACE,Card.Suit.SPADE);

		try
		{
			card.setVisible(true);
			boolean result = card.isVisible();
			assertTrue("Card should be visible",result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testSetVisibleFalse()
	{
		Card card = new Card(Card.Face.ACE,Card.Suit.SPADE);

		try
		{
			card.setVisible(false);
			boolean result = card.isVisible();
			assertFalse("Card should not be visible",result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}
}