package edu.osu.blackjack;

import static org.junit.Assert.*;
import org.junit.Test;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;	
import java.util.Random;


/*
C# = output condition
B# = input partition
*/

public class DealerTest
{
	final int DECK_SIZE = 52;

	@Test
	public void testDealer()
	{
		try
		{
			Dealer d = new Dealer();
			assertNotNull("Dealer object was not created",d);
			assertNotNull("The dealer does not have a deck",d.getHand().toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test
	public void testAcceptCard()
	{
		Dealer d = new Dealer();
		Card card = new Card(Card.Face.ACE,Card.Suit.SPADE);

		try
		{
			d.acceptCard(card);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertEquals("Card was not added to the deck",card.toString(),d.getHand().toArray()[DECK_SIZE].toString());
	}

	@Test
	public void testAcceptCardNull()
	{
		Dealer d = new Dealer();

		try
		{
			d.acceptCard(null);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertFalse("A null value should not be allowed in the deck",d.getHand().get(DECK_SIZE) == null);
	}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test
	public void testShuffleDeck()
	{
		Dealer d = new Dealer();
		List<Card> deckCopy = Card.newDeck();

		try
		{
			d.shuffleDeck();
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertFalse("The deck was not shufled",Arrays.toString(deckCopy.toArray()) == Arrays.toString(d.getHand().toArray()));
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	input = dealer or player object
	B1 - card is dealt to dealer object
		B1_1 - card is dealt to calling dealer
		B1_2 - card is dealt to separate dealer
	B2 - card is dealt to player object
	B3 - card is dealt to null
	*/

	@Test
	public void testDealCardToActiveDealer()
	{
		Dealer d = new Dealer();
		Card cardRemoved = d.getHand().get(0);

		try
		{
			d.dealCard(d);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertFalse("Top card was not removed from the dealer's deck",d.getHand().get(0).toString() == cardRemoved.toString());
		assertEquals("Removed card was not added to the dealer's deck",cardRemoved.toString(),d.getHand().get(DECK_SIZE-1).toString());
		assertTrue("Card should be visible",d.getHand().get(DECK_SIZE-1).isVisible());
	}

	@Test
	public void testDealCardToPassiveDealer()
	{
		Dealer d1 = new Dealer();
		Dealer d2 = new Dealer();
		Card cardRemoved = d1.getHand().get(0);

		try
		{
			d1.dealCard(d2);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertFalse("Top card was not removed from the dealer's deck", d1.getHand().get(0).toString() == cardRemoved.toString());
		assertEquals("Removed card was not added to the dealer's deck", cardRemoved.toString(),d2.getHand().get(DECK_SIZE).toString());
		assertTrue("Card should be visible",d2.getHand().get(DECK_SIZE).isVisible());
	}

	@Test
	public void testDealCardToPlayer()
	{
		Dealer d = new Dealer();
		Player p = new Player();
		Card cardRemoved = d.getHand().get(0);

		try
		{
			d.dealCard(p);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertFalse("Top card was not removed from the dealer's deck", d.getHand().get(0).toString() == cardRemoved.toString());
		assertEquals("Removed card was not added to the player's hand", cardRemoved.toString(),p.getHand().get(0).toString());
		assertTrue("Card should be visible",p.getHand().get(0).isVisible());
	}

	@Test
	public void testDealCardNull()
	{
		boolean hit = false;
		Dealer d = new Dealer();
		Card cardRemoved = d.getHand().get(0);

		try
		{
			d.dealCard(null);
		}
		catch(NullPointerException e)
		{
			hit = true;
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertTrue("Expected a NullPointerException",hit);
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	input = player
	B1 - player is null
	B2 - player is not null
		C1 - player wins
		C2 - dealer wins
		C3 - shuffle deck and see what happens
	*/

	@Test
	public void testCompareHandAndSettlePlayerNull()
	{
		boolean hit = false;
		Dealer d = new Dealer();

		try
		{
			d.compareHandAndSettle(null);
		}
		catch(NullPointerException e)
		{
			hit = true;
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertTrue("Expected a NullPointerException",hit);
	}

	@Test
	public void testCompareHandAndSettlePlayerWin()
	{
		Dealer d = new Dealer();
		Player p = new Player();
		int playerBet = p.makeBet();
		Integer expected = (playerBet * 2) + p.currentWallet;

		p.moveMoneyToBet(playerBet);
		
		for(int i = 0; i < 4; i++)
		{
			d.dealCard(p);
			d.dealCard(d);
		}

		try
		{
			d.compareHandAndSettle(p);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertEquals("The Player didn't win",expected,p.currentWallet);

	}

	@Test
	public void testCompareHandAndSettleDealerWin()
	{
		Dealer d = new Dealer();
		Player p = new Player();
		int playerBet = p.makeBet();
		Integer expected = p.currentWallet - playerBet;

		p.moveMoneyToBet(playerBet);

		for(int i = 0; i < 4; i++)
		{
			d.dealCard(d);
			d.dealCard(p);
		}

		try
		{
			d.compareHandAndSettle(p);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertEquals("The Dealer didn't win",expected,p.currentWallet);

	}

	//functional test
	@Test
	public void testCompareHandAndSettleShuffle()
	{
		final int GAMES_PLAYED = 5;
		Random rand = new Random();

		Dealer d = new Dealer();
		Player p = new Player();

		for(int i = 0; i < GAMES_PLAYED; i++)
		{
			try
			{
				d.shuffleDeck();
				int playerBet = p.makeBet();
				p.moveMoneyToBet(playerBet);

				for(int j = 0; j < rand.nextInt(3) + 2; j++)
				{
					d.dealCard(p);
				}
				
				for(int k = 0; k < rand.nextInt(3) + 2; k++)
				{
					d.dealCard(d);
				}

				d.compareHandAndSettle(p);
			}
			catch(Exception e)
			{
				fail("An unhandled exception occured during game " + i + " -> " + e.toString());
			}
		}
	}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test
	public void testReset()
	{
		Dealer d = new Dealer();
		List<Card> originalDeck = d.getHand();

		try
		{
			d.reset();
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertFalse("A new deck was not created",Arrays.equals(originalDeck.toArray(),d.getHand().toArray()));
		assertFalse("A new deck was not created",Arrays.deepEquals(originalDeck.toArray(),d.getHand().toArray()));
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test
	public void testSetDeckNull()
	{
		Dealer d = new Dealer();

		try
		{
			d.setDeck(null);	
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertNull("The deck should be null",d.getHand());
	}

	@Test
	public void testSetDeckNotNull()
	{
		Dealer d = new Dealer();
		List<Card> newDeck = Card.newDeck();

		try
		{
			d.setDeck(newDeck);	
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertArrayEquals("The deck was not set",newDeck.toArray(),d.getHand().toArray());
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test
	public void testIsInsuranceAvailableFalse()
	{
		Dealer d = new Dealer();

		try
		{
			boolean result = d.isInsuranceAvailable();
			assertFalse("No way to access the dealer's hand. Output should always be false",result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testIsInsuranceAvailableTrue()
	{
		Dealer d = new Dealer();

		try
		{
			boolean result = d.isInsuranceAvailable();
			assertTrue("No way to access the dealer's hand. Output should always be false",result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testIsInsuranceAvailable()
	{
		Dealer d = new Dealer();
		Card card1 = new Card(Card.Face.ACE,Card.Suit.SPADE);
		Card card2 = new Card(Card.Face.TWO,Card.Suit.HEART);

		d.acceptCard(card1);
		d.acceptCard(card2);

		card1.setVisible(true);
		card2.setVisible(false);

		boolean result = d.isInsuranceAvailable();

		assertTrue("Dealer should have insurance", result);
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test
	public void testDumpDeckNonEmptyDeck()
	{
		List<Card> deck = new ArrayList<Card>(Arrays.asList(new Card(Card.Face.ACE,Card.Suit.SPADE),new Card(Card.Face.KING,Card.Suit.CLUB)));

		try
		{
			Dealer.dumpDeck(deck);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test
	public void testDumpDeckEmptyDeck()
	{
		try
		{
			Dealer.dumpDeck(null);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}
}
