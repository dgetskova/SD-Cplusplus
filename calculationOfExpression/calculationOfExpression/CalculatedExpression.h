#pragma once
using namespace std;
#include <string>
#include "stack.h"

class CalculatedExpression
{
	string expression;
	Stack<char> a;

	bool isValidBrackets();// -
	void calculatedExpression();
public:
	void getExpression();
};