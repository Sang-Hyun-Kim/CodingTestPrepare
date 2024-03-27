// 백준 빙산 2573

#include <iostream>
#include <vector>
#include <array>
#include <queue>
using namespace std;
array<int, 4> dx{ 1,-1,0,0 };
array<int, 4> dy{ 0,0,1,-1 };

// 히든 케이스
// 1. 덩어리가 안나올때 flag 초기화 안해줘서 무한루프 오류
// 2. queue진입 조건(방문처리 후 queue에 넣기)를 제대로 안해줘서 queue 스택 오버 플로우 에러(큐에서 꺼내고 방문처리하는 실수)
// 3. 좌표 값이 0이상의 정수가 되는 조건문 기입 실수
// 단순한 그래프 탐색 및 그룹핑 문제
// => 침착하게 풀어 오류 및 실수를 줄이자
int flag = false;

int r, c=0;
bool InRange(int x, int y);
int Water(int x, int y, vector<vector<int>>& ps);
void Grouping(int g, int x, int y, vector<vector<int>>& ns, vector<vector<int>>& visited);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);


    cin >> r >> c;
    vector<vector<int>> sea(r,vector<int>(c,0));
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            cin >> sea[i][j];
        }
    }
    int years = 0;
    
    while (true)
    {
        years++; //+1년지남
        vector<vector<int>> ns = sea;
        for (int i = 0; i < r; ++i)
        {
            for (int j = 0; j < c; ++j)
            {
                ns[i][j] -= Water(i, j,sea);
                ns[i][j] = max(ns[i][j], 0);
            }
        }
        // 남은 빙산이 있었냐
        if (!flag)
        {// 다녹을때 까지 발견 못함
            cout << 0;
            return 0;
        }
        else
        {
            int g = 0;
            vector<vector<int>> visited(r, vector<int>(c, 0));
            // 그룹핑 2개이상 나오는지 체크
            for (int i = 0; i < r; ++i)
            {
                for (int j = 0; j < c; ++j)
                {
                    if (ns[i][j] > 0 && visited[i][j] == 0)
                    {
                        Grouping(++g, i, j, ns, visited);
                        if (g >= 2)
                        {
                            cout << years;
                            return 0;
                        }
                            
                    }
                }
            }
            sea = ns;

        }
        flag = false;
    }
    
}

bool InRange(int x, int y)
{

    if (x >= 0 && y >= 0 && x < r && y < c) {
        return true;
    }
    return false;
}
int Water(int x, int y,vector<vector<int>>& ps)
{
    int wc = 0;
    if (ps[x][y] == 0)
    {
        return wc;
    }
    else
    {//빙산 중에서
        flag = true; // 빙산이 있다.
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (InRange(nx, ny))
            {
                if (ps[nx][ny] == 0)
                {//동서남북 바다가 있다면 
                    wc++;
                }
            }
        }
        return wc;
    }
}
void Grouping(int g,int x, int y, vector<vector<int>>& ns, vector<vector<int>>& visited)
{
    if (visited[x][y] > 0)
    {
        return;
    }
    else
    {
        queue<pair<int,int>> gq;
        gq.push({x,y});
        visited[x][y] = g; // 그룹핑
        while (!gq.empty())
        {
            auto cursea = gq.front();
            gq.pop();
            
            for (int i = 0; i < 4; ++i)
            {
                int nx = cursea.first + dx[i];
                int ny = cursea.second + dy[i];
                if (InRange(nx, ny))
                {
                    if (ns[nx][ny] != 0 && visited[nx][ny] == 0)
                    {//1년지난 해당 좌표가 방문(그룹핑여부)안했고 빙산인 경우
                        visited[nx][ny] = g;
                        gq.push({ nx,ny });
                    }
                }
            }
        }
       
        return;

    }
}