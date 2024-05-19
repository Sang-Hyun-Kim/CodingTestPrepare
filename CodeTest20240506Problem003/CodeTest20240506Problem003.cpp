// 백준 86 ─에이티식스─ 1 골드 5
// 체스판 거리 측정법 + 체스판 같은 색상 판별하기

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;
int N;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N;
	vector<vector<int>> board(N, vector<int>(N, 0));
	vector<pair<int, int>> regions;
	pair<int, int> srt;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> board[i][j];
			if (board[i][j] == 2)
				srt = { i,j };
			else if (board[i][j] == 1)
			{
				regions.push_back({ i,j });
			}
				
		}
	}
	// 처음에받은 최대 11개의 좌표에 대해 계산하여 |x-x| + |y-y| 가 짝수가 나오는지 검수 ==> (x1+y1)%2==(x2+y2)%2 가 성립함을 보거나 |x1-x2|+|y1-y2|=0;
	regions.push_back(srt);
	for (int i = 0; i < regions.size(); ++i)
	{
		for (int j = 0; j < regions.size(); ++j)
		{
			if ((abs(regions[i].first - regions[j].first) + (abs(regions[i].second - regions[j].second))) % 2 != 0)
			{
				cout << "Shorei";
				return 0;
			}
				
			
		}
	}
	regions.erase(regions.end() - 1);
	int answer = INT_MAX;
	do // 최대 10개의 레기온들에 사냥 순서 조합 만들기
	{
		int curx = srt.first;
		int cury = srt.second;
		int time =0;
		for (int i = 0; i < regions.size(); ++i)
		{
			time += max(abs(regions[i].first - curx), abs(regions[i].second - cury));
			curx = regions[i].first;
			cury = regions[i].second;
		}
		answer = min(answer, time);
	}while (next_permutation(regions.begin(), regions.end()));

	cout << "Undertaker" << "\n" << answer ;

}

