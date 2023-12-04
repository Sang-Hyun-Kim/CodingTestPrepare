// Greedy_Kruskal_MST(최소신장트리)
// 코드 출처: 코딩테스트를 위한 자료구조 알고리즘 with C++
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

// 최소 신장 트리를 찾기 위해 Disjoint-Set 자료구조를 도입하면 많은 양의 데이터에서 더 좋은 성능을 추구할 수 있다.
// Disjoint-Set 자료구조에서는 union(x,y)라는 함수를 사용할 것인데 해당 함수는 두개의 노드 x,y 중 Rank가 높은 노드 밑에 다른 노드를 배치시켜 합치는 함수이나 서로 이미 root가 같을 경우 합치지 않는 함수이다.
// 해당 함수로 최소 신장 트리를 만드는 코드에서 최소 가중치 엣지의 양 끝단 정점을 계속해서 union() 해서 추가하는 과정중 root가 같은 두 노드에 대해서는 Cycle이 발생할 수 있으므로 수행 하지 않는 특성을 이용한 것이다.

// Disjoint-Set 자료구조 구현을 위한 SimpleDisjointSet 구현
class SImpleDIsjointSet
{
private:
    struct Node
    {
        unsigned id;
        unsigned rank;
        unsigned parent;
        // 생성자
       
        Node(unsigned _id) : id(_id), rank(0), parent(_id) {}

        
        bool operator != (const Node& n) const
        {
            return this->id != n.id;
        }
    };
    // 디스조인트-셋 포레스트
    // 각각의 노드는 하나의 Tree를 형성하며, 자식 노드의 개수 만큼 rank 값이 결정됨
    vector<Node> nodes;
public:
    SImpleDIsjointSet(unsigned N)
    {
        nodes.reserve(N);
    } // 디스조인트-셋 자료구조 생성시 N개의 랭크가 0이고 부모는 자기 자신을 참조하는 노드 1개짜리 트리 생성

    void make_set(const unsigned& x)
    {
        nodes.emplace_back(x);
    }// 새로운 트리 추가

    unsigned find(unsigned x)
    {
        auto node_it = find_if(nodes.begin(), nodes.end(),
            [x](auto n) { return n.id == x; });
        unsigned node_id = (*node_it).id;

        while (node_id != nodes[node_id].parent)
        {
            node_id = nodes[node_id].parent;
        } // 루트노드는 parent 가 자기 자신을 가르키고 있다.

        return node_id;
    }// 원소 x에서 시작해서 부모 포인터를 따라 반복적으로 이동하여 트리의 루트를 반환

    void union_sets(unsigned x, unsigned y)
    {
        auto root_x = find(x);
        auto root_y = find(y);
        // find 연산을 통해 가져온 두 원소의 Root를 비교한다.
        if (root_x == root_y)
            return;

        // 작은 랭크의 트리를 큰 랭크의 트리 쪽으로 병합
        if (nodes[root_x].rank > nodes[root_y].rank)
            swap(root_x, root_y);

        nodes[root_x].parent = nodes[root_y].parent;
        nodes[root_y].rank++;

    }
};

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

// 여기서 구현한 Graph 구조체는 처음 정점 개수를 설정하면 이후 변경할 수 없습니다. 또한 에지 추가는 구현되어 있지만, 에지 삭제는 연습 문제에서 사용하지 않으므로 구현하지 않았습니다.


// 크루스칼 최소 신장 트리 구현
// 트리도 그래프로 표현할 수 있으므로 최소 신장 트리도 Graph 객체로 반환합니다.
// 다만 여기에는 사이클이 있으면 안 됩니다.
template <typename T>
Graph<T> minimum_spanning_tree(const Graph<T>& G)
{
    // 에지 가중치를 이용한 최소 힙 구성
    priority_queue<Edge<T>, vector<Edge<T>>, greater<Edge<T>>> edge_min_heap;

    // 모든 에지를 최소 힙에 추가
    for (auto& e : G.edges())
        edge_min_heap.push(e);

    // 정점 개수에 해당하는 크기의 디스조인트-셋 자료 구조 생성 및 초기화
    auto N = G.vertices();
    SImpleDIsjointSet dset(N);
    for (unsigned i = 0; i < N; i++)
        dset.make_set(i);

    // 디스조인트-셋 자료 구조를 이용하여 최소 신장 트리 구하기
    Graph<T> MST(N);
    while (!edge_min_heap.empty())
    {
        // 최소 힙에서 최소 가중치 에지를 추출
        auto e = edge_min_heap.top();
        edge_min_heap.pop();
        
        // 선택한 에지가 사이클을 생성하지 않으면 해당 에지를 MST에 추가
        if (dset.find(e.src) != dset.find(e.dst))
        {
            MST.add_edge(Edge <T>{e.src, e.dst, e.weight});
            dset.union_sets(e.src, e.dst);
        }
    }

    return MST;
}

int main()
{
    using T = unsigned;

    // 그래프 객체 생성
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

    cout << "[입력 그래프]" << endl;
    cout << G << endl;

    Graph<T> MST = minimum_spanning_tree(G);
    cout << "[최소 신장 트리]" << endl;
    cout << MST;
}

/*

디스조인트-셋 자료 구조를 사용하지 않는 크루스칼 알고리즘의 시간 복잡도는 O(E log E)입니다. 여기서 E는 그래프에서 에지 개수를 의미합니다. 
그러나 디스조인트-셋 자료 구조를 사용하면 전체 복잡도가 O(Eα(V))로 줄어들며, 
여기서 α(v)는 아커만 함수(Ackermann function)의 역함수입니다. 아커만 함수의 역함수는 로그 함수보다 훨씬 느리게 증가합니다. 
그러므로 정점 개수가 작은 그래프에서는 두 구현의 성능 차이가 작지만, 정점이 많은 그래프에서는 큰 성능 차이가 발생할 수 있습니다.

*/