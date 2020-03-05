#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

int get_hash(const string &s)
{
	long long h = 0, BASE = 1000000007;
	for (int i = 0; i < (int)s.size(); i++)
		h = (h * 101 + s[i] - 'a' + 1) % BASE;
	return (int)h;
}

queue<string> states;
map<int, int> dp;

void check(const string &s, int w)
{
	int cur_h = get_hash(s);
	if (dp.count(cur_h) == 0)
	{
		dp[cur_h] = w + 1;
		states.push(s);
	}
}

void permutate(string &s)
{
	int ch = get_hash(s);

	int es = s.find('#');
	if (es == string::npos)
		return;

	if (es != 3 && es != 7)
	{
		swap(s[es], s[es + 1]);
		check(s, dp[ch] + 1);
		swap(s[es], s[es + 1]);
	}

	if (es != 0 && es != 4)
	{
		swap(s[es], s[es - 1]);
		check(s, dp[ch] + 1);
		swap(s[es], s[es - 1]);
	}

	swap(s[es], s[(es + 4) % 8]);
	check(s, dp[ch] + 1);
	swap(s[es], s[(es + 4) % 8]);
}

int main()
{
	freopen("input.txt", "r", stdin);
	string src, res, t;
	cin >> src >> t;
	src += t;

	cin >> res >> t;
	res += t;
	int nhash = get_hash(res);

	dp[get_hash(src)] = 0;
	states.push(src);

	while (!states.empty() && dp.count(nhash) == 0)
	{
		string cur = states.front();
		states.pop();
		permutate(cur);
	}

	if (states.empty() && !dp.count(nhash))
		cout << -1;
	else
		cout << dp[nhash] / 2;
}
