#include <iostream>

struct elem
{
	int data;
	elem *next;
	elem(const elem& elemCame)
	{
		data = elemCame.data;
		next = elemCame.next;
	}
	elem(int dataCame, elem* nextCame = NULL)
	{
		data = dataCame;
		next = nextCame;
	}
	~elem()
	{
		//cascade destructor
		delete next;
	}
};


class List
{
private:
	elem* first;
	//if we want to make push and pop faster for expense of care for one morе pointer
	//elem_in* last;

public:
	List();
	~List();
	void free();

	void pop();
	void push(const elem &elemCame);
	bool isEmpty()const;

};

