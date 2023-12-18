// 2022_KAKAOTECH INTERNSHIP 등산코스 정하기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// { 정점, 해당 정점까지 갈 수 있는 Intensity 중 최소 값}을 저장
// 시간을 줄이기 위해 모든 시작 정점에서 출발 
struct cmp
{
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        if (a.second == b.second)
            return a.first > b.first;
        return a.second > b.second;
    }
};
vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    
    vector<int> answer;
    vector<bool> visited(n+1,false);
    vector<vector<int>> list;
    //vector<bool> distance(n, -1);
    vector<vector<pair<int, int>>> graph(n+1,vector<pair<int,int>>());
    for (vector<int> path : paths)
    {
        graph[path[0]].push_back({path[1],path[2]});
        graph[path[1]].push_back({ path[0],path[2] });
        
        // graph[출발 정점] = {도착 정점, 가중치}
    }// 그래프 등록
    priority_queue < pair<int, int>, vector < pair<int, int>>, cmp > queue;
   
    for (auto start : gates)
    {
        //다익스트라 큐에 넣기
        queue.push({ start,0 });
        //distance[start] = 0;
    }
    while (!queue.empty())
    {
        auto currentvertex = queue.top();
        queue.pop();

        if (find(summits.begin(), summits.end(), currentvertex.first) != summits.end())
        {
            list.push_back({currentvertex.first,currentvertex.second});
            continue; // 테스트 케이스 3번 중복 정상 정상 처리 
        }

        if (!visited[currentvertex.first])
        {   // 방문하지 않은 정점
            auto vertex = currentvertex.first;
            auto weight = currentvertex.second;
            for (auto v : graph[vertex])
            {
                // 다음 정점, 가중치를 꺼내서
                // queue에는 다음 정점과의 거리와 지금까지의 최소 가중치 중 큰 것이 들어간다.
                
                queue.push({ v.first,max(v.second, weight) });

            }

            visited[vertex] = true;
        }
    }
    if (list.size() == 0) return {};
    sort(list.begin(), list.end(), [](vector<int> a, vector<int> b) {
        if (a[1] == b[1]) return a[0] < b[0];
        return a[1] < b[1]; });

    return list.front();
}
int main()
{
    
    auto answer = solution(7,{ {1,4,4},{1,6,1},{1,7,3},{2,5,2},{3,7,4},{5,6,6}}, { 1 }, { 2,3,4 });
    cout << answer[0] <<" | "<< answer[1] << endl;
}
