#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    vector<int> h(m, 0);
    stack<pair<int, int>> rects;

    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        s.push_back('0');
        for (int j = 0; j < s.size(); j++)
        {
            if (s[j] == '0')
                h[j] = 0;
            else
                h[j]++;

            int sJ = j;
            while (!rects.empty() && h[j] < rects.top().second)
            {
                ans = max(ans, (j - rects.top().first) * rects.top().second);
                sJ = rects.top().first;
                rects.pop();
            }

            if (h[j] > 0 && (rects.empty() || h[j] > rects.top().second))
                rects.push(make_pair(sJ, h[j]));
        }
    }

    cout << ans << endl;
}
