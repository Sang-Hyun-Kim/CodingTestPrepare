// 백준 저울

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
// 출력: 구슬 하나에 대해 Y or N 하고 한칸 띄우기
// 왼쪽에 구슬을 놓는다고 가정했을 때
// 현재 왼쪽과 오른쪽의 무게가 같지 않을 경우 0. 추를 오른쪽에, 1. 추를 왼쪽에, 2. 올려놓지 않는다.

// 0인경우 => 아직 계산이 안됨 => cache 계산
// -1 => 불가능 , 1 => 가능 => 반환
// 좀 더 좋은 풀이=> 주어진 추로 나올 수 있는 모든 무게 값을 2차원 배열로 미리 계산, 저장한다음 주어지는 무게추에 대해 바로바로 dp 비교로 true || false 반환...
using namespace std;
int Confirmable(vector<int>& _weights, map<pair<int, pair<int, int>>, int>& _cache, int _weightnum, int _way, int _currentW);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int wcnt;
    cin >> wcnt;
    vector<int> weights(wcnt, 0); // 추
    for (int i = 0; i < wcnt; ++i)
        cin >> weights[i];
    int mcnt;
    cin >> mcnt;
    vector<int> marbles(mcnt, 0); // 구슬
    for (int i = 0; i < mcnt; ++i)
        cin >> marbles[i];
    map<pair<int, pair<int, int>>, int> cache;// {현재 무게 차,{추 번호, 방법}},0,1 => 1: 성공 0 실패;
    // 왼쪽 무게 추가 : -값, 오른쪽 무게 추가 + 값

    for (auto marble : marbles)
    {
        int currentW = -1 * marble;
        int answer = 0;
        answer = max({Confirmable(weights,cache,0,0,currentW),Confirmable(weights,cache,0,1,currentW),Confirmable(weights,cache,0,2,currentW) });
        if (answer == 1) cout << "Y ";
        else cout << "N ";

    }
}

int Confirmable(vector<int>& _weights, map<pair<int, pair<int, int>>, int>& _cache,int _weightnum,int _way,int _currentW)
{
    // 초기값
    // - 마지막무게 추에 대한 처리;
    if (_weightnum >= _weights.size())
    { //마지막 이후는 전부 X 반환
        return 0;
    }
    // 캐쉬 확인
    // 왼쪽에 넣기 안넣기 오른쪽에 넣기 이후의 값 계산 맡기고
    // 해당 값 저장하기
    // 캐쉬 확인
    if (_cache.find({ _currentW,{_weightnum,_way}}) != _cache.end())
    {
        return _cache.at({ _currentW,{_weightnum,_way} });
    }

    // 캐쉬 계산 후 저장
    else // ==0 인 경우
    {// 넘겨받은 방법에 따라 계산 0: 오른쪽, 1: 왼쪽, 2: 올려놓지 않는다.
        // 계산이 성공하면 =1
        // 아니면 그 다음 것 계산
        int nextW = _currentW;
        if (_way == 0)
        {
            nextW += _weights[_weightnum];
            if (nextW == 0)
            {
                _cache.insert({ {_currentW,{_weightnum,_way}},1 });
                return 1;
            }
            else
            {
                int value = max(
                    {Confirmable(_weights,_cache,_weightnum+1,0,nextW),Confirmable(_weights,_cache,_weightnum + 1,1,nextW) ,Confirmable(_weights,_cache,_weightnum + 1,2,nextW) }
                );
                _cache.insert({ {_currentW,{_weightnum,_way}},value });
                return value;
            }
        }
        else if (_way == 1)
        {
            nextW -= _weights[_weightnum]; // 왼쪽 저울의 무게는 음수로
            if (nextW == 0)
            {
                _cache.insert({ {_currentW,{_weightnum,_way}},1 });
                return 1;
            }
            else
            {
                int value = max(
                    { Confirmable(_weights,_cache,_weightnum + 1,0,nextW),Confirmable(_weights,_cache,_weightnum + 1,1,nextW) ,Confirmable(_weights,_cache,_weightnum + 1,2,nextW) }
                );
                _cache.insert({ {_currentW,{_weightnum,_way}},value });
                return value;
            }
        }
        else// _way == 2
        {// 뭐가 안됐으니까 안올렸겠지 바로 다음진행
            int value = max(
                { Confirmable(_weights,_cache,_weightnum + 1,0,nextW),Confirmable(_weights,_cache,_weightnum + 1,1,nextW) ,Confirmable(_weights,_cache,_weightnum + 1,2,nextW) }
            );
            _cache.insert({ {_currentW,{_weightnum,_way}},value });
            return value;
        }
    }
    // 캐쉬 반환
}