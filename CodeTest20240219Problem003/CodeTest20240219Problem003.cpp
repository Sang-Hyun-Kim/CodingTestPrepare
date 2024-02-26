// 백준 13023 ABCDE
// dfs그래프순회를 통한 조건에맞는 깊이찾기
// 방문 초기화 및 실패한 순회에 대한 방문 초기화가 중요
#include <iostream>
#include <vector>
using namespace std;
int ans = 0;
void dfs(int _depth, int _next, vector<vector<int>>& _f, vector<bool>& _visited);
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int v, e;
	cin >> v >> e;
	vector<vector<int>> f(v);
	for (int i = 0; i < e; ++i)
	{
		int f1, f2;
		cin >> f1 >> f2;
		f[f1].push_back(f2);
		f[f2].push_back(f1);
	}
	for (int i = 0; i < v; i++)
	{
		vector<bool> visited(v);
		visited[i] = true;
		dfs(0,i, f, visited);
		if (ans) break;
	}
	cout << ans;

}
void dfs(int _depth, int _next, vector<vector<int>>& _f, vector<bool>& _visited)
{
	if (_depth == 4)
	{
		ans = 1;
		return;
	}

	for (auto& a : _f[_next])
	{
		if (_visited[a]) continue;
		_visited[a] = true;
		dfs(_depth + 1, a, _f, _visited);
		_visited[a]=false;
	}
}