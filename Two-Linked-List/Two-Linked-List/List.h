#include <iostream>

// not complete
struct elem
{
	int data;
	elem* next;
	elem* prev;

	elem() : data(0), next(NULL), prev(NULL){}
	elem(int i)
	{
		data = i;
		next = NULL;
		prev = NULL;
	}
	elem(const elem& e)
	{
		data = e.data;
		next = e.next;
		prev = e.prev;
	}
	~elem()
	{ 
		delete next;
		next = NULL;
	}
};

class List
{
	elem* first;
	elem* last;
	void free();

public:
	List():first(NULL), last(NULL){}
	~List(){ free(); }
	

	void add(elem elemCame);
	void remove(const elem& elemCame);
	//bool isEmpty();
};

void List::remove(const elem& elemCame)
{
	/*
	elem*& pmove = last;
	while (pmove != first)
	{
		if (pmove->data == elemCame.data)

	}*/
	
}

void List::free()
{
	delete last;
	last = NULL;
}

void List::add(elem elemCame)
{
	elem* e = new elem(elemCame);
	if (first == NULL && last == NULL)
	{
		first = e;
		last = e;
		return;
	}

	if (first == last)
	{
		last = e;
		first->next = e;
		e->prev = first;
		return;
	}
	else
	{
		last->next = e;
		e->prev = last;
		last = e;
	}

}
