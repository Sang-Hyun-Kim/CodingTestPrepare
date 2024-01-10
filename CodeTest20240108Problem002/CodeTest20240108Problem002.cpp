// 백준 2206번 벽 부수고 이동하기

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <queue>
#include <map>
// 경로를 찾지 못했을 때 반환 -1
// 최소값을 반환
// 2차원 배열 * 벽개수만큼 순회는 시간초과
// dp처럼 현재 벽을 부수었는지 여부에 따라 상태를 나눈다는 아이디어를 이용해보세요. 힌트
// 
using namespace std;
array<int, 4> dx{-1, 1, 0, 0};
array<int, 4> dy{ 0,0,-1,1 };
// '0' == 48, '1'== 49
struct Pos // 2차원으로 풀때 사용했던 구조체 지금은 크게 필요없지만 냅두고 사용했다.
{
    bool operator==(Pos& other) // Pos  구조체끼리의 자료비교를 위한 연산자 오버로딩
    {
        return y == other.y && x == other.x;
    }
    bool operator<(const Pos& other) const // 틀린 코드에서 사용했던 STL::map parent배열(역추적을 위해 선언)에서 요소간의 크기비교를 위해 연산자 오버로딩 
    {
        if (y != other.y)
        {
            return y < other.y;
        }
        return x < other.x;
    }
    int x = 0;
    int y = 0;
};
int BFS(vector<string>& _prob, int _row, int _col);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int row, col;
    cin >> row >> col;
    vector<string> problem(row);
    for (int i = 0; i < row; ++i)
    {
        cin >> problem[i];
    }
    // 한칸씩 나아가면서 벽을 만났을때 해당 벽을 부실지 안부실지 체크
    // 부셨다면 다음 칸부터는 부실 수 없기에 1을 만난다면 사출
    // 안부시면서 나아갔다면 다음에 만나는 1에대해서 안부실지 부실지를 고민
    // 
    // 방문체크: 내가 벽을 한번도 부시지 않고 탐색했을때 방문과 아닐때의 방문이 구분되어야함
    // 즉 방문이 3차원 배열이여야함
    int answer = BFS(problem, row, col);
    cout << answer;
}

int BFS(vector<string>& _prob, int _row, int _col)
{
    // {벽파괴 유무,{x,y}}
    queue<pair<int, Pos>> bfsqueue;
    vector <vector<vector<int>>> visited(2, vector<vector<int>>(_row, vector<int>(_col, 0))); //[0][x][y] . [1][x][y]
    // 벽을 안부신 상황에서의 방문, 벽을 부신 상태에서의 x,y좌표 방문
    // 여기서 방문할때마다 이전 방문에 +1
    // 최종 지점의 visited[][][]값을 반환
    if (_prob[0][0] == 49)
    {
        bfsqueue.push({ 1,{0,0} });
        visited[1][0][0] = 1;
    }
    else
    {
        bfsqueue.push({ 0,{0,0} });
        visited[0][0][0] = 1;
    }
    Pos dest = { _row - 1,_col - 1 };
    
    while (!bfsqueue.empty())
    {
        
        auto current = bfsqueue.front();
        bfsqueue.pop();
        int wall = current.first;
        if (current.second == dest)
        {
            return visited[wall][current.second.x][current.second.y];
        }
        for (int i = 0; i < 4; ++i)
        {
            int nx = current.second.x + dx[i];
            int ny = current.second.y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < _row && ny < _col)
            {
                // wall이 0이나 1이냐에따라 방문처리
                if (visited[wall][nx][ny]) continue; // 이번 벽파괴 유무에 따른 해당 좌표가 0이 아니면 이미 방문한 것 무시
                if (_prob[nx][ny] == 48)
                { // 벽없으면 벽뿌수기 세이브 가능
                    bfsqueue.push({ wall,{nx,ny} });// 이번 벽파괴 여부+좌표
                    visited[wall][nx][ny] = visited[wall][current.second.x][current.second.y] + 1; // 더 하 기 
                }
                else
                { // 벽이 있다
                    if (wall == 0)
                    { // 한번도 부순적없다.
                        bfsqueue.push({ 1,{nx,ny} });
                        // 따로 방문처리 해야함
                        visited[wall][nx][ny] = visited[wall][current.second.x][current.second.y] + 1; // 안부시면 여기서 멈추지만 방문처리는 해놓고
                        visited[1][nx][ny] = visited[wall][current.second.x][current.second.y] + 1; // 부시고나서의 진행을 위해 추가로 방문처리
                    }
                    else
                    {   // 아 이미 한번 부셨다!
                        visited[wall][nx][ny] = visited[wall][current.second.x][current.second.y] + 1; // 뭔갈 부시고 다시 여기오면 방문처리해놓기
                    }
                }
            }
        }
    }

    // 목적지 못찾음
    return -1;
}