package edu.osu.blackjack;

import org.junit.Test;
import static org.junit.Assert.*;
import static org.mockito.Mockito.*;

public class VerifiedTest
{
//--------------------------Title: Incorrect Dealer and Player Hand Size at Start of Game-------------------------------------------------------------

	@Test
	public void testStartingPlayerHand()
	{
		DealerAction da = mock(DealerAction.class);
	    PlayerAction pa = mock(PlayerAction.class);

		when(pa.getAction()).thenReturn(PlayerAction.ActionType.STAND);

		SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

		verify(da,times(2)).dealCard(pa);
	}

	@Test
	public void testStartingDealerHand()
	{
		DealerAction da = mock(DealerAction.class);
	    PlayerAction pa = mock(PlayerAction.class);

		when(pa.getAction()).thenReturn(PlayerAction.ActionType.STAND);

		SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

		verify(da,times(2)).dealCard(da);
	}


	@Test
	public void testStartingDealerHandWithMultiplePlayers()
	{
		DealerAction da = mock(DealerAction.class);
	    PlayerAction pa = mock(PlayerAction.class);
		PlayerAction pa2 = mock(PlayerAction.class);
		PlayerAction pa3 = mock(PlayerAction.class);

		when(pa.getAction()).thenReturn(PlayerAction.ActionType.STAND);
		when(pa2.getAction()).thenReturn(PlayerAction.ActionType.STAND);
		when(pa3.getAction()).thenReturn(PlayerAction.ActionType.STAND);

		SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa,pa2,pa3});
		bj.playRound();

		verify(da,atMost(2)).dealCard(da);
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------------



//---------------------------Title: Insurance is Never Available - Dealer's Hand is Always Empty------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------------------------------------------------------------------



//----------------------Title:  A Player's Wallet is Emptied After Round----------------------------------------------------------------------------------
	
	@Test
	public void testCompareHandAndSettlePlayerWin()
	{
		Dealer d = new Dealer();
		Player p = new Player();
		int playerBet = p.makeBet();
		Integer expected = playerBet + p.currentWallet;

		p.moveMoneyToBet(playerBet);
		
		for(int i = 0; i < 4; i++)
		{
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

		assertEquals("The Player didn't win",expected,p.currentWallet);
	}
}