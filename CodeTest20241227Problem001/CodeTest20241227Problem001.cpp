#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;
//프로그래머스 소수찾기
// 실수한 부분
// numbers의 사이즈가 n개면 1~n개를 선택한 숫자를 소수찾기해야하는데 전부 순열로 돌려버림(제일 중요한 처리)
// 소수찾기 함수의 예외처리 2이하의 수에 대해서 찾기를 빼먹음
// 소수찾기는 제곱근"까지" 해야하는데 부등호를 < 넣어버림...
int answer = 0;
set<int> ansset;
bool isPrime(int _num);
int solution(string numbers) {

    sort(numbers.begin(), numbers.end());
    int numsize = numbers.size();
    do
    {
        string tmpstr;
        for (int i = 0; i < numsize; ++i)
        {
            tmpstr += numbers[i];
            int tmpnum = stoi(tmpstr);
            if (isPrime(tmpnum))
            {
                ansset.insert(tmpnum);
            }

        }


    } while (next_permutation(numbers.begin(), numbers.end()));
    return ansset.size();
}



bool isPrime(int _num)
{
    if (_num < 2)
        return false;
    for (int i = 2; i <= sqrt(_num); ++i)
    {
        if (_num % i == 0)
        {
            return false;
        }
    }
    return true;
}
int main()
{
}

