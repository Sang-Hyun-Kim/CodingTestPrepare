/*
프로그래머스 2023 현대 모비스 알고리즘 경진대회 예선상담원 인원
// 조합
// 완전탐색
*/
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
vector<vector<int>> coms;
int mintime = 300000000;
void make_combination(int n, int idx, vector<int> combinations);
int solution(int k, int n, vector<vector<int>> reqs) {
    int answer = 0;
    vector<int> com(k + 1, 1);
    make_combination(n - k, 1, com);

    for (auto curcom : coms)
    {
        int curmintime = 0;
        vector<priority_queue<int, vector<int>, greater<int>>> mentors(k + 1);
        for (int i = 1; i <= k; ++i)//0 제외 1~k번
        {
            for (int j = 0; j < curcom[i]; ++j)
            {
                mentors[i].push(0);//현재 조합의상담원 갯수만큼 초기 상담시간 기입
            }
        }

        // 상담시작

        for (auto req : reqs)
        {
            int curtype = req[2];
            int curst = req[0];
            int curdur = req[1];

            if (mentors[curtype].top() > curst)
            {
                int timediff = mentors[curtype].top() - curst;

                mentors[curtype].push(mentors[curtype].top() + curdur);
                mentors[curtype].pop();
                curmintime += timediff;
            }
            else
            {// 상담 가능
                mentors[curtype].pop();
                mentors[curtype].push(curst + curdur);
            }

        }
        mintime = min(mintime, curmintime);

    }



    return mintime;
}
void make_combination(int n, int idx, vector<int> combinations)
{
    if (n <= 0)
    {
        coms.push_back(combinations);
        return;
    }
    else
    {
        for (int i = idx; i < combinations.size(); ++i)
        {
            combinations[i]++;
            make_combination(n - 1, i, combinations);
            combinations[i]--;
        }
    }

}