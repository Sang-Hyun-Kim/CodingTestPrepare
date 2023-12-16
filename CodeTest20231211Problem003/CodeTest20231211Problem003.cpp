// 백준 15989 번 1,2,3 더하기 4
#include <iostream>
#include <vector>

using namespace std;
// 노가다로 구한 점화식 규칙 응용하기
int main()
{
    int Number;
    int num;
    vector<int> dp(10001, -1);
    cin >> Number;
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;
    dp[4] = 4;
    dp[5] = 5;

    for (int i = 0; i < Number; ++i)
    {
        cin >> num;
        if (num <= 5)
        {
            cout << dp[num] << endl;
            continue;
        }
        else
        {
            if (dp[num] != -1)
            {
                cout << dp[num] << endl;
                continue;
            }
            else
            {
                for (int j = 6; j < num + 1; ++j)
                {
                    dp[j] = j + dp[j - 6];
                }

            }
        }
        cout << dp[num] << endl;
    }

}