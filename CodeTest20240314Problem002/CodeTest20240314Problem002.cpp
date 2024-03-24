// CodeTest20240314Problem002.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <array>
// 선택된 카드가 없는 상태에서 다음 카드를 찾는 법
// value 별 카드쌍의 좌표를 저장해놓기// 1 => (a,b),(c,d)
using namespace std;
array<int, 4> dx{ -1,1,0,0 };
array<int, 4> dy{ 0,0,-1,1 };
int answer = 0;
int solution(vector<vector<int>> board, int r, int c) {
    int answer = 0;
    map<pair<int, int>, pair<int, int>> mates;
    return answer;
}

int main()
{

}
void FindCard(int cx, int cy)// 
{
    // 현재 위치에서 bfs로 가장 가까운 0이 아닌 값을 찾기
    // 0이 아닌 것은 카드이므로 뒤집으면서 뒤집은 카드 좌표 값과 value를 저장 해놓기
    vector<vector<int>> visited(4, vector<int>(4, false));
    queue<pair<int, int>> q;
    visited[cx][cy] = true;
    q.push({ cx,cy });
    while (!q.empty())
    {

    }
}

void FindMate(int x, int y)
{

}