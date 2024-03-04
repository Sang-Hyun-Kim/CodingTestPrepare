// 백준  1799 비숍
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
// DFS 두번으로 안풀고 대각선을 직선으로 만들기 위해 격자를 45도 돌린 풀이
using namespace std;
int bsize = 0;
int answer = 0;
vector<vector<int>> board(10, vector<int>(10, 0));
vector<bool> Rused(20, false); // 10 * 2 -1;
vector<bool> Lused(20, false); //
void NVishop(int n, int size);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> bsize;
    for (int i = 0; i < bsize; ++i)
    {
        for (int j = 0; j < bsize; ++j)
        {
            cin >> board[i][j];
        }
    }

    NVishop(0, 0);
    cout << answer;
}

void NVishop(int k, int size) // 우상향 대각선의 순서 th에 대한 비숍놓기 시작
{
    if (k >= 2 * bsize - 1)
    { // 대각선 전부 돌았다.
        answer = max(answer, size);
    }
    else
    {
        bool flag = false;
        for (int i = 0; i < bsize - abs(k - (bsize - 1)); ++i)
        {
            int x = (bsize - 1 <= k) ? bsize - 1 - i : k - i;
            int y = (bsize - 1 <= k) ? k - (bsize - 1) + i : i;

            if (board[x][y] == 1 && !Rused[k] && !Lused[bsize - 1 - (x - y)])
            {
                flag = true;
                Rused[k] = true;
                Lused[bsize - 1 - (x - y)] = true;
                NVishop(k + 1, size + 1);
                // 안 놨을 경우도 
                Rused[k] = false;
                Lused[bsize - 1 - (x - y)] = false;
            }
        }
        if (!flag) NVishop(k + 1, size); // 이번 대각선에서 놓지 못했다면 다음 대각선 진행 
    }
}
// 시간초과 풀이
; // -1 빈공간, 1 비숍을 넣을 수 있는 공간, 2 킬존(연산 이후 비숍을 놓을 수 없는 공간)
// 하나 배치할때마다 다음 연산은 남은 보드를 복사해서 다시 새로운 배치 공간을 마련하기?
//int Kill(int _bsize, int _x, int _y, vector<vector<int>> _board, int _count);
//int main()
//{
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    cout.tie(NULL);
//    int bsize;
//    cin >> bsize;
//    set<pair<int, int>> bs;
//    vector<vector<int>> board(bsize, vector<int>(bsize, -1));
//    for (int i = 0; i < bsize; ++i)
//    {
//        for (int j = 0; j < bsize; ++j)
//        {
//            cin >> board[i][j];
//            if (board[i][j]) bs.insert({i,j});
//        }
//    }
//    int answer=0;
//    for (int i = 0; i < bsize; ++i)
//    {
//        for (int j = 0; j < bsize; ++j)
//        {
//           // 좌표하나에 대해 진행
//            if (board[i][j] == 1)
//            {
//                answer =max(answer, Kill(bsize, i, j, board, 0));
//            }
//        }
//    }
//    cout << answer;
//}
//int Kill(int _bsize,int _x,int _y,vector<vector<int>> _board,int _count)// 비숍이 좌표에 배치되었을 때 잡을 수 있는 좌표들을 계산해서 없애기 그리고 남은 보드판을 반환?
//{
//    _count++;
//    // 대각선 좌표 두좌표 a,b, x,y 에 대해 a-x ==abs(b-y) 성립하면 대각선
//    for (int i = 0; i < _bsize; ++i)
//    {
//        for (int j = 0; j < _bsize; ++j)
//        {
//            // 좌표하나에 대해 진행
//            if (abs(i - _x) == abs(j - _y))
//            {
//                _board[i][j] = 0;
//            }
//        }
//    }
//
//    // 남은 좌표에 대해 또 다시 진행
//    int _answer = _count;
//    for (int i = 0; i < _bsize; ++i)
//    {
//        for (int j = 0; j < _bsize; ++j)
//        {
//            // 남은 좌표들을 진행했을때의 최대값 반환
//            if (_board[i][j] == 1)
//                _answer = max(_answer, Kill(_bsize, i, j, _board, _count));
//        }
//    }
//    return _answer;
//}