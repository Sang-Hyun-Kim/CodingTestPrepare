// HeapCodTest_001.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// 우선순위 큐(오름차순)으로 정리해서
//  제일 작은 값 + 그 다음 작은 값 * 5 해서 우선순위 Queue 안에 넣고
// K (넘어야하는 스코빌 지수) 값을 넘냐? 비교 후 아니면 재진행
// 실패시 -1 return;
// 한번 돌때마다 answer ++;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int,vector<int>,greater<int>> pq;
    for (int i : scoville)
    {
        pq.push(i);
    }
    int curLeast = 0;
    while (pq.top() < K)
    {
        if (pq.size() < 2)
        {
            return -1; // 최소값이 K를 못넘었는데 size가 1이하일 경우(마지막 하나)
        }

        curLeast = pq.top();
        pq.pop();
        curLeast += pq.top() *2;
        pq.pop();
        pq.push(curLeast);
        answer++;
    }

    return answer;
}

int main()
{
    int answer = solution(vector<int>{1,2}, 7);   
    cout << answer << endl;
    return 0;
}