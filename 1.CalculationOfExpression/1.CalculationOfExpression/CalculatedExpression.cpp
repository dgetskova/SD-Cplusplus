#include "CalculatedExpression.h"
#include <sstream>
#include <cassert>


void CalculatedExpression::getExpressionAndFile()
{
	cout << "Enter Expression: ";
	getline(cin, expression);
	//expression = "10 a 10 b 3 c 7 d 12 c 2 c 4 a 10";				
	//expression = "1 a 2 a 3 a 4 c 10";							
	//expression = "1 c 2 a 3 c 2 c 10";							
	//expression = "31 a ( 5 b 32 f 10 e -230 ) c 324 d 17";			// moodle ---
	//expression = " 2 a 3 b 7  c ( 3 a 3 b 2 c 9 a 3 ) a 2 b 1";		
	cout << "Enter File name: ";
	string fileName = "";
	//getline(cin, fileName);
	//fileName = "file.txt";
	fileName = "moodle.txt";  // moodle
	file.readFromFileFunc(fileName);

	if (!isValidBrackets() || !isValidSymbols())
	{
		cout << "No valid expression";
		throw "No valid expression";
	}

	makeParts();
	extraPriority = 0;
}



bool CalculatedExpression::isNum(string str)
{
	size_t i = 0;
	if (str[i] == '-')
		i++;
	for (i; i < str.length(); i++)
		if (str[i] < '0' || str[i] > '9')
			return false;
	return true;
}


bool CalculatedExpression::isSymbol(string str)
{
	for (size_t i = 0; i < str.length(); i++)
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] == '(' || str[i] == ')'))
			return true;
	return false;
}


void CalculatedExpression::makeParts()
{
	exprressionPartsSize = 0;
	string buf; // Have a buffer string
	stringstream ss(expression); // Insert the string into a stream

	while (ss >> buf)
	{
		exprParts.push_back(buf);
		exprressionPartsSize++;
	}
}


double CalculatedExpression::stringToNum(string str)
{
	int num = 0;
	stringstream ss(str);
	ss >> num;
	return num;
}

char CalculatedExpression::stringToChar(string symbolStr)
{
	return symbolStr[0];
}



double CalculatedExpression::makeCalc()
{
//	symbolInfo symbolBefore;
	for (size_t i = 0; i < exprressionPartsSize; i++)
	{
		if (isNum(exprParts[i]))
		{
			numStack.push(stringToNum(exprParts[i]));
			continue;
		}

		if (isSymbol(exprParts[i]))
		{

			symbolInfo currentSymbol = file.getSymbolInfo(exprParts[i]);
			// extra priority for all operation which are in brackets
 
			// Every time when in the expression it has brackets () the elements which are between brackets get extra priority
			// so it can these operations to execute first
			if (currentSymbol.operat == '(')
			{		
				extraPriority += currentSymbol.priority;
				continue;
			}
			else if (currentSymbol.operat == ')')
			{
				extraPriority -= currentSymbol.priority;
				continue;
			}
			currentSymbol.priority += extraPriority;

			if (symbStack.isEmpty())
				symbStack.push(currentSymbol);
			else
			{
				//finds priority of the current symbol and it compares with the symbol before
				if (currentSymbol.priority <= symbStack.peek().priority)
				{
					while (currentSymbol.priority <= symbStack.peek().priority)
					{
						oneCalc();
						if (symbStack.isEmpty())
							break;
					}
					symbStack.push(currentSymbol);
				}
				// (currentSymbol.priority > symbStack.peek().priority)
				else
					symbStack.push(currentSymbol);
			}
		}	
	}
	// the last element of expression is number. because of that  has to make all calculations which are left in stack of symbols
	while (!symbStack.isEmpty())
		oneCalc();
	return numStack.pop();
}


void CalculatedExpression::oneCalc()
{
	double result = 0;
	// first pop b after a because the expression is a + b
	double b = numStack.pop();
	double a = numStack.pop();

	//1 = right assoc, 0 = left assoc
	symbolInfo symbolObj = symbStack.pop();

	//1 = right assoc, 0 = left assoc
	// change to right associativity
	if (symbolObj.assoc == 1)
	{
		double temp = a;
		a = b;
		b = temp;
	}
	cout << a << "	"<< symbolObj.symbol <<
		"	("<< symbolObj.operat << ")	" <<
		"("   << symbolObj.assoc  << ")	" << b;
	switch (symbolObj.operat)
	{
	case '+':
		result = a + b;
		break;
	case '-':
		result = a - b;
		break;
	case '*':
		result = a * b;
		break;
	case '/':
		result = a / b;
		break;
	}
	cout <<"	" <<  " = " << result << "	"<< endl;
	numStack.push(result);
}




bool CalculatedExpression::isValidBrackets()const
{
	size_t length = expression.length();
	Stack<char> brackets;
	for (size_t i = 0; i < length; i++)
	{
		if ( expression[i] == '(')
		{
			brackets.push(expression[i]);
		}
		else if (expression[i] == ')')
		{
			if (brackets.isEmpty())
				return false;
			else
				brackets.pop();
		}
	}
	//if stack is empty therefore brackets are correct 
	return brackets.isEmpty();
}
bool CalculatedExpression::isValidSymbols()const
{
	size_t length = expression.length();
	
	for (size_t i = 0; i < length; i++)
		if ((expression[i] >= 'a' && expression[i] <= 'z') || (expression[i] == '(' || expression[i] == ')'))
		{
			if (file.searchSymbol(expression[i]))
				return true;
			else
				return false;
		}
	return false;
}
