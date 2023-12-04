// 백준 1744 수묶기
// // 골드4
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int number;
	cin >> number;
	int currentnumber;

	vector<int> zero; //0
	zero.reserve(number);

	vector<int> one; // 1
	one.reserve(number);

	vector<int> positive; // 양수
	one.reserve(number);

	vector<int> negative; // 음수
	one.reserve(number);
	
	// 값마다 분류해서 넣기
	for (int i = 0; i < number; i++)
	{
		cin >> currentnumber;
		if (currentnumber == 0) // 0
		{
			zero.emplace_back(currentnumber);
		}
		
		if (currentnumber == 1) // 1
		{
			one.emplace_back(currentnumber);
		}

		if (currentnumber > 1) // 양
		{
			positive.emplace_back(currentnumber);
		}

		if (currentnumber < 0) // 음
		{
			negative.emplace_back(currentnumber);
		}
	}
	int sum = 0;
	// 정렬
	sort(positive.begin(), positive.end(),greater<int>()); //양은 큰거부터
	sort(negative.begin(), negative.end()); // 음은 작은거부터
	
	// 음의 개수가 홀수인지 짝수개인지
	if (negative.size() % 2 == 0)
	{
		for (int i = 0; i < negative.size(); i += 2)
		{
			sum += negative[i] * negative[i + 1];
		}
	}
	// 홀수 => 0이 있는지 확인 0이있다? => 가장 작은 수는 0과 곱하고 
	if (negative.size()  % 2 == 1)
	{
		if (zero.size() > 0)
		{//0이 있다면
			for (int i = 0; i < negative.size()-1; i += 2)
			{
				sum += negative[i] * negative[i + 1];
			}// 0 *마지막녀석은 생략
		}
		else
		{// 0이 없다면
			for (int i = 0; i < negative.size() - 1; i += 2)
			{
				sum += negative[i] * negative[i + 1];
			}
			sum += negative.back();
		}
	}
	
	if (positive.size() % 2 == 0)
	{
		for (int i = 0; i < positive.size(); i+=2)
		{
			sum += positive[i] * positive[i + 1];
		}
	}
	if (positive.size() % 2 == 1)
	{
		for (int i = 0; i < positive.size()-1; i += 2)
		{
			sum += positive[i] * positive[i + 1];
		}
		sum += positive.back();
	}

	// 1은 전부 더하고, 양의 값 또한 가장 큰값 두개끼리 곱하고 더하기 가장 작은 값만 더하기
	for (int i = 0; i < one.size(); ++i)
	{
		sum += one[i];
	}


	cout << sum << endl;
}
