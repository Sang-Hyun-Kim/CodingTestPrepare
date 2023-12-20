// 백준 13305번 주유소
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;


// 도시 인덱스가 {가격, 도시 순서} 를 순회하면서 해당 순번이 최소 값보다 순번이 빠를경우 가격 정렬 순번을 증가 
// 이때 자신의 순서에 도착했을 경우 자신 도시에 해당하는 가격을 먼저 구매 현재 도시=>바로 다음 도시 가격 구매
// 정렬된 최소값을 순회중 현재 도시보다 순번이 빠른 경우=> 해당 가격* 거리 추가
// 자기 값으로 계산된 도시 index를 제외 해야 하나 => 성능이 빨라질수는 있으나 너무 빨리 최소값이 있으면 제거될 수도 있으니 ㄴㄴ
// => 틀린 풀이(시간복잡도 최대 n*n), 그냥 도시 순회와 동시에 최소 기름값 갱신으로 풀이 O(n)
int main()
{
	int num;
	cin >> num;
	vector<long long> ranges;
	vector<long long> cities;
	//vector<pair<long long, int>> prindex;
	long long total = 0;
	int lowest = INT_MAX;
	for (int i = 0; i < num - 1; ++i)
	{
		int distance;
		cin >> distance;
		ranges.push_back(distance);
	}

	for (int i = 0; i < num; ++i)
	{
		int price;
		cin >> price;
		cities.push_back(price);
		//if(i!=num-1) prindex.push_back({ price,i });
	}
	//sort(prindex.begin(), prindex.end());
	// {가격, 도시 순서} 에서 가격 순으로 정렬
	
	for (int i = 0; i < num-1; ++i)
	{
		if (lowest > cities[i]) lowest = cities[i];
		total += lowest * ranges[i];
	}

	cout << total << endl;
}