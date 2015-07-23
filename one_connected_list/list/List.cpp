#include "List.h"

List::List()
{
	first = NULL;
	//last = NULL;
}

List::~List()
{
	free();
}

void List::free()
{
	delete first;
	first = NULL;
}


void List::pop()
{
	if (this->isEmpty())
	
	{
		try{
			throw "You can't pop from empty one connected list.";
		}

		catch (char *e)
		{
			std::cout << e;
			return;
		}
	}
	elem *pointer = first;
	while (pointer != NULL)
	{
		if (pointer->next != NULL)
		{
			//check if the next elem is the last elem and delete it 
			if (pointer->next->next == NULL)
			{
				delete pointer->next;
				pointer->next = NULL;
			}
			pointer = pointer->next;
		}
		//when it's just one elem
		else
		{
			free();
			pointer = first;
		}
	}
}
void List::push(const elem &elemCame)
{	
	
	elem* pointer = NULL;
	if (isEmpty())
		first = new elem(elemCame);
	else
	{
		pointer = first;
		while (pointer->next != NULL)
			pointer = pointer->next;
		pointer->next = new elem (elemCame);
	}
	
}
bool List::isEmpty()const
{
	return first == NULL;
}
