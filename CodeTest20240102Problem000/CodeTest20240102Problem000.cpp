// LeetCode 120. Triangle
// Triangle Path Sum

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int answer = 0;
        int tsize = triangle.size();
        vector<vector<int>> cache(tsize, vector<int>(triangle.back().size(), 10001));
        cache.back() = triangle.back();
        answer = Caching(0, 0, cache, triangle);
        return answer;
    }

    int Caching(int i,int j,vector<vector<int>>& _cache, vector<vector<int>>& _triangle)
    {
        if (_cache[i][j] != 10001) return _cache[i][j];

        _cache[i][j] = _triangle[i][j] + min(Caching(i + 1, j, _cache, _triangle), Caching(i + 1, j + 1, _cache, _triangle));

        return _cache[i][j];
    }
};


int main()
{
    vector<vector<int>> Input = { {-10} };
    Solution s1;
    cout << s1.minimumTotal(Input) << endl;
    return 0;
}