#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
// 백준 16928번 뱀과 사다리 게임
using namespace std;
int main()
{
	int ladder, snake;
	cin >> ladder;
	cin >> snake;
	int startpoint = 0;
	int destination = 0;


	vector<bool> visited(101, false);
	vector<int> LS(101, -1);
	queue<int> bfsqueue;
	vector<int> distance(101, -1);
	// 사디라
	for (int i = 0; i < ladder; ++i)
	{
		cin >> startpoint;
		cin >> destination;
		LS[startpoint] = destination;
	}
	// 뱀 입력
	for (int i = 0; i < snake; ++i)
	{
		cin >> startpoint;
		cin >> destination;
		LS[startpoint] = destination;
	}

	// BFS 준비
	bfsqueue.push(1);
	visited[1] = true;
	distance[1] = 0;
	// 1부터 시작된 1+1~6 위치 에대해 BFS 진행
	while (!bfsqueue.empty())
	{
		int currentboard = bfsqueue.front();
		bfsqueue.pop();
		
		if (currentboard == 100)
		{
			cout << distance[currentboard] << endl;
			break;
		}

		// 주사위수 1~6에대해
		for (int i = 1; i < 7; ++i)
		{
			int dice = currentboard + i;
			// 100 넘기면 X, 1보다 낮으면 X
			if (dice > 100)
			{
				continue; 
			}

			// 현재위치 + 주사위 눈금 자리에 사다리, 뱀 유무 체크
			if (LS[dice] != -1)
			{
				// 사다리/ 뱀 있으면 BFSQueue에 순간이동
				dice = LS[dice];
				
			}
			
			if (visited[dice] == true)
				continue;

			bfsqueue.push(dice); // 도착 지점 넣기
			visited[dice] = true; // 사다리/뱀 방문 체크
			distance[dice] = distance[currentboard] + 1;
		}
	}
}
