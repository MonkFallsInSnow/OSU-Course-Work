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