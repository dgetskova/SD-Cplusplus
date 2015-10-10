#include"List.h"

int main()
{
	List<int> list;
	list.push(1);
	list.push(2);
	list.push(3);
	list.removeElem(1, 3); // middle
	list.removeElem(1, 2); // last
	list.removeElem(0, 1); // first
	list.push(1);
	list.push(2);
	//list.removeElem(0, 2);
	list.pop();
}