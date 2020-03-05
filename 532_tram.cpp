#include <iostream>
#include <queue>
#include <vector>

typedef long long dll;

using namespace std;

const int SIZE = 200000;
enum {SIT, STAND, OUT};

dll freeplaces, curPleasure;
vector<dll> df(SIZE, 0);
vector<int> state(SIZE, OUT);

struct top_greater
{
	bool operator() (int &l, int &r)
	{
		return df[l] < df[r];
	}
};

struct top_smaller
{
	bool operator() (int &l, int &r)
	{
		return df[l] > df[r];
	}
};

priority_queue<int, vector<int>, top_greater> standQ;
priority_queue<int, vector<int>, top_smaller> sitQ;

void deal_with_leaving(int pnum)
{
	while (!standQ.empty() && state[standQ.top()] == OUT)
		standQ.pop();
	while (!sitQ.empty() && state[sitQ.top()] == OUT)
		sitQ.pop();

	if (state[pnum] == SIT)
	{
		curPleasure -= df[pnum];
		if (!standQ.empty())
		{
			int best_stander = standQ.top();
			standQ.pop();
			sitQ.push(best_stander);
			curPleasure += df[best_stander];
			state[best_stander] = SIT;
		}
		else
			freeplaces++;
	}

	state[pnum] = OUT;
}

void deal_with_entering(int pnum)
{
	while (!standQ.empty() && state[standQ.top()] == OUT)
		standQ.pop();
	while (!sitQ.empty() && state[sitQ.top()] == OUT)
		sitQ.pop();

	if (freeplaces > 0)
	{
		curPleasure += df[pnum];
		state[pnum] = SIT;
		freeplaces--;
		sitQ.push(pnum);
	}
	else if (!sitQ.empty() && df[pnum] > df[sitQ.top()])
	{
		int worst_sitter = sitQ.top();
		sitQ.pop();
		curPleasure += df[pnum] - df[worst_sitter];

		standQ.push(worst_sitter);
		sitQ.push(pnum);

		state[pnum] = SIT;
		state[worst_sitter] = STAND;
	}
	else
	{
		state[pnum] = STAND;
		standQ.push(pnum);
	}
}

dll ans, n, nStops;

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> n >> freeplaces >> nStops;

	vector<vector<int>> inS(SIZE, vector<int>()), outS(SIZE, vector<int>());

	for (int i = 1; i <= n; i++)
	{
		dll sitH, standH;
		int st, fn;
		cin >> sitH >> standH >> st >> fn;
		if (sitH > standH)
		{
			inS[st].push_back(i);
			outS[fn].push_back(i);
			df[i] = sitH - standH;
		}
		ans += standH * (fn - st);
	}

	for (int i = 1; i < nStops; i++)
	{ 
		for (vector<int>::iterator j = outS[i].begin(); j < outS[i].end(); ++j)
			deal_with_leaving(*j);

		for (vector<int>::iterator j = inS[i].begin(); j < inS[i].end(); ++j)
			deal_with_entering(*j);

		ans += curPleasure;
	}

	cout << ans << endl;
}
