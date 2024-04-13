// 백준 17135 캐슬 디펜스
#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <set>
#include <algorithm>
#define OUT // 아무 의미 없고 가독성을 위해 만든 매크로, 해당 함수의 인자로 들어갈때 OUT이 붙어있는 경우엔 함수의 결과로 해당 인자의 값이 변경됨을 명시
using namespace std;
int answer = 0;
int N, M, D;
int ecnt = 0;
array<int, 3> dx{ 0,-1,0 };
array<int, 3> dy{ -1,0,1 };
struct compare
{
    bool operator()(pair<int,pair<int,int>>& a, pair<int,pair<int,int>>& b)
    {
        if (a.first == b.first)
        {
            if (a.second.second == b.second.second)
                return a.second.first > b.second.first;
            return a.second.second > b.second.second;
        }
        return a.first > b.first;
    }
};
bool InRange(int x, int y);
void Shooting(vector<pair<int, int>> curarchers, OUT vector<vector<int>>& board, OUT int& curenemycnt, OUT int& kp);
void Move(OUT vector<vector<int>>& board, OUT vector<pair<int, int>>& curarchers, OUT int& curenemycnt);
void Game(OUT vector<vector<int>>& board);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> D;
    vector<vector<int>> board(N, vector<int>(M, 0));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> board[i][j];
            if (board[i][j] == 1) ecnt++;
        }
    }

    //ecnt와 curecnt를 활용해서 게임 종료를 판단할 예정
    Game(board);
    cout << answer;
}
bool InRange(int x, int y)
{
    if (x >= 0 && y >= 0 && x < N && y < M)
        return true;
    return false;

}
// 궁수의 좌표 인자 3개와 넘겨받은 현재 board 상태를 기준으로 각 궁수의 가장 가까운 적을 찾아 좌표 저장 후 한번에 삭제한 새로운 board 상태를 넘겨주는 함수
void Shooting(vector<pair<int,int>> curarchers, OUT vector<vector<int>>& board, OUT int& curenemycnt, OUT int& kp)
{
    set<pair<int, int>> targets;
    // 스캔 처리 하기
    for (auto archer : curarchers)
    {// 거리는 최소1, x-1,y 부터 거리이내의 적을 bfs로 탐색해 있다면 사살 후 적카운트 감소 못찾았다면 아무 행동 X
        if (curenemycnt <= 0)
            return; // 이번턴 이전 궁수 선에서 다잡아버림

        int x = archer.first - 1;
        int y = archer.second; // {x,y} 사거리 1의 bfs 탐색 시작지점
        int depth = 1;
        vector<vector<bool>> visited(N, vector<bool>(M,false));
        priority_queue<pair<int,pair<int, int>>,vector<pair<int,pair<int,int>>>,compare> pq; // bfs라 최단거리 발견이 보장되지만 조건문 작성으로 가장 좌측, 가까운 행까지 보장하고 싶었음
        visited[x][y] = true;
        pq.push({ depth,{x,y} });
        while (!pq.empty())
        {
            auto curpos = pq.top();
            pq.pop();
            auto curdepth = curpos.first;
            auto curx = curpos.second.first;
            auto cury = curpos.second.second;
            if (board[curx][cury] == 1) // 가장 가깝고 좌측 칸 갔을때 1이면
            {
                // 사살 대상 targets에 저장해 놓고 kill 처리 하기
                targets.insert({curx,cury});
                break; // 이거 안해줬다가 루난의 화살씀
            }
            // 현재 x,y좌표에서 bfs 수행 거리가 가장 가까운 순으로 큐에서 꺼내고, 큐에 넣을 때에는 반드시 사거리 이내까지만 탐색 
            for (int i = 0; i < 3; ++i)
            {
                int nx = curx + dx[i]; // 순서  좌 상 우
                int ny = cury + dy[i];
                int newdepth = curdepth + 1;
                if (newdepth <= D && InRange(nx, ny)) // 방문한적 없고 사거리 이내이며 격자 내의 좌표인지 확인
                {
                    if (!visited[nx][ny])
                    {
                        pq.push({newdepth ,{nx,ny} });
                        visited[nx][ny] = true;
                    }
                }
            }
        }
    }
    // 스캔 끝 사격 시작
    for(auto target : targets)
    {
        // 적사살, 현재 배치의 적카운트 1감소
        board[target.first][target.second]--;
        curenemycnt--;
        kp++;
    }

}

// 적이 이동하는 함수, 사실 성이 한칸씩 위로감
void Move(OUT vector<vector<int>>& board, OUT vector<pair<int,int>>& curarchers, OUT int& curenemycnt)
{
    for (int i = 0; i < 3; ++i)
    {
        curarchers[i].first--; // 3개의 궁수의 위치를 한칸씩 낮춤
    }
    for (int i = 0; i < M; ++i)
    {
        if (board[curarchers[0].first][i] == 1)
        {
            curenemycnt--;// 잡지못하고 남은 상태로 성에 도달한 모든 적에 대해 제거 하면서 개수 감소
            board[curarchers[0].first][i] = 0;
        }
    }
}


void Game(OUT vector<vector<int>>& board)
{
    // 궁수의 좌표 3개 결정
    for (int i = 0; i < M - 2; ++i)
    {
        for (int j = i + 1; j < M - 1; ++j)
        {
            for (int k = j + 1; k < M; ++k)
            {
                vector<pair<int, int>> curarchers = { {N,i},{N,j},{N,k} };
                vector<vector<int>> newboard = board; // 이번 궁수 배치에 사용할궁수 복사
                int curkill = 0;
                int curenemycount = ecnt;// 적의 개수 추적=> 0이되면 이번 게임 종료
                while (curenemycount > 0 && curarchers[0].first > 0)
                {// 적이 남아있고 동시에 모든 적이 빠져나갔을때 종료(즉 성의 행 좌표가 0에 도달했을때)
                    // 1. 현재 배치에서 사격 진행
                    Shooting(curarchers, newboard, curenemycount, curkill);
                    // 2. 사격 끝 이동 시작
                    Move(newboard, curarchers, curenemycount);
                    // 
                }
                // 이번 배치 게임 끝나고 최대값 조회
                answer = max(curkill, answer);
            }
        }
    }
}