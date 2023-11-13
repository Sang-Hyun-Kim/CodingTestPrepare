
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;
void BFS(int number, vector<int>& best, vector<bool>& visited, queue<int> q, int& dest);
int main()
{
    int start = 0;
    int dest = 0;
    cin >> start;
    cin >> dest;

    queue<int> q;
    vector<int> best;
    vector<bool> visited(100001, false);

    BFS(start, best, visited, q, dest);
}

void BFS(int number, vector<int>& best, vector<bool>& visited, queue<int> q, int& dest)
{
    int _number;
    q.push(number);
    visited[number] = true; // 시작은 발견
    // vector<int> distance;
    vector<int> parent(100001,INT_MAX); // 0~10만의 부모 전부 최대
    parent[number] = number; // 시작점의 이전 X

    if (number == dest) // 시작하자 마자 같다면
    {
        cout << 0 << endl;
        cout << dest;
        return;
    }

    while (!q.empty())
    {
        _number = q.front();
        q.pop();
        if (_number < 0 || _number > 100000) continue;
        
        if (_number == dest)// 답이라면
        {
            // TODO
            break;
        }
        // 답이 아니라면 연산 진행
        // 2배, -1 , +1

        // 각각의 연산은 BFS 큐에 넣기
        // 이미 발견한것이 아니라면 무시
        if (_number * 2 <= 100000)
        {
            if (visited[_number * 2] != true && _number * 2 <= 100000)
            {
                q.push(_number * 2);
                visited[_number * 2] = true;
                if (parent[_number * 2] > _number)
                {
                    parent[_number * 2] = _number;
                }

            }
        }
        
        if (visited[_number + 1] != true )
        {
            q.push(_number + 1);
            visited[_number + 1] = true;
            if (parent[_number + 1] > _number)
            {
                parent[_number + 1] = _number;
            }

        }

        if (_number - 1 >= 0)
        {
            if (visited[_number - 1] != true && _number >= 0)
            {
                q.push(_number - 1);
                visited[_number - 1] = true;
                if (parent[_number - 1] > _number)
                {
                    parent[_number - 1] = _number;
                }

            }
        }
        
    }

    // 루프끝
    
    int index = dest;
    // 부모 거슬러 올라가기
    best.push_back(index);
    while (number != parent[index])
    {
        index = parent[index];
        best.push_back(index);
    }
    cout << best.size() << endl;
    best.push_back(number); // 출발지
    //출력1 count
    

    //출력2 거슬러 올라간 기록 반대로 출력
    for (auto it = best.rbegin(); it != best.rend(); it++)
    {
        cout << *it << " ";
    }

}

// 출발==도착 제거
// 연산 3개 x-1 x+1 2x
// 3개에 대해서 다시 찾기 수행
// 만약 연산이 Dest 보다 너무 크다 제거
// 찾으면 최소값에 기록
// 찾는 과정을 bestcast에 기록
// 모든 연산후 최소값 반환 및 해당 최소 연산을 출력

