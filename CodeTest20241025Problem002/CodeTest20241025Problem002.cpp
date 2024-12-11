// 21941번 백준 문자열 제거
// 로직은 맞췄는데 테케만 맞추고 히든에서 자꾸 틀려서 다른 사람의 코드를 참고
// 출처 : https://boomrabbit.tistory.com/167

#include <iostream>
#include <vector>
#include <map>
using namespace std;

string s;
int m;
vector<string> v[30]; // 앞글자만 땐 다음 검색 범위를 줄이는 코드 => 모든 문자열을 글자 하나마다 검사할 필요가 없음
map<string, int> mp;
int dp[1010];

int f(int x);

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string x;
	int y;
	cin >> s >> m;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		mp[x] = y;
		v[x[0] - 'a'].push_back(x);
	}
	memset(dp, -1, sizeof(dp));
	cout << f(0);
	return 0;
}
int f(int x)
{
	if (x == s.length())return 0;
	if (x > s.length())return -1;
	int& ret = dp[x];
	if (ret != -1)return ret;

	ret = 0;
	for (string str : v[s[x] - 'a']) // 모든 문자열을 검사하지 않고 앞글자만 같은 문자열의 집합에서만 검사하는 코드 ㅁㅊㄷ
		if (str == s.substr(x, str.length()))
			ret = max(ret, f(x + str.length()) + mp[str]);
	ret = max(ret, f(x + 1) + 1);
	return ret;
}