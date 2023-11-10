#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;
// 백준 1655 가운데를 말해요 풀이
// 
// 입력하나 들어올때마다 전체 값 변수 totalNum 저장 1
// currentValue = 입력된 변수 값 저장 1
// middleValue = 중간 값 및 연산 마지막에 출력 1
// 출력될 값의 순서인 queue<int> answer; 1
// 우선 순위 큐 두개 정의 LMax: 중간 값보다 작은 값중 최대값, Rmin 중간 값보다 큰 값중 최소 값
// currentValue < middleValue ? LMax.push() : Rmin.push();

// 작업 하나 끝나면 currentNum / 2 가 == 0 (짝수 일 경우) 
// LMax.size() - Rmin.size() 가 1or -1 이 어야함
// 맞으면 다음 순을 위해 middleValue를 answer에 push
// 아닐 경우 Shifting 진행 균형을 맞춰주기 위해 많은 쪽을 찾아 많은 쪽에서 적은 쪽으로 이동
// 중간 값을 적은 쪽으로 push => 많은쪽의 top을 적은 값으로 지정
// currentNum / 2 !=0 => 홀수일 경우
//  양쪽의 사이즈가 같아야함
// 같으면 다음 순을 위해 middleValue를 answer에 push
// 아닐 경우 Shifting 진행
// middlevalue의 값을 적은 쪽으로 많은 쪽의 top을 middleValue로,  

// 다 끝나면 answer 값을 차례대로 배출


//
int main()
{
    int totalNum = 0;
    int currentNum = 0;
    int middleValue = 0; // 중간 값
    int currentValue = 0;
    queue<int> answer;
    priority_queue<int, vector<int>, greater<>> Rmin;
    priority_queue<int> LMax;

    scanf("%d", &totalNum);

    for (int i = 0; i < totalNum; ++i)
    {
        scanf("%d", &currentValue); // 현재값 입력 받기

        if (i == 0)
        {
            middleValue = currentValue;
            printf("%d\n", middleValue);
            continue;
        }

        if (middleValue <= currentValue)
        {
            Rmin.emplace(currentValue);
        }
        else
        {
            LMax.emplace(currentValue);
        }

        // 한쪽에 두개 씩
        if (Rmin.size() - LMax.size() == 2)
        {
            LMax.emplace(middleValue);
            middleValue = Rmin.top();
            Rmin.pop();
        }
        else if (LMax.size() - Rmin.size() == 2)
        {
            Rmin.emplace(middleValue);
            middleValue = LMax.top();
            LMax.pop();
        }
        else if (LMax.size() - Rmin.size() == 1 && middleValue > LMax.top())
        {
            Rmin.emplace(middleValue);
            middleValue = LMax.top();
            LMax.pop();
        }

        printf("%d\n", middleValue);
    }
}
