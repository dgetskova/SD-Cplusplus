

class QuickSort
{
public:
	void quickSort(int * arr, size_t size);
	size_t partition(int * arr, size_t size);
};

void swapIf(int &a, int &b)
{
	if (a > b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	//a is smaller than b
}

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}


void QuickSort::quickSort(int * arr, size_t size)
{
	if (size == 1 || 0)
		return;
	if (size == 2)
	{
		swapIf(arr[0], arr[1]);
		return;
	}

	if (size == 3)
	{
		swapIf(arr[0], arr[size - 1]);
		swapIf(arr[0], arr[size / 2]);
		swapIf(arr[size / 2], arr[size - 1]);
		return;
	}
	int pos = partition(arr, size);

	//without pos (the elem in pos position is in the right place)
	quickSort(arr, pos);
	quickSort(arr + pos + 1, size - pos - 1);

}
size_t QuickSort::partition(int * arr, size_t size)
{
	
	//find middle between 3 elements
	swapIf(arr[0], arr[size - 1]);
	swapIf(arr[0], arr[size / 2]);
	swapIf(arr[size / 2], arr[size - 1]);

	
	//move middle(of3) at last but one because of the left and right pointers moving to each other
	swap(arr[size / 2], arr[size - 2]);

	int &partition = arr[size - 2];

	size_t left = 0, right = size - 2;

	while (true)
	{
		while (arr[++left] < partition)
			;
		while (arr[--right] > partition)
		// if left points->12 11 4 and partition = 9 right will pass throw all (including left)
		{
			if (left == right)
				break;
		}
		//protect for infinite loop
		if (left >= right)
			break;
		//this mean that in left pos elem is bigger than partition and in right elem is smaller than partition
		swap(arr[left], arr[right]);
	}
	//to put partition on the right place(all in left are smaller, all in right are bigger)
	swap(arr[left], partition);
	return left;
}