#pragma once

#include <iostream>

struct symbolInfo
{
	char operat, symbol;
	int assoc, priority;

};

class ReadFromFile
{
	symbolInfo* symbols;
	size_t size;

	void fileStateCheck(std::istream &ifile)const;
	int calculateSize(std::istream & const ifile)const;
	void allocateSymbols(size_t size);

public:
	ReadFromFile();
	~ReadFromFile();

	void readFromFileFunc(std::string fileName);
	symbolInfo getSymbolInfo(std::string)const;
	bool searchSymbol(char)const;
};			   