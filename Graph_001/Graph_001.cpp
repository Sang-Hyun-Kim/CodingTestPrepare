// Graph_001.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 출처: 코딩테스트를 위한 자료구조 알고리즘 with C++
// 연습 문제: 프림알고리즘 구현 실습 
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <limits>

using namespace std;
// 그래프와 엣지 코드는 Kruskal MST 코드오 ㅏ동일
// 그래프 자료구조 구현을 위한 에지
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
}; //에지 구조체는 템플릿으로 구현했기 때문에 < 연산자와 > 연산자를 지원하는 모든 데이터 타입을 에지 가중치로 사용할 수 있습니다.

// Graph 클래스를 정의합니다. Graph 클래스는 << 연산자를 이용하여 그래프 정보를 출력할 수 있습니다.    
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

    // 표준 출력 스트림 지원
    template <typename U>
    friend ostream& operator<< (ostream& os, const Graph<U>& G);

private:
    unsigned V;     // 정점 개수
    vector<Edge<T>> edge_list;
};

template <typename U>
ostream& operator<< (ostream& os, const Graph<U>& G)
{
    for (unsigned i = 1; i < G.vertices(); i++)
    {
        os << i << ":\t";
        auto edges = G.edges(i);
        for (auto& e : edges)
            os << "{" << e.dst << ": " << e.weight << "}, ";

        os << endl;
    }

    return os;
}
// 프림 알고리즘을 위한 그래프 생성
// 정점하나는 연결된 정점 번호: 해당 정점과의 거리(가중치) 값을 저장함
// 그리고 해당 그래프 정보를 반환함
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

//정점에 경계로부터 거리 정보를 저장하기 위해 사용할 Label 구조체를 정의. Label 객체 비교는 거리 값을 이용하도록 비교 연산자를 오버로딩합니다.
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

int main()
{
    using T = unsigned;

    // 그래프 객체 생성
    auto G = create_reference_graph<T>();
    cout << "[입력 그래프]" << endl;
    cout << G << endl;

    auto MST = prim_MST<T>(G, 1);

    cout << "[최소 신장 트리]" << endl;
    for (auto v : MST)
        cout << v << endl;
    cout << endl;
}

// 시간복잡도
// 이진 최소 힙과 MST저장을 위해 인접 리스트사용=> O(ElogV)

// 크루스칼 알고리즘
// 그래프의 최소 가중치 에지를 차례대로 추가하여 MST를 구성합니다.
// 가장 널리 알려진 시간복잡도는 O(ElogV)입니다.
// 주로 적은 수의 에지로 최소 그래프(sparse graph)에서 사용됩니다.

// 프림 알고리즘
// 그래프의 아무 정점부터 시작하여 MST를 구성합니다.
// 가장 널리 안려진시간 복잡도는 O(E+logV)
// 주로 많은 수의 에지로 구성된 밀집그래프(dense graph)에서 사용 