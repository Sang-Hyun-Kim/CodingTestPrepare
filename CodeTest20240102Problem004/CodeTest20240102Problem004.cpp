// 백준 2533 사회망 서비스

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
void Caching(int x, vector<vector<int>>& _cache, vector<vector<int>>& _graph, vector<bool>& _visited);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int nodeNum;
    cin >> nodeNum;
    vector<vector<int>> graph(nodeNum+1, vector<int>());
    for (int i = 0; i < nodeNum - 1; ++i)
    {
        int src, dst;
        cin >> src >> dst;
        graph[src].push_back(dst);
        graph[dst].push_back(src);
    }
    vector<vector<int>> cache(nodeNum + 1, vector<int>(2,INT_MAX));
    vector<bool> visited(nodeNum+1,false);
    Caching(1,cache,graph,visited);
    int answer = min(cache[1][0], cache[1][1]);
    cout << answer << endl;
}

void Caching(int x, vector<vector<int>>& _cache, vector<vector<int>>& _graph, vector<bool>& _visited)
{
    // [x][0]: 일반인 [x][1] 얼리어답터
    // 마지막 노드가 0인경우 0 반환, 1인경우 1반환
    
    _cache[x][0] = 0;
    _cache[x][1] = 1;
    _visited[x] = true;

   for (auto a : _graph[x])
   {
       if (_visited[a]) continue;
       Caching(a, _cache, _graph, _visited);
       _cache[x][0] += _cache[a][1];
       _cache[x][1] += min(_cache[a][0], _cache[a][1]);
   }

}
