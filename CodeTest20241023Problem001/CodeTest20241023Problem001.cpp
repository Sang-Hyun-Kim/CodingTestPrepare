// 백준 2470 두 용액
// 투포인터 탐색
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
int N;
using namespace std;
int main()
{
    cin >> N;
    vector <long long> nums(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> nums[i];
    }
    vector<long long> best2(2, 0);
    sort(nums.begin(), nums.end());

    int left=0;
    int right=nums.size()-1;
    long long sum;
    long long cursum=LLONG_MAX;


    while (left < right)
    {
        sum = nums[left] + nums[right];
        if (cursum >= abs(sum))
        {
            cursum = abs(sum);
            best2[0] = nums[left];
            best2[1] = nums[right];
        }
       
        if (sum > 0)
        {
            right--;
        }
        else
        {
            left++;
        }

    }
    sort(best2.begin(), best2.end());
    cout << best2[0] <<' ' << best2[1] << endl;;
}