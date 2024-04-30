// 백준 소수의 연속합 1644

#include <iostream>
#include <vector>

// N이하의 소수를 판별하는 법 공부: 1: 단순 약수 순회, 2: N의 제곱근 기준 이하의 수에 대한 순회, 3: N이하의 소수 하나를 찾는다면 N이하의 해당 소수의 배수를 전부 후보에서 소거하는 방법
// 3번의 방법을 에라토스테네스의 체 알고리즘이라 함
// + 그렇게 걸러낸 소수를 하나의 컨테이너에 넣고 해당 컨테이너에서 2 포인터를 통한 원소의 합, 차를 통한 경우의 수 계산 진행하기

using namespace std;
int N;
vector<int> prime;
int ans = 0;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N;

	vector<bool> nums(N+1, true);//0~N
	prime.reserve(N);
	for (int i = 2; i < N + 1; ++i)
	{
		if (nums[i])
		{
			prime.push_back(i);// 소수 모음집 넣기
			for (int j = i * 2; j <= N; j += i)
			{
				// i의 n배수 전부 소수 아님 처리(2*i 부터 N 이하의 수까지)
				nums[j] = false;
			}
		}
	}

	// N이하의 소수들로 계산
	// [0] : 2 , [1]: 3 ~
	int low = 0;
	int high = 0;
	int sum = 0;

	while (true)
	{
		if (sum<N)
		{
			if (high >= prime.size()) break;
			sum += prime[high];
			high++;
		}
		else if (sum > N)
		{
			sum -= prime[low];
			low++;
		}
		else
		{
			ans++;
			if (high >= prime.size()) break;
			sum += prime[high];
			high++;
		}
	}
	cout << ans;
}

