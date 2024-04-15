//  백준 17472 다리만들기2

#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

array<int, 4> dx{ 1,0,-1,0 }; // 하, 좌, 상, 우 0 1 2 3
array<int, 4> dy{ 0,-1,0,1 };
int N, M = 0;
int answer = 10000000;
int numofislands = 0; // 넘버링은 2부터 7까지 최대 6개라서
vector<vector<int>> bridges(8, vector<int>(8, 10000));
vector<bool> constructed(8,false);
bool InRange(int x, int y);
void Grouping(vector<vector<int>>& boards);
void Construction(vector<vector<int>>& boards, int x, int y);
void UnderCons(int dir, int x, int y, vector<vector<int>>& boards, int curg);
void Connecting(vector<vector<int>>& bridges);

struct compare
{
    bool operator()(pair<int,int>& a, pair<int, int>& b)
    {
        if (a.first == b.first)
        {
            return a.second > b.second;
        }
        return a.first > b.first;
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    vector<vector<int>> boards(N, vector<int>(M, 0));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> boards[i][j];
        }
    }

    Grouping(boards);
    constructed[0] = true;
    constructed[1] = true;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            // 모든 섬에 다른 모든 섬에대한 다리 건설 시도
            if (!constructed[boards[i][j]])
            {
                Construction(boards, i, j);
            }

        }
    }

    // 모든 섬을 잇는 최소 길이를 반환하기
    // 섬은 최소 2개이며 모든 섬은 2부터 시작하여 3에서 7로 끝남
    Connecting(bridges);
    
}

bool InRange(int x, int y)
{
    if (x >= 0 && y >= 0 && x < N && y < M)
    {
        return true;
    }
    return false;
}

void Grouping(vector<vector<int>>& boards)
{
    int groupnum = 1;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if (boards[i][j] == 1)
            { // 그룹핑 안된 섬찾기
                groupnum++;
                numofislands++;
                vector<vector<bool>> visited(N, vector<bool>(M, false));
                queue<pair<int, int>> bfs;
                bfs.push({ i,j });
                visited[i][j] = true;

                while (!bfs.empty())
                {
                    auto curpos = bfs.front();
                    bfs.pop();
                    boards[curpos.first][curpos.second] = groupnum; //
                    for (int k = 0; k < 4; ++k)
                    {
                        int nx = curpos.first + dx[k];
                        int ny = curpos.second + dy[k];
                        if (InRange(nx,ny))
                        {
                            if (boards[nx][ny] ==1 && !visited[nx][ny]) // 방문한적이 없고 땅인 경우
                            {
                                visited[nx][ny] = true;
                                bfs.push({ nx,ny });
                            }
                        }
                    }
                }

            }
        }
    }
}

void Construction(vector<vector<int>>& boards,int x,int y)
{
    constructed[boards[x][y]] = true;
    int curgroup = boards[x][y];
    // 현재 좌표 기준 모든 땅 탐색
    queue<pair<int, int>> bfs;
    bfs.push({ x,y });
    vector<vector<bool>> convisit(N, vector<bool>(M, false)); // 이번섬에서 건설을 해본 땅인지
    convisit[x][y] = true;
    while (!bfs.empty())
    {
        // 큐에서 뺀 원소는 4방향에서 바다를 찾고
        // 같은 그룹의 땅인 경우 다음 건설 대기 큐에 넣음
        // 바다를 찾은 경우 해당 방향으로 다리 건설 진행
        // 만약 땅을 찾으면 해당 땅과의 다리 길이를 계산, 각섬간의 다리길이를 저장하는 2차원 배열에 최소값인 것을 저장

        auto curpos = bfs.front();
        bfs.pop();

        for (int i = 0; i < 4; ++i)
        {// 0하, 1좌 2상  3우
            int nx = curpos.first + dx[i];
            int ny = curpos.second + dy[i];
            if (InRange(nx, ny))
            {
                if (boards[nx][ny] == 0)
                {// 해당 방향으로 다리 건설이 가능
                    UnderCons(i, nx, ny, boards, curgroup);
                }
                else
                {
                    if (!convisit[nx][ny])
                    {
                        convisit[nx][ny] = true;
                        bfs.push({ nx,ny });
                    }

                }
            }
        }
    }

 
}

void UnderCons(int dir,int x,int y,vector<vector<int>>& boards,int curg)
{
    int length = 1;
    // 해당 섬의 모든 해안가에 해안가 방향으로 다리 건설 진행(방향 고정 중요)
    // 다리 길이가 하나면 안된다.
    // 넘겨 받은 바다 좌표로 시작해서 (x,y), i 방향으로만 건설 시작
    int nx = x;
    int ny = y;

    // 다른 섬을 만나거나 경계에 도달했을때 끝나는 반복문 시작
    while (true)
    {
        nx += dx[dir];
        ny += dy[dir];
        if (InRange(nx, ny))
        {
            if (boards[nx][ny] != 0 && length > 1&& boards[nx][ny]!=curg)// 섬 만났고 , 다리길이는 2이상이며, 다른 그룹일 경우!!
            {
                bridges[curg][boards[nx][ny]] = min(bridges[curg][boards[nx][ny]],length);
                return;
            }
            else if(boards[nx][ny] == 0)
            {
                length++; // 바다=> 다리 증설
            }
            else if (boards[nx][ny] != 0 && length <=1 &&boards[nx][ny] != curg)// 다른 섬 도착했는데 다리 길이가 조건에 맞지 않음
            {
                return;
            }
            else// 섬을 밟았는데 다리의 길이 상관없이 같은 섬인 경우
            {
                return;
            }
        }
        else
        {
            return;// 경계를 넘어간 경우 건설 종료
        }
    }
}

void Connecting(vector<vector<int>>& bridges)
{// Prim의 최소 신장 트리 연결 
    set<int> islands;
    int curlength = 0;
    // 순서 섬하나 선정-> 섬의 간선 전부 
    priority_queue < pair<int,int>,vector<pair<int,int>>, compare> pq;
    vector<bool> visited(2 + numofislands,false);
    visited[0] = true; visited[1] = true; visited[2]=true;
    
    int srtisland = 2;
    islands.insert(2);
    for (int i = 2; i < 2 + numofislands; ++i)
    {
        if (bridges[2][i] != 10000)
        {
            pq.push({ bridges[2][i],i });
        }
    }

    while (!pq.empty())
    {
        auto curval = pq.top();
        pq.pop();
        auto curweight = curval.first;
        auto curisl = curval.second;
        if (visited[curisl])
            continue;
        curlength += curweight;
        visited[curisl] = true;
        islands.insert(curisl);
        for (int i = 2; i < 2 + numofislands; ++i)
        {
            if (!visited[i] && bridges[curisl][i] != 10000)
            {
                pq.push({ bridges[curisl][i] , i });
            }
        }

    }
    // 간선 순회가 끝났는데 섬의 개수를 만족하지 못함
    if (islands.size() != numofislands)
        cout << -1;
    else
        cout << curlength;
}