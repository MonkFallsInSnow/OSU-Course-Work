package edu.osu.cs362;

import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.Random;

import static org.junit.Assert.*;
import org.junit.Test;
import static org.hamcrest.CoreMatchers.*;
import static org.junit.matchers.JUnitMatchers.*;


/*
B# = test input block
Q# = output to assert (in the absence of input to partition)
*/

public class CardCollectionTest
{

	/*
	function: CardCollection()
	input = any number of Card objects (init)
	B1 - init provides no cards
	B2 - init provides at least one card
		B2_1 - each card is unique
		B2_2 - each card is a duplicate
			B2_2_1 - cards are shallow copies
			B2_2_1 - cards are deep copies
	*/
	@Test
	public void testCardCollectionEmptyParams()
	{
		try
		{
			CardCollection col = new CardCollection();
			assertEquals("There should be no cards in the collection",0,col.cards.size());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testCardCollectionMultipleUniqueParams()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = new Card(Card.Face.THREE,Card.Suit.CLUB);
		Card card3 = new Card(Card.Face.FOUR,Card.Suit.CLUB);

		try
		{
			CardCollection col = new CardCollection(card1,card2,card3);
			assertEquals("There should be 3 cards in the collection",3,col.cards.size());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testCardCollectionMultipleShallowCopyParams()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = card1;
		Card card3 = card2;

		try
		{
			CardCollection col = new CardCollection(card1,card2,card3);
			assertEquals("There should be 3 cards in the collection",3,col.cards.size());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testCardCollectionMultipleDeepCopyParams()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card3 = new Card(Card.Face.TWO,Card.Suit.CLUB);

		try
		{
			CardCollection col = new CardCollection(card1,card2,card3);
			assertEquals("There should be 3 cards in the collection",3,col.cards.size());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	function: getCards()
	input = none (the CardCollection cards property may be considered a type of input)
	B1 - empty card collection
	B2 - non empty card collection
	*/

	@Test
	public void testGetCardsEmpty()
	{
		CardCollection col = new CardCollection();

		try
		{
			List<Card> result = col.getCards();
			assertArrayEquals("There should be no cards in the collection",new Card[] {},result.toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testGetCardsNotEmpty()
	{
		Card card = new Card(Card.Face.TWO,Card.Suit.CLUB);
		CardCollection col = new CardCollection(card);

		try
		{
			List<Card> result = col.getCards();
			assertArrayEquals("There should be 1 cards in the collection",new Card[] {card},result.toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	function: add()
	input = Card c
	B1 - c is not null
	...passing a null param causes a compilation error since the add() method is overloaded
	...uses an empty collection
	*/

	@Test
	public void testAddNotNull()
	{
		Card card = new Card(Card.Face.TWO,Card.Suit.CLUB);
		CardCollection col = new CardCollection();

		try
		{
			col.add(card);
			assertEquals("The collection should have a single card, the 2 of clubs",card,col.getCards().get(0));
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	function: add()
	input = List<Card> c
	B1 - c is empty
	B2 - c is not empty
		B2_1 - c contains uniqe cards
		B2_2 - c contains card copies
			B2_2_1 - c contains shallow copies
			B2_2_2 - c contains deep copies
	...uses an empty collection
	*/

	@Test
	public void testAddEmpty()
	{
		List<Card> cardList = new ArrayList<Card>();
		CardCollection col = new CardCollection();

		try
		{
			col.add(cardList);
			assertArrayEquals("The collection should be empty", cardList.toArray(),col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testAddListUniqueCards()
	{
		List<Card> cardList = Card.newDeck();
		CardCollection col = new CardCollection();

		try
		{
			col.add(cardList);
			assertArrayEquals("The collection should represent a full deck", cardList.toArray(),col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testAddListShallowCopies()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = card1;
		Card card3 = card2;

		List<Card> cardList = new ArrayList<Card>(Arrays.asList(card1,card2,card3));
		CardCollection col = new CardCollection();

		try
		{
			col.add(cardList);
			assertArrayEquals("The collection should have 3 identical cards", cardList.toArray(),col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testAddListDeepCopies()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card3 = new Card(Card.Face.TWO,Card.Suit.CLUB);

		List<Card> cardList = new ArrayList<Card>(Arrays.asList(card1,card2,card3));
		CardCollection col = new CardCollection();

		try
		{
			col.add(cardList);
			assertArrayEquals("The collection should have 3 identical cards", cardList.toArray(),col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	function: discardCard()
	input = int handPos
	B1 - handPos is inside collection bounds
		B1_1 - handPos references a unique card
			B1_1_1 - handPos references top of collection
			B1_1_2 - handPos references bottom of collection
			B1_1_3 - handPos references middle of collection
		B1_2 - handPos references a card with copy
			B1_2_1 - card has shallow copy
				B1_2_1_1 - handPos references top of collection
				B1_2_1_2 - handPos references bottom of collection
				B1_2_1_3 - handPos references middle of collection
			B1_2_2 - card has deep copy
				B1_2_2_1 - handPos references top of collection
				B1_2_2_2 - handPos references bottom of collection
				B1_2_2_3 - handPos references middle of collection
	B2 - handPos is outside collection bounds 
		B2_1 - handPos is larger than collection
			B2_1_1 - handPos is larger than an int
			B2_1_2 - handPos is collection.size() + 1
		B2_2 - handPos is smaller than collection
			B2_1_1 - handPos is smaller than an int
			B2_1_2 - handPos is collection.size() - (collection.size() + 1)
	*/

	@Test
	public void testDiscardCardTopUnique()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = new Card(Card.Face.THREE,Card.Suit.CLUB);
		Card card3 = new Card(Card.Face.FOUR,Card.Suit.CLUB);

		CardCollection col = new CardCollection(card1,card2,card3);

		try
		{
			Card result = col.discardCard(0);
			assertEquals("Wrong card was discarded",card1,result);
			assertArrayEquals("Collection is out of order",new Card[] {card2,card3},col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDiscardCardBottomUnique()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = new Card(Card.Face.THREE,Card.Suit.CLUB);
		Card card3 = new Card(Card.Face.FOUR,Card.Suit.CLUB);

		CardCollection col = new CardCollection(card1,card2,card3);

		try
		{
			Card result = col.discardCard(col.getCards().size()-1);
			assertEquals("Wrong card was discarded",card3,result);
			assertArrayEquals("Collection is out of order",new Card[] {card1,card2},col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDiscardCardMiddleUnique()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = new Card(Card.Face.THREE,Card.Suit.CLUB);
		Card card3 = new Card(Card.Face.FOUR,Card.Suit.CLUB);

		CardCollection col = new CardCollection(card1,card2,card3);

		try
		{
			Card result = col.discardCard((col.getCards().size()-1)/2);
			assertEquals("Wrong card was discarded",card2,result);
			assertArrayEquals("Collection is out of order",new Card[] {card1,card3},col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDiscardCardTopShallowCopy()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card1Copy = card1;
		Card card2 = new Card(Card.Face.ACE,Card.Suit.CLUB);
		Card card2Copy = card2;

		CardCollection col = new CardCollection(card1,card2,card1Copy,card2Copy);

		try
		{
			Card result = col.discardCard(0);
			assertEquals("Wrong card was discarded",card1,result);
			assertArrayEquals("Collection is out of order",new Card[] {card2,card1Copy,card2Copy},col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDiscardCardBottomShallowCopy()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card1Copy = card1;
		Card card2 = new Card(Card.Face.ACE,Card.Suit.CLUB);
		Card card2Copy = card2;

		CardCollection col = new CardCollection(card1,card2,card1Copy,card2Copy);

		try
		{
			Card result = col.discardCard(col.getCards().size()-1);
			assertEquals("Wrong card was discarded",card2Copy,result);
			assertArrayEquals("Collection is out of order",new Card[] {card1,card2,card1Copy},col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDiscardCardMiddleShallowCopy()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card1Copy = card1;
		Card card2 = new Card(Card.Face.ACE,Card.Suit.CLUB);
		Card card2Copy = card2;

		CardCollection col = new CardCollection(card1,card2,card1Copy,card2Copy);

		try
		{
			Card result = col.discardCard((col.getCards().size())/2);
			assertEquals("Wrong card was discarded",card1Copy,result);
			assertArrayEquals("Collection is out of order",new Card[] {card1,card2,card2Copy},col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDiscardCardTopDeepCopy()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card1Copy = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = new Card(Card.Face.ACE,Card.Suit.CLUB);
		Card card2Copy = new Card(Card.Face.ACE,Card.Suit.CLUB);

		CardCollection col = new CardCollection(card1,card2,card1Copy,card2Copy);

		try
		{
			Card result = col.discardCard(0);
			assertEquals("Wrong card was discarded",card1,result);
			assertArrayEquals("Collection is out of order",new Card[] {card2,card1Copy,card2Copy},col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDiscardCardBottomDeepCopy()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card1Copy = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = new Card(Card.Face.ACE,Card.Suit.CLUB);
		Card card2Copy = new Card(Card.Face.ACE,Card.Suit.CLUB);

		CardCollection col = new CardCollection(card1,card2,card1Copy,card2Copy);

		try
		{
			Card result = col.discardCard(col.getCards().size()-1);
			assertEquals("Wrong card was discarded",card2Copy,result);
			assertArrayEquals("Collection is out of order",new Card[] {card1,card2,card1Copy},col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDiscardCardMiddleDeepCopy()
	{
		Card card1 = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card1Copy = new Card(Card.Face.TWO,Card.Suit.CLUB);
		Card card2 = new Card(Card.Face.ACE,Card.Suit.CLUB);
		Card card2Copy = new Card(Card.Face.ACE,Card.Suit.CLUB);

		CardCollection col = new CardCollection(card1,card2,card1Copy,card2Copy);

		try
		{
			Card result = col.discardCard((col.getCards().size())/2);
			assertEquals("Wrong card was discarded",card1Copy,result);
			assertArrayEquals("Collection is out of order",new Card[] {card1,card2,card2Copy},col.getCards().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDiscardCardLargerThanCollection()
	{
		CardCollection col = new CardCollection();

		try
		{
			Card result = col.discardCard(1);
			assertThat("A card should not have been returned",result,not(instanceOf(Card.class)));
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDiscardCardLargerThanInt()
	{
		CardCollection col = new CardCollection();

		try
		{
			Card result = col.discardCard(Integer.MAX_VALUE + 1);
			assertThat("A card should not have been returned",result,not(instanceOf(Card.class)));
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDiscardCardSmallerThanCollection()
	{
		CardCollection col = new CardCollection(new Card(Card.Face.TWO,Card.Suit.CLUB));

		try
		{
			Card result = col.discardCard(-1);
			assertThat("A card should not have been returned",result,not(instanceOf(Card.class)));
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDiscardCardSmallerThanInt()
	{
		CardCollection col = new CardCollection(new Card(Card.Face.TWO,Card.Suit.CLUB));

		try
		{
			Card result = col.discardCard(Integer.MIN_VALUE - 1);
			assertThat("A card should not have been returned",result,not(instanceOf(Card.class)));
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}
}