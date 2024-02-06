// 백준 1700번 멀티탭 스케쥴링

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int Remove_one(int now, vector<int>& _powerBar, vector<int>& _changing);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int msize; int elect;
    cin >> msize >> elect;
    vector<int> changing(elect);

    vector<int> powerBar;
    int changecount = 0;
    for (int i = 0; i < elect; ++i)
    {
        cin >> changing[i];
    }
    // 전기 제품의 사용 횟수를 입력받고 멀티탭의 꽂힌 플러그의 변경을 최소화 하는 방법
    // 꽂힌 것중 현재 시점에서 나중에 등장하는 녀석을 뽑기
    for (int i = 0; i < elect; ++i)
    {
        int current = changing[i];
        auto iter = find(powerBar.begin(), powerBar.end(), current);
        // 현재 꽂혀있는건가
        if (iter == powerBar.end())
        {// 꽂혀있지 않음
            if (powerBar.size() >= msize)
            {
                auto plug = Remove_one(i, powerBar, changing);
                powerBar.erase(remove(powerBar.begin(), powerBar.end(), plug));
                changecount++;
                powerBar.push_back(current);
            }
            else powerBar.push_back(current);

        }
    }
    cout << changecount;
}

int Remove_one(int now,vector<int>& _powerBar,vector<int>& _changing) //삭제할 요소를 반환하는 함수
{
    int last = -1;
    for (auto plug : _powerBar)
    {
        int index = -1;
        for (int i = now; i < _changing.size(); ++i)
        {
            if (_changing[i] == plug)
            {
                index = i;
                break;
            }
        }
        if (index == -1) return plug;
        else  last = max(last, index);

    }
    return _changing[last];
}

/* 빈도를 기준으로 풀면 최적해가 아님
// 백준 멀티탭 스케쥴링

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int msize; int elect;
    cin >> msize >> elect;
    vector<int> changing(elect);
    vector<int> frequency(elect+1,0);
    map<int, int> powerBar;
    int changecount = 0;
    for (int i = 0; i < elect; ++i)
    {
        cin >> changing[i];
        frequency[changing[i]]++;//전체 사용 횟수
    }
    // 전기 제품의 사용 횟수를 입력받고 멀티탭의 꽂힌 플러그의 변경을 최소화 하는 방법

    for (auto a : changing)
    {
        auto iter = powerBar.find(a);
        if (iter == powerBar.end()) // 멀티탭안에 꽂혀있지 않다면
        {
            if (powerBar.size() < msize)
            {
                powerBar.insert(make_pair(a, frequency[a]));
            }
            else
            {
                auto pullout = min_element(powerBar.begin(), powerBar.end(), [](const auto& a, const auto& b)
                    {
                        if (a.second == b.second)
                        {
                            return a.first < b.first;
                        }
                        return a.second < b.second;
                    });
                powerBar.erase(pullout);
                powerBar.insert(make_pair(a, frequency[a]));
                changecount++;
            }
        }

    }
    cout << changecount;
}
*/