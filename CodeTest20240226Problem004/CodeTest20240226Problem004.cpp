// 백준 17136번 색종이 붙이기
// 

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;
int bsize = 0;
// 종이 행길이 1~5까지 각각 5장
// 찾은 1에 대해 종이 1~5까지 하나씩 붙여본다음 최소값을 저장하고 넘어가기
// 애로사항
// 1: 백트래킹 재귀함수의 설계
// 2: 경계 처리에 따른 return 설정
// 3: 백트래킹 함수의 return 위치(무한루프 주의)
vector<vector<int>> board(10, vector<int>(10, 0));
vector<int> paper{5,5,5,5,5};
int answer = 25;
void Backtrack(int pvalue);
bool Border(int x, int y);
bool Checkstatus();
int CheckSize(int x, int y);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            cin>>board[i][j];
        }
    }
    Backtrack(1);

    if (answer == 25) cout << -1;
    else cout << answer - 1;

}

// 재귀함수
void Backtrack(int pvalue)
{
    // 전체 재귀 검증if()
    // 진행하다가 현재 순회에 계산된 개수 보다 커질 경우 스톱
   

    if (pvalue > answer)
    {
        return;
    }
    // 남은 1이 없는 경우 저장
    if (Checkstatus())
    {
        answer = pvalue;
        return;
    }

    // 넘겨받은 현재 진행 좌표 전체에 대한 순환
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (board[i][j] == 1)
            {// 남은 구역에 대해서
                int max = CheckSize(i, j);
                while (max > 0)
                {
                    if (paper[max - 1] > 0)
                    {
                        paper[max - 1]--;
                        for (int p = i; p < i + max; ++p)
                        {
                            for (int q = j; q < j + max; ++q)
                            {
                                board[p][q] = pvalue + 1;
                            }
                        }
                        Backtrack(pvalue + 1);
                        paper[max - 1]++;
                        for (int p = i; p < i + max; ++p)
                        {
                            for (int q = j; q < j + max; ++q)
                            {
                                board[p][q] = 1;
                            }
                        }

                    }
                    max--;
                }
                return; // 이번 좌표에 대한 순회에 대해 가능한 조회가 전부 끝났으면 여기서 끝내줘야함 
                // 끝나는 조건: 현재 호출스택에서 가능한 모든 것을 끝냈을 때 도달함
            }

        }
    }
}

// border()
bool Border(int x, int y)
{
    return (x>=0 && x<10 && y>=0 && y<10);
}
bool Checkstatus()
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j <10; ++j)
        {
            if (board[i][j] == 1) return false; // 아직 덮을 곳이 남음

        }
    }
    return true;
}
int CheckSize(int x,int y)
{  // 1인 값을 찾았으면 int x, y에 대해 크기 몇짜리 정사각형인지 계산하기
    int size = 0;
    while (size <= 5)
    {
        size++;
        for (int i = x; i < x + size; ++i)
        {
            for (int j = y; j < y + size; ++j)
            {
                if (Border(i, j))
                {
                    if (board[i][j] != 1)
                    {
                        return size-1;
                    }
                }
                else
                {
                    return size - 1;
                }
                
            }
        }

    }
    return size-1;
}
// return의 위치
// 이전 순회(x번 종이 사용) 이후의 보드 상태를 넘겨받았고 거기서 보드가 1이 있는 상황  1을 찾아서 새로운 순회를 시작 함
// 종이를 붙인 다음 남은 모든 좌표에에 대한 1을 찾는 순회를 도는 이 이중 루프문은 가장 빠른 것을 찾는 다면 그것을 골라 그 이후를 순회하고 돌아온다면 그 외의 좌표들은 돌 필요가 없기 때문에
// return을 호출하는 것이다. 종류별 종이 개수와 경계에 맞는 조건에 맞추어 알아서 계산될 것이다
