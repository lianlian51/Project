int cuttingRope(int n){
	if (n <= 3)
		return n - 1;

	int a = 0;
	int b = 0;
	long long int sum = 1;

	b = n % 3;
	a = n / 3 - 1;
	int p = 1000000007;

	while (a > 0)
	{
		sum = (sum * 3) % p;
		a--;
	}

	if (b == 0)
		sum = (sum * 3) % p;
	else if (b == 1)
		sum = (sum * 4) % p;
	else if (b == 2)
		sum = (sum * 6) % p;

	return sum;
}