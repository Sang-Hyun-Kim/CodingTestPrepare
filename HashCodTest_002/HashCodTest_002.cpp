#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
// N P Q 입력받기
// 백준 1351번 무한 수열
// 수열 저장받기
using namespace std;
long long Cal(long long _number, long long& _P, long long& _Q, unordered_map<long long, long long>& _cache);
int main()
{
	// 00 ≤ N ≤ 1조
	// 2 ≤ P, Q ≤ 10억
	long long N;
	long long P;
	long long Q;
	
	cin >> N;
	cin >> P;
	cin >> Q;

	unordered_map<long long, long long> cache;
	cache[0] = 1;
	cache[1] = 2;
	long long answer = Cal(N,P,Q,cache);
	cout << answer << endl;
	return 0;
}

long long Cal(long long  _number, long long& _P, long long& _Q, unordered_map<long long, long long>& _cache)
{
	
	if (_number == 0)
	{
		return _cache[0]; // 1
	}
	if (_number == 1)
	{
		return _cache[1]; // 2
	}

	// 캐시 확인
	auto it = _cache.find(_number);
	if ( it != _cache.end()) // 미리 계산된 값이 있나
	{
		return (*it).second;
	}

	// 저장된 값 없으면 계산 후 저장
	_cache[_number] = Cal(_number/_P,_P,_Q, _cache) + Cal(_number / _Q, _P, _Q, _cache);

	// 계산 값 반환
	return _cache[_number];
	

}
