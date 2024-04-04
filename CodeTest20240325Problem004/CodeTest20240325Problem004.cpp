// 백준 14572 스터디그룹
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <bitset>
#include <algorithm>
using namespace std;
int sn, ak, d = 0;
int effi=0;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> sn >> ak >> d;
    vector<pair<int,bitset<30>>> students(sn);
   // 각 학생들이 아는 알고리즘 비트(int형 한칸=> 알고있는 알고리즘, 알고있는 알고리즘 n에 대해서 & 2의n승)
   for (int i = 0; i < sn; ++i)
   {
       int san, score;
       cin >> san >> score;
       students[i].first = score;
       for (int j = 0; j < san; ++j)
       {
           int a;
           cin >> a; 
           students[i].second |= (1ULL << (a-1));// i학생이 a알고리즘을 알고있다: i번째 인트의 자리수 1활성화
       }
   }
   sort(students.begin(), students.end(), [&](auto& a,auto& b)->bool {
       if(a.first == b.first)
           return a.second.to_ulong() < b.second.to_ulong();
       return a.first < b.first; });

   // 그룹내 학생들이 아는 비트
   // 그룹내 학생들이 동시에 알고 있는 비트
   
    int low = 0; 
    int high = 0;
    bitset<30> alla=students[low].second;
    bitset<30> aka=students[low].second;
    while (high < sn)
    {
        if (students[high].first- students[low].first<=d)
        {// 그룹 가입 가능, 효율성 계산
            alla |= students[high].second;
            aka &= students[high].second;
            bitset<30> group = alla & (~aka);
            int count = 0;
            for (int i =0;i<group.size();++i)
            {
                if (group[i] == 1)
                    count++;
            }
            effi = max(effi, count * (high - low + 1));
            high++;
        }
        else
        {// 그룹 변경
            while (students[high].first - students[low].first > d)
                low++;
            // 점수 범위안에 드는 가장 낮은 학생
            // 현재 그룹 계산
            alla = students[low].second;
            aka = students[low].second;
            int curlow = low;
            while (curlow <= high)
            {
                alla |= students[curlow].second;
                aka &= students[curlow].second;
                curlow++;
            }
            bitset<30> group = alla & (~aka);
            int count = 0;
            for (int i = 0; i < group.size(); ++i)
            {
                if (group[i] == 1)
                    count++;
            }
            effi = max(effi, count * (high - low + 1));
            high++;
        }
    }
    cout << effi;
}

