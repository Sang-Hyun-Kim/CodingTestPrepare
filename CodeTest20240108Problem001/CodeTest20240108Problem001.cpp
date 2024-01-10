#include <string>
#include <vector>
#include <stack>
using namespace std;
// 출력: 생성한 정점의 번호, 생성 전 도넛모양 그래프의 수, 막대 모양 그래프 수, 8자 모양 그래프 수 
void Search(int nodenum, vector<vector<int>>& _graph, vector<int>& _answer, vector<int>& _visited);
vector<int> solution(vector<vector<int>> edges) {
    vector<int> answer(4,0);//0: 임의 정점 번호,1: 도넛,2:막대,3:8자;
    vector<vector<int>> graph(1000001);
    vector<int> visited(1000001, 0);
    for (auto a : edges)
    {
        graph[a[0]].push_back(a[1]);
    }

    //---모든 노드에 대해 Search 함수 실행
    for (int i = 1; i < graph.size(); ++i)
    {   
        if(graph[i].size()!=0) Search(i, graph, answer, visited);
    }
    return answer;
}

void Search(int nodenum, vector<vector<int>>& _graph, vector<int>& _answer,vector<int>& _visited)
{
    // graph[nodenum]의 사이즈가 3이상이다? 그냥 이새끼는 임의정점임ㅋㅋ
    if (_graph[nodenum].size() > 2)
    {
        _answer[0] = nodenum;
        _visited[nodenum] = 1;
        return;
    }
    // 이미 계산된 녀석이면 순회 돌지말자하
    if (_visited[nodenum] != 0) return;
    // 사이즈가 2이다? 판단해야함 모양이 두개뿐인 상황의 임의 정점일 수도 있고 임의의 8자 그래프의 중심 노드일 수도 있음
    if (_graph[nodenum].size() == 2)
    {
        stack<int> stack;
   
        for (auto a : _graph[nodenum])
        {
            stack.push(a);
        }

        while (!stack.empty())
        {
            auto currentnode = stack.top();
            stack.pop();
            if (_visited[currentnode] != 0)
            {
                // 방문 한 노드일 경우 그래프 모양에 따른 분류 필요 // 하나짜리 재방문 도넛인지 막대인지 분류해야함 다만 2 
                if (_graph[currentnode].size() == 2) 
                { //8자 한쪽을 끝냄
                    continue;
                }
                else
                {
                    if (_graph[currentnode].size() == 0)
                    { // 막대 마지막을 발견 + 이미 막대는 기존에 처리했음
                        _answer[0] = nodenum;
                        return;
                    }
                    if (_visited[currentnode] == 2)
                    { // 2차방문이면 도넛임 8자는 어떻게든 가장 먼저 2를찍는 것은 가운데고 가운데는 위의 사이즈로 걸러짐
                         _answer[1]++;
                        _answer[0] = nodenum;
                        return;
                    }
                    _visited[currentnode]++;// 또방문 추가
                    // 아직 모르니까 한번 더 돌림
                    for (auto b : _graph[currentnode])
                    {
                        stack.push(b);
                    }
                }
            }
            else
            { // 방문한적 없음
                if (_graph[currentnode].size() == 2)
                {// 두개짜리 로 시작했는데 두개짜릴 또 만난다=> 무조건 8자 노드 + 시작이 임의의 정점
                    _answer[0] = nodenum;
                    _answer[3]++;
                    _visited[currentnode]++;

                    for (auto b : _graph[currentnode])
                    {
                        stack.push(b);
                    }
                }
                else if (_graph[currentnode].size() == 0)
                {// 막대의 마지막을 만남 + 2개짜리로 시작했는데 마지막에 닿는다? 이건 임의 정점일 수 밖에 없다.
                    _answer[2]++;
                    _answer[0] = nodenum;
                    _visited[currentnode]++;
                    
                    return;
                }
                // 방문한적 없고 사이즈가 1인것들
                for (auto b : _graph[currentnode])
                {
                    stack.push(b);
                }
                _visited[currentnode]++;

            }
        }

    }
    // 사이즈가 1이다? => 순환 하면서 도넛, 막대, 8자 중 하나 결정해야 함
    if (_graph[nodenum].size() == 1)
    {
        stack<int> stack;
        for (auto a : _graph[nodenum])
        {
            stack.push(a);
        }
   
        while (!stack.empty())
        {
            auto currentnode = stack.top();
            stack.pop();
            if (_visited[currentnode] != 0)
            {// 방문 한 노드일 경우 그래프 모양에 따른 분류 필요
                if (_graph[currentnode].size() == 2)
                {//8자의 중간 노드를 재방문 했을 경우, 첫방문 일 때 체크할 꺼니까 무시, 즉 8자의 한쪽 팔 순회를 끝낸 것임
                    continue;
                }
                else
                { // 하나짜리 재방문 
                    if (_graph[currentnode].size() == 0) return; // 막대였음
                    if (_visited[currentnode] == 2) // 억지로 큐에 넣고
                    { // 도넛 이거나 8자거나 
                        _answer[1]++;
                        return;
                    }
                    // 도넛인지 막대인지 알때까지  순회 한바퀴 더 돌기
                    _visited[currentnode]++;
                    for (auto b : _graph[currentnode])
                    {
                        stack.push(b);
                    }
                }
            }
            else
            { // 방문한 곳이 아닐 경우
                if (_graph[currentnode].size() == 0)
                {// 첫방문인데 막대 마지막임=>막대 추가
                    
                    _answer[2]++;
                    _visited[currentnode]++;
                    return;
                }
                else if (_graph[currentnode].size() == 2)
                {// 첫방문인데 8자 중심임 // 순환을 돌다 간선이 두개인 녀석을 발견했다=> 도중에 발견된 간선2개 정점은 반드시 8자임 순환을 돌면서 전부 체크해주고  
                    _answer[3]++;

                }

                // 8자 중심을 방문했던 진행중이던 다음 방문 stack 넣기
                for (auto b : _graph[currentnode])
                {
                    stack.push(b);
                }
                _visited[currentnode]++;
            }
        }
    }
    
    // 순환을 시작하다가 1을 만난다? 이건 막대다 하지만 기존 막대 순환을 찾으면서 +1을 해놨으니 무시하자
    
    // 사이즈가 0이다? => 어느 막대 정점의 마지막 노드임
    if (_graph[nodenum].size() == 0)
    {
        _answer[2] += 1;
        _visited[nodenum]++;
        return;//끝
    }
}

int main()
{
    vector<vector<int>> a={ {2,3},{4,3},{1,1},{2,1} };
    vector<vector<int>> c = { {4, 11},{1, 12},{8, 3},{12, 7},{4, 2},{7, 11},{4, 8},{9, 6},{10, 11},{6, 10},{3, 5},{11, 1},{5, 3},{11, 9},{3, 8} };
    auto b = solution(c);
    b;
}