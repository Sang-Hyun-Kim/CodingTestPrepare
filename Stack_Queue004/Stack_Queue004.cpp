#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

int solution(vector<int> priorities, int location) {
    
    
    int answer = 1;
    int index = 0; 
    queue<pair<int,int>> q;
    vector<int> priority;// 해당 vector에는 vector priorities의 Index를 순서대로 보관할 예정임

    for (int i = 0; i < priorities.size(); ++i)
    {
        q.push({ priorities[i],i });
    }
    sort(priorities.begin(), priorities.end(), greater<>()); // [1,5,4,2,3,6,5]  => [6,5,5,4,2,3,1]

    while (!q.empty())
    {
        pair<int, int> current = q.front();
        q.pop();
     
        if (current.first == priorities[index])
        {
            if (current.second == location)
            {
                break;
            }
            
            index++;
            answer++;
        }
        else
            q.push(current);
      
    }

    return answer;
}

int main()
{
    solution(vector<int>{1, 1, 9, 1, 1}, 0);
    return 0;
}
// priorities       index 실행 순서
// [1,5,4,2,3,6,5]  [0,1,2,3,4,5,6]
// [6,5,1,5,4,2,3]  [5,6,0,1,2,3,4]
// [5,1,5,4,2,3]    [5][6,0,1,2,3,4]
// [1,5,4,2,3]      [5,6][0,1,2,3,4]
// [5,4,2,3,1]      [5,6][1,2,3,4,0]
// [4,2,3,1]        [5,6,1][2,3,4,0]
// [2,3,1]          [5,6,1,2][3,4,0]
// [3,1,2]          [5,6,1,2][4,0,3]
// [1,2]            [5,6,1,2,4][0,3]
// [2,1]            [5,6,1,2,4][3,0]
// [1]              [5,6,1,2,4,3][0]
// []               [5,6,1,2,4,3,0]
// 재배치 또는 Pop
// 조건-> 현재 Priority가 다른 Priority와 비교하며 판단 있으면 순회 + Cache화 하여 순회 필요 없애기
