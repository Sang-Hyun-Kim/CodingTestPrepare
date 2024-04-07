// 백준 1202 보석도둑 골드 2 그리디 문제

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
using namespace std;
// 가방 최대 무게 100,000,000 1억
// 최대 무게와 가격 백만 1,000,000
// 틀린거: 문제 제대로 안읽고 모든 가방의 모든 공간을 활용하기 위해 가격/무게 비율도 만들고 가방도 재사용하려고 남은공간을 저장하는 class 만들어서 그것도 정렬해서 보관하게
// 만들고 헛짓함, 코드가 긴 것은 공부의 흔적들
long long price = 0;
struct compairVW
{
	bool operator()(int& a, int& b)//{무게,가격} // 항상 헷갈리는 부분 priority_queue의 우선순위를 비교해주는 인자를 넣을때에는
		// 두번째 인자가 원하는 요구사항에 우선순위가 높도록 즉, true가 되는 경우를 반환하도록 조건을 설정하면 된다.
		// 즉 가치가 더 큰것이 b(두번째 인자)일 경우 true를 반환하도록 설정했고 만약 가치가 같을 경우 무게가 가벼운것을 먼저 넣는다.(상관없어짐)
	{
		return a < b;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int jn, bn;
	cin >> jn >> bn;
	vector<pair<int,int>> jews(jn); // 필요한 컨테이너 견적, v/w를 높은 순부터 반환하는 v,w를 전부 가진 priority_queue;
	priority_queue<int, vector<int>,compairVW> highvalue; // 사실 가치만 담아줘도 됨, 이전코드 버린게 억울해서 씀

	vector<int> bags(bn);
	for (int i = 0; i < jn; ++i)
	{
		cin >> jews[i].first >> jews[i].second; // 무게 >> 가격
	}

	for (int i = 0; i < bn; ++i)
	{
		cin >> bags[i];
	}
	sort(bags.begin(), bags.end(), [&](auto& a, auto& b) {return a < b; }); // 정말 정말 중요한건 sort()에 넣어주는 조건은 priority_queue에 넣어줄때의 조건과 정반대라는 것이다.
	// a가 자신이 생각하는 우선순위가 높을때  true를 반환하는 식을 넣어주는 것이다.
	sort(jews.begin(), jews.end());// 위와 같은 오름차순 default less<int>
	int jewIndex = 0; // 이미 넣어준 보석들은 무시 예정
	
	for (int i = 0; i < bn; ++i)
	{
		// 이번 작은 가방[i]에 담을 수 있는 모든 보석 삽입
		for (int j = jewIndex; j < jn; ++j)
		{
			if (jews[j].first <= bags[i])
				highvalue.push(jews[jewIndex++].second);
			else
				break; // 이거 안해줘서 시간초과남: 쓸대없는 것들 자꾸 넣어주고 문제나려했음
		}

		// 그리고 이 가방에 담을 수 있는 최대 가치 합산
		if (!highvalue.empty())
		{// 담을 게 없었다.
			auto maxjew = highvalue.top();
			highvalue.pop();
			price += (long long)(maxjew);
		}
		
	}

	
	cout << price;
	
}

