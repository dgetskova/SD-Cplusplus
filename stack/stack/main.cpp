#include "stack.h"
#include <typeinfo>
using namespace std;
#include <string>

int main()
{
	int a = 9;
	typeid(a);	
	elem<int> element1(1);
	elem<int> element2(2);
	elem<int> element3(3);
	elem<int> elementCopy(element1);

	Stack<int> stack1(element1);
	stack1.push(element2);
	stack1.push(element3);

	Stack<int> stack2(stack1);
	cout << "a";
	stack2.push(element1);
	stack2.push(element1);
	stack1.push(element2);

	stack1 = stack2;

	Stack<string> s;
	string aso = "asa";
	s.push(aso);

	stack2.pop();
	elem<int> fromPeek(stack2.peek());

}