// 백준 2473 세 용액
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
    vector<long long> best2(3, 0);
    sort(nums.begin(), nums.end());

    long long sum;
    long long cursum = LLONG_MAX;
    
    for (int k = 0; k < nums.size() - 2; k++)
    {
        int left = k+1;
        int right = nums.size() - 1;
        while (left < right)
        {
            sum = nums[k] + nums[left] + nums[right];
            if (cursum >= abs(sum))
            {
                cursum = abs(sum);
                best2[0] = nums[left];
                best2[1] = nums[right];
                best2[2] = nums[k];
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

    }
    sort(best2.begin(), best2.end());
    cout << best2[0] << ' ' << best2[1] << ' ' << best2[2] << endl;;
}