#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <iomanip>

typedef long double LD;

using namespace std;

struct coord {
    LD x, y;

    coord(LD X = 0, LD Y = 0) {
        x = X; y = Y;
    }

    coord operator+ (coord q) {
        return coord(x + q.x, y + q.y);
    }
    coord operator- (coord q) {
        return coord(x - q.x, y - q.y);
    }
    bool operator== (coord q) {
        return x == q.x && y == q.y;
    }
};

LD vect(coord a, coord b) {
    return a.x * b.y - b.x * a.y;
}

LD dist(coord &a, coord &b) {
    coord v = a - b;
    return sqrt(v.x * v.x + v.y * v.y);
}

int main()
{
    int n;
    cin >> n;
    vector<coord> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i].x >> c[i].y;
        if (c[0].x > c[i].x || (c[0].x == c[i].x && c[0].y > c[i].y))
            swap(c[0], c[i]);
    }

    vector<coord> ans;
    ans.push_back(c[0]);
    while (true) {
        coord cur = ans.back(), b(INT_MAX, INT_MAX);

        for (int i = 0; i < n; i++) {
            if (c[i] == ans.back())
                continue;
            if (b.x == INT_MAX) {
                b = c[i];
                continue;
            }
            if (vect(c[i] - cur, b - cur) > 0)
                b = c[i];
        }

        ans.push_back(b);


        if (ans[0] == ans.back())
            break;
    }

    LD p = 0;
    for (int i = 0; i < ans.size() - 1; i++)
        p += vect(ans[i], ans[i + 1]) / 2;
    cout << fixed << setprecision(0) << p + 1e-6 << endl;
}


