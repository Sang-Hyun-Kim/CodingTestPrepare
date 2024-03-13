// 백준 1949 우수마을
// 음수 가중치가 없는 그래프라서 조건 3번: 인접한 우수마을이 하나라도 있어야한다는 자동 처리된다....
// DFS + DP로 트리 그래프 순회
// Cycle도 없고 음수 가중치도 없어서 쉬웠다.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int DFS(int _cn, int _way, vector<vector<int>>& _routes, vector<vector<int>>& _cache, vector<bool>& _visited, vector<int>& _pop);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int vn = 0;
    cin >> vn;
    vector<int> pop(vn+1, 0);
    for (int i = 1; i <= vn; ++i)
    {
        cin >> pop[i];
    }
    vector<vector<int>> routes(vn+1);

    int src, dst;
    for (int i = 0; i < vn - 1; ++i)
    {
        cin >> src >> dst;
        routes[src].push_back(dst);
        routes[dst].push_back(src);
    }
    vector<vector<int>> cache(vn+1, vector<int>(2, -1));// 0 지정안됨, 1 지정됨
    vector<bool> visited(vn+1, false);

    visited[1] = true;
    int answer = max(DFS(1,0,routes,cache,visited,pop), DFS(1, 1, routes, cache, visited, pop));
    cout << answer;
}

int DFS(int _cn,int _way, vector<vector<int>>& _routes, vector<vector<int>>& _cache, vector<bool>& _visited, vector<int>& _pop)
{
    if (_cache[_cn][_way]!=-1)
    {
        return _cache[_cn][_way];
    }
    else
    {
        // 해당 도시가 지정됨,안됨에따른 계산 결과의 최대값 저장후 반환
        if (_way == 0) // 지정안됨
        {
            _cache[_cn][_way] = 0;
            for (auto nc : _routes[_cn])
            {
                if (!_visited[nc])
                {
                    _visited[nc] = true;
                    _cache[_cn][_way] += max(DFS(nc,0,_routes,_cache,_visited,_pop),DFS(nc,1,_routes,_cache,_visited,_pop));
                    _visited[nc] = false;
                }
            }
            return _cache[_cn][_way];
        }
        else// 이번 도시가 지정됨 : 인구수 포함 필요
        {
            _cache[_cn][_way] = 0;
            for (auto nc : _routes[_cn])
            {
                if (!_visited[nc])
                {
                    _visited[nc] = true;
                    _cache[_cn][_way] += DFS(nc,0,_routes,_cache,_visited,_pop);
                    _visited[nc] = false;
                }
            }
            _cache[_cn][_way] += _pop[_cn];
            return _cache[_cn][_way];
        }
    }
}