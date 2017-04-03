package edu.osu.blackjack;

import org.junit.*;
import static org.junit.Assert.*;
import java.util.*;

public class SimpleBlackjackRandomTest 
{
	private static final int DECK_SIZE = 52;
	private static final int STANDARD_BET = 10;
	private static final int MAX_PLAYERS = 4;
	private static final int MIN_PLAYERS = 1;
	private static final int MAX_WALLET = 1000;
	private static final int NUM_TESTS = 500;

	private Random randSeed = new Random();
	private long seed = randSeed.nextLong();
	private Random rand = new Random(seed);
	private List<Integer> startingWallets = new ArrayList<Integer>();
	private Dealer dealer;
	private int randPlayerCount;
	private Player[] players;
	private SimpleBlackjack game;

	public void initRandomGameState()
	{

		dealer = new Dealer();
		dealer.shuffleDeck();

		randPlayerCount = rand.nextInt(MAX_PLAYERS - MIN_PLAYERS + 1) + MIN_PLAYERS;
		players = new Player[randPlayerCount];

		for(int i = 0; i < randPlayerCount; i++)
		{
			Player p = new Player();
			p.currentWallet = rand.nextInt(MAX_WALLET + 1);
			startingWallets.add(new Integer(p.currentWallet));
			players[i] = p;
		}

		game =  new SimpleBlackjack(dealer,players);
	}

	@Test
	public void testGetBets()
	{
		System.out.println("Function: testGetBets() | Seed: " + seed);

		for(int i = 0; i < NUM_TESTS; i++)
		{
			initRandomGameState();

			try
			{
				game.getBets();
			}
			catch(Exception e)
			{
				fail("An unhandled exception occured -> " + e.toString());
			}

			genWalletAsserts(players,startingWallets, i);
		}
	}

	@Test
	public void testDealRound()
	{
		System.out.println("Function: testDealRound() | Seed: " + seed);

		for(int i = 0; i < NUM_TESTS; i++)
		{
			initRandomGameState();

			try
			{
				game.dealRound();
			}
			catch(Exception e)
			{
				fail("An unhandled exception occured -> " + e.toString());
			}
			
			genHandSizeAsserts(dealer,players,i);
			genDeckSizeAsserts(dealer,randPlayerCount,i);
		}	
	}


	@Test
	public void testCheckInsurance()
	{
		System.out.println("Function: testCheckInsurance() | Seed: " + seed);

		for(int i = 0; i < NUM_TESTS; i++)
		{
			initRandomGameState();

			try
			{
				game.checkInsurance();
			}
			catch(Exception e)
			{
				fail("An unhandled exception occured -> " + e.toString());
			}

			genInsuranceAsserts(players,startingWallets,i);
		}
	}


	@Test
	public void testplayHand()
	{
		System.out.println("Function: testPlayHand() | Seed: " + seed);

		boolean hitRequested = false;

		for(int i = 0; i < NUM_TESTS; i++)
		{
			initRandomGameState();

			try
			{
				game.playHand();

				for(int j = 0; i < players.length; i++)
				{
					if(players[j].getHand().size() > 2)
					{
						hitRequested = true;
					}
				}
			}
			catch(Exception e)
			{
				fail("An unhandled exception occured -> " + e.toString());
			}
			
			assertTrue("Not a single hit was requested after " + NUM_TESTS + " tests", hitRequested);
		}
	}

	@Test
	public void testPlayRound()
	{
		System.out.println("Function: testPlayRound() | Seed: " + seed);

		for(int i = 0; i < NUM_TESTS; i++)
		{
			initRandomGameState();

			try
			{
				game.playRound();
			}
			catch(Exception e)
			{
				fail("An unhandled exception occured -> " + e.toString());
			}

			genPlayRoundAsserts(dealer,players,startingWallets,i);

		}
	}


//------------------ASSERT GENERATORS-----------------------------------------------------------------------------------------------------------------

	private void genWalletAsserts(Player[] p,List<Integer> startingWallets, int testNum)
	{
		for(int i = 0; i < p.length; i++)
		{
			assertNotNull("Test " + (testNum+1) + ": Player " + (i+1) + "\'s wallet is null", p[i].currentWallet);
			assertTrue("Test " + (testNum+1) + ": The wrong amount was removed from player " + (i+1) + "\'s wallet after making a bet",
				p[i].currentWallet == (startingWallets.get(i).intValue() - STANDARD_BET));
		} 
	}

	private void genHandSizeAsserts(Dealer dealer, Player[] p, int testNum)
	{
		assertTrue("Test " + (testNum+1) + ": The dealer should only have 2 cards at the start of the round",dealer.getHand().size() == 2);

		for(int i = 0; i < p.length; i++)
		{
			assertTrue("Test " + (testNum+1) + ": A player should only have 2 cards at the start of the round", p[i].getHand().size() == 2);
		}
		
	}

	private void genDeckSizeAsserts(Dealer dealer, int playerCount, int testNum)
	{
		assertTrue("Test " + (testNum+1) + ": The deck has an incorrect number of cards. Expected: " + ((DECK_SIZE - 2) - (playerCount * 2)) + 
			" cards Actual: " + dealer.getDeck().size() + " cards", dealer.getDeck().size() == ((DECK_SIZE - 2) - (playerCount * 2)));
	}

	private void genInsuranceAsserts(Player[] p,List<Integer> startingWallets, int testNum)
	{
		for(int i = 0; i < p.length; i++)
		{
			assertNotNull("Test " + (testNum+1) + ": Player " + (i+1) + "\'s insurance is null", p[i].currentInsurance);
			assertTrue("Test " + (testNum+1) + ": The wrong ammount was removed from player " + (i+1) + "\'s wallet after taking insurance",p[i].currentWallet < startingWallets.get(i).intValue());
		}
	}

	private void genPlayRoundAsserts(Dealer d, Player[] p,List<Integer> startingWallets,int testNum)
	{
		assertTrue("Test " + (testNum+1) + ": Not all cards were returned to the deck",d.getDeck().size() == DECK_SIZE);

		for(int i = 0; i < p.length; i++)
		{
			assertTrue("Test " + (testNum+1) + ": Player " + (i+1) + "\'s wallet should either be less than or greater than the " +
				"amount at the start of the game", 
				((p[i].currentWallet < startingWallets.get(i).intValue()) || (p[i].currentWallet > startingWallets.get(i).intValue())));
			assertTrue("Test " + (testNum+1) + ": Player " + (i+1) + "\'s hand is not empty",p[i].getHand().size() == 0);
			assertTrue("Test " + (testNum+1) + ": Player " + (i+1) + "\'s current bet was not reset", p[i].currentBet == null);
			assertTrue("Test " + (testNum+1) + ": Player " + (i+1) + "\'s current insurance was not reset", p[i].currentInsurance == null);
		}
	}

//------------------END ASSERT GENERATORS---------------------------------------------------------------------------------------------------------------
}