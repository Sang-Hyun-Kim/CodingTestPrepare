// 백준 1520번 내리막길

#include <iostream>
#include <vector>
#include <array>
using namespace std;
array<int, 4> dx = {0,0,-1,1};
array<int, 4> dy = {-1,1,0,0};
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
			
	vector<vector<int>> cache(row, vector<int>(colm, -1));
	int answer = DFS(0, 0, map, cache);
	cout << answer << '\n';
}

int DFS(int i, int j, vector<vector<int>>& _map, vector<vector<int>>& _cache)
{

	if (i == _map.size() - 1 && j == _map[0].size() - 1) return 1;
	if (_cache[i][j] != -1) return _cache[i][j];


	_cache[i][j] = 0;
	for (int p = 0; p < 4; ++p)
	{
		int nx = i + dx[p];
		int ny = j + dy[p];
		if (nx >= 0 && nx < _map.size() && ny >= 0 && ny < _map[0].size())
		{
			if (_map[i][j] > _map[nx][ny])
				_cache[i][j] = _cache[i][j] + DFS(nx, ny, _map, _cache);
		}
			
	}
		
		return _cache[i][j];
		

}