#include <iostream>
#include <vector>
#include <string>

using namespace std;
void Failure(string _key, vector<int>& _keypattern);
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	string original;
	string key;

	cin >> original;
	cin >> key;
	vector<int> keypattern(key.length());
	Failure(key, keypattern);
	// key 문자열에 대한 실패함수실행
	for (int i = 0, j = 0; i < original.length(); ++i)
	{
		while (j > 0 && key[j] != original[i])
		{
			j = keypattern[j-1];
		}
		if (key[j] == original[i])
		{
			if (j == key.length() - 1)
			{// 다똑같음

				cout << 1 << endl;
				return 0;
				// 만약 전체 반복 개수를 찾는다면
				// i에서 검색어의 길이를 뺀 다음 1을 더 한다면 일치하는 곳의 index이므로 이를 저장하는 처리를한다음
				// j의 위치를 j=keypattern[j]; 해준다면
				// 이후의 검색을 i-(검색어 사이즈)+1 +1 위치부터 검색하지 않고, 접두==접미가 반복되는 위치부터 검색하도록 찾기 시작한다.
			}
			else
				j++;// 검색어의 j번째 index까지 같으니 다음 순서도 검사
		}
	}
	// 같은 것이 없다.
	cout << 0 << endl;
	return 0;
}

void Failure(string _key, vector<int>& _keypattern)
{
	int nkey = _key.length();
	// 현재위치부터 접두사로 몇글자 반복되는지 구하는 함수

	int j = 0;

	for (int i = 1; i < nkey; ++i)
	{
		while (j > 0 && _key[j] != _key[i])
		{// 일치하지 않는 부분 확인시, 접두사와 접미사의 같은 부분이 나타나지 않았을 때, 다시 겹치는 부분이 나올때까지 j를 감소시키는 코드
			// 이후 더이상 같은 부분이 없는 경우 j는 0까지 내려가게된다.
			j = _keypattern[j -1];// 2->1->0; => 2개까지같아진 후 다음 i에서 같지 않아 이전까지 
		}
		if (_key[i] == _key[j])
		{
			_keypattern[i] =++j;
		}
	}
}