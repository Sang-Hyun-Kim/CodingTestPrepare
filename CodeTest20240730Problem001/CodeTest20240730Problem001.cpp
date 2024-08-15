// 백준 26607번 시로코와 은행털기
#include <iostream>
#include <vector>
#include <algorithm>
int cand = 0;
int pick = 0;
int tot = 0;
bool dp[80][81][16001] = {false,};// [index]][고른 수][최고A능력치] 가 가능하냐 // 160001 넣어서 메모리 터짐 아오

int solution(std::vector<int>& candsa)
{
    int answer = 0;
    dp[0][1][candsa[0]] = true;
    for (int i = 1; i < cand; ++i)// i개를 고를 때
    {    // 기저 조건
    // [i 번째][1][i의 능력치]
    // [i번째][0][0]
        dp[i][1][candsa[i]] = true;
        dp[i][0][0] = true;
        for (int j = 1; j <= i + 1; ++j)
        {
            for (int a = 0; a <= tot * pick; a++)
            {
                // i번째 후보를 고르는 경우
                if (a - candsa[i] >= 0 && j > 0)
                    dp[i][j][a] |= dp[i - 1][j - 1][a - candsa[i]]; // i-1번째에 j-1개 만큼 고른 후 i의 a능력치만큼 지금 임의의 a합에서 뺀 경우가 존재하는 경우 지금의 값이 true로 가능
                // i번째 후보를 안 고르는 경우
                dp[i][j][a] |= dp[i - 1][j][a]; // i번째에 j만큼 고를때 a만큼의 a합을 가질 수 있는 경우는 i-1번째에 j만큼 고르면서 a만큼의 합을 가질 수 있을 경우(true)에 true 하다
            }
        }
    }

    // 가능한 경우의 A값이 나오는경우 계산
    // 이때 최대 능력치 합 * 선택하는 후보의 수 만큼 까지만 능력치가 나올 것
    for (int a = 0; a <= tot * pick; a++)
    {
        if (dp[cand - 1][pick][a])
            answer = std::max(answer, a * (tot * pick - a));
    }
    return answer;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> cand >> pick >> tot;

    std::vector<int> candsa(cand, 0);
    for (int i = 0; i < cand; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        candsa[i] = a;
    }

    std::cout << solution(candsa);
}