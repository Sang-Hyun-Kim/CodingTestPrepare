// 프로그래머스 그래프 문제 가장 먼 노드

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;

    // 그래프 저장 1차원 배열
    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < edge.size(); i++)
    {
        int from = edge[i][0]; // { { 0 , 1},{ 0 , 1} }
        int to = edge[i][1];

        graph[from].push_back(to); // graph[i] : 정점 i와연결된 정점 번호들을 담음
        graph[to].push_back(from);
    }

    vector<int> dist(n + 1, -1);
    queue<int> q;

    dist[1] = 0;
    q.push(1);


    while (!q.empty())
    {
        auto currentNode = q.front();
        q.pop();

       for (auto next : graph[currentNode])
       {
           if (dist[next] == -1)
           {
               dist[next] = dist[currentNode] + 1;
               q.push(next);
           }
       }
    }

    int far = *max_element(dist.begin(),dist.end());

    for (int i = 0; i < dist.size(); i++)
    {
        if (dist[i] == far)
        {
            answer++;
        }
    }
    return answer;
}
int main()
{
    vector<vector<int>> edge = { {3,6},{4,3},{3,2}, {1,3}, {1,2}, {2,4}, {5,2} };
    auto answer = solution(6, edge);
    cout << answer << endl;
}

