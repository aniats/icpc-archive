#include <stdio.h>

const int RADIX = 1000;
const int SIZE = 501;

struct longnum {
    int a[SIZE];
    int l;
};

int p[SIZE];

void add_primes(int sign, int fact)
{
    int i, cd;

    for (i = 2; i <= fact; i++)
    {// добавляем в разложение fact
        int num = i;
        for (cd = 2; num > 1; cd++)
            while (num % cd == 0)
            {
                p[cd] += sign;
                num /= cd;
            }
    }
}


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

void long_short_mult(struct longnum *num, int mult)
{
    int i, rest = 0;
    for (i = 0; i < num->l || rest > 0; i++)
    {
        num->a[i] = num->a[i] * mult + rest;
        rest = num->a[i] / RADIX;
        num->a[i] %= RADIX;
    }

    num->l = i;
}


int main()
{
    int x, k, i, j;
    struct longnum a;

    scanf("%d %d", &x, &k);  x /= 5;

    add_primes(+1, k + x);
    add_primes(-1, x);
    add_primes(-1, k);

    init(&a, 1);

    for (i = 2; i < SIZE; i++)
        for (j = 0; j < p[i]; j++)
            long_short_mult(&a, i);

    long_print(&a);

    return 0;
}


