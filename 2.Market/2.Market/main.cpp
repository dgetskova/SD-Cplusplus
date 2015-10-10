#include "List.h"
#include "Queue.h"
#include "Market.h"

int main()
{
	//		Test for queue with person objects
	Client person (0, 0,false);
	Client person1 (1, 1, false);
	Client person2 (2, 2, false);
	Client person3 (3, 3, false);
	Client person4 (4, 4, true);
	Client person5 (5, 5, true);
	Client person6 (6, 6, true);
	Client person7 (7, 7, false);
	Client person8 (8, 8, false);
	Client person9 (9, 9, false);
	
	/*Queue<Client> a;
	a.enqueue(person);
	a.enqueue(person2);
	a.enqueue(person3);
	a.dequeue();
	a.dequeue();
	a.dequeue();
	a.dequeue();*/

	size_t clientsSize = 10;
	Client * clientArr = new Client[clientsSize];

	clientArr[0] = person;
	clientArr[1] = person1;
	clientArr[2] = person2;
	clientArr[3] = person3;
	clientArr[4] = person4;
	clientArr[5] = person5;
	clientArr[6] = person6;
	clientArr[7] = person7;
	clientArr[8] = person8;
	clientArr[9] = person9;

	

	Market market(clientsSize);
	market.addClient(clientArr, clientsSize);
	market.addClient(clientArr, clientsSize);  //						   -- checkPeopleOnQueue
	market.addClient(clientArr, 10); // 4 for express and 3 for cash desks -- checkBiggestQueue
	
	MarketState a (market.getMarketState());

	//////-- checkLittleQueue
	Market m(4);
	m.addClient(clientArr, clientsSize);
	m.addClient(clientArr + 8, 2);
	m.addClient(clientArr + 8, 2);

	delete[]clientArr;
}
