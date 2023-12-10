// 백준 2667 단지번호 붙이기

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 각 좌표에 대한 BFS 실행 후
// 0 미만, N이상일 경우 종료
// 이미 탐색한 좌표라면 종료
// 값이 0이라면 종료
// 상하좌우에 대해 실행
// Queue에 넣고
void BFS(int _N, vector<vector<int>>& _graph, vector<vector<bool>>& _visited, vector<int>& _numofDanchi, int i, int j);
int main()
{
	int N=0;
	int danchi=0;
	vector<int> numofDanchi;
	
	cin >> N;
	cin.ignore();
	string string;
	vector<vector<bool>> visited(N, vector<bool>(N, false));
	vector<vector<int>> graph(N, vector<int>(N, 0));
	
	for (int i = 0; i < N; ++i)
	{
		getline(cin, string);
		for (int j = 0; j < N; ++j)
		{
			graph[i][j] =  string[j]-48;
		}
	}
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			//좌표별 BFS
			BFS(N, graph, visited, numofDanchi, i, j);
		}
	}
	sort(numofDanchi.begin(), numofDanchi.end());
	cout << numofDanchi.size() << endl;
	for (auto i : numofDanchi)
	{
		cout << i << endl;
	}
}
// 아파트 단지 좌표,방문 여부, 단지 저장 벡터
void BFS(int _N,vector<vector<int>>& _graph, vector<vector<bool>>& _visited, vector<int>& _numofDanchi,int i,int j)
{
	// 방문했다면리턴
	if (_visited[i][j] == true) return;
	// 값이 없다면 0
	if (_graph[i][j] == 0) return;

	queue<pair<int,int>> dqueue;
	int count = 0;
	dqueue.push({ i,j });
	

	vector<vector<bool>> visitedbuilding(_N, vector<bool>(_N, false)); // bfs 순회간의 단지 찾기

	while (!dqueue.empty())
	{
		auto currentvalue = dqueue.front();
		dqueue.pop();
		// 좌표 내의 값에 대해서
		if (currentvalue.first >=0 && currentvalue.first < _N
			&& currentvalue.second >= 0 && currentvalue.second < _N)
		{
			// 방문했다면
			if (visitedbuilding[currentvalue.first][currentvalue.second]) continue;
			// 해당 좌표가 이번 순회간에 발견 되지 않았다면
			// 값이 1이라면
			
			if (_graph[currentvalue.first][currentvalue.second] == 1)
			{
				count++;

				dqueue.push({ currentvalue.first - 1 ,currentvalue.second}); // 상
				dqueue.push({ currentvalue.first + 1 ,currentvalue.second });// 하
				dqueue.push({ currentvalue.first ,currentvalue.second - 1 });// 좌
				dqueue.push({ currentvalue.first ,currentvalue.second + 1});// 우
			}
			else
			{// 0 이라면
				continue;
			}
			_visited[currentvalue.first][currentvalue.second] = true;
			visitedbuilding[currentvalue.first][currentvalue.second] = true;

		}		
	}
	_numofDanchi.push_back(count);
	return;
}
