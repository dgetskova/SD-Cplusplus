#include "queue.cpp"

struct List_str 
{
	List_str * nextList;
	Queue * queue;
	int numberOfCashDeck;

	List_str (List_str * nextList_Input = NULL) // za purviq i vtoriq elem (expresna kasa i normalna kasa)
	{
		numberOfCashDeck = 0; // i dvete shte sa mi s 0
		queue = new Queue; /// za ostanalite trqbva da e NULL
		nextList = nextList_Input;  
	}
};

class List_cls
{
	List_str *tos;
public:
	List_cls ()
	{
		tos= new List_str ();
	}
	~List_cls ()
	{
		delete tos;
	}
};



int main () 
{
	///////////////////////////////////test na opawkata
	Queue queue;
	Client client = {8, 5, 0};
	Elem elem (client);

	for (size_t i = 0; i<=8; i++)
	{
		try{
		queue.enqueue (elem);
		}catch (int)
		{
			cout<< "No memory";
		}

	}
	for (size_t i = 0; i<=10; i++)
	{
		try{
		queue.dequeue ();
		}catch (char*){cout<<"Empty queue!"<<endl;}
	}


///////////////////////////////////////////////////////////////


	List_cls market ;


}
