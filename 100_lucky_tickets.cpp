#include <stdio.h>

const int SIZE = 500;
const int MAXSUM = 450;

const int LSIZE = 1000;
const int RADIX = 10000;

struct longnum {
	int a[LSIZE];
	int l;
};

void init(struct longnum *num, int val)
{
	int i;
	for (i = 0; val > 0; i++)
	{
		num->a[i] = val % RADIX;
		val /= RADIX;
	}

	num->l = i;

	for (i = i; i < SIZE; i++)
		num->a[i] = 0;
}

void long_print(struct longnum *num)
{
	int i, j;
	printf("%d", num->a[num->l - 1]);

	for (i = num->l - 2; i >= 0; i--)
	{
		int t = num->a[i];
		for (j = RADIX / 10; j > 0; j /= 10)
		{
			printf("%d", t / j);
			t %= j;
		}
	}

	printf("\n");
}

void long_long_sum(struct longnum *a, struct longnum *b)
{
	int i, rest = 0;
	for (i = 0; i < SIZE; i++)
	{
		a->a[i] = a->a[i] + b->a[i] + rest;
		rest = a->a[i] / RADIX;
		a->a[i] %= RADIX;

		if (a->a[i] > 0 && i == a->l)
			a->l++;
	}
}

struct longnum long_long_mult(struct longnum *a, struct longnum *b)
{
	int i, j, r = 0;
	struct longnum t;
	init(&t, 0);

	for (i = 0; i < a->l; i++)
	{
		r = 0;
		for (j = 0; j < b->l; j++)
		{
			r = r + a->a[i] * b->a[j] + t.a[i + j];
			t.a[i + j] = r % RADIX;
			r /= RADIX;
		}
		if (r > 0)
			t.a[i + j] = r;
	}

	t.l = a->l + b->l - 1;	
	while (t.a[t.l] > 0)
		t.l++;

	return t;
}

struct longnum pre_line[SIZE], cur_line[SIZE];

int main()
{
	int i, j, k, n;

	struct longnum *p_pre = pre_line, *p_cur = cur_line, ans;

	scanf("%d", &n);

	init(&ans, 0);

	for (i = 0; i <= 9; i++)
		init(&p_pre[i], 1);

	for (i = 2; i <= n / 2; i++)
	{
		for (j = 0; j <= MAXSUM; j++)
		{
			init(&p_cur[j], 0);
			for (k = j; k >= 0 && k >= j - 9; k--)
				long_long_sum(&p_cur[j], &p_pre[k]);
		}

		struct longnum *t = p_pre;
		p_pre = p_cur;
		p_cur = t;
	}

	for (i = 0; i <= MAXSUM; i++)
	{
		struct longnum t = long_long_mult(&p_pre[i], &p_pre[i]);
		long_long_sum(&ans, &t);
	}

	long_print(&ans);

	return 0;
}
