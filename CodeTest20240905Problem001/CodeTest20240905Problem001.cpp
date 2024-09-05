// 백준 2493번 탑 골드 5
// 역순으로 내림차순 스택을 만들며 조건에 따라 값을 기입하는 처리
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
int N = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    vector<int> answers(N, 0);
    vector<int> nums(N, 0);
    stack<pair<int, int>> st;
    for (int i = 0; i < N; ++i)
    {
        cin>>nums[i];
    }


    for (int i = nums.size()-1;i>=0;--i)
    {
        pair<int,int> cp = make_pair(nums[i], i);//v,idx

        if (st.empty())
        {
            st.push(cp);
        }
        else
        {
            if (st.top().first >= cp.first)
            {
                st.push(cp);
            }
            else
            {// 다음 역순 기둥이 더 큰 경우(송신 처리)
                while (st.top().first < cp.first)
                {
                    auto ctop = st.top();
                    st.pop();
                    answers[ctop.second] = cp.second + 1;
                    if (st.empty()) break;
                }
                st.push(cp);
            }
        }
        
    }

    for (auto n : answers)
    {
        cout << n << " ";
    }
}

