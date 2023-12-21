// 백준 16234 인구이동 골드 4
//https://www.acmicpc.net/problem/16234
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>

// 전체 좌표 순회 하며 각각의 좌표에 bfs 수행
// bfs 수행하면서 조건에 일치하는 좌표 방문 처리 및 방문 좌표의 인구 저장, 나라 수 증가
// bfs끝나면 bfs가 다 돈 곳들이 연합이니까 인구/방문횟수 연산후 저장했던 좌표들에 해당 인구 갱신
// 각 좌표 마다 bfs 수행하면서 방문처리 된곳(이미 연합연산처리가 되었으므로)은 스킵
// 전부 끝나면 bfs를 수행했는지 체크
// 수행했으면 한번 더 반복 하면서 인구이동이 일어난 날 변수++
// 수행 안했으면 반복문을 탈출
using namespace std; 

bool IsinScope(pair<int,int> p, int& _num)
{
    if (p.first < 0 || p.first >= _num ||
        p.second < 0 || p.second >= _num) return false;
    return true;
}
int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int num;
    int moreL; int lessR;
    cin >> num;
    cin >> moreL;
    cin >> lessR;
    vector<vector<int>> Continent(num,vector<int>(num,-1));
    
    int migrationDay =0;
    bool ismigr = true;
    for (int i = 0; i < num; ++i)
    {
        for (int j = 0; j < num; ++j)
        {
            cin >> Continent[i][j];
        }
    }


    while (ismigr)
    {
        ismigr = false;
        vector<vector<int>> cvisits(num, vector<int>(num, false));
        
        
        for (int i = 0; i < num; ++i)
        {
            for (int j = 0; j < num; ++j)
            {
                //BFS계산
                if (cvisits[i][j]) continue;
                queue<pair<int,int>> bfsq;
                vector<pair<int,int>> Union; // 연합만들기
                vector<int> uPop; // 연합이 될 나라 좌표 넣기
                int ucount = 0; // 연합의 국가 수
                
                bfsq.push(make_pair(i,j));
                while (!bfsq.empty())
                {
                    auto currenc = bfsq.front();
                    bfsq.pop();
                    // if (IsinScope(currenc,num)) continue;
                    if (!cvisits[currenc.first][currenc.second])
                    {
                        Union.push_back(make_pair(currenc.first, currenc.second));
                        // 상
                        if (IsinScope(make_pair(currenc.first - 1, currenc.second), num))
                        {
                            if (moreL <= abs(Continent[currenc.first][currenc.second] - Continent[currenc.first - 1][currenc.second])
                                && abs(Continent[currenc.first][currenc.second] - Continent[currenc.first - 1][currenc.second]) <= lessR)
                                bfsq.push(make_pair(currenc.first - 1, currenc.second));
                        }

                        // 하
                        if (IsinScope(make_pair(currenc.first + 1, currenc.second), num))
                        {
                            if (moreL <= abs(Continent[currenc.first][currenc.second] - Continent[currenc.first + 1][currenc.second])
                                && abs(Continent[currenc.first][currenc.second] - Continent[currenc.first + 1][currenc.second]) <= lessR)
                                bfsq.push(make_pair(currenc.first + 1, currenc.second));
                        }
                        // 좌
                        if (IsinScope(make_pair(currenc.first, currenc.second -1), num))
                        {
                            if (moreL <= abs(Continent[currenc.first][currenc.second] - Continent[currenc.first][currenc.second - 1])
                                && abs(Continent[currenc.first][currenc.second] - Continent[currenc.first][currenc.second - 1]) <= lessR)
                                bfsq.push(make_pair(currenc.first, currenc.second - 1));
                        }
                        // 우
                        if (IsinScope(make_pair(currenc.first , currenc.second + 1), num))
                        {
                            if (moreL <= abs(Continent[currenc.first][currenc.second] - Continent[currenc.first ][currenc.second + 1])
                                && abs(Continent[currenc.first][currenc.second] - Continent[currenc.first ][currenc.second + 1]) <= lessR)
                                bfsq.push(make_pair(currenc.first , currenc.second + 1));
                        }

                        cvisits[currenc.first][currenc.second] = true;
                    }
                    // BFS끝
                   
                }
                if (Union.size() > 1)
                { // 연합 형성시
                    ismigr = true;
                    ucount = Union.size();
                    int totalPop = 0;
                    for (auto a : Union)
                    {
                        totalPop += Continent[a.first][a.second];
                    }
                    int avrgPop = totalPop / ucount;
                    for (auto a : Union)
                    {
                        Continent[a.first][a.second] = avrgPop;
                    }

                }
            }
        }
        if (ismigr) migrationDay++; // 이민 했으니까 날짜 추가 

    }
    // 전체 순회끝

    cout << migrationDay << endl;
}
