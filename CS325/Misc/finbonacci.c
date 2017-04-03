#include <stdio.h>
#include <time.h>

unsigned long long itrFib(long long n);
unsigned long long recFib(int n);

int main()
{
	for (long long i = 300000000; i <= 1500000000; i += 100000000)
	{
		long long timer = clock();
		itrFib(i);
		timer = clock() - timer;
		printf("Iterative n = %lld: %f\n", i, (float)timer / (float)CLOCKS_PER_SEC);
	}

	printf("\n");

	for (int i = 40; i < 50; i++)
	{
		int timer = clock();
		recFib(i);
		timer = clock() - timer;
		printf("Recursive n = %d: %f\n", i, (float)timer / (float)CLOCKS_PER_SEC);
	}
	

	return 0;
}

unsigned long long itrFib(long long n)
{
	unsigned long long fib = 0;
	unsigned long long a = 1;
	unsigned long long t = 0;

	for (long long i = 0; i < n; i++)
	{
		t = fib + a;
		a = fib;
		fib = t;
	}

	return fib;
}

unsigned long long recFib(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return recFib(n - 1) + recFib(n - 2);
}