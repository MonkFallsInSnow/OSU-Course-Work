package edu.osu.blackjack;

import static org.junit.Assert.*;
import org.junit.Test;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;	

public class PlayerTest
{
	@Test
	public void testAcceptCardNull() 
	{
		Player p = new Player();

		try
		{
			p.acceptCard(null);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertNotEquals("A null value should not be allowed in the player's hand",null,p.getHand().get(0));
	}

	@Test
	public void testAcceptCardNotNull() 
	{
		Player p = new Player();
		Card card1 = new Card(Card.Face.ACE,Card.Suit.SPADE);
		Card card2 = new Card(Card.Face.KING,Card.Suit.SPADE);
		String expected = card1.toString() + " " + card2.toString();

		try
		{
			p.acceptCard(card1);
			p.acceptCard(card2);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		List<Card> hand = p.getHand();
		String result = hand.get(0).toString() + " " + hand.get(1).toString();

		assertEquals("Card was not added to the player's hand",expected,result);
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test
	public void testMakeBet()
	{
		Player p = new Player();
		int expected = 10;

		try
		{
			int playerBet = p.makeBet();
			assertEquals("Wrong bet was made", expected,playerBet);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test
	public  void testDoubleDownBetWithoutPrevBet()
	{
		Player p = new Player();

		try
		{
			int playerBet = p.doubleDownBet();
			assertEquals("Doubling down without first making a bet should keep the current bet at 0", 0, playerBet);

		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

	}

	@Test
	public  void testDoubleDownBetWithPrevBet()
	{
		Player p = new Player();
		int playerBet = p.makeBet();

		try
		{
			int doubleDownBet = p.doubleDownBet();
			assertEquals("Double down did not occur", 20, doubleDownBet);

		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	@Test
	public void testMoveMoneyToInsuranceWalletGreaterThanAmnt() 
	{
		Player p = new Player();
		int amnt = 10;

		try
		{
			p.moveMoneyToInsurance(amnt);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertEquals("Wrong insurance amount", amnt,p.currentInsurance.intValue());
		assertEquals("Wrong wallet amount",990,p.currentWallet.intValue());
	}

	@Test
	public void testMoveMoneyToInsuranceAmmountWalletLessThanAmnt() 
	{
		boolean hit = false;
		Player p = new Player();
		int amnt = p.currentWallet + 10;

		try
		{
			p.moveMoneyToInsurance(amnt);
		}
		catch(Exception e)
		{
			hit = true;
		}

		assertTrue("A RuntimeException was expected",hit);
	}

	@Test
	public void testMoveMoneyToInsuranceAmntNeg() 
	{
		Player p = new Player();
		int amnt = -20;
		int originalWallet = p.currentWallet.intValue();

		try
		{
			p.moveMoneyToInsurance(amnt);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertTrue("Player should not be allowed to move negative amounts to insurance",p.currentWallet < originalWallet);
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test	
	public  void testMakeInsuranceBetCurrentInsuranceNull()
	{
		Player p = new Player();

		try
		{
			int insurance = p.makeInsuranceBet();
			assertNull("Can't make and insurance bet without first moving money to insurance", p.currentInsurance.intValue());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}	
	}

	@Test	
	public  void testMakeInsuranceBetCurrentInsuranceNotNull()
	{
		int insurance;
		int amnt = 10;
		Player p = new Player();
		p.moveMoneyToInsurance(amnt);

		try
		{
			insurance = p.makeInsuranceBet();
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertEquals("Can't make and insurance bet without first moving money to insurance",amnt, p.currentInsurance.intValue());
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	@Test
	public  void testGetAction()
	{
		Player p = new Player();

		try
		{
			PlayerAction.ActionType act = p.getAction();
			assertEquals("Wrong action returned",PlayerAction.ActionType.STAND,act);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test	
	public void testGetHandEmpty() 
	{
		Player p = new Player();

		try
		{
			List<Card> hand = p.getHand();
			assertEquals("Player's hand should be empty",new Card[] {},hand.toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test	
	public void testGetHandNotEmpty() 
	{
		Player p = new Player();
		Card card1 = new Card(Card.Face.ACE,Card.Suit.SPADE);
		Card card2 = new Card(Card.Face.KING,Card.Suit.SPADE);

		p.acceptCard(card1);
		p.acceptCard(card2);

		try
		{
			List<Card> hand = p.getHand();
			assertEquals("Player's hand should be empty",new Card[] {card1,card2},hand.toArray());
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test	
	public void testGetCurrentBetNull() 
	{
		Player p = new Player();

		try
		{
			int curBet = p.getCurrentBet();
			assertNull("The player has not yet made a bet",curBet);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}	
	}

	@Test	
	public void testGetCurrentBetNotNull() 
	{
		Player p = new Player();
		int betMade = p.makeBet();

		try
		{
			int curBet = p.getCurrentBet();

			assertEquals("The player's bet was not accurate",betMade,curBet);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}	
	}

	@Test	
	public void testGetCurrentBetOverflow() 
	{
		Player p = new Player();
		p.currentBet = Integer.MAX_VALUE;
		int originalBet = p.currentBet;
		int betMade = p.makeBet();

		try
		{
			int curBet = p.getCurrentBet();
			assertTrue("The player's bet was not accurate",curBet > originalBet);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}	
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test	
	public void testAcceptMoney() 
	{
		Player p = new Player();
		int amnt = 100;
		int expected = amnt + p.currentWallet.intValue();

		try
		{
			p.acceptMoney(amnt);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertEquals("Wallet amount is inaccurate",expected,p.currentWallet.intValue());
	}

	@Test	
	public void testAcceptMoneyOverflow() 
	{
		Player p = new Player();
		int amnt = Integer.MAX_VALUE;

		try
		{
			p.acceptMoney(amnt);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertTrue("Wallet amount is inaccurate",p.currentWallet.intValue() > 0);
	}
	
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test
	public void testMoveMoneyToBetWalletGreaterThanBet() 
	{
		Player p = new Player();
		int amnt = p.makeBet();
		int expected = p.currentWallet - amnt;

		try
		{
			p.moveMoneyToBet(amnt);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertEquals("Wallet does not reflect that a bet was made",expected,p.currentWallet.intValue());
	}

	@Test
	public void testMoveMoneyToBetWalletLessThanBet() 
	{
		boolean hit = false;
		Player p = new Player();
		int amnt = p.makeBet();
		p.currentWallet = 0;

		try
		{
			p.moveMoneyToBet(amnt);
		}
		catch(RuntimeException e)
		{
			hit = true;
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertTrue("Expected a RuntimeException",hit);
	}

	@Test
	public void testMoveMoneyToBetAmntNeg() 
	{
		Player p = new Player();
		int originalWallet = p.currentWallet.intValue();
		int amnt = -20;

		try
		{
			p.moveMoneyToBet(amnt);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertFalse("Player should not be allowed to make negative bets",originalWallet < p.currentWallet.intValue());

	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test	
	public void testNextHand() 
	{
		Player p = new Player();

		try
		{
			p.nextHand();
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}

		assertNull("Bet should be null",p.currentBet);
		assertNull("Wallet should be null",p.currentWallet);
		assertNull("Insurance should be null",p.currentInsurance);
		
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@Test		
	public void testToStringNullVals() 
	{
		Player p = new Player();
		String expected = "Player: nullw nullb nulli";

		p.nextHand();

		try
		{
			String result = p.toString();
			assertEquals("Inaccurate string representation",expected,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}

	@Test		
	public void testToStringNonNullVals() 
	{
		Player p = new Player();
		String expected = "Player: 1000w 10b 10i";
		
		p.currentInsurance = 10;
		p.currentBet = 10;

		try
		{
			String result = p.toString();
			assertEquals("Inaccurate string representation",expected,result);
		}
		catch(Exception e)
		{
			fail("An unhandled exception occured -> " + e.toString());
		}
	}
}