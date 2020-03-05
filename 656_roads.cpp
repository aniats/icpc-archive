#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cassert>

using namespace std;

#define EI vector<edge>::iterator

struct edge
{
    int vTo;
    int cost;
    int id;
};

bool operator< (const edge &l, const edge &r) {
    return l.cost < r.cost;
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int nV, nE, need;
    cin >> nV >> nE >> need;

    vector<vector<edge>> g(nV);

    for (int id = 1; id <= nE; id++)
    {
        int v1, v2, cost;
        cin >> v1 >> v2 >> cost;
        v1--; v2--;
        edge e1 = { v2, cost, id }, e2 = { v1, cost, id };
        g[v1].push_back(e1);
        g[v2].push_back(e2);
    }


    vector<vector<edge>> rc;
    vector<edge> path;

    if (nE == nV)
    { // ring
        for (int i = 0; i < nV; i++)
            if (g[i].size() != 1)
            {
                int cur = i, start = i, prev = -1;
                while (true)
                {
                    int next = -1;
                    rc.push_back(vector<edge>());
                    for (EI j = g[cur].begin(); j < g[cur].end(); j++)
                    {
                        if (j->vTo == prev)
                            continue;
                        if (g[j->vTo].size() == 1)
                            rc.back().push_back(*j);
                        else if (next == -1)
                        {
                            next = j->vTo;
                            path.push_back(*j);
                        }
                    }

                    prev = cur;
                    cur = next;

                    if (cur == start)
                        break;
                }

                break;
            }

        //ring path generation
        priority_queue<int> costs;

        int bestCost = INT_MAX;
        int bFirst = -1, bLast = -1;
        bool isLoop = false;

        for (int first = 0; first < (int)rc.size(); first++)
        {
            while (!costs.empty())
                costs.pop();

            int curCost = 0;
            for (EI j = rc[first].begin(); j < rc[first].end(); j++)
            {
                costs.push(j->cost);
                curCost += j->cost;
            }

            while ((int)costs.size() > need)
            {
                curCost -= costs.top();
                costs.pop();
            }

            if (costs.size() == need && curCost < bestCost)
            {
                bestCost = curCost;
                bFirst = first;
                bLast = first;
            }

            int last = first, rcEdges = 0;
            while (true)
            {
                curCost += path[last].cost;
                rcEdges++;
                last = (last + 1) % (int)rc.size();

                if (first == last)
                    break;
                if (need < rcEdges)
                    break;

                for (EI j = rc[last].begin(); j < rc[last].end(); j++)
                {
                    costs.push(j->cost);
                    curCost += j->cost;
                }

                while ((int)costs.size() > need - rcEdges)
                {
                    curCost -= costs.top();
                    costs.pop();
                }

                if ((int)costs.size() == need - rcEdges && curCost < bestCost)
                {
                    bestCost = curCost;
                    bFirst = first;
                    bLast = last;
                    isLoop = false;
                }
            }
            if (rcEdges <= need)
            {
                while ((int)costs.size() > need - rcEdges)
                {
                    curCost -= costs.top();
                    costs.pop();
                }

                if ((int)costs.size() == need - rcEdges && curCost < bestCost)
                {
                    bestCost = curCost;
                    bFirst = first;
                    bLast = last;
                    isLoop = true;
                }
            }
        }
        priority_queue<edge> edges;
        if (isLoop)
        {
            for (int i = 0; i < (int)rc.size(); i++)
                for (EI j = rc[i].begin(); j < rc[i].end(); j++)
                    edges.push(*j);

            while ((int)edges.size() > need - (int)rc.size())
                edges.pop();

            for (int i = 0; i < (int)rc.size(); i++)
                edges.push(path[i]);
        }
        else
        {
            int i = bFirst, rcEdges = 0;
            while (true)
            {
                for (EI j = rc[i].begin(); j < rc[i].end(); j++)
                    edges.push(*j);
                if (i == bLast)
                    break;
                i = (i + 1) % (int)rc.size();
                rcEdges++;
            }

            while ((int)edges.size() > need - rcEdges)
                edges.pop();

            i = bFirst;
            while (true)
            {
                if (i == bLast)
                    break;
                edges.push(path[i]);
                i = (i + 1) % (int)rc.size();
            }
        }

        while (!edges.empty())
        {
            cout << edges.top().id << endl;
            edges.pop();
        }
    }



    else if (nE == nV - 1)
    { // chain path generation
        for (int i = 0; i < nV; i++)
        {
            int rc_ways = 0;
            if (g[i].size() <= 1)
                continue;
            for (EI j = g[i].begin(); j < g[i].end(); j++)
                if (g[j->vTo].size() > 1)
                    rc_ways++;

            if (rc_ways == 0)
            {
                rc.push_back(g[i]);
                break;
            }
            else if (rc_ways == 1)
            {
                int prev = -1, cur = i;
                while (true)
                {
                    int next = -1;
                    rc.push_back(vector<edge>());

                    for (EI j = g[cur].begin(); j < g[cur].end(); j++)
                    {
                        if (j->vTo == prev)
                            continue;

                        if (g[j->vTo].size() == 1)
                            rc.back().push_back(*j);
                        else if (next == -1)
                        {
                            next = j->vTo;
                            path.push_back(*j);
                        }
                    }

                    if (next == -1)
                        break;

                    prev = cur;
                    cur = next;
                }

                break;
            }
        }


        // chain segment choose
        priority_queue<int> costs;

        int bestCost = INT_MAX;
        int bFirst = -1, bLast = -1;

        for (int first = 0; first < (int)rc.size(); first++)
        {
            while (!costs.empty())
                costs.pop();

            int curCost = 0;
            for (EI j = rc[first].begin(); j < rc[first].end(); j++)
            {
                costs.push(j->cost);
                curCost += j->cost;
            }

            while ((int)costs.size() > need)
            {
                curCost -= costs.top();
                costs.pop();
            }

            if (costs.size() == need && curCost < bestCost)
            {
                bestCost = curCost;
                bFirst = bLast = first;
            }

            for (int last = first + 1; last < (int)rc.size() && last - first <= need; last++)
            {
                curCost += path[last - 1].cost;

                for (EI j = rc[last].begin(); j < rc[last].end(); j++)
                {
                    costs.push(j->cost);
                    curCost += j->cost;
                }

                while ((int)costs.size() > need - (last - first))
                {
                    curCost -= costs.top();
                    costs.pop();
                }

                if ((int)costs.size() == need - (last - first))
                {
                    if (curCost < bestCost)
                    {
                        bestCost = curCost;
                        bFirst = first;
                        bLast = last;
                    }
                }
            }
        }

        assert(bFirst != -1);
        assert(bLast != -1);

        //chain answer regeneration
        priority_queue<edge> edges;
        for (int i = bFirst; i <= bLast; i++)
            for (EI j = rc[i].begin(); j < rc[i].end(); j++)
                edges.push(*j);

        assert(need - bLast + bFirst >= 0);
        while ((int)edges.size() > need - (bLast - bFirst))
            edges.pop();

        for (int i = bFirst; i < bLast; i++)
            edges.push(path[i]);

        while (!edges.empty())
        {
            cout << edges.top().id << endl;
            edges.pop();
        }
    }
}
