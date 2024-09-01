// 프로그래머스 고득점 킷 정렬 2번 가장 큰 수
// 쟁점: string 과 int 타입간의 변화를 잘 수행 할 수 있냐, string 타입의 함수를 잘 사용할 수 있냐, sort의 비교 연산을 위해 custom한 비교 함수를 사용 할 수 있냐
// 이어지는 수에 대해 내림 차순 우선선위 a>b를 수행하기
// 이때 어떤 수가 합쳤을 때 더 큰 수가 되는 지는 문자열로 변환 후 a+b, b+a 수행해서 더 큰 수가 나오는 경우 그 수가 sort시 더 큰 수가 되도록 한다
// 예) 39 33이 있을 때 3933 > 3339가 true 가 되도록 하면  3933이 정렬시 앞으로 가도록 함수를 custom해서 sort() 함수의 인자로 넣는다.

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool sorting(string a, string b)
{
    return a + b > b + a;
}

string solution(vector<int> numbers) {

    string answer;
    vector<string> numStrings;

    for (auto num : numbers)
    {
        numStrings.push_back(to_string(num));
    }
    sort(numStrings.begin(), numStrings.end(), sorting);

    if (numStrings[0] == "0") return "0";
    for (auto ns : numStrings)
    {
        answer.append(ns);
    }

    return answer;
}

int main()
{

}