// 카카오 인턴쉽 2020 경주로 건설
// 프로그래머스
// 풀이는 다양할 것같은데 조건설정을 못해서 너무 틀리고 헤맴
// 결국엔 출발,도착지가 정해져있다는 것을 활용,
// 우선순위 큐에 가중치를 오름차순으로 정렬해서
// 다익스트라 변형으로 풀었다.
// 문제의 조건을 너무 어렵게 해석해 DP+DFS로 풀려다가 너무 틀려서 포기(4차원 배열의 cache까지 만듬)
// 최단가격의 출발지를 도착지에서부터 찾는다면 풀린다=> 다익스트라 
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
using namespace std;
int bsize = 0;
enum Vel
{
    RIGHT, DOWN, LEFT, UP// 0,1,2,3
};
array<int, 4> dx = {0,1,0,-1};
array<int, 4> dy = {1,0,-1,0};

int BFS(int _x, int _y, vector<vector<int>>& _board, vector<vector<vector<bool>>>& _visited);
bool InRange(int x,int y);
int solution(vector<vector<int>> board) {
    int answer = 0;
    bsize = board.size();

    vector<vector<vector<bool>>> visited(bsize, vector<vector<bool>>(bsize,vector<bool>(4, false)));
    // 우, 하에 대한 방향 계산 시작
    answer = BFS(bsize - 1, bsize - 1, board, visited);
    return answer;
}

int BFS(int _x, int _y, vector<vector<int>>& _board, vector<vector<vector<bool>>>& _visited)
{
    priority_queue<pair<int, pair<int, pair<int, int>>>, vector<pair<int, pair<int, pair<int, int>>>>, greater<pair<int, pair<int, pair<int, int>>>>> pq;// 가중치, 좌표,방향
    _visited[_x][_y][0] = true;
    _visited[_x][_y][1] = true;
    _visited[_x][_y][2] = true;
    _visited[_x][_y][3] = true;
    int price = 0;
    if(_board[_x][_y-1]!=1)
        pq.push({ 100,{2,{_x, _y-1}} });
    if(_board[_x-1][_y]!=1)
        pq.push({ 100,{3,{_x-1, _y}} });

    while (!pq.empty())
    {
        auto cur = pq.top();
        int cx = cur.second.second.first;
        int cy = cur.second.second.second;
        int cval = cur.first;
        int cvel = cur.second.first;
        pq.pop();
        if (cx == cy && cx == 0)
        {
            price = cval;
            break;
        }

        for (int i = 0; i < 4; ++i)
        {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (InRange(nx, ny))
            {
                if (_board[nx][ny] != 1 && !_visited[nx][ny][i])
                {
                    if (i % 2 == cvel % 2) // 직선
                    {
                        pq.push({ cval + 100,{i,{nx,ny}} });
                    }
                    else // 코너
                    {
                        pq.push({ cval + 600,{i,{nx,ny}} });
                    }
                    _visited[nx][ny][i] = true;
                }
            }
        }
    }
    return price;

}

bool InRange(int x, int y)
{
    if (x >= 0 && x < bsize && y >= 0 && y < bsize)
    {
        return true;
    }
    return false;
}
int main()
{
    vector<vector<int>> board{  {0, 0, 0, 0, 0, 0, 0, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 1, 0, 0},
                                {0, 0, 0, 0, 1, 0, 0, 0},
                                {0, 0, 0, 1, 0, 0, 0, 1},
                                {0, 0, 1, 0, 0, 0, 1, 0},
                                {0, 1, 0, 0, 0, 1, 0, 0},
                                {1, 0, 0, 0, 0, 0, 0, 0} };
    //vector<vector<int>> board{ {0, 0, 1, 0},
    //                        {0, 0, 0, 0},
    //                        {0, 1, 0, 1},
    //                        {1, 0, 0, 0},
    //};

    int answer = solution(board);
    std::cout << answer;
}