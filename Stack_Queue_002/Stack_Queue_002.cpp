// Stack_Queue_002.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
vector<int> solution(vector<int> progresses, vector<int> speeds);

int main()
{
    vector<int> v1 = { 95, 90, 99, 99, 80, 99 };
    vector<int> v2 = { 1, 1, 1, 1, 1, 1 };
    vector<int> answer1 = solution(v1,v2);
    for (auto iter = answer1.begin(); iter != answer1.end(); ++iter)
        cout << *iter << endl;
    return 0;
}

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    
    int day = 0; // 기준 배포 갱신
    int jobDays; // 계산된 개발 소요 일 수
    vector<int> answer;

    
    for (int i = 0; i < progresses.size(); i++)
    {
        jobDays = ceil( ( (double)( 100 - progresses[i] ) / (double)speeds[i] ) );

        if (answer.empty() || day < jobDays)
            answer.push_back(1);
        else
            ++answer.back();

        if (jobDays > day) // 배포 날짜 갱신
            day = jobDays;
    }
    return answer;
}