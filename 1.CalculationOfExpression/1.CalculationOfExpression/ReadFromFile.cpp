#include "ReadFromFile.h"
#include <string>
#include <fstream>
using namespace std;


ReadFromFile::ReadFromFile()
{
	symbols = NULL;
	size = 0;
}
ReadFromFile::~ReadFromFile()
{
	delete  [] symbols;
	size = 0;
}

void ReadFromFile::readFromFileFunc(std::string fileName)
{
	std::ifstream ifile(fileName);
	fileStateCheck(ifile);

	allocateSymbols(calculateSize(ifile));
	fileStateCheck(ifile);

	int maxPriority = 0;
	//last elem for bracket '('
	for (size_t i = 0; i < (size - 2) && ifile.good(); i++)
	{
		ifile >> symbols[i].symbol;
		ifile >> symbols[i].operat;
		ifile >> symbols[i].priority;
		ifile >> symbols[i].assoc;

		// to determine priority of brackets
		if (i == 0)
			maxPriority = symbols[0].priority;
		if (symbols[i].priority > maxPriority)
			maxPriority = symbols[i].priority;
	}

	symbols[size - 1].symbol = '(';
	symbols[size - 1].operat = '(';
	symbols[size - 1].priority = maxPriority + 1;
	symbols[size - 1].assoc = 1;

	symbols[size - 2].symbol = ')';
	symbols[size - 2].operat = ')';
	symbols[size - 2].priority = maxPriority + 1;
	symbols[size - 2].assoc = 1;

	ifile.close();
	
}
int ReadFromFile::calculateSize(istream & const ifile)const
{
	
	fileStateCheck(ifile);

	string line;
	size_t currentCount = 0;

	while (getline(ifile, line) && ifile.good())
		currentCount++;
	// for the last row
	if (line != "")
		currentCount++;

	//why it needs clear? getline gets all until '\n'
	ifile.clear();
	ifile.seekg(0);
	//int checkPos = ifile.tellg(); -- to check position

	return currentCount;
}

void ReadFromFile::fileStateCheck(istream &ifile)const
{
	if (!ifile || !ifile.good())
	{
		throw "Problem with file";
	}
}

void ReadFromFile::allocateSymbols(size_t sizeCame)
{
	// two more elemnts for brackets
	size = sizeCame + 2;
	try{
		symbols = new symbolInfo[size];
	}
	catch (bad_alloc){ throw "Bad alloc"; }

}


symbolInfo ReadFromFile::getSymbolInfo(string wanted)const
{
	//wanted is one symbol
	char wantedC = wanted[0];

	for (size_t i = 0; i < size; i++)
	{
		if (wantedC == symbols[i].symbol)
		{
			return symbols[i];
		}
	}
	throw"No symbol in file";
}

bool ReadFromFile::searchSymbol(char symbCame)const
{
	for (size_t i = 0; i < size; i++)
		if (symbCame == symbols[i].symbol)
			return true;
	return false;
}