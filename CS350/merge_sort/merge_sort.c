//Bradley Chang CS350 Mergesort
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void merge_sort(int data[], int lo, int hi);

void merge(int data[], int lo, int mid, int hi);

int main()
{
	int data[1000];	//Data array
	int size = 0;	//Size of data that user wants
	int input = 0;
	printf("Insert the amount of data you want to input: ");
	scanf("%d", &size);
	
	for(int i = 0; i < size; ++i)
	{
		printf("Input data: ");
		scanf("%d", &input);
		data[i] = input;
	}
	printf("\nShowing inputted data:\n");
	for(int i = 0; i < size; ++i)
	{
		printf("%d ", data[i]);
	}
	printf("\n");

	merge_sort(data, 0, size - 1);

	printf("\nShowing data sorted from least to greatest: \n");
	for(int i = 0; i < size; ++i)
	{
		printf("%d ", data[i]);
	}
	printf("\n");	


	return 0;
}

void merge_sort(int data[], int lo, int hi)
{
	if(lo < hi)
	{
		//Calculate middle
		int mid = (lo + hi) / 2;
		
		//Call left
		merge_sort(data, lo, mid);
		//Call right
		merge_sort(data, mid + 1, hi);
	
		//Call the merge function to sort
		merge(data, lo, mid, hi);
	}

	return;
}

void merge(int data[], int lo, int mid, int hi)
{
	int left_size = mid - lo + 1;
	int right_size = hi - mid;
	
	int left_temp[left_size];
	int right_temp[right_size];

	int left = 0;		//Left starts at the beginning of the left temp array
	int right = 0;		//Right starts at the beginning of the right temp array

	int i = lo; 		//Start of real array

	for(int left = 0; left < left_size; ++left)	//Copying data from original array into temp arrays
	{
		left_temp[left] = data[lo + left];
	}
	for(int right = 0; right < right_size; ++right)
	{
		right_temp[right] = data[mid + 1 + right];
	}

	left = right = 0;
	
	while(left < left_size && right < right_size)	//Stops before left reaches mid or right reaches end of array
	{
		if(left_temp[left] <= right_temp[right] )
		{
			data[i] = left_temp[left];
			++left;
		}
		else
		{
			data[i] = right_temp[right];
			++right;
		}
		++i;
	}
	
	while(left < left_size)	//Copies the rest of the array
	{
		data[i] = left_temp[left];
		++left;
		++i;
	}
	while(right < right_size)
	{
		data[i] = right_temp[right];
		++right;
		++i;
	}


	return;
}
