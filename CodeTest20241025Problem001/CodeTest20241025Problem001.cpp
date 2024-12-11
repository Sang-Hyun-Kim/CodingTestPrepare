// 백준 선긋기 2170
// 라인 스위핑

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int N;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N;
	vector<pair<int, int>> lines(N);
	
	for (int i = 0; i < N; ++i)
	{
		cin >> lines[i].first;
		cin >> lines[i].second;
	}

	sort(lines.begin(), lines.end(), [&](pair<int, int>& a, pair<int, int>& b) {

		if (a.first == b.first)
			return a.second < b.second;
		return a.first < b.first;
		});
	int answer=0;
	int cursline = -1000000001; 
	int cureline = -1000000001;
	for (auto line : lines)
	{
		if (cursline == -1000000001)
		{
			cursline =line.first;
			cureline = line.second;

			continue;
		}

		if (line.first < cureline)
		{
			cureline = max(cureline, line.second);
			continue;
		}
		else if (line.first == cureline)
		{
			cureline = line.second;
			continue;
		}
		else
		{
			answer += (cureline - cursline);
			cursline = line.first;
			cureline = line.second;
		}

	}
	answer += cureline - cursline;
	cout << answer;
}

