// 백준 1915번 가장 큰 정사각형
// DP 사용
// DP[i][j] => 좌표 i,j가 마지막 꼭지점을 끝나는 정사각형의 최대 "변" 길이를 저장하는 배열
// 이때 DP[i][j]는 주어진 좌표에서 해당 좌표의 값(board[i][j])가 0이 아닐 경우 최소 하나의 정사각형(자기 자신)을 가짐
// 따라서 최소 변의 길이는 1 이상임
// 이때 해당 좌표 i,j에 대해서 왼쪽(j-1), 위(i-1) 그리고 왼쪽 위(i-1,j-1)가 만들 수 있는 사각형의 크기에 따라 결정됨
// 그러므로 3개의 값 중 "최소" 값에 + 1(자기자신) 을 더한 것이 해당 좌표가 만들 수 있는 "최대" 크기의 정사각형의 "변의 길이" 이다.
// 수식 DP[i][j] = min(DP[i][j],DP[i][j],DP[i][j])+1 이며
// 정답은 DP[i][j] * DP[i][j]

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    //ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int row, col;
    cin >> row >> col;
    vector<vector<int>> board(row+1, vector<int>(col+1, 0));
    vector<vector<int>> sum(row+1, vector<int>(col+1, 0));
    cin.ignore();
    for (int i = 1; i <= row; ++i)
    {
        string line;
        getline(cin, line);
        for (int j = 1; j <= col; ++j)
        {
            board[i][j]=line[j - 1] - 48;
            sum[i][j] = line[j - 1] - 48;
        }
    }
 
    int max = 0;
    for (int i = 0; i <= row; ++i)
    {
        for (int j = 0; j <= col; ++j)
        {
            if (sum[i][j] == 0) continue;
            sum[i][j] += min(sum[i - 1][j], min(sum[i - 1][j - 1], sum[i][j - 1]));
            if (max < sum[i][j]) max = sum[i][j];
        }
    }
    cout << max*max << '\n';
}

