﻿// 프로그래머스 2022KAKAO TECH INTERNSHIP 등산 코스 정하기
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;
template <typename T>
struct Edge
{
    unsigned src;
    unsigned dst;
    T weight;

    // Edge 객체 비교는 가중치를 이용
    // 해당 비교 연산자 오버로딩은 추후 PriorityQueue의 Predicate로 사용되니 유의
    inline bool operator< (const Edge<T>& e) const
    {
        return this->weight < e.weight;
    }

    inline bool operator> (const Edge<T>& e) const
    {
        return this->weight > e.weight;
    }
};

template <typename T>
class Graph
{
public:
    // N개의 정점으로 구성된 그래프
    Graph(unsigned N) : V(N) {}

    // 그래프의 정점 개수 반환
    auto vertices() const { return V; }

    // 전체 에지 리스트 반환
    auto& edges() const { return edge_list; }

    // 정점 v에서 나가는 모든 에지를 반환
    auto edges(unsigned v) const
    {
        vector<Edge<T>> edges_from_v;
        for (auto& e : edge_list)
        {
            if (e.src == v)
                edges_from_v.emplace_back(e);
        }
        return edges_from_v;
    }

    void add_edge(Edge<T>&& e)
    {
        // 에지 양 끝 정점 ID가 유효한지 검사
        if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
            edge_list.emplace_back(e);
        else
            cerr << "에러: 유효 범위를 벗어난 정점!" << endl;
    }

private:
    unsigned V;     // 정점 개수
    vector<Edge<T>> edge_list;
};
template <typename T>
auto create_reference_graph()
{
    Graph<T> G(9);

    map<unsigned, vector<pair<unsigned, T>>> edge_map;
    edge_map[1] = { {2, 2}, {5, 3} };
    edge_map[2] = { {1, 2}, {5, 5}, {4, 1} };
    edge_map[3] = { {4, 2}, {7, 3} };
    edge_map[4] = { {2, 1}, {3, 2}, {5, 2}, {6, 4}, {8, 5} };
    edge_map[5] = { {1, 3}, {2, 5}, {4, 2}, {8, 3} };
    edge_map[6] = { {4, 4}, {7, 4}, {8, 1} };
    edge_map[7] = { {3, 3}, {6, 4} };
    edge_map[8] = { {4, 5}, {5, 3}, {6, 1} };

    for (auto& i : edge_map)
        for (auto& j : i.second)
            G.add_edge(Edge<T>{ i.first, j.first, j.second });

    return G;
}

template <typename T>
struct Label
{
    unsigned ID;
    T distance;
    // Label 객체 비교는 거리(distance) 값을 이용
    inline bool operator> (const Label<T>& l) const
    {
        return this->distance > l.distance;
    }
};


template <typename T>
auto prim_MST(const Graph<T>& G, unsigned src)
{
    // 최소 힙
    priority_queue<Label<T>, vector<Label<T>>, greater<Label<T>>> heap;

    // 모든 정점에서 거리 값을 최대로 설정
    vector<T> distance(G.vertices(), numeric_limits<T>::max());

    set<unsigned> visited;     // 방문한 정점
    vector<unsigned> MST;      // 최소 신장 트리

    heap.emplace(Label<T>{src, 0});

    while (!heap.empty())
    {
        auto current_vertex = heap.top();
        heap.pop();

        // 현재 정점을 이전에 방문하지 않았다면
        if (visited.find(current_vertex.ID) == visited.end())
        {
            MST.push_back(current_vertex.ID);

            for (auto& e : G.edges(current_vertex.ID))
            {
                auto neighbor = e.dst;
                auto new_distance = e.weight;


                // 인접한 정점의 거리 값이 새로운 경로에 의한 거리 값보다 크면
                // 힙에 추가하고, 거리 값을 업데이트함
                if (new_distance < distance[neighbor])
                {
                    heap.emplace(Label<T>{neighbor, new_distance});
                    distance[neighbor] = new_distance;
                }
            }

            visited.insert(current_vertex.ID);
        }
    }
    // 반환은 정점만 반환하지만 distance에는 최소 거리가 담겨있음
    // 코드 수정을위해 최소 거리로 연결된 노드도 저장한다면 좋음
    return MST;
}
vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer;
    return answer;
}
int main()
{
    using T = unsigned;

    // 그래프 객체 생성
    auto G = create_reference_graph<T>();


    auto MST = prim_MST<T>(G, 1);

}

