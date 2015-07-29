#pragma once

#include <iostream>

class ReadFromFile
{
	struct symbolInfo
	{
		char operat, symbol;
		int assoc, priority;
	};

	symbolInfo* symbols;
	size_t count;
	void fileStateCheck(std::istream &ifile)const;
	int ReadFromFile::calculateSize(std::istream & const ifile)const;
	//int calculateSize(std::istream &file)const; // zashto trqbva da q &   mogat li da se slagat constove
												//(ne zashtota samiqt rejim ne mi go pozlvolqva)
	void ReadFromFile::allocateSymbols(size_t size);
public:
	ReadFromFile();
	~ReadFromFile();

	void readFromFileFunc(std::string fileName);
	//int ReadFromFile::calculateSize(const std::istream & const ifile)const;


};