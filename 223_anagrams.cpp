#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

typedef __float128 T;

const int SIZE = 51;

T count[SIZE][SIZE][SIZE], t;
int n;

void print(T n)
{
	long long hi, lo;
	const long long _1e18 = 1000LL * 1000 * 1000 * 1000 * 1000 * 1000;
	if (n < _1e18)
		printf("%lld", (long long)n);
	else
	{
		hi = (long long)(n / _1e18);
		lo = (long long)(n - (T)hi * _1e18);
		printf("%lld%018lld", hi, lo);
	}
}


int main()
{
	int len, srcFirst, dstFirst, add;
	char src[SIZE], dst[SIZE];

	gets(src);
	gets(dst);
	for (n = 0; src[n]; n++);

	for (len = 0; len <= n; len++)
		for (srcFirst = 0; srcFirst + len <= n; srcFirst++)
			for (dstFirst = 0; dstFirst + len <= n; dstFirst++)
			{
				if (len == 0)
					count[len][srcFirst][dstFirst] = 1;
				else if (len == 1)
					count[len][srcFirst][dstFirst] = (src[srcFirst] == dst[dstFirst]);
				else
				{
					t = 0;
					for (add = 0; add < len; add++)
						if (src[srcFirst] == dst[dstFirst + add])
							t += count[add][srcFirst + 1][dstFirst] * count[len - add - 1][srcFirst + add + 1][dstFirst + add + 1];

					count[len][srcFirst][dstFirst] = t;
				}

			}

	print(count[n][0][0]);

	return 0;
}
