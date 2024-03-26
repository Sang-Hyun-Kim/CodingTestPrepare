// 백준 1654 랜선자르기
// 실버2
// 풀이

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int K; int N;
    cin >> K >> N;
    vector<long long> cables(K);
    long long mx = 0;
    for (int i = 0; i < K; ++i)
    {
        cin >> cables[i];
        mx = max(mx, cables[i]);
    }
    // 가장 짧은 랜선을 사용하지 않아도 된다. // 처음에는 이를 인지하지못함(가장 짧은 선을 최대한 이용하기=> 최적의 길이를 찾아 개수를 맞추기)
    // 가장 긴 랜선 기준으로 이분탐색하며 어울리는 값찾기.
    long long srtV = 1;// 
    long long lastV = mx;
    long long mid = 0;
    long long answer = 0;
    while (srtV <= lastV)
    {
        mid = (srtV + lastV) / 2;
        long long value=0;
        for (int i = 0; i < cables.size(); ++i)
        {
            value += cables[i] / mid;
        }

        if (value < N) // 너무 길기 때문에 좀 더 짧은 값으로 탐색 시작
        {
            lastV = mid - 1;
        }
        else// mid>= N => 최대값을 찾아야 하기때문에 srtV를 올리면서 찾는다
        {
            srtV = mid + 1;
            answer = max(answer, mid);
        }

    }
    cout<< answer;
}
