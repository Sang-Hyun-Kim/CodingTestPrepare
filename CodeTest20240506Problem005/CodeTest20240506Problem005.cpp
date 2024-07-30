// 백준 14500 테트로미노 골드 4
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
// 좌표 하나를 중심으로 4방향 어디든지 총 3번 더 움직이면 모든 테트리스 모양이나옴
// DFS 돌면서 점수하나 갱신하고 돌아오는 방식으로 백트래킹 하기

using namespace std;
int N, M;
int answer = 0;
array<int, 4> dx{1,-1,0,0}; // 하 상 우 좌
array<int, 4> dy{0,0,1,-1};

bool InRange(int x, int y);
void DFS(int count, int x, int y, int sum, vector<vector<int>>& board, vector<vector<bool>>& visited, int way);
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	vector<vector<int>> board(N, vector<int>(M, 0));
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cin >> board[i][j];
		}
	}

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{// 모든 칸에대해서 모든 모양 찾기 후 빠져나와서 원복시키기
			vector<vector<bool>> visited(N, vector<bool>(M, false));
			visited[i][j] = true;
			DFS(3, i, j, board[i][j],board, visited,0);
			visited[i][j] = false;//실수 1
		}
	}
	cout << answer;
}

void DFS(int count, int x, int y,int sum, vector<vector<int>>& board,vector<vector<bool>>& visited,int way)
{
	if (count <= 0)
	{//4칸 탐색끝
		answer = max(sum, answer);
		return;
	}
	else
	{
		// T를 찾는 백트래킹, 이때 way를 사용한다
		// 0 하 1 상 2 우 3 좌
		if (count == 2)
		{
			if (way == 0)
			{// 이전에 하(-1 ,0)으로 옴 ㅗ
			// 현재 좌표에서 0,-1, 0,1 더한 좌표를 점검
				if (InRange(x, y - 1) && InRange(x, y + 1))
				{// 내려온 곳 양옆 좌표가 좌표 안쪽 인 경우
					sum += board[x][y - 1] + board[x][y + 1];// 3칸의 합
					answer = max(answer, sum);
					// 자 이제 count가 2여도 나아가야하는 좌표계산을 위해 원복
					sum -= board[x][y - 1] + board[x][y + 1];
				}
			}
			else if (way == 1)
			{
				if (InRange(x, y - 1) && InRange(x, y + 1))
				{
					sum += board[x][y - 1] + board[x][y + 1];// 3칸의 합
					answer = max(answer, sum);
					sum -= board[x][y - 1] + board[x][y + 1];
				}
			}
			else if (way == 2)
			{
				if (InRange(x-1, y) && InRange(x+1, y))
				{
					sum += board[x-1][y] + board[x+1][y];// 3칸의 합
					answer = max(answer, sum);
					sum -= board[x-1][y] + board[x+1][y];
				}
			}
			else if(way ==3)
			{
				if (InRange(x - 1, y) && InRange(x + 1, y))
				{
					sum += board[x - 1][y] + board[x + 1][y];// 3칸의 합
					answer = max(answer, sum);
					sum -= board[x - 1][y] + board[x + 1][y];
				}
			}
		}
		// 4번 찾는 백트래킹
			// 4방향 하나씩 해서 걍 찾기만 하면됨
		for (int i = 0; i < 4; ++i)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (InRange(nx, ny))
			{
				if (!visited[nx][ny])
				{
					visited[nx][ny] = true;
					DFS(count - 1, nx, ny, sum + board[nx][ny], board, visited, i);
					visited[nx][ny] = false;
				}
			}
		}
	}
}

bool InRange(int x,int y)
{
	if (x >= 0 && y >= 0 && x < N && y < M)
		return true;
	return false;
}