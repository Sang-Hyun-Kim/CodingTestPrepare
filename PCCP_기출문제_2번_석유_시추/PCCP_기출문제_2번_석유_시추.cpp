// PCCP_기출문제_2번_석유_시추 프로그래머스 맞은 코드 + 틀린 코드(정확성다 맞아도 효율성 하나만 맞음)
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>

// 열별 순회
// 열별 순회당 행별 순회 여부 파악
// 그룹 ID를 땅 배열에 기입, 땅 ID당 기름개수를 미리 파악해서 중복 순회시 연산을 하지말고 리턴
using namespace std;

int solution(vector<vector<int>> land);
void BFS(vector<vector<bool>>& _visited, vector<vector<int>>& _land, int i, int j, int _group, map<int, int>& _oilGroup);
int main()
{
    int answer = -1;

    answer = solution({
        {0, 0, 0, 1, 1, 1, 0, 0 },
        {0, 0, 0, 0, 1, 1, 0, 0},
        {1, 1, 0, 0, 0, 1, 1, 0 },
        {1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 1, 1 }
    });
    
    cout << answer << endl;
}

int solution(vector<vector<int>> land) {


    vector<int> score; // 순회 점수 기록
    int maxOil=0;
    int group = 1;
    int depth = land.size();
    int width = land[0].size();
    // 시추 열별 기름 값
    map<int,int> oilGroup;
    vector<vector<bool>> visited(depth, vector<bool>(width, false));
    // 시추관 순서 순회
    for (int i = 0; i < width; ++i)
    {
        // 열별 순회에 따른 방문처리
        int currentOil = 0;
        for (int j = 0; j < depth; ++j)
        {
            if (land[j][i] > 0 && !visited[j][i])  BFS(visited, land, i, j, ++group, oilGroup);
        }
        
    }

    for (int i = 0; i < width; ++i)
    {
        set<int> groupcheck;
        int currentOil = 0;
        for (int j = 0; j < depth; ++j) groupcheck.insert(land[j][i]);
        for (auto oil : groupcheck)
        {
            currentOil += oilGroup[oil];
        }
        if (maxOil < currentOil) maxOil = currentOil;
    }
    return maxOil;
}

void BFS(vector<vector<bool>>& _visited, vector<vector<int>>& _land, int i, int j, int _group, map<int,int>& _oilGroup)
{
    queue<pair<int, int>> queue;
    int currentoil = 0;
    queue.push({j,i});
    while (!queue.empty())
    {
        auto currentland = queue.front();
        queue.pop();
        if (currentland.first >= 0 && currentland.first < _land.size()
            && currentland.second >= 0 && currentland.second < _land[0].size())
        {
            if (_visited[currentland.first][currentland.second]) continue;
            
            if (_land[currentland.first][currentland.second] == 1)
            {
                currentoil++;
                _land[currentland.first][currentland.second] = _group;
                queue.push({ currentland.first - 1 ,currentland.second });// 상
                queue.push({ currentland.first + 1 ,currentland.second });// 하
                queue.push({ currentland.first ,currentland.second - 1 });// 좌
                queue.push({ currentland.first ,currentland.second + 1 });// 우
            }
            else continue;
            _visited[currentland.first][currentland.second] = true;
        }
    }

    _oilGroup.emplace(pair<int,int>( _group, currentoil));
}

/* 시간 초과 오류 코드
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<vector<int>> land);
int BFS(vector<vector<bool>>& _visited, vector<vector<int>>& _land, int i, int j);

int solution(vector<vector<int>> land) {


    vector<int> score; // 순회 점수 기록
    int maxOil=0;

    vector<vector<int>> oil(land.size(),vector<int>(land[0].size(),-1)); // 순회돌때 각 칸에 그룹이 있다면 그 그룹의 기름값 저장, 순회하면서 이미 계산된 기
    int answer = 0;
    

    // 시추관 순서 순회
    for (int i = 0; i < land[0].size(); ++i)
    {
        vector<vector<bool>> visited(land.size(),vector<bool>(land[0].size(), false));
        int currentOil = 0;
        for (int j = 0; j < land.size() ; ++j)
        {
            if (land[j][i] == 0)
            {// 흙
                continue;
            }
            else
            {// 와!! 기름 => bfs 수행
                if (visited[j][i])
                {// 이번 시추에서 이미 캔 것
                    continue;
                }
                else
                {

                    currentOil += BFS(visited,land,i,j);
                }
            }

        }
        if (maxOil < currentOil) maxOil = currentOil;
    }

    return maxOil;
}

int BFS(vector<vector<bool>>& _visited, vector<vector<int>>& _land, int i, int j)
{
    queue<pair<int, int>> queue;
    vector<vector<bool>> bfsvisited(_land.size(), vector<bool>(_land[0].size(), false)); // bfs하면서 수행할 큐
    int currentoil = 0;
    queue.push({j,i});
    while (!queue.empty())
    {
        auto currentland = queue.front();
        queue.pop();
        if (currentland.first >= 0 && currentland.first < _land.size()
            && currentland.second >= 0 && currentland.second < _land[0].size())
        {
            if (bfsvisited[currentland.first][currentland.second]) continue;
            
            if (_land[currentland.first][currentland.second] == 1)
            {
                currentoil++;
                queue.push({ currentland.first - 1 ,currentland.second }); // 상
                queue.push({ currentland.first + 1 ,currentland.second });// 하
                queue.push({ currentland.first ,currentland.second - 1 });// 좌
                queue.push({ currentland.first ,currentland.second + 1 });// 우
            }
            else
            {
                continue;
            }
            bfsvisited[currentland.first][currentland.second] = true;
            _visited[currentland.first][currentland.second] = true;
        }
    }
    return currentoil;
}*/