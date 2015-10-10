#pragma once

using namespace std;
#include <string>
#include "stack.h"
#include "ReadFromFile.h"
#include <vector>

class CalculatedExpression
{
	ReadFromFile file;
	size_t extraPriority;

	string expression;
	vector<string> exprParts;
	size_t exprressionPartsSize;

	Stack<symbolInfo> symbStack;
	Stack<double> numStack;

	bool isValidBrackets()const;
	bool isValidSymbols()const;

	bool isNum(string);
	bool isSymbol(string);

	void makeParts();
	void oneCalc();

	double stringToNum(string);
	char stringToChar(string);

public:
	void getExpressionAndFile();
	double makeCalc(); 
};
