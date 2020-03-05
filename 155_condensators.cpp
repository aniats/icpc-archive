#include <iostream>
#include <cmath>

using namespace std;

const int SIZE = 6;
const double EPS = 0.01;

int ans;
double C;

struct cond {
    double a[SIZE];
};

void next(int n, struct cond a)
{
    for (int i = 0; i < n; i++)
        if (fabs(a.a[i] - C) <= EPS)
            ans = 1;

    if (n == 1)
        return;

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
        {
            struct cond t = a;
            t.a[i] += t.a[j];
            t.a[j] = t.a[n - 1];
            next(n - 1, t);

            t = a;
            t.a[i] = (t.a[i] * t.a[j]) / (t.a[i] + t.a[j]);
            t.a[j] = t.a[n - 1];
            next(n - 1, t);
        }
}

int main()
{
    int n;
    struct cond a;

    freopen("input.txt", "r", stdin);

    cin >> n >> C;
    for (int i = 0; i < n; i++)
        cin >> a.a[i];

    next(n, a);

    puts(ans ? "YES" : "NO");
}
