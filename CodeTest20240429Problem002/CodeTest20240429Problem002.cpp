// 백준 2096  내려가기 
// 슬라이딩, 인풋 전부 저장하면 4mb 터짐
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N;
 // N 줄의 0 1 2(좌 중 우)

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int Mans;
	int mans;

	cin >> N;
	vector<int> mnums(3, 0);
	cin >> mnums[0] >> mnums[1] >> mnums[2];
	vector<int> Mnums(mnums.begin(), mnums.end());

	for (int i = 1; i < N; ++i)
	{
		int one, two, three;
		cin >> one >> two >> three;
		// 이번에 들어온 수를 통해 현재 최소 경로, 현재 최대 경로 값 계산
		// 최대 계산
		vector<int> temp(3, 0);
		for (int j = 0; j <= 2; ++j)
		{
			if (j == 0)
			{
				temp[j] = one + max(Mnums[0], Mnums[1]);
			}
			else if (j == 1)
			{
				temp[j] = two + max({ Mnums[0], Mnums[1] ,Mnums[2] });
			}
			else
			{
				temp[j] = three + max({ Mnums[1] ,Mnums[2] });
			}
		}
		Mnums = temp;
		
		for (int j = 0; j <= 2; ++j)
		{
			if (j == 0)
			{
				temp[j] = one + min(mnums[0], mnums[1]);
			}
			else if (j == 1)
			{
				temp[j] = two + min({ mnums[0], mnums[1] ,mnums[2] });
			}
			else
			{
				temp[j] = three + min({ mnums[1] ,mnums[2] });
			}
		}
		mnums = temp;
		// 최소 계산
	}
	cout << max({Mnums[0],Mnums[1],Mnums[2] }) << " " << min({ mnums[0],mnums[1],mnums[2] });
}

