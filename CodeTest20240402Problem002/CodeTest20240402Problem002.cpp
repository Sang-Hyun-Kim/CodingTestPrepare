// 백준 1074 Z

#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;
// 재귀+분할
// 실수 1: pow함수의 반환값은 double형이다
// 조건을 생각하는 과정에서 당연히 mid값이 나눠지며 정수의 몫부분만 생기는 것으로 코드를 짰다가 분기가 너무 세분화되는 문제가 발생
// 전부 double로 선언했던 자료형을 int변경한 뒤 pow의 결과값을 형변환 해주는 것으로 해결
// 실수 2: 계속 첫번째 구역으로 갈때마다 문제가 발생함(무한 루프 또는 이상한 반환값) => 1번째 분기로 갈때 N 빼주는 것을 까먹음=>해결
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int N;
	cin >> N;
	int r, c;
	cin >> r >> c;
	int rowlow = 0;
	int collow = 0;
	int colhigh = static_cast<int>(pow(2, N))-1;
	int rowhigh = static_cast<int>(pow(2, N)) - 1;
	int nextN=N;
	int currentVal=0;
	while (nextN > 0)
	{
		int rowmid = (rowlow + rowhigh) / 2;
		int colmid = (collow + colhigh) / 2;
		if (r<=rowmid&&c<=colmid)
		{// 1
			// curval변화없음
			rowhigh = rowmid;
			colhigh = colmid;
			nextN--; // 실수했던 부분:깜박함
		}
		else if (r <= rowmid && c > colmid)
		{// 2
			currentVal += static_cast<int>(pow(pow(2, --nextN), 2));
			rowhigh = rowmid;
			collow = colmid;
		}
		else if (r > rowmid && c <= colmid)
		{// 3
			currentVal += static_cast<int>(pow(pow(2, --nextN), 2)) * 2;
			rowlow = rowmid;
			colhigh = colmid;
		}
		else// r>&&c>
		{// 4
			currentVal += static_cast<int>(pow(pow(2, --nextN), 2)) * 3;
			rowlow = rowmid;
			collow = colmid;
		}
	}

	cout << currentVal;
}

