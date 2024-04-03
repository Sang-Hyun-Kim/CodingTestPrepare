//  백준 2961번 도영이가 만든 맛있는 음식


#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int delicious = 1'000'000'000;
int nf;
void BackTrack(int i, vector<pair<int, int>>& food, int cs, int cb);
// 실수 1: 제조 과정에서 최소값이 나온다면 당연히 그게 최소값
// => 최소값 갱신을 Backtracking 마무리에서 할 이유가 없음, 간소화 및 최적화 신경쓰기
int main()
{
	int totalsour;
	int totalbitter;
	
	cin >> nf;
	vector<pair<int,int>> food(nf);
	
	for (int i = 0; i < nf; ++i)
	{
		int s,b;
		cin >> s >> b;
		food[i] = {s,b};
		delicious = min(delicious, abs(s - b));
	}
	BackTrack(0, food, 1, 0);
	cout << delicious;
}

void BackTrack(int i,vector<pair<int,int>>& food,int cs,int cb)
{
	if (i >= nf)
	{
		return;
	}
	// 재료 안넣는 경우 바로 재귀호출
	BackTrack(i + 1, food, cs, cb);
	// 이번 것을 넣는 경우를 계산
	cs *= food[i].first;
	cb += food[i].second;

	delicious = min(delicious,abs(cs - cb));
	BackTrack(i + 1, food, cs, cb);
	
}
