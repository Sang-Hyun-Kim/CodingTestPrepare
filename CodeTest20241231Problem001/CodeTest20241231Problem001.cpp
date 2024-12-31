// CodeTest20241231Problem001.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;
int R, C;
array<int, 4> dx = { 1, -1 , 0 , 0 };
array<int, 4> dy = { 0, 0, 1, -1 };// 하 상 우 좌
void DFS(vector<string>& _maps, int _i, int _j, int& sum, vector<vector<bool>>& _discovered);
bool InRange(int _x, int _y)
{
    if (0 <= _x && _x < R && 0 <= _y && _y < C)
    {
        return true;
    }
    return false;
}
vector<int> solution(vector<string> maps);

void DFS(vector<string>& _maps, int _i, int _j, int& sum, vector<vector<bool>>& _discovered)
{
    sum += _maps[_i][_j] - '0';
    _discovered[_i][_j] = true;

    for (int k = 0; k < 4; ++k)
    {
        int ni = _i + dx[k];
        int nj = _j + dy[k];
        if (InRange(ni, nj))
        {
            if (!_discovered[ni][nj] && _maps[ni][nj] != 'X')
            {
                DFS(_maps, ni, nj, sum, _discovered);
            }
        }
    }
}

vector<int> solution(vector<string> maps) {
    R = maps.size();
    C = maps[0].size();

    vector<vector<bool>> discovered(R, vector<bool>(C, false));

    vector<int> answer;

    for (int i = 0; i < maps.size(); i++)
    {
        for (int j = 0; j < maps[i].size(); j++)
        {
            if (maps[i][j] != 'X' && !discovered[i][j])
            {
                int sum = 0;
                DFS(maps, i, j, sum, discovered);
                answer.push_back(sum);
            }
        }
    }

    sort(answer.begin(), answer.end());
    if (answer.size() == 0)
        answer.push_back(-1);
    return answer;
}
int main()
{
    vector<int> ans = solution({ "X591X", "X1X5X", "X231X", "1XXX1" });
}
