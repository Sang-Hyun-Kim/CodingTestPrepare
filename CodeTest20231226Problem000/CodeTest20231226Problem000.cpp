// 백준 구간 합 구하기 4 실버3
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int num;
    int snum;
    cin >> num;
    cin >> snum;
    vector<int> nums(num);
    vector<int> sums(num+1);
    sums[0] = 0;

    for (int i = 0; i < num; ++i)
    {
        cin >> nums[i];
        sums[i + 1] = sums[i] + nums[i];
    }

    for (int i = 0; i < snum; ++i)
    {
        int L;
        int R;
        cin >> L;
        cin >> R;
        int answer = sums[R] - sums[L - 1];
        cout << answer<<"\n" ;

    }
}