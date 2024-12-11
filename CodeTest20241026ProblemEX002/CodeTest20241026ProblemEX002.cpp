#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>
using namespace std;

unordered_set<int> cycleV;
int SN;
void BFS(vector<int>& dis, vector<vector<int>>& graph, int v);
vector<int> nodeDistance(int s_nodes, vector<int> s_from, vector<int> s_to) {

    SN = s_nodes;
    int noe = s_from.size();
    vector<vector<int>> graph(s_nodes);

    vector<int> parent(s_nodes);
    vector<int> rank(s_nodes);
    for (int i = 0; i < s_nodes; ++i)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < noe; ++i)
    {
        int from = s_from[i];
        int to = s_to[i];

        graph[from].push_back(to);
        graph[to].push_back(from);
    }
    vector<int> dis(SN, 0);

    return dis;

}
void BFS1(vector<int>& dis, vector<vector<int>>& graph, int v)
{

}

void BFS(vector<int>& dis, vector<vector<int>>& graph, int v)
{

    vector<bool> visited(SN, false);
    queue<pair<int, int>> q;
    q.push({ v,0 });
    visited[v] = true;
    while (!q.empty())
    {
        auto curq = q.front();
        q.pop();
        int curv = curq.first;
        int curdis = curq.second;

        for (auto nv : graph[curv])
        {// bfs
            if (cycleV.find(nv) != cycleV.end())
            {// we find CycleV
                dis[v] = curdis + 1;// next v
                return;
            }
            if (!visited[nv])
            {
                q.push({ nv,curdis + 1 });
                visited[nv] = true;
            }
        }

    }

}

int main()
{
    vector<int> distances;
    distances = nodeDistance(6, { 0,1,2,2,5,0 }, { 2,0,1,4,1,3 });
    int a = 0;
}