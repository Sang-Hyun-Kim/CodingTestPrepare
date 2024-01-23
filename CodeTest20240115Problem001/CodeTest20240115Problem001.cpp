// 프로그래머스 2024 KAKAO WINTER INTERNSHIP
// 가장 많이 받은 선물 LV.1

//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;
// 서로 주고받은 기록이 있는 경우 두사람 사이에 더 많은 선물을 준 사람이 다음 달에 선물을 하나 받습니다.
// map1 : {주는 사람 : 받는사람, 횟수 } , map2 <인물 : 선물지수>


int solution(vector<string> friends, vector<string> gifts) {
    int answer = 0;
    std::vector<std::string> result;
    map<pair<string, string>, int> presents;
    map<string, int> gPoint;
    map<string, int> nextday;
    for (auto a : friends)
    {
        gPoint.insert(make_pair(a,0));
        nextday.insert(make_pair(a, 0));
    }
    for (auto a : gifts)
    {
        istringstream iss(a);
        string giver;
        string receiver;
        iss >> giver;
        iss >> receiver;
        gPoint[giver]++;
        gPoint[receiver]--;
        auto pairs = make_pair(giver, receiver);
        if (presents.find(pairs) == presents.end())
        {
            presents.insert(make_pair(pairs, 1));
            continue;
        }
        presents[pairs]++;
    }

    // 두 사람 사이의 주고 받은 기록 확인
    // 중복 처리 필요
    for (int i = 0; i < friends.size()-1; ++i)
    {
        for (int j = i+1; j < friends.size(); ++j)
        {
            auto friend1 = friends[i];
            auto friend2 = friends[j];
            // 서로 주고 받은 기록 확인
            bool both = true;
            auto iter1 = presents.find(make_pair(friend1, friend2));
            auto iter2 = presents.find(make_pair(friend2, friend1));

            if (iter1 != presents.end() && iter2 == presents.end())
            {// friend1->friend2 로만 기록이있음
                nextday[friend1]++;
            }
            else if(iter2 != presents.end() && iter1 == presents.end())
            {// friend2->friend1 로만 기록이있음
                nextday[friend2]++; 
            }
            else if (iter1 != presents.end() && iter2 != presents.end())
            {
                if (iter1->second > iter2->second)
                {
                    nextday[friend1]++;
                }
                else if (iter1->second < iter2->second)
                {
                    nextday[friend2]++;
                }
                else // ==
                { // 선물지수 가 큰 쪽이 선물을 받게 됨
                    if (gPoint[friend1] > gPoint[friend2])
                    {
                        nextday[friend1]++;
                    }
                    else if (gPoint[friend1] < gPoint[friend2])
                    {
                        nextday[friend2]++;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else // 서로 준 적이 없음
            {// 선물지수
                if (gPoint[friend1] > gPoint[friend2])
                {
                    nextday[friend1]++;
                }
                else if (gPoint[friend1] < gPoint[friend2])
                {
                    nextday[friend2]++;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    auto pr = max_element(nextday.begin(), nextday.end(), [](auto x, auto y)
        {
            return x.second < y.second;
        });

    return pr->second;
}

int main()
{
    vector < string> friends{ "muzi", "ryan", "frodo", "neo" };
    vector<string> gifts{ "muzi frodo", "muzi frodo", "ryan muzi", "ryan muzi", "ryan muzi", "frodo muzi", "frodo ryan", "neo muzi" };

    cout << solution(friends, gifts);
}
