#include <string>
#include <vector>
#include <iostream>
#define ll long long 
using namespace std;
// 이해 안되서 힌트 보고 품
// 최소 값을 찾기 위해 통 벡터에 넣고 회전하는 포인터 각각 두 개, 총 4개를 만듬 이것으로 각각의 큐를 구현함
// sum1 sum2의 값 차이에 따른 포인터 회전
// 투 포인터는 정렬 조건이 보장되어야 하는 것이아니냐 라는 탐욕법은 카카오 해설 풀이에 따라 증명됨
// 각 방향의 총합 L,R 에 대해서 L>R인 상황에서 L로 넘기는 상황이 맞다면 언젠간 R로 넘겨줘야한다. 그래야 L과 R 합의 최소를 만들기 위해
// L->R, R->L이 어떻게든 순서 상관없이 수행만 된다면 결과는 같으므로
// L>R일 때 L의 값을 넘겨주는 것은 항상 최적 해 이다.
int solution(vector<int> queue1, vector<int> queue2) {
    int answer = 0;
    vector<int> total;
    int totalvectorsize = queue1.size() * 2;// 전체 크기
    ll sum1 = 0;
    ll sum2 = 0;
    // 회전하는 벡터의 포인터, 두 큐를 의미함
    int qs1 = 0;
    int qs2 = queue1.size();
    int qe1 = queue1.size() - 1;
    int qe2 = queue1.size() * 2 - 1;

    // 하나의 통 벡터로 합침
    for (auto q : queue1)
    {
        sum1 += q;
        total.push_back(q);
    }
    for (auto q : queue2)
    {
        sum2 += q;
        total.push_back(q);
    }

    while (answer <= totalvectorsize * 2)
    {
        if (sum1 < sum2)
        {
            sum1 += total[++qe1 % totalvectorsize];
            sum2 -= total[qs2++ % totalvectorsize];
        }
        else if (sum1 > sum2)
        {
            sum1 -= total[qs1++ % totalvectorsize];
            sum2 += total[++qe2 % totalvectorsize];
        }
        else
        {
            return answer;
        }
        answer++;
    }
    return answer = -1;
}
int main()
{
    std::cout << "Hello World!\n";
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
