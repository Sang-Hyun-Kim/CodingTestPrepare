// 백준 2075 N번째 큰수
// 용량 초과를 막기 위해 넣으면서 최적화
// 시간 초과를 막기 위해 인풋 동기화 해제
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main()
{
    int N = 0;
    int value = 0;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    priority_queue<int,vector<int>,greater<int>> pq;
    int popcount = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> value;
            pq.push(value);
        }
        while (pq.size() > N)
        {
            pq.pop();
        }
    }
    cout << pq.top() << endl;

}
