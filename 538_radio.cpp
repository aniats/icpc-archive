#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int SIZE = 1200;

struct coord {
    int x, y;
};

struct coord v[SIZE];

int n, last_e;
int clr[SIZE], e[SIZE * SIZE / 2], adj[SIZE][SIZE];

int dst(struct coord a, struct coord b)
{
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

int dfs(int v, int curclr)
{
    int i;

    clr[v] = curclr;

    for (i = 0; i < n; i++)
    {
        if (adj[v][i] && clr[i] == curclr)
            return -1;

        if (adj[v][i] && clr[i] == 0)
            if (dfs(i, 3 - curclr) == -1)
                return -1;
    }

    return 0;
}

int is_correct(int s)
{
    int i, j;

    memset(clr, 0, sizeof clr[0] * SIZE);

    for (i = 0; i < n - 1; i++)
    {
        struct coord a = { v[i].x, v[i].y };
        for (j = i + 1; j < n; j++)
        {
            struct coord b = { v[j].x, v[j].y };
            adj[i][j] = adj[j][i] = (dst(a, b) < s); // 1 == not suitable
        }
    }

    for (i = 0; i < n; i++)
        if (clr[i] == 0 && dfs(i, 1) == -1)
            return 0;

    return 1;
}

double bin_search()
{
    int L = 0, R = last_e - 1, m;

    while (R - L > 1)
    {
        m = (L + R) / 2;

        if (is_correct(e[m]))
            L = m;
        else
            R = m;
    }

    if (is_correct(e[R]))
        m = R;
    else if (is_correct(e[L]))
        m = L;

    return sqrt((double)e[m]) / 2;
}

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    int i, j;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d %d", &v[i].x, &v[i].y);

    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            e[last_e++] = dst(v[i], v[j]);

    qsort(e, last_e, sizeof e[0], cmp);

    printf("%0.9lf\n", bin_search());

    for (i = 0; i < n; i++)
        printf("%d ", clr[i]);

    return 0;
}
