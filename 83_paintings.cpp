#include <stdio.h>

const int SIZE = 50;    

int n, m, maxcode, comp[SIZE][SIZE], ans[SIZE][SIZE];

int if_compatible(int a, int b)
{
    int l = n, shift;

    for (shift = 0; shift < l - 1; shift++)
    {
        if ((a % 2 == a % 4 / 2) && (a % 4 / 2 == b % 4 / 2) && (b % 4 / 2 == b % 2))
            return 0;
        a /= 2; b /= 2;
    }

    return 1;
}

void init_compatibles()
{
    int i, j;
    for (i = 0; i < maxcode; i++)
        for (j = 0; j < maxcode; j++)
            comp[i][j] = if_compatible(i, j);
}

int main()
{
    int i, j, k, total = 0;
    scanf("%d %d", &n, &m);

    if (n > m)
    {
        int t = n;
        n = m;
        m = t;
    }

    maxcode = 1 << n;

    if (n == 1)
    {
        printf("%d", 1 << m);
        return 0;
    }

    init_compatibles();

    for (i = 0; i < maxcode; i++)
        ans[i][0] = 1;

    for (j = 1; j < m; j++)
        for (i = 0; i < maxcode; i++)
            for (k = 0; k < maxcode; k++)
                if (comp[i][k])
                    ans[i][j] += ans[k][j - 1];

    for (i = 0; i < maxcode; i++)
        total += ans[i][m - 1];

    printf("%d", total);

    return 0;
}
