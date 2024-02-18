//백준 2437번 저울

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 정렬된 배열의 첫 원소가 1이 아닌 경우=> 무조건 1이 나옴
// 정렬된 배열의 N번째까지의 총합을 S(N)이라고 했을 때
// 정렬된 배열의 N+1번째 원소의 값이 S(N)+1보다 클 경우
// S(N)+1이 정답이됨 다음 원소 a[N+1]이 S(N)+1보다 작을 경우
// S(N+1)은 S(N) + a[N+1] 로 계속 갱신되며 1~S(N+1) 사이의 값이 전부 표현 가능

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int Num;
    cin >> Num;
    vector<int> weights(Num, 0);
    for (auto& w:weights) cin >> w;

    sort(weights.begin(), weights.end());
    int sum=0;
    // 원소 a까지 열람=> Sum은 원소 A까지의 총합
    for (auto w : weights)
    {
        if (w > sum + 1) break;
        sum += w;
    }
    cout << sum + 1;
}
