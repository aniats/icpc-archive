#include <stdio.h>

#define DEBUG1
const int SIZE = 2000;
const int ENDL = -100;
const int INF = 1000000;

int vill[SIZE], nextfree, p, n, ans = INF;
struct village {
	int st, fn, next;
} list[SIZE];

struct prom_ans {
	int a[SIZE];
};

int min(int a, int b)
{
	return (a < b) ? a : b;
}

void addE(int st, int fn)
{
	list[nextfree].next = vill[st];
	list[nextfree].fn = fn;
	list[nextfree].st = st;

	vill[st] = nextfree++;
}

struct prom_ans go(int node, int parent)
{
	struct prom_ans count;
	int i, j, nChildren = 0, chNum;

	for (i = vill[node]; i != ENDL; i = list[i].next)
		nChildren++;
	if (parent != 0)
		nChildren--;

	for (i = 0; i < SIZE; i++)
		count.a[i] = INF;

	count.a[1] = nChildren;

	for (chNum = vill[node]; chNum != ENDL; chNum = list[chNum].next)
		if (list[chNum].fn != parent)
		{
			struct prom_ans childCount = go(list[chNum].fn, node);
			for (i = n; i > 0; i--)
			{
				if (count.a[i] == INF)
					continue;
				for (j = 1; j <= n; j++)
				{
					if (childCount.a[j] == INF)
						continue;
					count.a[i + j] = min(count.a[i + j], count.a[i] + childCount.a[j] - 1);
				}
			}
		}


	if (parent == 0)
		ans = min(ans, count.a[p]);
	else 
		ans = min(ans, count.a[p] + 1);
	
	// printf("node = %d: ", node);
	// for (i = 1; i <= n; i++)
	// 	printf("%d ", count.a[i]);
	// printf("\n");

	return count;
}

int main()
{
	int i, j;

#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d", &n, &p);

	for (i = 1; i <= n; i++)
		vill[i] = ENDL;

	for (i = 1; i < n; i++)
	{
		int st, fn;
		scanf("%d %d", &st, &fn);
		addE(st, fn);
		addE(fn, st);
	}

	go(1, 0);

	printf("%d", ans);

	return 0;
}
