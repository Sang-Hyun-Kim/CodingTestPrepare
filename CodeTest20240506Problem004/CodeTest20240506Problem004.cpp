// 백준 14002 가장 긴 증가하는 부분 수열4 골드 4
// 이분탐색
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;
int N;
// 아이디어: LIS탐색을 nlogn 시간복잡도로 해결하면서 동시에 LIS 출력을 해결해주는 풀이
// 배열을 하나 더 생성해서 이분탐색으로 알게되는 해당 원소를 포함한 LIS가 있을 때 해당 원소의 LIS 상의 인덱스 위치를 기록하게 하고
// 이후 LIS의 길이를 통해 해당 배열을 순회하면서 출력하면 LIS를 알 수 있다. 
// 실수: 이분탐색 조건 설정 + 이분탐색 mid 위치
int binarySearch(vector<int>& lis, int right, int left, int num);
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	vector<int> A(N);
	for (int i = 0; i < N; ++i)
	{
		cin >> A[i];
	}
	vector<int> lis;
	vector<int> idxnums(N,0);
	int last = 0;
	int next = 0;
	lis.push_back(A[next]);
	idxnums[next] = last;
	next++;

	while (next < N)
	{
		if (A[next] > lis[last])
		{
			lis.push_back(A[next]);
			last++;
			idxnums[next] = last;
		}
		else
		{
			int idx = binarySearch(lis, 0, last,A[next]);
			lis[idx] = A[next];
			idxnums[next] = idx;
		}
		next++;
	}
	cout << last+1 << "\n";
	// 역순으로 idxnums를 찾으면서 순서 찾기 last부터 0까지 순서 찾기
	// idxnums[i]는 A[i]를 포함하는 경우의 최장 길이 순열에 대해 A[i]가 순열의 몇번째 인덱스 인지를 나타내는 값을 저장함 
	// last를 저장한 i를 찾아서 저장후 역순으로 출력
	vector<int> answers;
	for (int i = N - 1; i >= 0; --i)
	{
		if (idxnums[i] == last)
		{
			answers.push_back(A[i]);
			last--;
		}
	}
	
	for (int i = answers.size()-1; i >= 0; --i)
	{
		cout << answers[i] << " ";
	}

}
int binarySearch(vector<int>& lis, int left, int right, int num)
{ // 마지막값보단 작지만 LIS 후보군 인덱스를 지정해줘야하는 이분탐색
	int mid;
	while (left < right)
	{
		mid = (right + left) / 2;
		if (lis[mid] >= num)
		{
			right = mid;
		}
		else
		{// list[mid] < num
			left = mid + 1;
		}

	}
	return right;
}

// A = {10, 20, 10, 30, 20, 50} => 4 + 10 20 30 50 

// A = {10, 20,40, 10, 30, 20, 50} 10 20 40 50 
// A = {10, 20, 2,3,5,10, 30, 20, 50} 

// 넣을 수 있을 때 넣거나 안넣거나로 수행