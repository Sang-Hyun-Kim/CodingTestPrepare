// 백준 1920 수 찾기 실버 4
#pragma warning(disable:4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
bool BinarySearch(vector<int>& _nums, int _value);
int main()
{
    int totalNum;
    scanf("%d",&totalNum);
    vector<int> nums;
    nums.reserve(totalNum);
    for (int i = 0; i < totalNum; ++i)
    {
        int crnum;
        scanf("%d", &crnum);
        nums.push_back(crnum);
    }
    sort(nums.begin(), nums.end());

    int searchNums;
    scanf("%d", &searchNums);
    for (int i = 0; i < searchNums; ++i)
    {
        int value;
        scanf("%d", &value);
        int right = nums.size() - 1;
        int left = 0;
        int midi = right / 2;
        while (left <= right)
        {
            if (nums[midi] == value) break;
            else if (nums[midi] > value)
            {
                right = midi - 1;
            }
            else
            {
                left = midi + 1;
            }
            midi = (left + right) / 2;
        }

        if (nums[midi] == value)
        {
            printf("1\n");
            continue;
        }

        printf("0\n");
        
    }
}
