// 给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m - 1] 。
// 请问 k[0]*k[1]*...*k[m - 1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18


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