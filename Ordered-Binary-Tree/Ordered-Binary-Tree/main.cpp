#include <iostream>
#include "Tree.h"

int main()
{
	node<int> minusfive(-5, -5);
	node<int> minusten(-10, -10);
	node<int> a(1, 1);
	node<int> b(2, 2);
	node<int> c(3, 3);
	node<int> ten(10, 10);
	node<int> five(5, 5);
	node<int> fiveteen(15, 15);
	node<int> seven(7, 7);

	Tree<int> tree;
	tree.add(a);
	tree.add(b);
	tree.add(c);
	tree.add(minusfive);
	tree.add(minusten);

	int aint = tree.search(1);
	int bint = tree.search(2);
	tree.remove(2);
	tree.remove(3);
	tree.remove(-5);

	//right part is clean
	tree.add(ten);
	tree.add(five);
	tree.add(fiveteen);
	tree.add(c);
	tree.add(seven);
	//1, 10 (5 (3, 7) 15)

	tree.remove(10);
	//1, 7 (5 (3), 15)

}