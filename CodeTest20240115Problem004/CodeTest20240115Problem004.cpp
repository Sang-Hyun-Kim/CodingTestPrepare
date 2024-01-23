// 프로그래머스 2024 KAKAO WINTER INTERNSHIP
// N + 1 카드게임 Lv. 3

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
int NUM;
// set<int> hand는 매턴 변경되는 핸드를 기록
// map의 key로 라운드,set<int>hand,남은동전, value로 갈 수 있는 최대 round
int Discard(set<int> _hand);
int Memoization(int round, int coin, set<int> _hand, map<pair<int, pair<set<int>, int>>, int>& _cache, vector<int>& _cards);
int solution(int coin, vector<int> cards) {
    int answer = 0;
    NUM = cards.size();
    
    set<int> hand;
    for (int i = 0; i < NUM / 3; ++i)
    {
        hand.insert(cards[i]);
    }

    map<pair<int, pair<set<int>, int>>, int> cache;
    // 메모이제이션 실행
    answer = Memoization(1, coin, hand, cache, cards);
    return answer;
}
int Memoization(int round,int coin,set<int> _hand, map<pair<int, pair<set<int>, int>>, int>& _cache,vector<int>& _cards)
{
    if (coin < 0) return round;
    if (round >= NUM / 3 + 1) return NUM / 3 + 1; // 최대 라운드 도달
    int first = NUM / 3 + round * 2 - 2;
    int second = NUM / 3 + round * 2 - 1;
    auto key = make_pair(round, make_pair(_hand,coin));
    if (_cache[key] == 0) // 값이 없다면, 모든 경우는 최소한 1을 저장해야함
    {
        // 4가지 분기로 뻗어서 최대값을 반환받고 그것을 저장
        // 분기 1: 이번턴의 아무 카드도 받지 않고 자체적으로 _hand에서 해결 
        // 분기 2: 이번턴에 동전 하나를 소모해서 첫번째 카드를 드로우 한 다음 해결
        // 분기 3: 이번턴에 동전 하나를 소모해서 두번째 카드를 드로우 한 다음 해결
        // 분기 4: 이번턴에 동전 두 개를 소모해서 패에 전부 넣고 해결
        // 현재 카드만으로 해결 가능하냐
        auto card = Discard(_hand);
        if (card != -1)
        {
            // 패로 들어오는 두가지의 카드도 가능한지 확인 해야함
            _hand.erase(_hand.find(card));
            _hand.erase(_hand.find(NUM + 1 - card));
            // _hand의 분기 생성
            auto _handA = _hand;
            auto _handB = _hand;
            auto _handAB = _hand;

            _handA.insert(_cards[first]); _handB.insert(_cards[second]); _handAB.insert(_cards[first]); _handAB.insert(_cards[second]);
            
            _cache[key] = max(Memoization(round + 1, coin, _hand, _cache, _cards),
                max(Memoization(round + 1, coin - 1, _handA, _cache, _cards),
                    max(Memoization(round + 1, coin - 1, _handB, _cache, _cards),
                        Memoization(round + 1, coin - 2, _handAB, _cache, _cards)))
            );
            
        }
        else
        {// 현재 패에서 해결 불가능
            auto _handA = _hand;
            auto _handB = _hand;
            auto _handAB = _hand;
            _handA.insert(_cards[first]); 
            _handB.insert(_cards[second]);
            _handAB.insert(_cards[first]);
            _handAB.insert(_cards[second]);
            auto firstcard = Discard(_handA);
            auto secondcard = Discard(_handB);
            if (coin > 1)
            {
                // 첫패와 두번째패의 짝이 _hand에 있는지 확인 하고 분기
                if (firstcard != -1 && secondcard == -1)
                {// 첫패를 산다음 해결이 가능한 경우 => coin -1 하고 짝을 지우고 다음 라운드로 넘어가기
                    auto _handAD = _handA;
                    _handAD.erase(_handAD.find(firstcard));
                    _handAD.erase(_handAD.find(NUM + 1 - firstcard));
                    auto _handADB = _handAD;
                    _handADB.insert(_cards[second]);
                    // 돈하나 써서 버린 다음 패로 다음 라운드 와 동전 두 개 써서 짝하나 버리고 다른 패도 넣고 다음 라운드 진행 
                    _cache[key] = max( Memoization(round+1,coin-1,_handAD,_cache,_cards),Memoization(round+1,coin-2,_handADB,_cache,_cards));
                                    
                }
                else if (firstcard == -1 && secondcard != -1)
                {// 두번째 패로는 가능한 경우
                    auto _handBD = _handB;
                    _handBD.erase(_handBD.find(secondcard));
                    _handBD.erase(_handBD.find(NUM + 1 - secondcard));
                    auto _handBDA = _handBD;
                    _handBDA.insert(_cards[first]);
                    _cache[key] = max(Memoization(round + 1, coin - 1, _handBD, _cache, _cards), Memoization(round + 1, coin - 2, _handBDA, _cache, _cards));

                }
                else if(firstcard != -1 && secondcard != -1)
                { // 둘다 가능 한경우
                    auto _handAD = _handA;
                    _handAD.erase(_handAD.find(firstcard));
                    _handAD.erase(_handAD.find(NUM + 1 - firstcard));
                    auto _handBD = _handB;
                    _handBD.erase(_handBD.find(secondcard));
                    _handBD.erase(_handBD.find(NUM + 1 - secondcard));
                    auto _handADB = _handAB;
                    auto _handBDA = _handAB;
                    _handADB.erase(_handADB.find(firstcard));
                    _handADB.erase(_handADB.find(NUM + 1 - firstcard));
                    _handBDA.erase(_handBDA.find(secondcard));
                    _handBDA.erase(_handBDA.find(NUM + 1 - secondcard));
                    // 첫패를 버릴지, 첫패를 버리고 두번째패를 가져갈지, 두번째 패를 버릴지, 두번째 패를 버리고 첫패를 가져갈지
                    _cache[key] = max(Memoization(round + 1, coin - 1, _handAD, _cache, _cards), 
                        max(Memoization(round + 1, coin - 2, _handADB, _cache, _cards), 
                            max(Memoization(round + 1, coin - 1, _handBD, _cache, _cards), Memoization(round + 1, coin - 2, _handBDA, _cache, _cards))));

                }
                else
                {
                    // 패에서는 해결 안되는데 두개 다 사서 해결 가능한 경우
                    if (_cards[first] + _cards[second] == NUM + 1)
                    {
                        _cache[key] = Memoization(round+1,coin-2,_hand,_cache,_cards);
                    }
                    else
                    {
                        // 코인이 몇개든 현재 가진패와 들어오는 패로 해결 불가능
                        _cache[key] = round;
                    }
                } 
            }
            else if (coin == 1)
            {
                // 첫패와 두번째패의 짝이 _hand에 있는지 확인 하고 분기
                if (firstcard != -1 && secondcard == -1)
                {// 첫패를 산다음 해결이 가능한 경우 => coin -1 하고 짝을 지우고 다음 라운드로 넘어가기
                    auto _handAD = _handA;
                    _handAD.erase(_handAD.find(firstcard));
                    _handAD.erase(_handAD.find(NUM + 1 - firstcard));
               
                    _cache[key] = Memoization(round + 1,0,_handAD,_cache,_cards);
                }
                else if (firstcard == -1 && secondcard != -1)
                {// 두번째 패로는 가능한 경우
                    auto _handBD = _handB;
                    _handBD.erase(_handBD.find(secondcard));
                    _handBD.erase(_handBD.find(NUM + 1 - secondcard));
                 
                    _cache[key] = Memoization(round + 1, 0, _handBD, _cache, _cards);

                }
                else if (firstcard != -1 && secondcard != -1)
                { // 둘다 가능 한경우
                    auto _handAD = _handA;
                    _handAD.erase(_handAD.find(firstcard));
                    _handAD.erase(_handAD.find(NUM + 1 - firstcard));
                    auto _handBD = _handB;
                    _handBD.erase(_handBD.find(secondcard));
                    _handBD.erase(_handBD.find(NUM + 1 - secondcard));

                    // 첫패 사서 버리기 vs 두번째패 사서 버리기
                    _cache[key] = max(Memoization(round + 1, 0, _handAD, _cache, _cards), Memoization(round + 1, 0, _handBD, _cache, _cards));

                }
                else
                {// 코인이 몇개든 현재 가진패와 들어오는 패로 해결 불가능
                    _cache[key] = round;
                }
            }
            else//coin == 0
            {// 라운드 종료
                _cache[key] = round;
            }
        }
        return _cache[key];
    }
    return _cache[key];
}
// set<int> _hand 를 넘겨 받아 해결하는 함수
int Discard(set<int> _hand)
{
    if (_hand.size() == 0) return -1;
    for (auto a : _hand)
    {
        auto it = _hand.find(NUM + 1 - a);
        if (it !=_hand.end())         {
            return *it; // 합을 이루는 쌍이 있으면 루프를 끝내버리고 해당 쌍을반환, 가장 작은 값으로 시작하는 쌍을 반환함
        }
    }
    return -1;
}

int main()
{
    auto answer = solution(4, { 3,6,7,2,1,10,5,9,8,12,11,4 });
    cout << answer; 
}
