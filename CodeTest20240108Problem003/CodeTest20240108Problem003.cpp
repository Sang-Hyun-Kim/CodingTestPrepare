// LeetCode 787. Cheapest Flights Within K Stops

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
using namespace std;
// 시간 초과 코드와 비교하면서 시간 개선하기
// 플로이드 워셜 안쓸 때에는 그래프 구조를 단순 2차원배열로 만들지 않기
// 거리를 도착정점과 도약횟수라는 2차원배열로 저장하지 않고
// 그냥 도약 횟수에 따라 반복문 자체에서 스킵하게 만들고 최소거리를 1차원 배열에서 꾸준히 갱신하는게 더 빠른 연산
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>({}));
        for (auto a : flights)
        {
            graph[a[0]].push_back({ a[1],a[2] });// 현재 정점에 인접정점 및 해당 정점과의 가격(가중치)
            // vector[ 현재 정점] = {{인접 정점1, 가중치1}, {인접 정점2, 가중치2}}
        }
        
        vector<int> distance(n, INT_MAX);// 각 정점별 거리
        distance[src] = 0;
        // queue
        // [도약횟수][현재 정점, 현재까지의 가격 총합]
        queue<pair<int, pair<int, int>>> bfsqueue;
        bfsqueue.push({ 0,{src,0} });
        
        while (!bfsqueue.empty())
        {
            auto currentnode = bfsqueue.front();
            bfsqueue.pop();
            int count = currentnode.first;
            int cnode = currentnode.second.first;
            int price = currentnode.second.second;

            if (count > k) continue; // 스탑 횟수를 넘긴 순회에 대해서는 스킵
            if (cnode == dst) continue; // 도착 지점을 지난 연산을쓸모가 없음( 전부 양의 가중치 뿐이기때문에)
            for (auto nextnode: graph[cnode]) // 해당 그래프의 노드의 인접 정점에 대해서
            {
                if (distance[nextnode.first] > price + nextnode.second)// 지금까지의 다음 정점까지의 가격이 현재 정점까지의 가격(price) + 다음 정점까지의 가격(a.second)보다 짧은 경우 재기록
                {
                    distance[nextnode.first] = nextnode.second + price;
                    bfsqueue.push({ count +1,{nextnode.first, distance[nextnode.first]}});
                }
            }
            
            
        }
        if (distance[dst] != INT_MAX) return distance[dst];
        return -1;
    }
    
}; 
int main()
{
    Solution s1;
    vector<vector<int>> prob = { {0, 1, 100},{1, 2, 100},{2, 0, 100}, {1, 3, 600}, { 2, 3, 200 } };
    int answer = s1.findCheapestPrice(4, prob, 0, 3, 1);
    cout << answer << endl;
}
//시간 초과 코드
/* 시간 초과 코드

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
using namespace std;
// cache[node][k] =

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<int>> graph(n, vector<int>(n,INT_MAX));
        for (auto a : flights)
        {
            graph[a[0]][a[1]] = a[2];

        }


        int answer;
        queue<pair<int,int>> bfsq;
        vector<vector<int>> visited(n, vector<int>(n,INT_MAX)); // [node][k] = totalprice; [nextnode][k+1]=totalprice + currentprice;

        for (int i = 0; i<graph[src].size();++i)
        {
            // src 지점의 인접 노드 거리 visted[][] 값 삽입후 정리
            if (graph[src][i] != INT_MAX)
            {
                visited[i][0] = graph[src][i];
                bfsq.push({ i,0 });
            }

        }

        while (!bfsq.empty())
        {
            auto currentnode = bfsq.front();//{방문 정점, 방문 횟수}
            bfsq.pop();
            // 현재 노드의 정점 기준 인접 정점 큐에 넣기
            // 종료처리 : 목적지 도달, 또는 환승이 K번에 도달했을경우
            if (currentnode.first == dst)
            {
                continue;
            }
            if (currentnode.second == k)
            {
                continue;
            }
            if (currentnode.second>k) continue; // 같은 도약으로 이미 도착지에 도달한 것이 있고 그 값보다 클경우 스킵
            // 방문처리 필요
            for (int i =0;i<n;++i)
            {
                if (graph[currentnode.first][i] != INT_MAX)
                {   // 연결된 노드 중에
                    // 기존 인접 정점*도약횟수가 이번것 보다 작다면
                    if (visited[i][currentnode.second + 1] > visited[currentnode.first][currentnode.second] + graph[currentnode.first][i])
                    {
                        visited[i][currentnode.second + 1] = visited[currentnode.first][currentnode.second] + graph[currentnode.first][i];
                    }
                    // 기존 인접 정점+도약+1(다음 넘어갈경우)가 현재까지의 정점*도약횟수 + 인접정점까지의 거리보다 클경우 재 갱신
                    // queue에 재삽입
                    bfsq.push({i,currentnode.second+1});// 인접 노드와 지금까지의 도약 +1
                }
            }

        }
        answer = *min_element(visited[dst].begin(), visited[dst].begin() + k+1);
        if (answer == INT_MAX) return -1;
        return answer;
    }

};
*/