#include <stdio.h>

#define llu unsigned long long
#define SIZE 100
#define RADIX 1000

struct longnum {
    int a[SIZE];
    int l;
};


void init(struct longnum *num, llu val)
{
    int i;
    for (i = 0; val > 0; i++)
    {
        num->a[i] = (int)(val % RADIX);
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
        // нули
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


int main()
{
    llu n, i;
    struct longnum ans, pre_up, cur;

    scanf("%I64u", &n);
    init(&ans, 1);
    init(&pre_up, 0);
    for (i = 2; i <= n; i++)
    {
        init(&cur, (i + 1) * i / 2);
        long_long_sum(&ans, &cur);

        init(&cur, i / 2);
        long_long_sum(&ans, &cur);

        long_long_sum(&ans, &pre_up);

        long_long_sum(&pre_up, &cur);
    }

    long_print(&ans);

    return 0;
}
