#include <iostream>
#include <fstream>
using namespace std;

const size_t cSizeArray = 256;
const size_t arrFileSize = 16;

template <class T>
class stack {
	template <class T>
	struct node {
		T data;
		node <T> *prev;
		node (const T& el) : data (el), prev (NULL) {}
	};

	node <T>*head; // tos
	int lenght;

public:
	stack () : lenght (0), head(NULL) {}
	~stack (){while(lenght) pop();}

	node<T> pop () //hvurlq izkl
	{
		if (!head)
			throw runtime_error("Popping from empty stack"); /// std ::
		
		T holdData = head->data;
		node<T>* holdBox= head;
		node<T> *tempPrev = head->prev;
		head->prev = NULL;
		head = tempPrev;   /// ne sum mn sig za nuliraneto
		delete holdBox;

		lenght--;
		return holdData;

	}

	node<T> top ()
	{
		return head->data;
	}

	void push (const T & el )
	{
		node <T> * temp = head;
		head = new node<T> (el) ;
		head->prev = temp;
		lenght++;  // tuk eventualen problem
	}



	bool isEmpty ()
	{
		return lenght == 0;
	}

};

//moje da se izpolzvat ako v izraza sa pozvoleni vsichki vidove skobi
//const char * open = "([{";
//const char * close = ")]}";

//bool isOpen (char st)
//{
//	return strchr(open,st)!= NULL;
//}
//
//bool isClose (char c)
//{
//	return strchr (close, c) != NULL;
//}

bool isCorectBrackets ( const char * str )
{
	stack <char> st;
	int pos = 0;
	while (str[pos])
	{
		if (str[pos] == '(')
		{
			st.push(str[pos]);
		}else if(str[pos] == ')')
		{
			if(st.isEmpty())
			{
				cout << "Wrong brackets in expression "
					<< "at pos " << (pos++) << endl;
				return false;
			}
			else
				st.pop(); // pop vrushta neshto ?? tova moje da e problem
		}
		pos++;
	}

	if (st.isEmpty())
	{
		cout << "Corect brackets.";
		return true;
	}else
	{
		cout << "Wrong brackets in expression."<<endl;
		return false;
	}
}

struct forFile
{
	char operat, symbol;
	int assoc, priority;
};


//tova e po dobre  v klas inache ne moga da pravq promenite
forFile ** arrFileResize (forFile** old,const size_t size)
{
	const size_t sizeNew =2*size;
	forFile ** newArr = new forFile* [sizeNew];
	
	for(size_t i = 0; i<size; i++)
	{
		newArr[i] = old [i];
	}

	// da si nasocha ukazatelq kum noviq masiv
	//triene na pametta
	return newArr;
}



//int main (int argc, char*argv[])

int main ()
{
	char array[cSizeArray];
	cin.getline(array,cSizeArray); 

	try{
	if (!isCorectBrackets(array))
		throw 1;
	}catch (int)
	{
		cout<<"Wrong brackets";
		return -4;
	}

	//if(argc !=2)
	//cout<<"Wrong input";	
	///ifstream inFile (argv[1], ios::in);
	
	ifstream inFile ("kak.txt", ios::in);
	
	if(!inFile)
	{
		cout<<"File is not open!";
		return -1;
	}

	forFile  arrFile [arrFileSize];
	size_t row = 0;
	char proba[8];
	try
	{
		while (!inFile.eof() && inFile.good())
		{
			inFile.getline(proba,8);

			arrFile[row].symbol=proba[0];
			arrFile[row].operat=proba[2];

			if(proba[2] !='+' && proba[2] != '-' &&
				proba[2] !='*' && proba[2] !='/')
			{
				throw "Wrong operator in file";
			}

			arrFile[row].priority=proba[4]-'0';
			arrFile[row].assoc = proba[6]-'0';
			if((proba[6] - '0') != '1'&& (proba[6] - '0') != '0')
			{
				throw "wrong associativity";
			}
			row++;
			if(row>=arrFileSize)
			{
				cout<<"making resize, no resize ne raboti";
				/*try{arrFileResize(arrFile,arrFileSize);
				}catch (bad_alloc){
					cout << "Problem of memory.";
					return -2;}*/
			}
		}
	}catch (char*)
	{
		cout<<"Wrong input file";
		return -3;
	}



	stack <int> numbers;
	stack <char> operations;

	size_t capacity = strlen (array);
	bool symbolIn = false;
	for (int start = 0; start < capacity; start++)
	{
		//pravq gi s cifri 
		if(array[start] >= '0' && array[start] <= '9')
		{
			numbers.push (array[start] - '0');
		}


		if (array[start] >= 'a' && array[start] <='z' )
		{

			//dali simvola ot izraza se sreshta vuv faila
			for(int k = 0; k < arrFileSize; k++)
			{
				if (arrFile[k].symbol == array[start])
				{
					symbolIn = true;
				}
			}
			if(symbolIn == false)
				return -5;

			//zapisvam go v steka
			operations.push(array[start]);

			//i v edin moment ne moga da produlja s  sravnqvaneto na prioriteti i asociativnostta 

		}
		symbolIn = false;
		
	}
	
	inFile.close();
}
