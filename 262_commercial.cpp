#include <stdio.h>
#define SIZE 100000

struct priority_queue {
	int h[SIZE];
	int len;
};

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void insert(struct priority_queue *h, int v)
{
	int i = h->len++;

	while (i != 0 && v < h->h[(i - 1) / 2])
	{
		h->h[i] = h->h[(i - 1)/2];
		i = (i - 1) / 2;
	}

	h->h[i] = v;
}

int extract(struct priority_queue *h)
{
	int r = h->h[0], i = 0, min = 0;

	h->h[0] = h->h[--h->len];

	do
	{
		int left = 2 * i + 1;
		if (left < h->len)
		{
			int right = left + 1;
			min = h->h[i] <= h->h[left] ? i : left;

			if (right < h->len)
				if (h->h[min] > h->h[right])
					min = right;
		}

		if (i != min)
		{
			swap(&h->h[i], &h->h[min]);
			i = min;
		}
		else 
			break;

	} while (1);

	return r;
}

void makenull(struct priority_queue *h)
{
	h->len = 0;
}

int main()
{
	double cost = 0;
	struct priority_queue h;
	int i, n;

	makenull(&h);

	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		int x;
		scanf("%d", &x);
		insert(&h, x);
	}

	for (i = 0; i < n - 1; i++)
	{
		int a = extract(&h), b = extract(&h);
		cost += a + b;
		insert(&h, a + b);
	}

	printf("%0.2lf", cost / 20.0);

	return 0;
}
