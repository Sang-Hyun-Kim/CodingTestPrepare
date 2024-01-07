// 백준 램프 1034번
// 부르트포스, 애드혹 문제
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

	int row, col;
	cin >> row >> col;
	vector<string> lamps(row);
	for (int i = 0; i < row; ++i)
	{
		cin >> lamps[i];
	}
	int swi;
	cin >> swi;
	
	// 각 행에 대해
	// 전체 0의 개수 > swi: X
	// 해당 0의 개수가 짝수인 것과 홀수인 것을 나눠서 분류
	
	int maxi = 0;
	for (int i = 0; i < row; ++i)
	{// 행 하나에 대해서
		int zero = 0;
		for (int j = 0; j < col; ++j)
		{
			if (lamps[i][j] == '0')
				zero++;
		}
		int sum = 0;
		if (zero <= swi && swi % 2 == zero % 2)
		{
			for (int h = 0; h < row; ++h)
			{
				// 배열이 완전히 같지 않으면 해당 행에 맞는 횟수로 동시에 켤 수 없음
				if (lamps[i] == lamps[h])
					sum++;
			}
		}
		maxi = max(maxi, sum);
	}

	cout << maxi << '\n';
}
