#pragma once
#include <iostream>

struct MarketState
{
	size_t used; // which are been opened
	size_t * usedEach; // clients on every cash desk
	size_t usedExpress; //clients on express cash desk

	void allocate(size_t numCame)
	{
		usedExpress = 0;
		usedEach = NULL;
		used = 0;

		if (numCame == 0)
			return;

		try{
			usedEach = new size_t[numCame];
		}
		catch (std::bad_alloc){
			delete[]usedEach;
			throw "bad_alloc";
		}
		for (size_t i = 0; i < numCame; i++)
		{
			usedEach[i] = 0;
		}
		
	}
	// default 0 is for creating objects in class declarations
	MarketState(size_t numCame = 0)
	{
		allocate(numCame);
	}
	MarketState(const MarketState & other)
	{
		used = other.used;
		usedExpress = other.usedExpress;
		usedEach = new size_t[used];
		for (size_t i = 0; i < used; i++)
		{
			usedEach[i] = other.usedEach[i];
		}
	}
	~MarketState()
	{
		delete[]usedEach;
		usedEach = NULL;
		usedExpress = 0;
		used = 0;
	}

};


struct Client
{
	int ID;
	int numberOfFoods;
	bool creditCard;

	Client()
	{
		int ID = 0;
		numberOfFoods = 0;
		creditCard = false;
	}
	//maybe i don't need this constructor
	Client(int uniqueID)
	{
		int ID = uniqueID;
		uniqueID++;
		numberOfFoods = 0;
		creditCard = false;
	}
	Client(int IDCame, int numberOfFoodsCame, bool creditCardCame) :
		ID(IDCame), numberOfFoods(numberOfFoodsCame), creditCard(creditCardCame){}
};

struct ClientState
{
	int CashDeskPosition;
	int QueuePosition;
	Client * client;
	ClientState() :CashDeskPosition(0), QueuePosition(0), client(NULL){};
};


