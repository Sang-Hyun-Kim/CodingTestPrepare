
// 프로그래머스 고득점 Kit 정렬 H-index
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
    int n = citations.size();
    int hidx = 0;

    sort(citations.begin(), citations.end());

    // iterator lower_bound(시작점, 끝점,값,비교함수) 
    // => [시작점,끝지점) 사이에서 값보다 이전에 정렬되는 값중 가장 앞의 값을 원소로 가진 iterator를 반환 
    // vector가 연속된 iterator임을 착안 해당 위치에서 빼고 더하고의 값을 통해 H-index를 찾으면된다.
    while (true)
    {
        auto iter = lower_bound(citations.begin(), citations.end(), hidx);
        if (citations.end() - iter >= hidx && iter - citations.begin() <= hidx)
            hidx++;
        else
            break;
    }
    answer = hidx - 1;
    return answer;
}

int main()
{

}