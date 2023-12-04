// 백준 2482 색상환
// 골드 2

#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;

typedef long long LL;
const LL MOD = 1000000003;
// 고르는 방법을 S라고할때
// nSk = n-1 S k + n-3 S k-1

LL Count(vector<vector<LL>> &Cache, int _color, int _pick);
int main()
{
    int count;
    int pick;
    cin >> count;
    cin >> pick;


    vector<vector<LL>> Cache(count + 1, vector<LL>(count +1 , -1));
    for (int i = 0; i < count + 1; i++)
    {
        
        Cache[i][0] = 1;
        Cache[i][1] = i;
    }

    LL answer = Count(Cache, count, pick);
    cout << answer << endl;
}

// 숫자는 4부터 1000까지다


LL Count(vector<vector<LL>>& _Cache, int _color, int _pick)
{
    if (_color == 1 && _pick == 1)
        return 1;
    if (_color / 2 < _pick)
        return 0;

    if (_Cache[_color][_pick] != -1)
        return _Cache[_color][_pick];

    // 저장된 계산값이 없다면 
    _Cache[_color][_pick] = (Count(_Cache, _color - 1, _pick) + Count(_Cache, _color - 2, _pick - 1))% MOD ;
    
    return _Cache[_color][_pick];
  
}
// 4 2
// => 3 2 + 1 1   1 2 3 4  => 1 2 3 
// => 2 2 + 0,1 + 1 1
// => 1 2 