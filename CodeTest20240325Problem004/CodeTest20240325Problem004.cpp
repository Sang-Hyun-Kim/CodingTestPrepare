// 백준 14572 스터디그룹
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
int sn, ak, d = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> sn >> ak >> d;
    vector<int> studentIndex;
    vector<pair<int,pair<int,vector<int>>>> studentD; // 실력,학생 번호; 실력 내림차순정리
    studentD.reserve(sn);
    vector<vector<int>> studentAL(sn); // i번학생이 가지고잇는 알고리즘들 [i]{};
    
    set<int> group;
    int stdnum;
    for (int i = 0; i < sn; ++i)
    {
        int san, sd = 0;
        cin >> san >> sd;
        studentD.push_back({ sd,{i,{}} });
        for (int j = 0; j < san; ++j)
        {
            int sa;
            cin >> sa;
            studentAL[i].push_back(sa);
        }
    }

    sort(studentD.begin(), studentD.end(), [&](auto& a, auto& b)->bool
        {
            if (a.first == b.first)
                return a.second.first < b.second.first;
            return a.first < b.first;
        });

    int low = 0; 
    int high = 0;

    while (high< sn)
    {
        if (studentD[high].first - studentD[low].first > 10)
        {              
            // 그룹 변경
             
            // 인덱스 변경 // 낮은칸 하나 증가=> 증가 해도 같은 실력 다른 학생일 경우?
        }
        else
        {
            // 그룹에 넣고 
            
            // 인덱스 변환
            high++;
        }
    }
        
}

