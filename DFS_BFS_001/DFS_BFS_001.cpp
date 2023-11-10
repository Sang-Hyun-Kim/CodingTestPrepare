#include <iostream>
#include <vector>
using namespace std;

void sol(vector<int>& _numbers, int _index, int _target, int _sum, int& _answer);
int solution(vector<int> numbers, int target);
int main()
{
    int answer = solution(vector<int>{4,1,2,1}, 4);
    cout << answer << endl;

}

int solution(vector<int> numbers, int target)
{
    int answer = 0;

    sol(numbers, 0, target, 0, answer);
    return answer;
}

// numbers[0], -numbers[0] 로 연산 시작

void sol(vector<int>& _numbers, int _index, int _target, int _sum, int& _answer)
{
    //if (_index == sizeof(_numbers))
    //    return;
    
    int sum1 = _sum + _numbers[_index];
    int sum2 = _sum - _numbers[_index];

    // 다음 Index++에게도 실행되도록 넘김 함계를 계속해서 넘김;
    // Index가 마지막일 경우 마지막 연산후 결과 값과 비교
    if (_index == _numbers.size() -1 )
    {
        // 마지막이 0일 수 도?
        // 조건이 맞다면 방법 횟수 증가
        if (sum1 == _target)
            ++_answer;
        if (sum2 == _target)
            ++_answer;

        return;
    }

    // 마지막 연산이 아니면
    sol(_numbers, _index + 1, _target, sum1, _answer);
    sol(_numbers, _index + 1, _target, sum2, _answer);
}