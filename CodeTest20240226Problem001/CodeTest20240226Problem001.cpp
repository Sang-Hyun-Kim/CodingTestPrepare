// 백준 2157번 여행
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
// 바텀업, dfs, 방문처리, dp
// 다풀어놓고 잔실수로 너무 오래 풀었다.
using namespace std; 
int Caching(vector<vector<pair<int, int>>>& _routes, vector<vector<int>>& _cache, int _jump, int _citynum, int _dst, int _max);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int c, v, k;
    cin >> c >> v >> k;

    vector<vector<pair<int,int>>> routes(c+1);
    for (int i = 0; i < k; ++i)
    {
        int sr, de, sc;
        cin >> sr >> de >> sc;
        routes[sr].push_back({ de,sc });
    }
    vector<vector<int>> cache(c+1,vector<int>(v+1,0));// [도시번호];
    int answer=Caching(routes,cache,1,1,c,v+1);

    cout << answer;
}

int Caching(vector<vector<pair<int, int>>>& _routes, vector<vector<int>>& _cache, int _jump, int _citynum,int _dst,int _max)
{

    if (_jump >= _max)
    {
        return INT_MIN;
    }
    if (_citynum == _dst)
    {
        return 0;
    }


    if (_cache[_citynum][_jump] != 0)
    {
        return _cache[_citynum][_jump];
    }
    else
    {
        _cache[_citynum][_jump] = INT_MIN;
        for (auto nextcity : _routes[_citynum])
        {
            int ncnum = nextcity.first;
            int nval = nextcity.second;
            if (ncnum > _citynum)
            {
                _cache[_citynum][_jump] = max(_cache[_citynum][_jump],Caching(_routes,_cache,_jump+1,ncnum,_dst,_max)+nval);
            }
        }
        return _cache[_citynum][_jump];
    }
}