#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>

using namespace std;

struct point {
	int x, y;
};

bitset<256> get_set_ptr(vector<vector<bitset<256>>>& h1, vector<vector<bitset<256>>>& h2, int i, int j, int k)
{
	if (h1[i][j].test(k))
		return h1[i][j];
	else
		return h2[i][j];
}

int main()
{
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;

	vector<struct point> p(n);

	for (int i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y;

	vector<vector<bitset<256>>> h1(n, vector<bitset<256>>(n));
	vector<vector<bitset<256>>> h2(n, vector<bitset<256>>(n));

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			for (int k = 0; k < n; k++)
				if (k != i && k != j)
				{
					int v = (p[j].x - p[i].x)  * (p[k].y - p[i].y) - (p[k].x - p[i].x) * (p[j].y - p[i].y);
					assert(v != 0);
					if (v > 0)
						h1[i][j].set(k);
					else
						h2[i][j].set(k);
				}

	int cnt = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			for (int k = j + 1; k < n; k++)
			{
				bitset<256> setIJ = get_set_ptr(h1, h2, i, j, k);
				bitset<256> setIK = get_set_ptr(h1, h2, i, k, j);
				bitset<256> setJK = get_set_ptr(h1, h2, j, k, i);

				cnt += (setIJ & setJK & setIK).none();
			}

	cout << cnt << endl;
}
