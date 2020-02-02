class Card
{
private:

    int value;

public:

	Card(int value)
	{
		this->value = value;
	}

	int getValue()
	{
		return value;
	}
};

class Hand
{
private:

	vector<Card *> *cards;

public:

	Hand()
	{
		cards = new vector<Card *>();
	}

	vector<int> *getPossibleValues()
	{
		vector<int> *results = new vector<int>;

		int aceCount = 0;
		int resultWithoutAce = 0;
		for (Card *card : (*cards))
		{
			if (card->getValue() == 1)
			{
				aceCount++;
			}
			else if (card->getValue() == 11 || card->getValue() == 12 || card->getValue() == 13)
			{
				resultWithoutAce += 10;
			}
			else
			{
				resultWithoutAce += card->getValue();
			}
		}

		for (int i = 0; i <= aceCount; i++)
		{
			int ones = i;
			int elevens = aceCount - i;

			results->push_back(resultWithoutAce + ones + elevens * 11);
		}

		return results;
	}

	int getBestValue()
	{
		vector<int> *results = getPossibleValues();

		int maxUnder = -1;
		for (int result : (*results))
		{
			if (result <= 21 && result > maxUnder)
			{
				maxUnder = result;
			}
		}
		return maxUnder;
	}

	void insertCard(Card *card)
	{
		cards->push_back(card);
	}

	string printHand()
	{
		string res = "Cards: ";
		for (int i = 0; i < cards->size(); i++)
		{
			res += to_string(cards->at(i)->getValue());
			if (i != (int)(cards->size()) - 1)
			{
				res += " , ";
			}
			else
			{
				res += ';';
			}
		}
		res += " Current best value is: " + to_string(getBestValue());
		return res;
	}
};

class BlackJack;

class NormalPlayer
{
private:

	BlackJack *game;
	int id;
	Hand *hand;
	int totalBets;
	int bets;
	bool StopDealing;

public:

	NormalPlayer(int id, int bets)
	{
		this->id = id;
		hand = new Hand();
		totalBets = 1000;
		try
		{
			placeBets(bets);
		}
		catch (string e)
		{
			cout << e << endl;
		}
		StopDealing = false;
	}

	void placeBets(int amount)
	{
		if (totalBets < amount)
		{
			throw "No enough money.";
		}
		bets = amount;
		totalBets -= bets;
	}

	int getId()
	{
		return this->id;
	}

	void insertCard(Card *card)
	{
		hand->insertCard(card);
	}

	int getBestValue()
	{
		return hand->getBestValue();
	}

	void stopDealing()
	{
		this->StopDealing = true;
	}

	void joinGame(BlackJack *game);

	void dealNextCard();

	int getCUrrentBets()
	{
		return bets;
	}

	string printPlayer()
	{
		return hand->printHand()+ ", current bets: " + to_string(bets) + ", total bets: " + to_string(totalBets) + "\n";
	}

	void win()
	{
		totalBets += bets * 2;
		bets = 0;
	}

	void lose()
	{
		bets = 0;
	}
};

class Dealer
{
private:

	BlackJack *game;
	Hand *hand;
	int bets;
public:

	Dealer()
	{
		hand = new Hand();
		bets = 10000;
	}

	void insertCard(Card *card)
	{
		hand->insertCard(card);
	}

	bool largerThan(NormalPlayer *p)
	{
		return hand->getBestValue() >= p->getBestValue();
	}

	void updateBets(int amount)
	{
		bets += amount;
	}

	void setGame(BlackJack *game);

	void dealNextCard();

	string printDealer()
	{
		return "Dealer " + hand->printHand() + ", total bets: " + to_string(bets) + "\n";
	}
};

class BlackJack
{
private:

	vector<NormalPlayer *> *players;
	Dealer *dealer;
	vector<Card *> *cards;
public:

	BlackJack()
	{
		players = new vector<NormalPlayer *>;
		dealer = new Dealer;
	}

	void initCards(vector<Card *> *cards)
	{
		this->cards = cards;
	}

	void addPlayer(NormalPlayer *p)
	{
		players->push_back(p);
	}

	void dealInitialCards()
	{
		for (NormalPlayer *player : (*players))
		{
			player->insertCard(dealNextCard());
		}
		dealer->insertCard(dealNextCard());

		for (NormalPlayer *player : (*players))
		{
			player->insertCard(dealNextCard());
		}

		dealer->insertCard(dealNextCard());
	}

	Card *dealNextCard()
	{
		Card *card = *(cards->begin());
		cards->erase(cards->begin());
		return card;
	}

	Dealer *getDealer()
	{
		return dealer;
	}

	void compareResult()
	{
		for (NormalPlayer *p : (*players))
		{
			if (dealer->largerThan(p))
			{
				dealer->updateBets(p->getCUrrentBets());
				p->lose();
			}
			else
			{
				dealer->updateBets(-(p->getCUrrentBets()));
				p->win();
			}
		}
	}

	string print()
	{
		string s = "";
		for (NormalPlayer *player : (*players))
		{
			s += "playerid: " + to_string((player->getId() + 1)) + " ;" + player->printPlayer();
		}
		return s;
	}
};

void NormalPlayer::joinGame(BlackJack *game)
{
	this->game = game;
	game->addPlayer(this);
}

void NormalPlayer::dealNextCard()
{
	insertCard(game->dealNextCard());
}

void Dealer::setGame(BlackJack *game)
{
	this->game = game;
}

void Dealer::dealNextCard()
{
	insertCard(game->dealNextCard());
}
