// 백준 1460 진욱이의 농장
#include <iostream>
#include <algorithm> // std::find
#include <vector>

// 0,1로이루어진 보드에서 가장 큰 정사각형 찾기 응용
// 두 가지 색으로 이루어진 정사각형 찾기
// 0~7까지의 경우의 수중 각각 하나씩으로 이루어진 경우 하나씩에 대해서 탐색
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int field;
	int seed;
	cin >> field >> seed;
	
	vector<vector<int>> fruit(field+1,vector<int>(field+1,0)); 
	for (int k = 0; k < seed; ++k)
	{
		int x, y, L, F;
		cin >> x >> y >> L >> F; // x+1, y+1 좌표로
		for (int i = x + 1; i < x +1+L; ++i)
			for (int j = y + 1; j < y +1+ L; ++j)
				fruit[i][j] = F;
	}
	// 0 은 제외 어쩌피 0으로 이루어진 사각형은 못만드니까
	// DP[i][j]는 정사각형 가장 우측 하단 꼭지점에서 만들 수 있는 가장 큰 정사각형의 변의 길이를 저장함
	// DP[i][j] = min(DP[i-1][j] + DP[i-1][j-1] + DP[i][j-1])
	int maxlength = 0;
	for (int color1 = 1; color1 <= 7; ++color1)
	{
		for (int color2 = 1; color2 <= 7; ++color2)
		{
			vector<vector<int>> colored(field+1, vector<int>(field+1, 0));
			for (int i = 1; i <= field; ++i)
			{
				for (int j = 1; j <= field; ++j)
				{
					if (fruit[i][j] == color1 || fruit[i][j] == color2) colored[i][j] = 1; // 이번 색 순회 2가지 중 하나와 일치한다면 1로 표시 아니면 0
				}
			}
		
			// 이번 색 조합의 대상(1로 이루어진) 최고 넓이의 사각형 찾기
			for (int i = 1; i <= field; ++i)
			{
				for (int j = 1; j <= field; ++j)
				{
					if (colored[i][j] == 0) continue;
					colored[i][j] = min(colored[i][j-1],min(colored[i-1][j-1],colored[i-1][j]))+1;
					maxlength = max(maxlength, colored[i][j]);
				}
			}
		}
	}
	cout << maxlength * maxlength;
}
	