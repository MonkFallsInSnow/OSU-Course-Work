int _binarySearch(TYPE * data, int size, TYPE val) 
{   
	int low  = 0;   
	int high = size;   

	while (low < high) 
	{     
		int mid = low + ((high - low) / 2); 
		
		if (data[mid] < val)
		{
			low  = mid + 1; 
		}
		else if(data[mid] > val)
		{		
			high = mid - 1;
		}
		else
		{
			return mid; //key found
		}
	}
	
	return -1; //key not found
}