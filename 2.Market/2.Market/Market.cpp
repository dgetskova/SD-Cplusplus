#pragma once 
#include "Market.h"


ClientState Market::getClientState(int ID)
{
	ClientState clientToReturn;
	//express desks
	for (size_t  l = 0; l < marketState.used; l++)
	{
		//get queue in current pos - push and pop and check if IDcame is the same
	}
	return clientToReturn;
}

size_t getMin(size_t *arr, size_t size)
{
	size_t minIndex = 0;
	for (size_t i = 1; i < size; i++)
	{
		if (arr[minIndex] > arr[i])
			minIndex = i;
	}
	return minIndex;
}
size_t getMax(size_t *arr, size_t size)
{
	size_t maxIndex = 0;
	for (size_t i = 1; i < size; i++)
	{
		if (arr[maxIndex] < arr[i])
			maxIndex = i;
	}
	return maxIndex;
}

MarketState Market::getMarketState()const
{
	return marketState;
}

Market:: Market(size_t numberOfAllCashDecks)
{
	capacity = numberOfAllCashDecks;
	marketState.allocate(capacity);
	unsigned int uniqueID = 0;
	createCashDeck();
}

void Market::addClient(Client * clients, int number)
{
	size_t productsLimitExpress = 3;
	for (size_t i = 0; i < number; i++)
	{
		//if for empty client
		// client products are less than 3 so he goes to EXPRESS cash desk

		//			EXPRESS
		if ((clients[i].numberOfFoods <= productsLimitExpress) &
			(marketState.usedExpress < 2 * capacity))
		{
			express.enqueue(clients[i]);
			marketState.usedExpress++;
		}
		else
		{
			//client goes to cash desk with minimal people
			size_t indexQ = getMin(marketState.usedEach, marketState.used);
			addSingleClient(indexQ, clients[i]);
		}
	}
	makeTick();
	checkQueues();
}

void Market::addSingleClient(size_t index, Client clientCame)
{
	if (index >= marketState.used)
	{
		throw "Cash desk no exsist";
	}

	Queue<Client> * currentQ = &cashDesks.getData(index, marketState.used);
	currentQ->enqueue(clientCame);
	marketState.usedEach[index]++;
}

bool Market::createCashDeck()
{
	if (capacity <= marketState.used)
		return false;
	Queue<Client> a;
	cashDesks.push(a);
	marketState.used++;

}

bool Market::checkPeopleOnQueue()
{
	size_t i = 0;
	for (i = 0; i < marketState.used; i++)
	{
		if (marketState.usedEach[i] > capacity)
		{
			createCashDeck();
			reorderMiddle(i);
			return true;
		}
	}
	return false;
}
bool Market::checkBiggestQueue()
{
	//biggestQ and smallerQ are indexs
	size_t biggestQ = getMax(marketState.usedEach, marketState.used),
		smallestQ = getMin(marketState.usedEach, marketState.used);
	if ((marketState.usedEach[biggestQ] - marketState.usedEach[smallestQ]) > 2)//*(capacity / 8))
	{
		reorderMiddle (biggestQ);
		return true;
	}
	return false;
}
bool Market::checkLittleQueue()
{
	if (marketState.used == 1) //if used is 1 there is no others queues to be reordered
		return true;

	for (size_t i = 0; i < marketState.used; i++)
	{
		if (marketState.usedEach[i] < capacity/1)
		{
			Queue<Client> *queueToRemove = &(cashDesks.getData(i, marketState.used));

			while (!queueToRemove->isEmpty())
			{
				for (size_t  e = 0; e < marketState.used; e++)
				{
					if (queueToRemove->isEmpty())
						break;  // go to while and there condition is the same

					if (i == e)
						continue;
					elem <Client> client = queueToRemove->dequeue();
					//cashDesks.getData(i) - get queue from market and to that queue push new client
					Queue<Client>* queuOnDesk = &(cashDesks.getData(e, marketState.used));
					queuOnDesk->enqueue(client.data);
					marketState.usedEach[e]++;
					marketState.usedEach[i]--; // queue which we want to remove
				}
			}
			cashDesks.removeElem(i, marketState.used);
			return true;
		}
	}
	return false;
}


void Market::checkQueues()
{
	if (checkPeopleOnQueue())
		return;
	if (checkBiggestQueue())
		return;
	checkLittleQueue();
}


void Market::reorderMiddle(size_t currentQIndex)
{
	Queue<Client> * moveP = &(cashDesks.getData(currentQIndex, marketState.used));
	Queue<Client> * queueToReorder = &(moveP->cutQueue(marketState.usedEach[currentQIndex]));
	while (!(queueToReorder->isEmpty()))
	{
		for (size_t i = 0; i < marketState.used; i++)
		{
			if (queueToReorder->isEmpty())
				break;

			elem <Client> client = queueToReorder->dequeue();
			//cashDesks.getData(i) - get queue from market and to that queue push new client
			Queue<Client>* queuOnDesk = &(cashDesks.getData(i, marketState.used));
			queuOnDesk->enqueue(client.data);
			marketState.usedEach[i]++;
		}
	}
	delete queueToReorder;
}

void Market::makeTick()
{
	for (size_t i = 0; i < marketState.used; i++)
	{
		Queue<Client>* q = &cashDesks.getData(i, marketState.used);
		Client* c = &(q->peek());
		if (c->creditCard) // credit card 1 tick
		{
			q->dequeue();
		}
		else
		{
			c->creditCard = true;
		}
	}

	//express desk
	Client * e = & (express.peek());
	if (e->creditCard)
		express.dequeue();
	else
		e->creditCard = true;
}