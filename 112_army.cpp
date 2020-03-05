#include <iostream>

using namespace std;

const int SIZE = 10010;

int ans, buffer[SIZE], a[SIZE];

void merge(int s1, int f1, int s2, int f2)
{
    int cur_in_sorted = s1, t_st = s1;

    while (s1 <= f1 && s2 <= f2)
    {
        if (a[s2] < a[s1])
        {
            ans += f1 - s1 + 1;
            buffer[cur_in_sorted++] = a[s2++];
        }
        else
            buffer[cur_in_sorted++] = a[s1++];
    }

    while (s1 <= f1)
        buffer[cur_in_sorted++] = a[s1++];

    while (s2 <= f2)
        buffer[cur_in_sorted++] = a[s2++];

    for (int i = t_st; i <= f2; i++)
        a[i] = buffer[i];
}

void merge_sort(int st, int fn)
{
    if (st == fn)
        return;

    int mid = st + (fn - st) / 2;

    merge_sort(st, mid);
    merge_sort(mid + 1, fn);

    merge(st, mid, mid + 1, fn);
}

int main()
{
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> a[j];

        merge_sort(0, n - 1);
    }

    cout << ans << endl;
}
