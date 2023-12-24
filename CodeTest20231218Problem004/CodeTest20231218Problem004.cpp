// 백준 14719 빗물
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    int worldheight;
    int worldwidth;
    cin >> worldheight;
    cin >> worldwidth;
    vector<int> blocks;
    for (int i = 0; i < worldwidth; ++i)
    {
        int bh;
        cin >> bh;
        blocks.emplace_back(bh);
    }
    stack<int> stk;
    bool canFill = false;// 첫 시작부터 높아지는건 못채움
    int highest = 0;
    int water = 0;
    for (auto a : blocks)
    {
        if (stk.empty())
        {
            stk.push(a);
            continue; // 시작하면 비어있고 넣기
        }
        if (stk.top() <= a && !canFill)
        {   // 다음 블록이 더 크지만 채울 수 없을때
            stk.pop();
            stk.push(a); // 큐 비우고 추가
        }
        else if (stk.top() < a && canFill)
        { // 다음 블록이 더 큰데 채울 수 있는 상태에서 
            // 가장 높은거 보다 크거나 같다 계산 아니면 넣기
            if (highest <= a)
            {
                while (!stk.empty())
                {
                    water += highest - stk.top();
                    stk.pop();
                }
                canFill = false;
                stk.push(a);
            }
            else
            {
                stk.push(a);
            }
        }
        else if (stk.top() > a && !canFill)
        { // 채울수 없는 상태에서 더 작은게 들어옴 
            highest = stk.top(); // 물차는 지점 설정
            canFill = true;
            stk.push(a);
        }
        else if (stk.top() >= a && canFill)
        {
            stk.push(a);
        }


    }
    // 채울수있는 상태인데 끝나버리고 고려해야하는 생황
    // 그저 내리막 상태로 끝나서 못함
    // 채워가는 과정에서 highest 보다 높은 블록이 안들어 온상태
    if (canFill)
    {
        // TODO
        auto last = stk.top();
        stk.pop();
        while (!stk.empty())
        {
            if (last <= stk.top())
            {
                last = stk.top();
                stk.pop();
            }
            else
            {
                if (highest <= last)
                {
                    water += highest- stk.top();
                    stk.pop();
                }
                else
                {
                    water += last - stk.top();
                    stk.pop();
                }
            }

        }
            
    }
    cout << water << endl;
}
