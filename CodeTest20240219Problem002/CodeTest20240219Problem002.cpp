// 백준 14907 프로젝트 스케쥴링
// 입력받는거 어려워서 힌트봄

#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
int main()
{
	int projects[26], time[26] = { 0, }, degree[26];
	vector<int> adj[26]; // [n] => n의 인접 정점(프로젝트) ex) : [0(A)] = {B,D}

	string str;
	while (getline(cin, str)) { // A 5 , B 3 A
		string tmp = "";
		vector<string> v;
		for (auto& i : str) {
			if (i != ' ')
				tmp.push_back(i);
			else
				v.push_back(tmp), tmp = "";
		}
		v.push_back(tmp);

		char task = v[0][0]; // 알파벳
		int day = stoi(v[1]); // 일처리에 소모되는 값
		string tasks = (v.size() == 2 ? "" : v[2]);

		for (auto& j : tasks)
			adj[j - 'A'].push_back(task - 'A');
		degree[task - 'A'] = tasks.size();
		projects[task - 'A'] = day; // 알파벳 순서에 따른 시간 소요 저장 A-A : 0, B-A => 1 ~ Z-A : [25] 총 26개
	}
	queue<int> pqueue;

	for (int i = 0; i < 26; i++) {
		if (projects[i] && !degree[i]) { // degree가 0이 아니면서 소요 시간이 있는 경우(빈 배열 제외)
			pqueue.push(i);
			time[i] = projects[i];// f[프로젝트] = 프로젝스 소요시간
		}
	}

	while (!pqueue.empty()) { //위상 정렬 queue 가 끝날 때 까지
		int now = pqueue.front();
		pqueue.pop();

		for (auto& next : adj[now]) {
			time[next] = max(time[next], time[now] + projects[next]); // 다음 프로젝트까지 계산된 시간  vs 현재까지 프로젝트 계산된시간 + 다음 프로젝트까지의 소요시간 

			if (!--degree[next])
				pqueue.push(next);
		}
	}

	int ans = 0;
	for (int i = 0; i < 26; i++)
		ans = max(ans, time[i]);

	cout << ans << '\n';
	return 0;
}

