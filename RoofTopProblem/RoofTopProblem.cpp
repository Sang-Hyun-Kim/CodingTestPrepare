#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <stack>

using namespace std;

int main()
{

    int Bnum;     // 빌딩의 수
    cin >> Bnum;

    list<int> Buildings;
    stack<int> Stk;
    int heights = 0; //각 빌딩 높이 입력용

    long long answer = 0 ; // 답안

    int currentBd;

    for (int i = 0; i < Bnum; ++i)
    {
        cin >> heights;
        Buildings.insert(Buildings.end(), heights);
    }

    while (!Buildings.empty()) // 빌딩 전부 넣으면 끝
    {
        // 빌딩 모음에서 하나 팝
        currentBd = Buildings.front();
        Buildings.pop_front();

        // MonotoneStack에 내림차순으로 넣기
        while(true)
        {   //CurrentBd를 넣을수 있거나 못넣게 되면 break;
            if ( !Stk.empty())
            { //안에 있으면
                if (Stk.top() > currentBd)// 크기비교
                {   // 제일 앞 빌딩보다 낮으면 
                    Stk.push(currentBd); // 스택에 넣고
                    answer += Stk.size() - 1; // 옥상 계산 넣기
                    break;
                }
                else                            // 제일 앞 빌딩과 같거나 더 크면
                {
                    // 제일 앞 빌딩 제거
                    Stk.pop();
                    // 순회
                    continue;
                }

            }
            else// Stk가 비어있음
            {
                Stk.push(currentBd);
                // size()-1 추가
                answer += Stk.size() - 1; // 어쩌피 0
                break; // 순회끝 다음빌딩
            }
            
        }
    }
    // 답안 출력
    cout << answer << endl;
}


// 개요 Monotone stack 알고리즘 사용
//  
// MonotoneStack 내림차순 기입
// Stack에 값을 넣을 때 <
