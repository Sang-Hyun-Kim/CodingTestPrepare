#include <iostream>
#include <string>
#include <vector>


int Memo(std::vector<std::vector<int>>& _dp, int i, int j, std::string& _str1, std::string& _str2);
int main()
{
    std::string str1;
    std::string str2;
    std::getline(std::cin, str1);
    std::getline(std::cin, str2);
    std::vector<std::vector<int>> dp(str1.size(),std::vector<int>(str2.size(),-1));

    
    int answer = Memo(dp, str1.size() - 1, str2.size() - 1, str1, str2);
    std::cout << answer << std::endl;

}

int Memo(std::vector<std::vector<int>>& _dp,int i, int j, std::string& _str1,std::string& _str2)
{
    if (i < 0 || j < 0) return 0;

    if (_dp[i][j] != -1)
        return _dp[i][j];

    if(_str1[i] == _str2[j])
    {
        _dp[i][j] = 1 + Memo(_dp, i - 1, j - 1, _str1, _str2);
        return _dp[i][j];
    }
    else
    {
        _dp[i][j] = std::max(Memo(_dp, i - 1, j, _str1, _str2), Memo(_dp, i, j - 1, _str1, _str2));
        return _dp[i][j];
    }
}