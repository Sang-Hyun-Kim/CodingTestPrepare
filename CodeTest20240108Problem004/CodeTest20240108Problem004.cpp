// 백준 2146 번 다리 만들기

#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>
#include <climits>
// BFS 두 번 돌기
// 1 : 그룹화
// 2 : 각 좌표별 다른 그룹까지의 거리 측정 후 최소값 반환
using namespace std;

array<int, 4> dx{ -1,1,0,0} ;
array<int, 4> dy{ 0,0,-1,1 };
void Grouping(vector<vector<int>>& board);
int Bridge(vector<vector<int>>& board);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int bsize;
    cin >> bsize;

    vector<vector<int>> board(bsize, vector<int>(bsize, 0));
    for (int i = 0; i < bsize; ++i)
    {
        for (int j = 0; j < bsize; ++j)
        {
            cin >> board[i][j];
        }
    }

    Grouping(board); // 그룹화 진행
    cout << Bridge(board);
}

void Grouping(vector<vector<int>>& board)
{
    int size = board.size();
    int group = 1;
    vector<vector<bool>> visited(size, vector<bool>(size,0));
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (board[i][j] == 0) continue;
            if (visited[i][j]) continue;
            group++;
            queue<pair<int, int>> bfsq;
            bfsq.push({ i,j });
            visited[i][j] = true;
            while (!bfsq.empty())
            {
                auto current = bfsq.front();
                bfsq.pop();
                
                board[current.first][current.second] = group;
                for (int k = 0; k < 4; ++k)
                {
                    int nx = current.first + dx[k];
                    int ny = current.second + dy[k];
                    if (nx >= 0 && ny >= 0 && nx < size && ny < size)
                    {
                        if (visited[nx][ny]) continue;
                        if (!board[nx][ny]) continue;
                        bfsq.push({ nx,ny });
                        visited[nx][ny] = true;
                    }
                }
            }
            
        }
    }
}

int Bridge(vector<vector<int>>& board)
{
    // 다른 그룹을 만날때까지 큐에 좌표 + 지금까지의 거리
    int size = board.size();
    int mini = INT_MAX;
    
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (board[i][j] == 0) continue;
            
            vector<vector<bool>> visited(size, vector<bool>(size, 0));
            queue<pair<int,pair<int, int>>> bfsq;
            bfsq.push({ -1,{ i,j } });
            int currentgroup = board[i][j];
            visited[i][j] = true;
            
            while (!bfsq.empty())
            {
                auto current = bfsq.front();
                int length = current.first;
                int cx = current.second.first;
                int cy = current.second.second;
                bfsq.pop();
                if (board[cx][cy] != currentgroup && board[cx][cy] != 0) 
                {
                    mini = min(mini, length);
                    break; 
                }


                for (int k = 0; k < 4; ++k)
                {
                    int nx = cx + dx[k];
                    int ny = cy + dy[k];
                    if (nx >= 0 && ny >= 0 && nx < size && ny < size)
                    {
                        if (visited[nx][ny]) continue;
                        if (board[nx][ny] == currentgroup) continue;
                        bfsq.push({ length + 1,{nx, ny} });
                        visited[nx][ny] = true;
                    }
                }
            }

        }
    }
    return mini;
}