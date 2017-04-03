package edu.osu.blackjack;



public class SimpleBlackjack {
	public enum ActionType {HIT , DOUBLE, STAND};
	private int numPlayers;
	
	DealerAction dealer;
	PlayerAction[] players ;

	
	public SimpleBlackjack(DealerAction d, PlayerAction[] ip){
		this.dealer = d;
		this.players = ip;
	}

//------------START MODIFICATIONS----------------------------------------------------------------------------------------------

	public void getBets()
	{
		for(PlayerAction p: players ){
			p.makeBet();
		}
	}

	public void dealRound()
	{
		dealer.shuffleDeck();
		
		dealer.dealCard(dealer);
		dealer.dealCard(dealer);
		
		for(PlayerAction p: players ){
			dealer.dealCard(p);
			dealer.dealCard(p);
		}
	}

	public void checkInsurance()
	{
		if(dealer.isInsuranceAvailable()){
			for(PlayerAction p: players ){
				p.makeInsuranceBet();
			}
		}
	}

	public void playHand()
	{
		for(PlayerAction p: players ){
			boolean turnOver = false;
			while(!turnOver){
				PlayerAction.ActionType a = p.getAction();	
				switch(a){
					case HIT:
						dealer.dealCard(p);		
						break;
					case DOUBLE:
						p.doubleDownBet();
						dealer.dealCard(p);
						turnOver = true;
						break;
					default: // stand
						turnOver = true;
						break;
				}
		
			}
		}
	}

	public void resolveGame()
	{
		for(PlayerAction p: players){
			dealer.compareHandAndSettle(p);
		}
	}
	
//-------------------------------------------END MODIFICATIONS------------------------------------------------------------------------------------------

	public void playRound()
	{
		getBets();
		dealRound();
		checkInsurance();
		playHand();
		resolveGame();

		/*dealer.shuffleDeck();

		for(PlayerAction p: players ){
			p.makeBet();
		}
		
		dealer.dealCard(dealer);
		dealer.dealCard(dealer);
		
		for(PlayerAction p: players ){
			dealer.dealCard(p);
			dealer.dealCard(p);
		}
	
		if(dealer.isInsuranceAvailable()){
			for(PlayerAction p: players ){
				p.makeInsuranceBet();
			}
		}

		for(PlayerAction p: players ){
			boolean turnOver = false;
			while(!turnOver){
				PlayerAction.ActionType a = p.getAction();	
				switch(a){
					case HIT:
						dealer.dealCard(p);		
						break;
					case DOUBLE:
						p.doubleDownBet();
						dealer.dealCard(p);
						turnOver = true;
						break;
					default: // stand
						turnOver = true;
						break;
				}
		
			}
		}

		for(PlayerAction p: players){
			dealer.compareHandAndSettle(p);
		}*/
	}
}
