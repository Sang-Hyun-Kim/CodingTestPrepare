#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 데드라인 순으로 정렬 후
// 우선순위 큐에는 오름차순으로 넣고
// 매 순회마다 데드라인 일정을 설정
// 현재 데드 라인 일정보다 우선순위 큐의 사이즈가 커질 경우
// 현재 데드라인 일정만큼 될때까지 Pop해주면
// 그것이 현재 데드라인 중 가장 최대의 보상을 가지는 우선순위 Queue가 됨
// 모든 문제 순회 후 남은 우선순위Queue의 내용물을 계산한다.

int main()
{
	int problemCount = 0;
	int deadline = 0;
	int noodles = 0;

	int now = 1;
	int answer = 0;
	int index = 0;
	
	struct cmpGreater {
		bool operator()(vector<int> a, vector<int> b)
		{

			return a[1] > b[1];
		}
	};
	priority_queue<vector<int>, vector<vector<int>>, cmpGreater> solution;
	vector<vector<int>> Problems;

	cin >> problemCount;
	for (int i = 0; i < problemCount; ++i)
	{
		cin >> deadline;
		cin >> noodles;
		Problems.push_back(vector<int>{deadline, noodles}); // [데드라인, 보상]
	}
	sort(Problems.begin(), Problems.end());

	for (auto problem : Problems)
	{
		solution.push(problem);
		now = problem[0];
		if (now < solution.size()) solution.pop();
	}
	
	while (!solution.empty())
	{
		answer += solution.top()[1];
		solution.pop();
	}

	cout << answer << endl;
	return 0;
}
