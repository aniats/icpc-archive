#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct point
{
    int x;
    int cur_opened;
    int is_st;
};

bool cmp(const point &p1, const point &p2)
{
    return p1.x < p2.x;
}

int find_left_closest(int x, vector<point> &sg)
{
    int L = 0, R = sg.size() - 1;

    if (sg[0].x > x || sg[sg.size() - 2].x <= x)
        return 0;


    while (R - L > 1)
    {
        int M = L + (R - L) / 2;
        if (sg[M].x > x)
            R = M;
        else
            L = M;
    }

    return (sg[R].x == x) ? sg[R].cur_opened : sg[L].cur_opened;
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<point> sg;
    for (int i = 0; i < n; i++)
    {
        int x1, x2;
        cin >> x1 >> x2;
        if (x1 > x2)
            swap(x1, x2);

        sg.push_back(point{ x1, -1, 1 });
        sg.push_back(point{ x2 + 1, -1, -1 });
    }

    sg.push_back(point{ INT_MAX, -1, -1 });

    sort(sg.begin(), sg.end(), cmp);

    int cur_opened = 1;
    sg[0].cur_opened = 1;
    for (int i = 1; i < sg.size(); i++)
    {
        if (sg[i].x == sg[i - 1].x)
        {
            cur_opened += sg[i].is_st;
            continue;
        }

        for (int j = i - 1; j >= 0 && sg[j].cur_opened == -1; j--)
            sg[j].cur_opened = cur_opened;

        cur_opened += sg[i].is_st;
        sg[i].cur_opened = cur_opened;
    }

    for (int i = 0; i < m; i++)
    {
        int x; 
        cin >> x;

        cout << find_left_closest(x, sg) << " ";
    }
}
