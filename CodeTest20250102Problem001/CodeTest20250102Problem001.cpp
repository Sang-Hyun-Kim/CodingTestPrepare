#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
int maxdiff = 100000000;
// 실수목록
// BFS 함수 매개변수를 사용해서 BFS 순회를 돌려버리는 대참사 => queue의 값으로 탐색하기
// 노드별 방문을 간선 별 방문을 해버려서 혼자 있는 node를 탐색하지 못하는 대참사
// => visted 1차원배열로 수정 및 탐색 수정하기
void BFS(vector<vector<int>>& _graph, vector<bool>& _visited, int _y, vector<int>& _sz)
{
    int sum = 0;
    queue<int> bq;
    bq.push(_y);
    sum++;
    while (!bq.empty())
    {
        auto curnode = bq.front();
        bq.pop();
        for (int i = 1; i < _graph[curnode].size(); ++i)
        {
            if (_graph[curnode][i] == 1 && !_visited[i])
            {
                bq.push(i);
                _visited[i] = true;
                sum++;
            }
        }
    }
    _sz.push_back(sum);
}
int solution(int n, vector<vector<int>> wires) {
    int answer = -1;
    // wires[i] 가 없는 경우의 그래프 생성후 탐색
    // 그렇게 나온 두 그룹의 차이 값 저장
    // 최소값차이를 비교 후 저장
    // 반환
    int wsize = wires.size(); // 

    for (int i = 0; i < wsize; ++i)
    {//뺄 연결점 선택 반복문

        vector<vector<int>> curgraph(n + 1, vector<int>(n + 1, 0)); // 0 ~n 1~n만 사용
        vector<bool> curvisited(n + 1, false);
        // 그래프 생성하기
        for (int j = 0; j < wsize; ++j)
        {
            if (i == j)
                continue;
            auto a = wires[j][0]; //srt
            auto b = wires[j][1]; // dst
            curgraph[a][b] = 1;
            curgraph[b][a] = 1;// connected

        }
        // 완성된 그래프 탐색
        // 연결이 안되어있거나 방문되어있으면 ㄴㄴㄴ
        vector<int> groupsize;
        // 모든 노드에 대해서 탐색호출
        for (int k = 1; k <= n; ++k)
        {
            if (!curvisited[k])
            {
                curvisited[k] = true;
                BFS(curgraph, curvisited, k, groupsize);
            }
        }
        


        int curdiff = (int)(abs(double(groupsize[1] - groupsize[0])));
        maxdiff = min(maxdiff, curdiff);
    }


    return maxdiff;
}
int main()
{
    int answer = solution(9, { {1,3},{2,3},{3,4},{4,5},{4,6},{4,7},{7,8},{7,9} });
    cout << answer << endl;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
