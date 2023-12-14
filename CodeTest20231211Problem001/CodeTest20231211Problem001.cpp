// 백준 11501번 주식

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 오름차순 Monostack만들기 시도=> 내림차순만 나오다 오름차순 나왔을때의 계산 실패로 포기
// 뒤에서부터 빼는 계산으로 수행
// 자체 피드백: reverse로 전체를 한번 바꾸는 수행을 자제하자 너무 오래걸린다.
// 그냥 뒤에서부터 인덱스 숫자 내렸으면 2배는 빠름
int main()
{
	int numofCases = 0;
	int numofStocks = 0;
	cin >> numofCases;
	for (int i = 0; i < numofCases; ++i)
	{
		vector<int> stocks;
		cin >> numofStocks;
		for (int j = 0; j < numofStocks; ++j)
		{
			int stock;
			cin >> stock;
			stocks.push_back(stock);
		}
		long long answer = 0;
		int maxima = -1;
		reverse(stocks.begin(), stocks.end());
		for (auto a : stocks)
		{
			if (maxima == -1) maxima = a;
				
			else
			{
				if (maxima < a) maxima = a;
				else answer += maxima - a;
			}
		}
		
		cout << answer << endl; // 이번 testcaseStock에 대한 출력
	}
}
