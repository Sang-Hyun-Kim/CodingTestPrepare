// 코드트리 nxn 표채우기
// 소용돌이 패턴 파악후 표에 숫자 채우기

#include <iostream>
#include <vector>
#include <array>
using namespace std;
array<int, 4> dx = { -1,0,1,0 };
array<int, 4> dy = { 0,1,0,-1 };
int N;
int target;
vector<int> answer;
int main() {
    // 여기에 코드를 작성해주세요.
    cin >> N >> target;
    int startx;
    int starty;
    vector<vector<int>> board(N, vector<int>(N, 0));
    if (N % 2 == 0)
    {
        startx = N / 2;
        starty = N / 2 - 1;
    }
    else
    {
        startx = N / 2;
        starty = N / 2;
    }

    int count = 1;
    int way = 0; // 0 위 1 오른 2 아래 3 왼
    int curmaxhop = 1;
    board[startx][starty] = 1;
    int maxC = N * N;
    int curx = startx;
    int cury = starty;
    int changehop = 0; // 2번 채우면 홉증가 
    while (count < maxC)
    {
        if (way % 4 == 0)
        {
            int curhop = 0;

            while (curhop < curmaxhop)
            {
                int nx = curx + dx[0];
                int ny = cury + dy[0];
                board[nx][ny] = board[curx][cury] + 1;
                if (board[nx][ny] == target)
                {
                    answer.push_back(nx);
                    answer.push_back(ny);
                }
                curx = nx;
                cury = ny;
                curhop++;
                count++;
            }
            way++;
        }
        else if (way % 4 == 1)
        {
            int curhop = 0;

            while (curhop < curmaxhop)
            {
                int nx = curx + dx[1];
                int ny = cury + dy[1];
                board[nx][ny] = board[curx][cury] + 1;
                if (board[nx][ny] == target)
                {
                    answer.push_back(nx);
                    answer.push_back(ny);
                }
                curx = nx;
                cury = ny;
                curhop++;
                count++;
            }
            way++;
        }
        else if (way % 4 == 2)
        {
            int curhop = 0;

            while (curhop < curmaxhop)
            {
                int nx = curx + dx[2];
                int ny = cury + dy[2];
                board[nx][ny] = board[curx][cury] + 1;
                if (board[nx][ny] == target)
                {
                    answer.push_back(nx);
                    answer.push_back(ny);
                }
                curx = nx;
                cury = ny;
                curhop++;
                count++;
            }
            way++;
        }
        else
        {//3
            int curhop = 0;

            while (curhop < curmaxhop)
            {
                int nx = curx + dx[3];
                int ny = cury + dy[3];
                board[nx][ny] = board[curx][cury] + 1;
                if (board[nx][ny] == target)
                {
                    answer.push_back(nx);
                    answer.push_back(ny);
                }
                curx = nx;
                cury = ny;
                curhop++;
                count++;
            }
            way++;

        }
        changehop++;
        if (changehop >= 2)
        {
            changehop = 0;
            if (curmaxhop != N - 1)
                curmaxhop++;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << answer[0] + 1 << " " << answer[1] + 1;
    return 0;
}