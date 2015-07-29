#include "QuickSort.h"
#include <iostream>

void printArr(int *arr, size_t size)

{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}
int main()
{
	const int ROW = 6, COL = 10;
	
	int dataTest[ROW][COL] = {
		{ 1, 0, 3, 2, 5, 4, 7, 6, 9, 8 },
		{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
		{ 1, 9, 6, 7, 1, 3, 2, 1, 5, 0 },
		{ 7, 3, 3, 5, 1, 6, 2, 4, 8, 9 },
		{ 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 }
	};
	
	QuickSort a;
	for (size_t j = 0; j<ROW; j++)
	{
		std::cout << "Before Sorting :: ";
		printArr(dataTest[j], COL);
		a.quickSort(dataTest[j], COL);
		std::cout << "After Sorting  ::	";
		printArr(dataTest[j], COL);
		std::cout << std::endl;
	}
}