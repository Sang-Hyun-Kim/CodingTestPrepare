// CodeTest20240115Problem002.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
//6의10승  60,466,176
// 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
int N;
// 주사위 0~3이 있을 때(1~4)
// 순열은 0 1 과 2 3,  1 0 과 2 3,0 1과 3 2,  1 0과 3 2 이 생성 된다고 하자
// 하지만 이는 전부 A가 0과 1번, B가 2와 3번을 가지는 조합 하나를 여러 방식으로 표현한 것이기 때문에 next_permutation을 사용하면서 중복 처리를 해주어야 한다.
vector<int> solution(vector<vector<int>> dice) {
    for (int i = 0; i < dice.size(); ++i)
    {
        sort(dice[i].begin(), dice[i].end());
    }
    N = dice.size();
    vector<int> dices;
    for (int i = 0; i < N; i++)
    {
        dices[i] = i; // 배열 생성
    }
    int half = N / 2; // 0~N/2-1 || N/2~N-1 ==> 배열 인덱스
    map<pair<set<int>, set<int>>, bool> duplication;
    do
    {
        vector<int> A, B;
        set<int> AS, BS; // 주사위 index를 순서대로 저장=> 중복 처리를 위한 set 자료구조
        for (int i = 0; i < N / 2; ++i)
        {
            A.push_back(dices[i]);
            AS.insert(dices[i]);
            B.push_back(dices[i + N / 2]);
            BS.insert(dices[i + N / 2]);
        }
        if (duplication.find({ AS,BS }) == duplication.end())
        {// A,B가 가진 주사위 index 번호의 조합이 없는 경우에 만
            // A와 B가 가진 주사위의 번호로 조합의 합을 도출
        }
    } while (next_permutation(dices.begin(), dices.end()));

    
    vector<int> answer;
    
    return answer;
}
int main()
{
    vector<vector<int>> dices = { {40,41,42,43,44,45},{43,43,42,42,41,41},{1,1,80,80,80,80},{70,70,1,1,70,70} };
    auto vec = solution(dices);
    int a = 0;
}
