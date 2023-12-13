#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {

        set<vector<int>> answerset;
        vector<int> originalnum = nums;
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < nums.size() - 2; i++)
        {
            int firstnum = nums[i];
            int left = i+1;
            int right = nums.size() - 1;
            int sum = firstnum;
            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }

            while (left < right)
            {
                int sndsum = nums[left] + nums[right];
                if (sndsum + sum == 0)
                {
                    answerset.insert({firstnum,nums[left],nums[right]});
                    //´ÙÀ½²¨ Ã£±â
                    left++;
                    right--;
                }
                else if (sndsum + sum < 0)
                {
                    left++;
                }
                else
                {
                    right--;
                }
            }
        }
        vector<vector<int>> answer(answerset.begin(), answerset.end());
        return answer;
    }
};

int main()
{

}