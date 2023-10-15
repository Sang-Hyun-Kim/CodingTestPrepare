// 프로그래머스 Lv.2 무인도 여행

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void DFS(vector<string>& _maps, int _i, int _j, int& sum, vector<vector<bool>>& _discovered);

vector<int> solution(vector<string> maps);

int main()
{
    vector<string> maps = { "XXX","XXX","XXX" };
    vector<int> answer = solution(maps);

    for (int i = 0; i < answer.size(); i++)
    {
        cout << i << " 번째 값: " << answer[i] << endl;
    }
}

void DFS(vector<string>& _maps, int _i, int _j, int& sum, vector<vector<bool>>& _discovered)
{
    if (_i < 0 || _j < 0 || _i >= _maps.size() || _j >= _maps[0].size() || _maps[_i][_j] == 'X' || _discovered[_i][_j])
    {
        return;
    }

    sum += _maps[_i][_j] - '0';
    _discovered[_i][_j] = true;
    DFS(_maps, _i - 1, _j, sum, _discovered); // 상

    DFS(_maps, _i + 1, _j, sum, _discovered); // 하

    DFS(_maps, _i, _j - 1, sum, _discovered); // 좌

    DFS(_maps, _i, _j + 1, sum, _discovered); // 우

}

vector<int> solution(vector<string> maps) {
    const int row = maps.size();
    const int colm = maps[0].size();

    vector<vector<bool>> discovered(row, vector<bool>(colm, false));

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