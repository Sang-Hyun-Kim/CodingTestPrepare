// DPCodeTest001.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<unordered_set<int>> mem(8);
// 반복되는 N을 계산해서 넣는함수
// N= 1(index) => NN
// N = 2 => NNN
// N = 7 => NN,NNN,NNN
int GetMultipleN(int number, int index)
{
    int next = number;
    for (int i = 1; i <= index; ++i)
    {
        next = next * 10 + number;
    }
    return next;
}

int solution(int N, int number) {
    
    if (N == number) return 1;
    int answer = 0;

    mem[0].insert(N);


    for(int n  = 1 ; n < 8; n++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i + j + 1 != n) continue;

                for ( auto first : mem[i])
                {
                    for (auto second : mem[j])
                    {
                        mem[n].insert(first + second); // 합
                        mem[n].insert(first * second); // 곱

                        // 빼기 이후의 값이  양의 정수만 들어가도록 수정, 음수는 횟수를 증가시킬 뿐이다. 제거
                        // 0은 사칙연산에서 나누기에서 오류가 생기는 것과 최소 횟수를 구하는 과정에 0은 가치가 없으므로 제거
                        if (first - second > 0)
                            mem[n].insert(first - second);
                        if (first / second > 0)
                            mem[n].insert(first / second);
                    }
                        
                        
                }

            }
        }

        // N이 연속으로 중복되는 값 넣기
        // 이는 이전 N의 중복값에서 *10을 하고 N을 넣으면 됨

        mem[n].insert(GetMultipleN(N,n));

        // 값 찾고 반환하기
        // n개로 생성하는 숫자의 모음집에서 목표를 발견했다면 
        // 해당 n개를 반환
        if (mem[n].find(number) != mem[n].end()) return n+1; // 최소 횟수 반환
    }

    // 못찾았으면 -1 반환
    return -1;
}


int main()
{
    int answer = solution(5,555);
    cout << answer << endl;

}

// S(N)(N으로 만들수있는 것의 조합은)
// N = I + J 일때 S(N) = S(I) + S(J) + N의N만큼 중복된 수 가 된다.
// S(N)
