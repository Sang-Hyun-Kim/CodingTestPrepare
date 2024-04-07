//백준 우체국 2141

#include <iostream>
#include <vector>
#include <algorithm>

// 이분탐색과 누적합 연산을 함께 사용해야함
// 누적합을 잊고있던 죄...
// 누적합을 통한 양쪽의 차이 계산 줄이기
// 와 우체국의 위치가 X[i]에서 i를 반환하는게 아니라 X[i]를 반환하는거네?????
// 누적합 끝은[cnum-1]인데 high 처넣고 오류발생함
// 자꾸 헷갈린다 mid 계산후 1개 2개 남았을때의 조건 설정: while안의 <= 또는 <, mid를 포함한 인구를 넣어서 계산하기 또는 미드 양 옆 따로 계산하기 등등
// 누적합과 평균/2를 동시에 계산하는 방법도있음(자료형 주의(나누어 떨어지는 버림값에 대한 히든케이스 존재))
using namespace std;
int mincity= 1'000'000'001;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int cnums;
	cin >> cnums;

	vector<pair<int, long long>> ax(cnums);
	for (int i = 0; i < cnums; ++i)
	{
		cin >> ax[i].first >> ax[i].second;
	}

	int low = 0;
	int high = cnums-1;
	sort(ax.begin(), ax.end(), [&](auto& a, auto& b) ->bool {
		if (a.first == b.first)
			return a.second > b.second;
		return a.first < b.first; });
	for (int i =1;i<cnums;++i)
	{
		ax[i].second += ax[i - 1].second;
	}

	while (low <= high)
	{
		int mid = (low + high)/2;

		if (ax[mid].second < ax[cnums-1].second - ax[mid].second)// mid 이전까지의 인구수 누적 vs high- mid(우측 도시들의 인구 총합)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
			mincity = min(mincity, ax[mid].first);
		}
	
	}
	
	cout << mincity;

}

