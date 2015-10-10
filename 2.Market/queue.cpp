#include <iostream>
using namespace std;

static unsigned long createID=0;

struct Client
{
    int ID; // уникален номер на клиента в магазина
    int numberOfGoods; // брой на покупките на клиента
    bool creditCard; // истина ако плаща с крединта карта
};

struct Elem 
{
	Client data;
	Elem *next;
public:
	Elem (const Client &original,Elem * n = NULL) //
	{
		data = original;
		next = n;
	}
	~Elem ()
	{
		if(next)
		{delete next;}
	}
};

class Queue 
{
	 Elem *first, *last;
	 int sizeQueue;
public: 
	Queue () : first (NULL), last (NULL),sizeQueue (0){}
	~Queue (){delete first;}			

	bool isEmpty ()
	{
		return first == NULL&& sizeQueue==0;
	}

	Elem dequeue ()
	{
		if ( !isEmpty() )
		{
			Elem *temp = first;
			first = first -> next;
			temp ->next = NULL;
			Client dataReturn = temp->data; 

			delete temp;
			sizeQueue--;
			return dataReturn;			
		}
		else 
		{
			cout<<"Empty queue";
		
			throw "Empty queue";
		}
		
	}

	void enqueue (const Elem & box)
	{
		Elem *newBox = new Elem (box);
		if (!newBox)
		{
			cout <<"No memory for enqueu";
			throw 2;
		}
		if (isEmpty ())
		{
			first = newBox;
		}else last->next = newBox;
		last = newBox;
		sizeQueue++;
	}
};



