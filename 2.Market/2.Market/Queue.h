#pragma once
#include "List.h"

//template <class T>
//struct elem
//{
//	T data;
//	elem<T> *next;
//public:
//	elem<T>(const T &dataCame, elem * nextCame = NULL) //
//	{
//		data = dataCame;
//		next = nextCame;
//	}
//	~elem<T>()
//	{
//		if (next)
//			delete next;
//	}
//};

template <class T>
class Queue
{
	elem<T> *first, *last;
	size_t sizeQueue;
public:
	Queue(elem<T>* f, elem<T>* l, size_t s) :first(f), last(l), sizeQueue(s){}
	Queue() : first(NULL), last(NULL), sizeQueue(0){}
	~Queue(){ delete first; }
	
	void enqueue(const T &);
	T dequeue();
	bool isEmpty()const;
	Queue<T>& cutQueue(size_t&); // creates queue
	T& peek();
};

template<class T>

T& Queue<T>::peek()
{
	return first->data;
}
template<class T>
Queue<T>& Queue<T>::cutQueue(size_t &size)
{
	
	size_t middle = size / 2;
	size_t newSize = size - middle;
	size = middle;
	sizeQueue = size;

	elem<T> * pointerOldQ = first; 
	//pointerOldQ = first because of that for is from 1
	for (size_t i = 1; i < middle; i++) 
	{
		pointerOldQ = pointerOldQ->next;
		// pointerOldQ is on last element of old Queue
	}
	//second part of queue which starts from middle and ends with last
	//Queue<T> secondPartOfQ(pointerOldQ->next, last, newSize);
	Queue<T> * secondPartOfQ = new Queue<T> (pointerOldQ->next, last, newSize);
	last = pointerOldQ;
	last->next = NULL;
	
	return *secondPartOfQ;
}


template <class T>
bool Queue<T>::isEmpty()const
{
	return (first == NULL) & (last == NULL);
}

template <class T>
T Queue<T>::dequeue()
{
	if (isEmpty())
	{
		std::cout << "Empty queue";
		throw "Yor can't pop from empty queue";
	}
	else
	{
		elem<T> *temp = first;
		if (first == last)
		{
			T dataReturn = temp->data;
			delete temp;
			first = last = NULL;
			sizeQueue--;
			return dataReturn;
		}

		first = first->next;
		temp->next = NULL;
		T dataReturn = temp->data;
		delete temp;
		sizeQueue--;
		return dataReturn;
	}
}

template <class T>
void Queue<T>::enqueue(const T& dataCame)
{
	elem<T> *newBox = new elem<T>(dataCame);
	if (!newBox)
	{
		std::cout << "No memory for enqueu";
		throw 2;
	}
	if (isEmpty())
		last = first = newBox;
	else
	{
		last->next = newBox;
		last = newBox;
	}
	sizeQueue++;
}
