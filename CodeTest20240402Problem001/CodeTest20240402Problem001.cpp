// 백준 1300번 K번째 수

#include <iostream>
#include <vector>
#include <algorithm>
// 10,000,000,000
// 10만 곱하기 10만은 저장할수도 없고 계산도 힘들다
// 이진탐색을 통해 필요할 때만 계산하는 방법으로 수행
// 필요한 수를 구하는건 어떻게 하냐
// 배열의 곱으로 생성되는 수는 정해져있고 해당 수들이 반복하면서 오름 차순 순서를 구성한다.
// 배열의 곱으로 나타나는 수 K에 대해서 N보다 작거나 같은 수의 개수를 구하는 가상의 배열 S에서 K가 A개를 가진다고 했을 때
// K 이전에 행렬곱으로 나타나는 K보다 작은 값중 제일 큰 값을 KP, 반대로 행렬 곱에서K보다 큰 수중 제일작은 값 KN이 있을때 각각 AP, AN개를 가진다고 하면 S[KP] = AP, S[KN] = AN;
// KP부터 K-1까지는 전부 AP개가 나타나고, K부터 KN-1은 전부 A개로 구성된다. 즉 S[i](KP<=i<K) = AP,   S[i](K<=i<KN) = A를 가진다. 이를 응용해서
// 만약 임의 k번째 수를 구해야한다면 S[x]가 AP<k<=A를 만족하는 x중 가장 작은 값인 K를 찾아야한다.
using namespace std;
int main()
{
	long long num;
	cin >> num;
	long long size = num * num;
	long long k;

	cin >> k;
	if (k == 1)
	{
		cout << 1;
	}
	else
	{
		long long  low = 1;
		long long high = size;
		long long mid;
		while (low < high)
		{
			mid = (low + high) / 2;
			long long last=0;
			for (int i = 1; i <= num; ++i)
			{
				last += min(num, mid/i);
			}

			if (k > last)
			{
				low = mid +1;
			}
			else
			{
				high = mid;
			}			
		}

		cout << low;
	}
}
