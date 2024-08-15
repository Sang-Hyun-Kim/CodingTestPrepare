// BinarySearch001.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
// 아오 times의 원소 가 int 이니까 (long long) 형변환하기, long long 끼리 연산하다 터질 수 있으니 mid 값 구할 때 센스 있게 구하기
// 진짜 중요한 이분탐색 시에 mid 값과 low, high 값 잘 고르기
long long solution(int n, vector<int> times) {
    long long answer = 0;
    // low :1분, high: times의 원소중 max * 사람의 수(N) 
    // mid 값이 정해졌을 때 N의 값과 비교
    // mid분 동안 몇 명을 처리해야했는지 mid 분  나누기 time(i)를 원소의 수 만큼 ㄱㄱ
    long long low = 1;
    sort(times.begin(), times.end());
    long long high = (long long)times.back() * n;

    // 첫 mid
    long long mid = 0;

    while (low < high)
    {
        mid = low + (high - low) / 2;
        long long people = 0;
        for (auto time : times)
        {
            people += (mid / (long long)time);
        }
        if (n <= people)
        {
            high = mid;
        }
        else// n > people
        {
            low = mid + 1;
        }

    }
    answer = low;
    return answer;
}

int main()
{
    long long answer = solution(6, { 7,10 });
    std::cout << answer;
}