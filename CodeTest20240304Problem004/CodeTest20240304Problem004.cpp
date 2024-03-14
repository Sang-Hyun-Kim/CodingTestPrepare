// 백준 17609 회문
// 투포인터 + 함수
#include <iostream>
#include <string>
#include <vector>

using namespace std;
bool WhatIF(int ldx, int rdx, string& s);
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int sn;
	cin >>sn;
	int ldx, rdx;
	for (int i = 0; i < sn; ++i)
	{
		string s;
		cin >> s;
		ldx = 0;
		rdx=s.size()-1;
		bool flag = true;
		bool anf = true;
		while (ldx < rdx)
		{
			if (s[ldx] == s[rdx])
			{
				ldx++; rdx--;
			}
			else
			{
				if (flag)
				{
					flag = false;
					anf = WhatIF(ldx + 1, rdx, s) || WhatIF(ldx, rdx - 1, s);
					break;
				}
			}
		}
		// 결과
		if (flag)
		{
			cout << 0 << "\n";
		}
		else if (!flag && anf)
		{
			cout << 1 << "\n";
		}
		else
		{
			cout << 2 << "\n";
		}
	}
	
}

// 재귀함수 회문()
// 넘겨받은 좌우 인덱스와 문자열에서 각각 한쪽씩 한칸 올리고 나서 회문 판별
bool WhatIF(int ldx,int rdx, string& s)
{
	while (ldx < rdx)
	{
		if (s[ldx] == s[rdx])
		{
			ldx++; rdx--;
		}
		else
		{
			return false;
		}
	}
	return true;
}