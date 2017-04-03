package edu.osu.blackjack;

import org.junit.*;
import static org.junit.Assert.*;
import static org.mockito.Mockito.*;
import org.junit.Test;

public class SimpleBlackjackTest 
{
	DealerAction da;
	PlayerAction pa;

	@Before
	public void initMock()
	{
		da = mock(DealerAction.class);
    	pa = mock(PlayerAction.class);
	}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

	@Test
	public void testPlayerBet()
	{	
    	when(pa.getAction()).thenReturn(PlayerAction.ActionType.STAND);

    	SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

		verify(pa,times(1)).makeBet();
	}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	From Reference: Each box is dealt an initial hand of two cards visible to the people playing on it, 
	and often to any other players.
	*/

    @Test
    public void testStartingPlayerHand()
    {
    	//player should have a starting hand of two cards, but stars with one

    	when(pa.getAction()).thenReturn(PlayerAction.ActionType.STAND);

    	SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

    	verify(da,times(2)).dealCard(pa);
    }

    @Test
    public void testStartingDealerHand()
    {
    	//dealer should have a starting hand of two cards, but stars with one

    	when(pa.getAction()).thenReturn(PlayerAction.ActionType.STAND);

    	SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

		verify(da,times(2)).dealCard(da);
    }
 	
 	@Test
    public void testStartingDealerHandWithMultiplePlayers()
    {
    	//dealer is dealt one card for each player, which allows the dealer to be dealt more than two cards

    	PlayerAction pa2 = mock(PlayerAction.class);
    	PlayerAction pa3 = mock(PlayerAction.class);

    	when(pa.getAction()).thenReturn(PlayerAction.ActionType.STAND);
    	when(pa2.getAction()).thenReturn(PlayerAction.ActionType.STAND);
    	when(pa3.getAction()).thenReturn(PlayerAction.ActionType.STAND);

    	SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa,pa2,pa3});
		bj.playRound();

		verify(da,atMost(2)).dealCard(da);
	}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

	@Test 
	public void testPlayerNotAbleToMakeInsuranceBets()
	{
    	when(da.isInsuranceAvailable()).thenReturn(false);
    	when(pa.getAction()).thenReturn(PlayerAction.ActionType.STAND);

    	SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

		verify(pa,never()).makeInsuranceBet();
	}

	/*
	From Reference: If the dealer's upcard is an ace, the player is offered the 
	option of taking "insurance" before the dealer checks the hole card.
	*/

	@Test 
	public void testPlayerChoosesToMakeInsuranceBets()
	{
    	when(da.isInsuranceAvailable()).thenReturn(true);
    	when(pa.getAction()).thenReturn(PlayerAction.ActionType.STAND);

    	SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

		verify(pa,times(1)).makeInsuranceBet();
	}

	@Test 
	public void testPlayerChoosesNotToMakeInsuranceBets()
	{
		//if insurance is available, a player must make an insurance bet. this should be optional
    	when(da.isInsuranceAvailable()).thenReturn(true);
    	when(pa.getAction()).thenReturn(PlayerAction.ActionType.STAND);

    	SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

		verify(pa,never()).makeInsuranceBet();
	}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

    /*
    From Reference: Each hand may normally "hit" as many times as desired so long as the total 
    is not above hard 20. On reaching 21 (including soft 21), the hand is normally required to 
    stand; busting is an irrevocable loss and the players' wagers are immediately forfeited to the house
    */

	@Test
    public void tesMaxAllowableCardsBeforeBust()
    {
    	//2(4) + 3(4) = 20; 8 cards is the most a player can have without busting
    	//player is allowed to hit after busting

    	when(pa.getAction()).thenReturn(PlayerAction.ActionType.HIT)
    						.thenReturn(PlayerAction.ActionType.HIT)
    						.thenReturn(PlayerAction.ActionType.HIT)
    						.thenReturn(PlayerAction.ActionType.HIT)
    						.thenReturn(PlayerAction.ActionType.HIT)
    						.thenReturn(PlayerAction.ActionType.HIT)
    						.thenReturn(PlayerAction.ActionType.HIT)
    						.thenReturn(PlayerAction.ActionType.HIT)
    						.thenReturn(PlayerAction.ActionType.STAND);

    	SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

    	verify(da,atMost(8)).dealCard(pa);
    }

//-----------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	From Reference: The player is allowed to increase the initial bet by up to 100% 
	in exchange for committing to stand after receiving exactly one more card
	*/

	@Test
    public void testStandAfterDoubleDown()
    {
		when(pa.getAction()).thenReturn(PlayerAction.ActionType.DOUBLE);

		SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

    	verify(pa,times(1)).doubleDownBet();
	}

	/*
	From Reference: After receiving an initial two cards, the player has up to four standard 
	options: "hit", "stand", "double down", or "split".
	*/

	@Test
    public void testHandSizeAfterDoubleDown()
    {
		when(pa.getAction()).thenReturn(PlayerAction.ActionType.DOUBLE);

		SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

    	verify(da,times(3)).dealCard(pa);
	}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

	@Test
	public void testHandSizeAfterStand()
	{
		when(pa.getAction()).thenReturn(PlayerAction.ActionType.STAND);

		SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

    	verify(da,times(2)).dealCard(pa);
	}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

	@Test
	public void testCompareHand()
	{	
    	when(pa.getAction()).thenReturn(PlayerAction.ActionType.STAND);

    	SimpleBlackjack bj = new SimpleBlackjack(da,new PlayerAction[]{pa});
		bj.playRound();

		verify(da,times(1)).compareHandAndSettle(pa);
	}

}