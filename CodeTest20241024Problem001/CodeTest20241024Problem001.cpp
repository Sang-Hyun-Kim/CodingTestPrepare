// 코드트리 실력 진단 BFS 마을 구분 문제
// 첫 진입지점 방문체크를 안하는 대참사때문에 1개씩 더 카운트 되는 문제로 20분안에 못품 아오
// => 함수 진입 이전에 true해야하는걸 이후에 true체크하는 대참사
// 그외로 queue에서 뺀 x,y를 더해야하는데 함수의 인자로 들어온 첫시작지점 x,y를 더하는 실수는 풀면서 찾아냈다.


#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <queue>
using namespace std;

array<int, 4> dx = { 0,1,0,-1 };
array<int, 4> dy = { 1,0,-1,0 };
void BFS(int x, int y, vector<vector<bool>>& visited, vector<vector<int>>& board, vector<int>& AB);
int N;
bool InRange(int x, int y)
{
    if (0 <= x && x < N && 0 <= y && y < N)
        return true;
    else
        return false;
}
int main() {

    cin >> N;
    vector<vector<int>> board(N, vector<int>(N, 0));
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> board[i][j];
        }
    }

    vector<int> AB(2, 0);
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (board[i][j] != 0 && visited[i][j] == false)
            {
                //BFS호출
                visited[i][j] = true;
                BFS(i, j, visited, board, AB);

            }
        }
    }

    cout << AB[0] << " " << AB[1];
    return 0;
}
void BFS(int x, int y, vector<vector<bool>>& visited, vector<vector<int>>& board, vector<int>& AB)
{
    int count = 0;
    queue<pair<int, int>> q;
    bool AFlag = false;
    // 1이상만 찾다가 2,3 확인
    q.push({ x,y });

    while (!q.empty())
    {
        auto curxy = q.front();
        q.pop();
        if (board[curxy.first][curxy.second] == 2)
        {
            AFlag = true;
        }
        count++;

        for (int i = 0; i < 4; i++)
        {
            int cx = curxy.first + dx[i]; 
            int cy = curxy.second + dy[i];
            if (InRange(cx, cy))
            {
                if (board[cx][cy] != 0 && !visited[cx][cy])
                {
                    q.push({ cx,cy });
                    visited[cx][cy] = true;
                }
            }
        }

    }


    if (AFlag)
    {
        AB[0] = count;
    }
    else {
        AB[1] = count;
    }
}