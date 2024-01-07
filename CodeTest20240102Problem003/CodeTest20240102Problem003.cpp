// 백준 11657 타임머신
// 음수 가중치가 있는 그래프 순회
// 벨만 포드 알고리즘 을 통한 음수 가중치 간선이 있는 그래프에서 음수 가중치 사이클 판별 및 각 정점별 최단 거리 출력
// 자료형 주의
// 처음 생각  Edges * Weight => 10000*60000 => 6억
// ㄴㄴ 벨만 포드 알고리즘 => 정점 -1개 만큼 반복
// 6억*500(Nodes) => Int의 -21억~21억 초과 따라서 long long 자료형 사용
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

struct Edge
{
    int src;
    int dst;
    int weight;
};

void BF(vector<Edge>& _Edges, int _nodenum, int start);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int nodenum;
    int edgenum;
    cin >> nodenum >> edgenum;
    vector<Edge> Edges(edgenum);
    for (int i = 0; i < edgenum; ++i)
    {
        cin >> Edges[i].src >> Edges[i].dst >> Edges[i].weight;
    }
    BF(Edges, nodenum, 1);

}

void BF(vector<Edge>& _Edges, int _nodenum, int start)
{
    vector<long long> discovered(_nodenum+1, LLONG_MAX);
    discovered[start] = 0;

    for (int i = 0; i < _nodenum - 1; ++i)
    {
        for (auto& e : _Edges)
        {
            if (discovered[e.src] == LLONG_MAX) continue; // 발견된 정점에 대해서만 실행, 노드개수-1개 만큼 실행하게 되니 나중에 계산됨
            // 인접 정점과의 거리가 새로운 경로에 의한 거리값 보다 크면 거리값 업데이트
            if (discovered[e.dst] > discovered[e.src] + e.weight)
            {
                discovered[e.dst] = discovered[e.src] + e.weight;
            }
        }
    }

    // 음수 가중치 사이클 발견
    // 해당 작업을 모든 정점에 대해서 처리했으나 
    // 위의 작업을 한번 반복하면서 discovered가 줄어드는 현상이 발견 되면 음수 사이클이 존재함

    for (int i = 0; i < _nodenum - 1; ++i)
    {
        for (auto& e : _Edges)
        {
            if (discovered[e.src] == LLONG_MAX) continue;
            // 인접 정점과의 거리가 새로운 경로에 의한 거리값 보다 크면 거리값 업데이트
            if (discovered[e.dst] > discovered[e.src] + e.weight)
            {
               // 음수 가중치 사이클이 있음 => 계산을 반복할 수 록 값이 계속해서 작아짐
                cout << -1;
                return;
            }
        }
    }

    for (int i =2 ;i<_nodenum+1;++i)
    {
        if (discovered[i] == LLONG_MAX)
        {
            cout << -1 << '\n';
            continue;
        }
        cout << discovered[i]<< '\n';
    }
}

