// 백준 7570 줄 세우기
// 증가 수열 찾기 어려워서 힌트 찾음
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N;
	vector<int> line(N+1,0);
	int answer = 0;
	for (int i = 1; i <= N; i++)
	{
		int a;
		cin >> a;

		line[a] = line[a - 1] + 1; // 증가수열은 자연스럽게 쌓인다.
		answer = max(answer, line[a]);
	}

	cout << N - answer;
}
