// 백준 16987 계란으로 계란치기
#include <iostream>
#include <vector>
#include <algorithm>
// 백트래킹, 오랜만에해서 실수 많았고 너무 오래걸렸음
// 실수 1: 손에 든 것 기준으로 가지치기 깜박
// 실수 2: 손에 든 것 제외 전부 깨졌을 경우의 예외처리 깜박
// 실수 3: 백트래킹 을 위해 벡터를 굳이 복사해야했을까? 그냥 빼준것 그대로 다시 더해주고 다음 계란 선택 진행시키기
using namespace std;
int N;
int answer = 0;
void Backtracking(vector<int>& eggs, vector<int> eh, int index, int be, vector<int>& maxegg);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    vector<int> eggs(N, 0);
    vector<int> eh(N, 0);
    vector<int> maxegg(N, 0);
    for (int i = 0; i < N; ++i)
    {
        cin >> eh[i] >> eggs[i];
    }


    Backtracking(eggs, eh, 0, 0, maxegg);
    cout << answer;
}

void Backtracking(vector<int>& eggs,vector<int> eh,int index,int be, vector<int>& maxegg)
{
    // 끝 도달
    if (index >= eggs.size())
    {
        answer = max(answer, be);
        return;
    }
    if (eh[index] <= 0)
    {
        Backtracking(eggs, eh, index + 1, be, maxegg);
    }
    else
    {
        // 계산 시작
    // 손에 든 계란에 대해 남은 계란판에 대한 모든 부딪힘 실행하기
        bool flag = false;
        for (int i = 0; i < N; ++i)
        {
            if (i != index && eh[i] > 0)
            {// 현재 손에든(INDEX) 계란과 현재 선택한 계란의 내구도가 남은 경우에만
                int newbe = be;
                eh[i] -= eggs[index];
                eh[index] -= eggs[i];
                // 부딪힌 계란의 내구도 계산
                if (eh[i] <= 0)
                {
                    newbe++;
                }
                if (eh[index] <= 0)
                {
                    newbe++;
                }
                // 이번 계산 이후의 계란판 + 다음 계란 선택을 하는 재귀함수 호출
                flag = true;
                Backtracking(eggs, eh, index + 1, newbe, maxegg);
                eh[i] += eggs[index];
                eh[index] += eggs[i];
            
            }
        }
        if (!flag) Backtracking(eggs, eh, index + 1, be, maxegg); // 든거제외 전부 깨짐
    }
    
}