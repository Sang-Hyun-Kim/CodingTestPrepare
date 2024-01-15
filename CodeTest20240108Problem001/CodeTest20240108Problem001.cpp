// 프로그래머스 2024 KAKAO WINTER INTERNSHIP 도넛과 막대 그래프
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
// 각 노드별 특정 파악
// 생성 정점: 들어오는 간선이 없고 나가는 간선만 2개
// 8자 노드: 중간 노드에 인풋 간선 2개, 아웃 풋 간선 2개
// 막대 노드: 시작정점으로 되돌아 오지않고 마지막 노드가 나가는 노드없이 끝남
// 도넛 노드: 한번 체크한 시작정점 노드로 되돌아오며 해당 되돌아온 노드까지 나가는 간선이 반드시 하나임
int Search(int nodenum);
vector<int> counts(1000001, 0);
unordered_map<int, vector<int>> nodes;
vector<int> solution(vector<vector<int>> edges) {
    vector<int> answer(4,0);//0: 임의 정점 번호,1: 도넛,2:막대,3:8자;
    // 
    unordered_map<int, vector<int>>::iterator iter;
    for (auto v : edges) // v[0] : edge의 시작, v[1] : edge의 끝, 노드 입력하기 // 노드 1 : 2 3  2 : 4  3 : 5
    {
        iter = nodes.find(v[0]);
        if (iter == nodes.end()) nodes.emplace(make_pair( v[0],vector<int>() )); //
        nodes[v[0]].push_back(v[1]);
        counts[v[1]]++;
    
    }
    // 순회
    for (iter = nodes.begin(); iter != nodes.end(); iter++)
    {
        if (iter->second.size() >= 2 && counts[iter->first] == 0) answer[0] = iter->first; // 생성 정점 찾기
    }
    for (auto curnode : nodes[answer[0]])
    {
        auto shape = Search(curnode);
        answer[shape]++; // 각 그래프 모양별 찾기
    }

    return answer;
}

int Search(int nodenum)
{
    int nextNum = nodenum;
    while (!nodes[nextNum].empty())
    {
        if (nodes[nextNum].size() >= 2) return 3; // 나가는 간선이 2개 이상일 경우 8자
            
        if (nodes[nextNum][0] == nodenum) return 1; // 다시 찾은 정점 => 도넛
        else nextNum = nodes[nextNum][0]; // 다음 순회 진행
    }
    // 반복되지 않고 도는 경우 막대그래프
    return 2;
}

int main()
{
    vector<vector<int>> a={ {2,3},{4,3},{1,1},{2,1} };
    vector<vector<int>> c = { {4, 11},{1, 12},{8, 3},{12, 7},{4, 2},{7, 11},{4, 8},{9, 6},{10, 11},{6, 10},{3, 5},{11, 1},{5, 3},{11, 9},{3, 8} };
    auto b = solution(c);
    b;
}