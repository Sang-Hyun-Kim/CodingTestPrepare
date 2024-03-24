// 프로그래머스 2024 KAKAO WINTER INTERNSHIP
// N + 1 카드게임 Lv. 3
// 인덱스 조절과 끝내는 분기를 잘 조절한다면 금방 푼다.
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
int NP;
bool FindBetweenTwo(set<int>& _d1, set<int>& _d2);
int solution(int coin, vector<int> cards) {
    int answer = 1;
    int sz = cards.size();
    int hsize = sz / 3;// 0~hsize-1 : hand, hsize~cards.size()-1 : deck
    NP = cards.size() + 1;
    set<int> hand;
    for (int i = 0; i < hsize; ++i)
    {
        hand.insert(cards[i]);
    }
    set<int> discard;
    int rcnt = hsize;
    while (rcnt<sz)// todo:몇라운드할지 지정
    {
        for (int i = 0; i < 2; ++i)
        {
            discard.insert(cards[rcnt++]);
        }
        
        if (hand.size()>=2 && FindBetweenTwo(hand,hand))
        {// 핸드에서성공, hand에서 쌍이 제거 될 것
            answer++;
            continue;
        }
        else
        {   // 코인하나로
            if (hand.size() >= 1 && coin>=1&& FindBetweenTwo(hand, discard))
            {
                coin--;
                answer++;
                continue;
            }
            else
            {// 코인두개로
                if (coin >= 2&&FindBetweenTwo(discard,discard))
                {
                    coin -= 2;
                    answer++;
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
        if (coin < 0)
        {
            break;
        }
    }
    return answer;
}
bool FindBetweenTwo(set<int>& _d1, set<int>& _d2)
{ // 핸드에서 n+1을 만족하는 쌍을 찾으면 지우고 true반환
    for (auto c : _d1)
    {
        auto iter = find(_d2.begin(), _d2.end(), NP - c);
        if (iter != _d2.end())
        {
            _d1.erase(c);
            _d2.erase(iter);
            return true;
        }
    }
    return false;
}

int main()
{
    auto answer = solution(4, { 3, 6, 7, 2, 1, 10, 5, 9, 8, 12, 11, 4 });
    cout << answer; 
}
