#include <iostream>
//until function is not used(compiles) it can have many errors (even compiles)

template <class T>
struct elem
{
	 T data;
	 elem * next;

	 elem() : data(0), next(NULL){}
	 elem(const T &dataCame, elem * nextCame = NULL) : data(dataCame), next(nextCame){}
	 elem(const elem<T>  &other)
	 {
		 data = other.data;
		 next = other.next;
	 }
};


template <class T>
class Stack
{
private:
	elem<T> * pointer;

public:
	Stack(const elem<T> &box);

	Stack();
	Stack(const Stack &other);
	Stack& Stack<T>::operator=(const Stack& other);
	~Stack();

	void free();
	void allocate(const Stack &other);

public:
	bool isEmpty()const;
	void push(const elem<T>& box);
	void pop();
	const T& peek()const;
};

template <class T>
Stack<T>::Stack()
{
	pointer = NULL; 
}

template <class T>
Stack<T>::Stack(const elem<T> &box)
{
	pointer = NULL;
	// it requires a copy construstor
	pointer = new elem<T>(box); 
}

template <class T>
Stack<T>::Stack(const Stack &other)
{
	allocate(other);
}

template<class T>
void Stack<T>::allocate(const Stack &other)
{
	this->pointer = NULL;
	try
	{
		this->pointer = new elem<T>(*other.pointer);
	}
	catch (bad_alloc)
	{
		free();
	}
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack &other)
{
	if (this != &other)
	{
		free();
		allocate(other);		
	}
	return *this;
}

template<class T>
Stack<T>::~Stack()
{
	free();
}

template <class T>
void Stack<T>::free()
{
	delete pointer;
	pointer = NULL;
}

template <class T>
void Stack<T>::push(const elem<T>& box)
{
	if (pointer == NULL)
		pointer = new elem<T>(box);
	else
	{
		elem<T> * temp = new elem<T>(box);
		temp->next = pointer;
		pointer = temp;
		temp = NULL;
	}
}

template<class T>
void Stack<T>::pop()
{
	if (isEmpty())
	{
		free();
		return;
	}
	elem<T>* pOld = pointer;
	pointer = pOld->next;
	pOld->next = NULL;
}

template<class T>
const T& Stack<T>::peek()const
{
	return pointer->data;
}

template<class T>
bool Stack<T>::isEmpty()const
{
	return pointer == NULL;
}