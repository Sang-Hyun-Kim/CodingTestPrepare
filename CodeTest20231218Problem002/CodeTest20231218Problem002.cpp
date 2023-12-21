// 백준 16234 인구이동 골드 4

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// 전체 좌표 순회 하며 각각의 좌표에 bfs 수행
// bfs 수행하면서 조건에 일치하는 좌표 방문 처리 및 방문 좌표의 인구 저장, 나라 수 증가
// bfs끝나면 bfs가 다 돈 곳들이 연합이니까 인구/방문횟수 연산후 저장했던 좌표들에 해당 인구 갱신
// 각 좌표 마다 bfs 수행하면서 방문처리 된곳(이미 연합연산처리가 되었으므로)은 스킵
// 전부 끝나면 bfs를 수행했는지 체크
// 수행했으면 한번 더 반복 하면서 인구이동이 일어난 날 변수++
// 수행 안했으면 반복문을 탈출
using point = pair<int, int>;
using namespace std;
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
                queue<point> bfsq;
                vector<point> Union; // 연합만들기
                vector<int> uPop; // 연합이 될 나라 좌표 넣기
                int ucount = 0; // 연합의 국가 수
                bfsq.push((i,j));
                while (!bfsq.empty())
                {
                    auto currenc = bfsq.front();
                    bfsq.pop();
                    if (currenc.first < 0 && currenc.first >= num &&
                        currenc.second < 0 && currenc.second >= num) continue;
                    if (!cvisits[currenc.first][currenc.second])
                    {
                        Union.emplace((currenc.first, currenc.second));
                        bfsq.push((currenc.first - 1 , currenc.second));
                        bfsq.push((currenc.first + 1, currenc.second));
                        bfsq.push((currenc.first, currenc.second - 1));
                        bfsq.push((currenc.first, currenc.second + 1));

                        cvisits[currenc.first][currenc.second] = true;
                    }

                }
                
            }
        }


    }
}
