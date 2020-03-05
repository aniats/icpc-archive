#include <iostream>
#include <string>

using namespace std;

int min_found, max_found, seg_for_dig[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
string min_s(100, '0'), max_s(100, '0'), s(100, '0');

void bruteforce_min(int cp, int lp, int ls)
{
    if (lp == 0 && ls == 0)
    {
        min_s = s;
        min_found = 1;
        return;
    }

    if (lp * 2 > ls || ls > 7 * lp)
        return;

    for (int i = 0; i < 10 && !min_found; i++)
    {
        s[cp] = i + 48;
        bruteforce_min(cp + 1, lp - 1, ls - seg_for_dig[i]);
    }
}

void bruteforce_max(int cp, int lp, int ls)
{
    if (lp == 0 && ls == 0)
    {
        max_s = s;
        max_found = 1;
        return;
    }

    if (lp * 2 > ls || ls > 7 * lp)
        return;

    for (int i = 9; i >= 0 && !max_found; i--)
    {
        s[cp] = i + 48;
        bruteforce_max(cp + 1, lp - 1, ls - seg_for_dig[i]);
    }
}

int main()
{
    int n, k;
    cin >> n >> k;

    min_s.resize(n);
    max_s.resize(n);
    s.resize(n);

    for (int i = 1; i < 10 && !min_found; i++)
    {
        s[0] = i + 48;
        bruteforce_min(1, n - 1, k - seg_for_dig[i]);
    }

    if (!min_found)
    {
        cout << "NO SOLUTION" << endl;
        return 0;
    }

    for (int i = 9; i > 0 && !max_found; i--)
    {
        s[0] = i + 48;
        bruteforce_max(1, n - 1, k - seg_for_dig[i]);
    }

    cout << min_s << endl << max_s << endl;
}
