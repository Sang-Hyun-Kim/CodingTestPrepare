// 2024_KAKAO_WINTER_INTERNSHIP_주사위고르기.cpp 
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
int nums;
int half;
void Pickdices(set<int>& _cur, vector<int>& comb, vector<int>& results, int nums, int index, vector<vector<int>>& dice);
vector<int> solution(vector<vector<int>> dice) {
    vector<int> answer;
    int maxwin = 0;
    nums = dice.size();
    half = nums / 2;
    vector<int> picks;
    map<set<int>, int> cache;
    for (int i = 1; i <= nums; ++i)
    {
        picks.push_back(i);
    }
    do
    {
        set<int> curA(picks.begin(), picks.begin() + half);
        set<int> curB(picks.begin() + half, picks.end());
        // 중복 체크
        
        if (cache[curA] == 0)
        {
            // 계산
            // 주사위수 n/2개 각각의 6가지의 값의 합의 비교
            // 고른 주사위 수 n/2개의 조합에 대한 반복문
            vector<int> Acombs(half);
            vector<int> Aresults;
            vector<int> Bcombs(half);
            vector<int> Bresults;
            map <int, int> sum;
            Pickdices(curA, Acombs, Aresults, half, 0, dice);
            Pickdices(curB, Bcombs, Bresults, half, 0, dice);
            sort(Aresults.begin(), Aresults.end());
            sort(Bresults.begin(), Bresults.end());
            for (auto ar : Aresults)
            {
                if (sum[ar] != 0)
                {
                    cache[curA] += sum[ar];
                    continue;
                }

                int start = 0; int end = Bresults.size();

                while (start +1 < end)
                {
                    int mid = (start + end) / 2;
                    if (ar > Bresults[mid])
                    {
                        start = mid;
                    }
                    else
                    {
                        end = mid;
                    }
                }
                sum[ar] = start;
                cache[curA] += start;
            }

            if (maxwin < cache[curA])
            {
                maxwin = cache[curA];
                answer.clear();
                answer.assign(curA.begin(), curA.end());
            }
        }

    } while (next_permutation(picks.begin(), picks.end()));

    return answer;
}

void Pickdices(set<int>& _cur, vector<int>& comb, vector<int>& results, int nums, int index, vector<vector<int>>& dice)
{
    if (index == nums)
    {
        int curvalue = 0;
        int comindex = 0;
        for (auto n : _cur)
        {
            curvalue += dice[n - 1][comb[comindex]];
            comindex++;
        }
        results.push_back(curvalue);
        return;
    }
    for (int i = 0; i < 6; ++i)
    {
        comb[index] = i;
        Pickdices(_cur, comb, results, nums, index + 1, dice);
    }
}

int main()
{
    vector<int> answer = solution({ {40, 41, 42, 43, 44, 45},{43, 43, 42, 42, 41, 41},{1, 1, 80, 80, 80, 80},{70, 70, 1, 1, 70, 70} });

    int a = 0;

}

