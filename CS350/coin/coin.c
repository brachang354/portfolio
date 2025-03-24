//Bradley Chang CS350 Coin Program
#include <stdio.h>

int coin_split(int n);
int memo_split_wrap(int n);
int memo_split(int n, int * table);

int main()
{
	int n;
	int total_coins;
	printf("Input number of coins to split: ");
	scanf("%d", &n);
	//total_coins = coin_split(n);
	total_coins = memo_split_wrap(n);

	printf("Number of coins: %d\n", total_coins);
	

	return 0;
}
int memo_split_wrap(int n)
{
	int table[1000];
	for(int i = 0; i < 1000; ++i)
		table[n] = -1;
	return memo_split(n, table);		
}
int memo_split(int n, int * table)
{
	if(table[n] != -1)
		return table[n];
	if(n == 1 || n == 3 || n == 4)
		return 1;
	if(n == 0)
		return 0;
	if(n == 2)
		return 2;
	int a;
	int b;
	int c;
	int min;

	a = memo_split(n-1, table);
	b = memo_split(n-3, table);
	c = memo_split(n-4, table);

	min = a;
	if(b < min)
		min = b;
	if(c < min)
		min = c;
	
	table[n] = 1 + min;
	return table[n];
}

int coin_split(int n)
{
	if(n == 1 || n == 3 || n == 4)
		return 1;
	if(n == 0)
		return 0;
	if(n == 2)
		return 2;
	int a;
	int b;
	int c;
	int min;

	a = coin_split(n-1);
	b = coin_split(n-3);
	c = coin_split(n-4);

	min = a;
	if(b < min)
		min = b;
	if (c < min)
		min = c;
	
	return 1 + min;
}
