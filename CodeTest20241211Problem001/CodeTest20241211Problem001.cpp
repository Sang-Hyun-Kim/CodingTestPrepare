// 프로그래머스 배열의 평균값

#include <string>
#include <vector>

using namespace std;

double solution(vector<int> numbers) {
    double answer = 0;
    double nsize = numbers.size();
    double sum = 0;
    for (auto num : numbers)
    {
        sum += num;
    }
    answer = sum / nsize;

    return answer;
}