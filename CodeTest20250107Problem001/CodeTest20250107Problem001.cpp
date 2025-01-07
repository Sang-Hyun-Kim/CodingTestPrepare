#include <string>
#include <vector>
#include <unordered_set>
#include <array>
#include <algorithm>
#include <queue>
#include <iostream>

/*
프로그래머스 행렬 테두리 회전하기
완전 탐색, bfs식 방향 변환하기
2차원 배열 풀이

*/
// 실수
// 왜틀렸지하고 IDE 켰는데
// Rotator 함수는 반환값이 없는데 int형반환으로 적어서
// seg dump fail 오류가 났다.
// 방문처리를 하려고 만든 unordered_set의 인자로 pair를 넣게되면
// hash함수에 맞는생성자가 없다
// 이를 위해 구조체를 하나 새로 만들어 준다음 조건문에 넘겨줬다.
// std::hash는 std::vector 헤더 안에 정의되어 있음
using namespace std;
array<int, 4> dx = { 0,1,0,-1 }; // 0 우,1하,2좌,3상
array<int, 4> dy = { 1,0,-1,0 };
vector<int> answer;
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator () (std::pair<T1, T2> const& pair) const
    {
        std::size_t h1 = std::hash<T1>()(pair.first);
        std::size_t h2 = std::hash<T2>()(pair.second);

        return h1 ^ h2;
    }
};
void Rotator(int xs, int ys, int xd, int yd, vector<vector<int>>& board);
vector<int> solution(int rows, int columns, vector<vector<int>> queries) {

    vector<vector<int>> board(rows + 1, vector<int>(columns + 1, 0));
    for (int i = 1; i < rows + 1; ++i)
    {
        for (int j = 1; j < columns + 1; ++j)
        {
            board[i][j] = ((i - 1) * columns + j);
        }
    }

    for (auto querie : queries)
    {
        int xs = querie[0];
        int ys = querie[1];
        int xd = querie[2];
        int yd = querie[3];
        Rotator(xs, ys, xd, yd, board);
    }
    return answer;
}

void Rotator(int xs, int ys, int xd, int yd, vector<vector<int>>& board)
{
    // 시계방향 x1,y1 기준 조건에 따라항상 왼쪽 위인 xs ys
    int mini = 10000001;

    unordered_set<pair<int, int>, pair_hash> visited;
    queue<pair<int, int>> rq;
    int curvalue = 10000001;
    rq.push({ xs,ys });
    curvalue = board[xs][ys];
    visited.insert({ xs,ys });
    int way = 0; // 0~3;
    mini = min(mini, curvalue);
    while (!rq.empty())
    {
        auto curpos = rq.front();
        rq.pop();

        int nx = curpos.first + dx[way];
        int ny = curpos.second + dy[way];

        if (nx == xs && ny == ys)
        {
            // 첫 지점 도착
            way = 0;//
        }
        else if (nx == xs && ny == yd)// 우상단
        {
            way = 1;
        }
        else if (nx == xd && ny == yd) // 우하단
        {
            way = 2;
        }
        else if (nx == xd && ny == ys) // 좌 하단
        {
            way = 3;
        }
        else
        {// 방향전환필요 x

        }
        // 
        int nexttemp = board[nx][ny];
        board[nx][ny] = curvalue; // 미리 저장한 이전 칸의 값
        curvalue = nexttemp;
        mini = min(curvalue, mini);
        if (visited.find({ nx,ny }) == visited.end())
        {
            rq.push({ nx,ny });
            visited.insert({ nx,ny });
        }
    }
    // 큐에서 빼기
    // 다음 지점 계산
    // 다음 지점의 값 curvalue 처리(nexttemp)
    // 다음 지점의 값을 curvalue 값으로 변환
    // 다음 지점의 좌표 queue에 넣기 이때 방문set에 있는 경우 제외
    // 다음 지점의 방문 처리
    // 방향 전환의 순간, 다음 지점이 네 꼭지점에 도달한 경우 다음 좌표는 방향이 전환되어야함

    answer.push_back(mini);
}
int main()
{
    vector<int> answer = solution(3, 3, { {1,1,2,2},{1,2,2,3},{2,1,3,2},{2,2,3,3} });
    answer;
}
