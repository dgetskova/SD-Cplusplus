#include "ReadFromFile.h"
#include "CalculatedExpression.h"

int main()
{
	CalculatedExpression a;
	a.getExpressionAndFile();
	double result = a.makeCalc();
}