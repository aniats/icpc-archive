#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

const int SIZE = 20, INF = 1000, TURNSIZE = 6, WALL = 1;
enum { E, U, L, R, D };

int n, m, max_t, si, sj, fi, fj;
int map[SIZE][SIZE];
int way[SIZE][SIZE][TURNSIZE];
int came_to_cell[SIZE][SIZE][TURNSIZE];

int min(int a, int b)
{
	return (a < b) ? a : b;
}

struct cell {
	int i, j, right_t, from, length;
};

struct queue {
	struct cell a[SIZE * SIZE * TURNSIZE * 4];
	int head, tail;
};

struct cell dequeue(struct queue *q)
{
	q->head++;
	return q->a[q->head - 1];
}

void enqueue(struct queue *q, struct cell p)
{
	q->a[q->tail++] = p;
}

int empty(struct queue *q)
{
	return q->head == q->tail;
}

void go(int ni, int nj, int rt, int cur_dist, int cur_dir, struct queue *q)
{
	int from_dir = 5 - cur_dir;
	if (ni >= 0 && ni < n && nj >= 0 && nj < m && map[ni][nj] != WALL && rt <= max_t
		&& (came_to_cell[ni][nj][rt] & (1 << from_dir)) == 0
		)
	{
		struct cell p = { ni, nj, rt, from_dir, cur_dist + 1 };
		enqueue(q, p);
		came_to_cell[ni][nj][rt] = came_to_cell[ni][nj][rt] | (1 << from_dir);
		way[ni][nj][rt] = min(way[ni][nj][rt], cur_dist + 1);
	}
}

void try_dir(struct cell p, int d_to, int d_from_which_right_turn, struct queue *q)
{
	if (p.from != d_to)
	{
		int ni = p.i, nj = p.j;

		switch (d_to)
		{
		case U: ni--; break;
		case D: ni++; break;
		case L: nj--; break;
		case R: nj++; break;
		}


		go(ni, nj,
			p.right_t + (p.from == d_from_which_right_turn),
			p.length, d_to, q);
	}
}

void bfs()
{
	struct queue q;
	q.head = q.tail = 0;

	struct cell p;
	p.i = si;
	p.j = sj;
	p.right_t = p.length = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k <= max_t; k++)
				way[i][j][k] = INF;

	way[si][sj][0] = 0;

	p.from = D;
	try_dir(p, U, R, &q);

	p.from = R;
	try_dir(p, L, U, &q);

	p.from = U;
	try_dir(p, D, L, &q);

	p.from = L;
	try_dir(p, R, D, &q);

	while (!empty(&q))
	{
		p = dequeue(&q);
		try_dir(p, U, R, &q);
		try_dir(p, L, U, &q);
		try_dir(p, D, L, &q);
		try_dir(p, R, D, &q);
	}
}

int main()
{
	int ans = INF;

	freopen("input.txt", "r", stdin);

	cin >> max_t >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			int x;
			cin >> x;
			switch (x)
			{
			case 1: map[i][j] = 1;  break;
			case 2: si = i; sj = j; break;
			case 3: fi = i; fj = j; break;
			}
		}

	bfs();

	for (int i = 0; i <= max_t; i++)
		ans = min(ans, way[fi][fj][i]);

	cout << ((ans == INF) ? -1 : ans) << endl;
}
