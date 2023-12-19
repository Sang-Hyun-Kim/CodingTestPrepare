// 백준 1863 스카이라인 쉬운거 
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    vector<int> lines;
    lines.reserve(1000000);
    int Num;
    cin >> Num;
    int x;
    int y;
    for (int i = 0; i < Num; ++i)
    {
        cin >> x;
        cin >> y;
        lines.push_back(y);
    }
    stack<int> linestack;
    int bcount=0;
    for (auto line : lines)
    {
        // 고도가 0일 경우 전부 초기화하고 개수 추가
        if (line == 0)
        {
            bcount += linestack.size();
            while (!linestack.empty()) linestack.pop();
            continue;
        }
        if (linestack.empty()) linestack.push(line);
        else
        {
            if (linestack.top() < line) linestack.push(line);
            else if (linestack.top() > line)
            {
                // 마지막 좌표보다 작은경우
                // 같아지거나 더 낮은 높이가 나올때까지 pop()
                // 같아지면 스킵
                while (linestack.top() > line)
                {
                    linestack.pop();
                    bcount++;
                    if (linestack.size() == 0) break;
                }
                // 작거나 같아졌을때 같을 경우
 
                 if (linestack.size() == 0)
                 {
                     linestack.push(line);
                     continue;
                 }

                 if (linestack.top() < line) linestack.push(line);
                 if (linestack.top() == line) continue; // 스킵하고 다음으로

            }
        }
    }
    // 남은 스택 처리
    while (!linestack.empty())
    {
        linestack.pop();
        bcount++;
    }
    cout << bcount << endl;
}
