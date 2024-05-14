// 백준 2617 구슬 찾기 골드 4
// 주어진 구슬쌍 무게 비교들을 통해
// 무게가 가운데가 될 수 없는 후보들을 미리 찾는 문제
// 구슬 개수는 항상 홀수 이며 가운데는 (N+1) / 2
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
int N = 0;

int main()
{
    int M;
    cin >> N >> M;
    vector<vector<int>> board(N+1, vector<int>(N+1, INT_MAX));// 0(제외), 1~N번
   


    for (int i = 0; i < M; ++i)
    {
        int H, L;
        cin >> H >> L;

        board[H][L] = 1;

    }

    for (int k = 1; k < N+1; ++k) // 징검다리 K에 대해
    {
        for (int i = 1; i < N + 1; ++i) // 구슬 i(첫번째)가
        {
            for (int j = 1; j < N + 1; ++j) // k를통해 구슬 j까지 도달할 수 있다면
            {
                if (board[i][k] + board[k][j] == 2)
                {
                    board[i][j] = 1;
                }
            }
        }
    }
    int count = 0;
    int count_2 = 0;
    int answer = 0;
    int limit = (N + 1) / 2;
    for (int i = 1; i < N + 1; ++i) {
        count = 0;
        count_2 = 0;
        for (int j = 1; j < N + 1; ++j) {
            if (j == i) { // 자기 자신 제외
                continue;
            }
            if (board[i][j] == 1) {
                count++;
            }
            if (board[j][i] == 1) {
                count_2++;
            }
        }
        if (count >= limit || count_2 >= limit) {
            answer++;
        }
    }
    cout << answer << endl;
    return 0;
}
