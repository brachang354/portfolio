//Binary Search Algorithm
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int binary_search(int key, int data[], int lo, int hi);

int main()
{
	int data[1000];
	int val;
	val = floor(10 * drand48());
	data[0] = val;
	int n;

	printf("Type in value for n to generate array: ");
	scanf("%d", &n);
	
	for(int i = 1; i < n; ++i)
	{
		val = floor(10 * drand48())+ 2;
		data[i] = data[i-1] + val;
		printf("%d\t", data[i]);	
	}
	printf("\n");
	
	int key;
	printf("Type in value we want to find: ");
	scanf("%d", &key);

	//int k = floor(10 * drand48());
	
	printf("Data item we want to find: %d\n", key);
	int lo = 0;
	int hi = n-1;

	int loc = binary_search(key, data, lo, hi);
	printf("Location of data item: %d\n", loc);

	return 0;
}

int binary_search(int key, int data[], int lo, int hi)
{
	if(lo > hi)
		return -1;

	//if(key == data[n])
	//	return n;

	int middle = (lo + hi) / 2;
	
	if(data[middle] == key)
		return middle;
	if(data[middle] < key)
	{
		lo = middle + 1;
	}
	else if(data[middle] > key)
	{
		hi = middle - 1;
	}

	return binary_search(key, data, lo, hi);

}
