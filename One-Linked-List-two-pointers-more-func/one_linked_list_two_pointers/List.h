#pragma once
#include <iostream>

template <class T>
struct elem
{
	T data;
	elem<T> *next;
	elem<T>(const elem<T>& elemCame)
	{
		data = elemCame.data;
		next = elemCame.next;
	}
	elem<T>(const T& dataCame, elem<T>* nextCame = NULL)
	{
		data = dataCame;
		next = nextCame;
	}
	~elem<T>()
	{
		//cascade destructor
		if (next)
		 delete next;
	}
};

template <class T>
class List
{
private:
	elem<T>* first;
	elem<T>* last;
	void free();

public:
	List();
	~List();

	T pop();
	void push(const T &elemCame);
	bool isEmpty()const;

	void removeElem(size_t index, size_t size);
	T& getData(size_t index, size_t);
	

	//it will  optimize searching but require two linked list
	//elem<T>& getRight(size_t);

};
template <class T>
void List<T>::removeElem(size_t index, size_t size)
{
	elem<T> *temp = last;
	if (index == 0)
	{
		if (first == last)
		{
			delete first;
			first = last = NULL;
			return;
		}
		if (last->next == first)
		{
			delete first;
			first = last;
			last->next = NULL;
			return;
		}
	}
	else if (index == size - 1)
	{
		temp = last;
		last = last->next;
		temp->next = NULL;
		delete temp;
		return;
	}
	// index in the vutreshnostta na opawkata
	temp = last;
	elem<T>*tempBefore = NULL;
	size_t diff = size - index;
	//if diff == 2
	for (size_t i = 1; i < diff; i++)
	{
		tempBefore = temp;
		temp = temp->next;
	}
	tempBefore->next = temp->next;
	temp->next = NULL;
	delete temp;	
}

template <class T>
T& List<T>::getData(size_t index, size_t size)
{
	if (index >= size)
		throw "access to memory  out of range";
	if (isEmpty())
		throw "nothing to get";
	if (index == 0)
		return first->data;
	size_t countMoves = size - index;

	elem<T>* temp = last;
	for (size_t i = 1; i < countMoves; i++)
	{
		temp = temp->next;
	}
	return temp->data;
}

template <class T>
List<T>::List()
{
	first = NULL;
	last = NULL;
}

template <class T>
List<T>::~List()
{
	free();
}

template <class T>
void List<T>::free()
{
	delete last;
	first = NULL;
	last = NULL;
}

template <class T>
T List<T>::pop()
{
	if (isEmpty())

	{
		try{
			throw "You can't pop from empty list.";
		}

		catch (char *e)
		{
			std::cout << e;
			throw "pop from empty stack";
		}
	}

	T dataToReturn;
	if (last == first)
	{
		dataToReturn = last->data;
		delete last;
		first = last = NULL;
		return dataToReturn;
	}
	dataToReturn = last->data;

	elem<T>*& temp = last;
	//last = last->next;
	temp->next = NULL;
	delete temp;
	temp = NULL;

	return dataToReturn;
}
template <class T>
void List<T>::push(const T &elemCame)
{
	elem<T> * temp = new elem<T>(elemCame);
	if (isEmpty())
	{
		first = temp;
		last = first;
	}
	else
	{
		temp->next = last;
		last = temp;
	}

}
template <class T>
bool List<T>::isEmpty()const
{
	return first == NULL;
}
