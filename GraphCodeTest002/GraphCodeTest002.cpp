#include <string>
#include <vector>
#include <iostream>
#include <climits>

using namespace std;

// 플로이드-워셜을 통해 m선수가 s선수를 이기고 s선수가 e선수를 이겼을때=> m선수도 e선수를 이긴다와
// m선수가 s선수한테 지고 s선수가 e선수에게 질때 m선수도 e선수에게 지는 것으로 확인
// 각 선수의 승패 배열을 담은 graph 이차원 배열에서 승패의결과가 없으면 0 있으면 1또는 -1로 표현되며
// 그 갯수를 세어 자기 자신에 대한결과값인 0 단 하나만 있다면 순위를 결정할 수 있게 됨

int solution(int n, vector<vector<int>> results) {
   
    int answer = 0;

    vector<vector<int>> graph(n+1, vector<int>(n+1, 0));
    
    for (int i = 0; i < results.size(); ++i)
    {
        int winner = results[i].front();
        int loser = results[i].back();
        graph[winner][loser] = 1;
        graph[loser][winner] = -1;
    }

    for (int m = 1; m <= n; ++m)
    {
        for (int s = 1; s <= n; ++s)
        {  
            for (int e = 1; e <= n; ++e)
           {
                if (graph[s][m] == 1 && graph[m][e] ==1)
                {
                    graph[s][e] = 1;
                    graph[e][s] = -1;
                }
                if (graph[s][m] == -1 && graph[m][e] == -1)
                {
                    graph[s][e] = -1;
                    graph[e][s] = 1;
                }
           }
        }
    }

    // n개의 정점있을때 정점 i에 대해 n-1개의 엣지가 있으면 순위 결정 가능
    for (int i = 1; i <= n; ++i)
    {
        int count = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (graph[i][j] == 0) count++;
        }
        if (count == 1) answer++;
    }
    return answer;
}

int main()
{
    auto answer = solution(5, { {4,1},{4,2},{3,2},{1,2},{2,5} });
    cout << answer << endl;
}