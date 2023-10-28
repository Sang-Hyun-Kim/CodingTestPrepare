#include <iostream>
#include <stack>
#include <string>
#include <algorithm>


using namespace std;
bool solution(string s);
int main()
{
    string s1 = "(())()";
    bool answer = solution(s1);
    cout << answer << endl;
}
bool solution(string s)
{
    int PtCnt = 0;
    stack<char> stk;
    bool answer = true;

    for (char ss : s)
    {
        stk.push(ss);
    }
    int stksize = stk.size();
    for (int i = 0; i < stksize; i++)
    {
        if (stk.top() == ')')
        {
            PtCnt++;
        }
        else if (stk.top() == '(')
        {
            PtCnt--;
            if (PtCnt < 0)
            {
                answer = false;
            }
        }
        else
        {
            cout << "괄호가 아닌 문자가 들어가있습니다." << endl;
        }
        stk.pop();
    }

    if (PtCnt != 0)
    {
        answer = false;
    }

    return answer;
}