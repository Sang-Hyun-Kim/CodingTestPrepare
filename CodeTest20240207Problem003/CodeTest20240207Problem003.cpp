// 백준 9935 문자열 폭발
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;
// 문자열 1<= <= 1,000,000
// 폭발문자열 1<= <= 36
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	string st;
	string bomb;
	cin >> st;
	cin >> bomb;
	int bsize;
	bsize = bomb.size();
	
	string sstack;
	for (auto ch : st)
	{
		sstack.push_back(ch); // 뒤에서 부터 문자 삽입
		if (sstack.size() >= bsize) // 
		{// 문자열의 크기가 크다면
			auto index = search(sstack.end() - bsize, sstack.end(), bomb.begin(), bomb.end());// 첫번째 배열의 범위 [)에서 비교할 범위 [)를 비교한다음 맞다면 첫번째 배열의 시작 위치를 반환한다. 아니면 end();
			if(index!= sstack.end())
			{ 
				sstack.erase(index, sstack.end());
			}
		}
	}

	if (sstack.size() == 0)
		cout << "FRULA" << endl;
	else
		cout << sstack << endl;

}
