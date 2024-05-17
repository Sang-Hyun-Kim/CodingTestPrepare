// 백준 신기한 소수 2023

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
// N이하의 소수를 판별하는 법 공부: N의 제곱근 기준 이하의 수에 대한 순회
// 메모리를 4mb밖에 안줘서 에라토스테네스의 체 방법을 사용할 수 없었음
// 조건 분기를 통해 최대한 수를 줄여서 계산하는 방법을 사용
using namespace std;
int E;
int LN, N;
vector<int> prime;
int ans = 0;
int square(int e);
bool IsPrime(int n);
bool Special(int N, int digit);
set<int> oneprime{ 2,3,5,7 };
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> E;
	LN = square(E - 1);
	N = square(E);
	// LN~N까지
	for (int i = LN; i < N; ++i)
	{
		if (oneprime.find(i/LN) != oneprime.end())
		{	// 첫째 자리가 소수 라면
			if (Special(i, LN / 10)) // 자리수의 그다음 칸까지 남기면서 재귀 검증 실행 // 4자리수 수에 대해 10의 3승으로 나눈 수에 대한 검증 후 반복
			{
				cout << i << "\n";
			}
		}

	}


}

int square(int e)
{
	int res = 1;
	for (int i = 0; i < e; ++i)
	{
		res *= 10;
	}
	return res;
}

bool IsPrime(int n)
{
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}

bool Special(int N,int digit) // digit은 10의 거듭제곱들이 넘어올 것
{
	if (digit == 0) return true;
	else
	{
		if (digit != 1 && N % 2 != 1)
			return false;
		int nextnum = N / digit; 
		if(IsPrime(nextnum))
		{
			return Special(N, digit / 10);
		}
		else
			return false;
	}
	
}