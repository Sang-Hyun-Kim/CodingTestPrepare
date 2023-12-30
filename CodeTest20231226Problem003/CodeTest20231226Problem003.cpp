// 백준 1520번 내리막길

#include <iostream>
#include <vector>

using namespace std;

int DFS(int i, int j, vector<vector<int>>& _map, vector<vector<int>>& _cache);
int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int row, colm;
	cin >> row >> colm;
	vector<vector<int>> map(row,vector<int>(colm,0));
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < colm; ++j)
			cin >> map[i][j];
			
	vector<vector<int>> cache(row, vector<int>(colm, 0));
	int answer = DFS(0, 0, map, cache);
	cout << answer << '\n';
}

int DFS(int i, int j, vector<vector<int>>& _map, vector<vector<int>>& _cache)
{
	if (i >= _map.size() || j >= _map[0].size()) return 0;
	if (i == _map.size() - 1 && j == _map[0].size() - 1) return 1;
	if (_cache[i][j] > 0) return _cache[i][j];
	else
	{
		bool routecheck = false;
		if (i == _map.size() - 1)
		{
			if (_map[i][j] > _map[i][j + 1])
			{
				_cache[i][j] += DFS(i, j+1, _map, _cache);
				routecheck = true;
			}
		}
		else
		{
			if (_map[i][j] > _map[i + 1][j])
			{
				_cache[i][j] += DFS(i + 1, j, _map, _cache);
				routecheck = true;
			}
		}

		if (j == _map[0].size() - 1)
		{
			if (_map[i][j] > _map[i + 1][j])
			{
				_cache[i][j] += DFS(i + 1, j, _map, _cache);
				routecheck = true;
			}
		}
		else
		{
			if (_map[i][j] > _map[i][j + 1])
			{
				_cache[i][j] += DFS(i, j+1, _map, _cache);
				routecheck = true;
			}
		}
		
		if (!routecheck) return 0;
		else
		{
			return _cache[i][j];
		}
	}
}