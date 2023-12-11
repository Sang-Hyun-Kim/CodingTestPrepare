#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int, int>> map;
        for (int i = 0; i < nums.size(); ++i)
        {
            map.push_back({i,nums[i]});
        }
        sort(map.begin(), map.end(), [](auto a, auto b)
            {return a.second < b.second; });

        int left = 0;
        int right = map.size() - 1;
        int sum = 0;

        while (left < right) {
            sum = map[left].second + map[right].second;

            if (sum == target) {
                return { map[left].first, map[right].first};
            }
            else if (sum < target) {
                left += 1;
            }
            else {
                right--;
            }

        }
        return {};
    }
};

int main()
{
    
}