// 백준 12100  2048(Easy)골드 2
// 구현 하는거 너무 힘들었고
// 잔실수(3중포문에서 i,j,k의 순서를 단 한 곳에서 잘못적었음)때문에 반례 모음집 단 하나 제외하고 전부 맞는 기현상을 겪어서
// 겨우 찾은 반례로 디버깅 해체 분석한 다음 오류를 찾았다.
// 오류 줄이기잘하자..
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int answer = 0;
int sz = 0;
void Slide(int _count, int _way, vector<vector<int>> _board);

enum Way {
    UP,RIGHT,DOWN,LEFT
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> sz;
    vector<vector<int>> board(sz, vector<int>(sz, 0));
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            int v = 0;
            cin >> v;
            board[i][j]= v;
            if (v > answer) answer = v;
        }
    }
    
    Slide(1, UP,board);
    Slide(1, RIGHT,board);
    Slide(1, DOWN,board);
    Slide(1, LEFT, board);

    cout << answer;


}

void Slide(int _count, int _way, vector<vector<int>> _board)
{
    // Slide 횟수 체크
    if (_count > 5) return; // 이미 5번 사용 끝
    // 현재 최대값
    int curmax = 0;
    // 넘겨 받은 방향에 대해 진행
    if (_way == UP)
    {
        // row[0]을 고정하고 1~size-1까지 진행하면서 0~size-1열의 합치기 진행
        vector<vector<int>> nb = _board;
       // 합칠 수 있다면 합치고 빈공간을 전부 당겨버려야함  그 다음 인덱스를 내려야 함
        for (int j = 0; j < sz; j++)
        {
            for (int i = 0; i < sz-1; ++i)
            {
               if (nb[i][j] != 0)
               {
                   curmax = max(curmax, nb[i][j]);
                   for (int k = i+1; k < sz; ++k)
                   {
                       if (nb[k][j] == nb[i][j])
                       {
                           nb[i][j] += nb[k][j];
                           nb[k][j] = 0;
                           if (answer < nb[i][j])
                               answer = nb[i][j];
                           if (curmax < nb[i][j]) curmax = nb[i][j];
                           i = k;
                           break;
                       }
                       else if (nb[k][j] != nb[i][j] && nb[k][j] != 0)// 다른 값이지만 0이 아닌 경우
                       { // 조사 인덱스 옮기고 새로시작
                           i = k-1;
                           break;
                       }

                   }
               }
            }
            // 한줄 끝 순서 압축
            int pivot = 0;
            for (int i = 0; i < sz; ++i)
            {
                if (nb[i][j] != 0)
                {
                    if (i != pivot)
                    {
                        swap(nb[pivot][j],nb[i][j]);
                    }
                    pivot++;
                }
            }
        }
        // 정해진 방향으로 합치기 완료
        // 현재 상태 기준으로 4방향 시작
        // 현재만든 값중의 최대 값이 2의 남은 횟수 거듭제곱만큼을 더 했을 때 현재 저장된 값보다 크거나 같을 수 있을 때만 진행(가지치기)
        if (curmax * (int)pow(2, 5 - _count) >= answer)
        {
            Slide(_count + 1, UP, nb);
            Slide(_count + 1, RIGHT, nb);
            Slide(_count + 1, DOWN, nb);
            Slide(_count + 1, LEFT, nb);
        }
        return;
    }
    else if (_way == RIGHT)
    {
        vector<vector<int>> nb = _board;
        for (int i = 0; i < sz; i++)
        {
            for (int j = sz - 1; j > 0; --j)
            {
                if (nb[i][j] != 0)
                {
                    curmax = max(curmax, nb[i][j]);
                    for (int k = j-1; k >= 0; --k)
                    {
                        if(nb[i][j] == nb[i][k])
                        {
                            nb[i][j] += nb[i][k];
                            nb[i][k] = 0;
                            if (answer < nb[i][j])
                                answer = nb[i][j];
                            if (curmax < nb[i][j]) curmax = nb[i][j];
                            j = k;
                            break;
                        }
                        else if(nb[i][j] != nb[i][k] && nb[i][k] != 0)
                        {
                            j = k+1;
                            break;
                        }
                    }
                }
            }
            // 한줄 끝 순서 압축
            int pivot = sz-1;
            for (int j = sz-1; j >=0; --j)
            {
                if (nb[i][j] != 0)
                {
                    if (j != pivot)
                    {
                        swap(nb[i][pivot], nb[i][j]);
                    }
                    pivot--;
                }
            }


        }

        if (curmax * (int)pow(2, 5 - _count) >= answer)
        {
            Slide(_count + 1, UP, nb);
            Slide(_count + 1, RIGHT, nb);
            Slide(_count + 1, DOWN, nb);
            Slide(_count + 1, LEFT, nb);
        }
        return;

    }
    else if (_way == DOWN)
    {
        vector<vector<int>> nb = _board;
        for (int j = 0; j < sz; j++)
        {
            for (int i = sz - 1; i > 0; --i)
            {
                if (nb[i][j] != 0)
                {
                    curmax = max(curmax, nb[i][j]);
                    for (int k = i - 1; k >= 0; --k)
                    {
                        if (nb[i][j] == nb[k][j])
                        {
                            nb[i][j] += nb[k][j];
                            nb[k][j] = 0;
                            if (answer < nb[i][j])
                                answer = nb[i][j];
                            if (curmax < nb[i][j]) curmax = nb[i][j];
                            i = k;
                            break;
                        }
                        else if (nb[i][j] != nb[k][j] && nb[k][j] != 0)
                        {
                            i = k + 1;
                            break;
                        }
                    }
                }
            }
            // 한줄 끝 순서 압축
            int pivot = sz-1;
            for (int i = sz-1; i >=0 ; --i)
            {
                if (nb[i][j] != 0)
                {
                    if (i != pivot)
                    {
                        swap(nb[pivot][j], nb[i][j]);
                    }
                    pivot--;
                }
            }
        }
        if (curmax * (int)pow(2, 5 - _count) >= answer)
        {
            Slide(_count + 1, UP, nb);
            Slide(_count + 1, RIGHT, nb);
            Slide(_count + 1, DOWN, nb);
            Slide(_count + 1, LEFT, nb);
        }
        return;
    }
    else// way==LEFT
    {
        vector<vector<int>> nb = _board;
        for (int i = 0; i < sz; i++)
        {
            for (int j = 0; j < sz-1; ++j)
            {
                if (nb[i][j] != 0)
                {
                    curmax = max(curmax, nb[i][j]);
                    for (int k = j+1; k <sz; ++k)
                    {
                        if (nb[i][j] == nb[i][k])
                        {
                            nb[i][j] += nb[i][k];
                            nb[i][k] = 0;
                            if (answer < nb[i][j])
                                answer = nb[i][j];
                            if (curmax < nb[i][j]) curmax = nb[i][j];
                            j = k;
                            break;
                        }
                        else if (nb[i][j] != nb[i][k] && nb[i][k] != 0)
                        {
                            j = k -1;
                            break;
                        }
                    }
                }
            }
            // 한줄 끝 순서 압축
            int pivot = 0;
            for (int j = 0; j <sz; ++j)
            {
                if (nb[i][j] != 0)
                {
                    if (j != pivot)
                    {
                        swap(nb[i][pivot], nb[i][j]);
                    }
                    pivot++;
                }
            }
        }

        if (curmax * (int)pow(2, 5 - _count) >= answer)
        {
            Slide(_count + 1, UP, nb);
            Slide(_count + 1, RIGHT, nb);
            Slide(_count + 1, DOWN, nb);
            Slide(_count + 1, LEFT, nb);
        }
        return;
    }

}

