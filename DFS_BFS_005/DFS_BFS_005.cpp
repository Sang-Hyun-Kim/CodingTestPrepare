// 백준 2667번 단지 번호 붙이기

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

enum Pos
{

};
int main()
{
    int N;
    cin >> N;
    char currentnumber;
    vector<vector<char>> Board(N,vector<char>(N,' '));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> currentnumber;
            Board[i][j] = currentnumber;
        }
    }

    int a = 3;
}
