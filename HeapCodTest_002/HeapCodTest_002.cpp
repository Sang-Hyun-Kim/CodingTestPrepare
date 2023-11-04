#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;


// [n,i] A 작업이 끝나고 다음 요청 B 작업 [m,j]의 시간
// 첫작업을 제외 A 작업이 끝난 지점(index) + j 에서 끝나고
//  B 작업의 평균 작업 시간은 첫 ((index)+j - m(요청시간) ) / 총 작업량
// 하드디스크가 작업을 수행하고 있지 않을 때에는 먼저 요청이 들어온 작업부터 처리합니다.
int solution(vector<vector<int>> jobs) {
    int answer = 0;
    int time = 0; // 현재 수행 가능한지 
    int index = 0; // jobs에서 index 관리
    struct cmpGreater {
        bool operator()(vector<int> a, vector<int> b)
        {
            return a[1] > b[1];
        }


    };

    priority_queue < vector<int>, vector<vector<int>>, cmpGreater > scheduler;

  /*  for (auto job : jobs) {
        scheduler.push(job);
    }*/

    sort(jobs.begin(), jobs.end()); // 작업 요청 시간별 

    while (jobs.size() > index || !scheduler.empty() )  // [작업요청시간, 작업수행시간], 작업 종료시간 - 작업 요청시간 => 총 요청 시간 , job 순회가 끝났어도 실행되어야함
    {
        if (jobs.size() > index && time >= jobs[index][0]) // 현재 시간 < 작업의 요청 시간 => 아직 실행 할 수 없다 + jobs에서 아직 안넣은 요소가 있나?
        {
            auto next = jobs[index];
            scheduler.push(next);
            index++;// jobs index 증가
            continue;
        }
        // Jobs를전부 순회 헀거나 현재시간(time)에 와있는 요청이 없는 경우 (time < jobs[index][0]) => jobs를 정렬해놨기 때문에
        
        if (!scheduler.empty()) // scheduler가 비어있냐
        {  
            auto currentJob = scheduler.top();
            scheduler.pop();
            
            time = time + currentJob[1]; // 작업완료, 작업완료시 현재 시간 갱신(이전 시간 + 작업 소요 시간)
            answer += time - currentJob[0]; // 완료 된 작업의 소요 시간은 
        }
        else // 현재 시간에 아직 아무 요청도 없고 스케쥴러도 없는 경우
        {
            time = jobs[index][0]; // 시간을 가장 빠른 현재 시간으로 당기기 => 아무 요청이 없을 경우 스케쥴러는 가장 빠른 요청을 처리하게 됨
        }
    }
 
    return answer / jobs.size();
}

int main()
{
    int answer = solution(vector<vector<int>>{{0, 3}, { 1,9 }, {2,6}});
    cout << answer << endl;
    return 0;
}