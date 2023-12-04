// 백준 1309 동물원
// // 실버 1
#include <iostream>
#include <vector>
using namespace std;
int MOD =  9901;

int main()
{
    int number;
    cin >> number;
    vector<vector<int>> DP(number, vector<int>(3, -1));

    // 0: 해당 행에서 아무것도 고르지 않는것
    // 1: 해당 행에서 좌측을 고르는 것
    // 2: 해당 행에서 우측을 고르는 것
    DP[0][0] = 1;
    DP[0][1] = 1;
    DP[0][2] = 1;
    for (int i = 1; i < number; ++i)
    {
        DP[i][0] = (DP[i - 1][0] + DP[i - 1][1] + DP[i - 1][2]) % MOD;
        DP[i][1] = (DP[i - 1][0] + DP[i - 1][2]) % MOD;
        DP[i][2] = (DP[i - 1][0] + DP[i - 1][1])% MOD;
    }
    // N개의 행에서 사자를 배치하는 경우의 수 => DP[N-1][0]+ DP[N-1][1] + DP[N-1][2]
    int sum = (DP[number - 1][0] + DP[number - 1][1] + DP[number - 1][2])%MOD;
    cout << sum << endl;
}
