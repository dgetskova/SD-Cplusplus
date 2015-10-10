#include "List.h"
//#include <exception>

int main()
{
	elem element1(1);
	elem element2(2);
	elem element3(3);


	List list;
	list.push(element1);
	list.push(element2);
	list.push(element3);
	const char* a = "You can't pop from empty one connected list.";
	list.pop();
	list.pop();
	list.pop();
	list.pop();

}

