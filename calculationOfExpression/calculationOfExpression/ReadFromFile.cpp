#include "ReadFromFile.h"
#include <string>
#include <fstream>
using namespace std;


ReadFromFile::ReadFromFile()
{
	symbols = NULL;
	count = 0;
}
ReadFromFile::~ReadFromFile()
{
	delete symbols;
	count = 0;
}

void ReadFromFile::readFromFileFunc(std::string fileName)
{
	std::ifstream ifile("file.txt");
	fileStateCheck(ifile);

	allocateSymbols(calculateSize(ifile));
	fileStateCheck(ifile);
	//puts pointer in the begining of file

	char t;
	for (size_t i = 0; i < count && ifile.good(); i++)
	{

		ifile >> symbols[i].symbol
			>> symbols[i].operat
			>> symbols[i].priority
			>> symbols[i].assoc;
	}

	ifile.close();
	
}
int ReadFromFile::calculateSize(std::istream & const ifile)const
{
	
	fileStateCheck(ifile);

	string line;
	size_t currentCount = 0;

	while (getline(ifile, line) && ifile.good())
	{
		////need this check because of the good state of file
		//pos = ifile.tellg();
		//ifile >> firstElem;
		//if (ifile.eof())
		//	break;
		//ifile.seekg(pos);

		currentCount++;
	}
	ifile.clear();
	ifile.seekg(0);
	int a = ifile.tellg();
	return currentCount;
}

void ReadFromFile::fileStateCheck(istream &ifile)const
{
	if (!ifile || !ifile.good())
	{
		throw "Problem with file";
	}
}

void ReadFromFile::allocateSymbols(size_t size)
{
	count = size;
	try{
		symbols = new symbolInfo[count];
	}
	catch (bad_alloc){ throw "Bad alloc"; }

}
