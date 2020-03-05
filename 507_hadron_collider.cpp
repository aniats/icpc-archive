#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define DEBUG
#define PSIZE 4
#define SIZE 100

int destr[PSIZE][PSIZE], n;

struct cond {
    int a[PSIZE];
};
typedef struct cond tcond;

tcond ans[SIZE];
int last_ans;

int same_cond(tcond a, tcond b)
{
    int i;
    for (i = 0; i < n; i++)
        if (a.a[i] != b.a[i])
            return 0;

    return 1;
}

void react(tcond a)
{
    int i, j, reacted = 0;

    for (i = 0; i < n; i++)
        for (j = i; j < n; j++)
        {
            if (i != j)
            {
                if (a.a[i] > 0 && a.a[j] > 0 && destr[i][j])
                {
                    a.a[j]--;
                    react(a);
                    a.a[j]++;
                    reacted = 1;
                }
                if (a.a[i] > 0 && a.a[j] > 0 && destr[j][i])
                {
                    a.a[i]--;
                    react(a);
                    a.a[i]++;
                    reacted = 1;
                }
            }
            else if (destr[i][i] && a.a[i] > 1)
            {
                a.a[i]--;
                react(a);
                a.a[i]++;
                reacted = 1;
            }
        }

    if (!reacted)
    {
        for (i = 0; i < last_ans; i++)
            if (same_cond(a, ans[i]))
                break;
        if (i == last_ans)
            ans[last_ans++] = a;
    }
}

int main()
{
    int i, j;
    tcond st;
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
#endif
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &st.a[i]);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &destr[i][j]);

    react(st);

    printf("%d\n", last_ans);

    for (i = 0; i < last_ans; i++)
    {
        for (j = 0; j < n; j++)
            printf("%d ", ans[i].a[j]);
        printf("\n");
    }


    return 0;
}
