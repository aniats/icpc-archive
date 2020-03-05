#include <stdio.h>
#include <stdlib.h>

const int SIZE = 500;

#define TOWALL (struct wall *)

struct wall {
    double a, b, s;
    int n;
} w[SIZE];

int cmp(const void *a, const void *b)
{
    if ((TOWALL a)->s < (TOWALL b)->s)
        return -1;

    return (TOWALL a)->s >(TOWALL b)->s;
}

double dissolve(int l_p, int r_p)
{
    double ans = 0;

    while (l_p != r_p)
        if (w[l_p].a < w[r_p].b)
        {
            ans += w[l_p].a;
            w[r_p].b -= w[l_p++].a;

            w[r_p].a = w[r_p].b / w[r_p].s;

        }
        else
        {
            ans += w[r_p].b;
            w[l_p].a -= w[r_p--].b;

            w[l_p].b = w[l_p].a * w[l_p].s;
        }

    if (w[l_p].a + w[l_p].b != 0)
        ans += w[l_p].a * w[l_p].b / (w[l_p].a + w[l_p].b);

    return ans;
}

int main()
{
    int i, n;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%lf %lf", &w[i].a, &w[i].b);
        w[i].s = w[i].b / w[i].a;
        w[i].n = i + 1;
    }

    qsort(w, n, sizeof(w[0]), cmp);

    printf("%lf\n", dissolve(0, n - 1));

    for (i = 0; i < n; i++)
        printf("%d ", w[i].n);

    return 0;
}
