#pragma once
#include "MarketStructures.h"
#include "Queue.h"
#include "List.h"
class Market
{
	MarketState marketState;
	
	unsigned int uniqueID = 0;
	size_t capacity;
	Queue<Client> express;
	List<Queue<Client>> cashDesks;

private:
	void Market::addSingleClient(size_t index, Client clientCame);
	bool createCashDeck();

	void checkQueues();
	bool checkPeopleOnQueue();
	bool checkBiggestQueue();
	bool checkLittleQueue();
	void reorderMiddle(size_t);

	void makeTick();
	
public:
	Market(size_t);
	void addClient(Client * clients, int number); 
	MarketState getMarketState()const; 
	ClientState getClientState(int ID); 
	
};
