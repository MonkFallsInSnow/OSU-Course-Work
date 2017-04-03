void swap(int* myArray, int first, int second)
{
	int temp = myArray[first];
	myArray[first] = myArray[second];
	myArray[second] = temp;
}

int partition(int* myArray, int start, int end)
{
	int pivot = myArray[end];
	int wall = start;

	for (int current = wall; current < end; current++)
	{
		if (myArray[current] < pivot)
		{
			swap(myArray, current, wall);
			wall++;
		}
	}

	swap(myArray, end, wall);

	return wall;
}

void quickSort(int* myArray, int start, int end)
{
		if(start < end)
		{
			int pivotPos = partition(myArray, start, end);
			quickSort(myArray, start, pivotPos - 1);
			quickSort(myArray, pivotPos + 1, end);
		}
			
}