// 백준 3190번 뱀
//

// 뱀 : 처음에는 몸길이 1(머리 끝) 오른쪽을 바라봄

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <algorithm>

using namespace std;
//array<int, 4> dx{ -1, 1, 0,0 }; // 상 하 좌 우
//array<int, 4> dy{ 0, 0, -1,1 }; // 0 1 2 3 
vector<pair<int, int>> direction{ {0,1},{1,0},{0,-1} ,{-1,0} };
// 우(0) 하(1) 좌(2) 상(3)

// 빈공간 -1
// 사과가 있으면 1
// 뱀이 있으면 0 
// 뱀의 몸통이 있는 좌표
// 뱀의 좌표를 넣을 deque
// 
int main()
{
	int boardSize;
	cin >> boardSize;

	vector<vector<int>> board(boardSize,vector<int>(boardSize,-1));
	int applenum;
	cin >> applenum;
	list<pair<int, int>> apples;
	for (int i = 0; i < applenum; i++)
	{
		int x, y;
		cin >> x;
		cin >> y;
	//	board[x][y] = 1;
		apples.push_back({ x-1,y-1 });
	}
	// 초,방향 은 큐에 보관
	queue<pair<int, char>> dq;
	int dnum;
	cin >> dnum;
	for (int i = 0; i < dnum; ++i)
	{
		int sec;
		char dir;
		cin >> sec;
		cin >> dir;
		dq.push({sec,dir});
		
	}

	int time = 0;
	deque<pair<int, int>> snake;
	snake.push_back({ 0,0 });
	int currentdir = 0;
	// 시간을 1초올리고
	// 머리 전진
	// 전진한 곳이
	// 벽이면 X, 몸통이 있는 곳이면 X
	// 사과면 몸길이 1 증가(deque)
	// 없으면 몸통 이동 처리
	// 현재 시간에
	// 시간에 맞는 방향이 있는지 체크하고
	// 방향 전환이 있다면 방향전환 // 우(0) 하(1) 좌(2) 상(3)
	// D 우회전 +1 , L 좌회전 -1, current<0 => 3 | current>3 => 0
	while (true)
	{
		time++;
		
		// 뱀의 머리 위치는 deque의 제일 앞 좌표
		auto head = snake.front();
		// 머리위치에서 방향 더하기=>다음위치
		int x = head.first + direction[currentdir].first;
		int y = head.second + direction[currentdir].second;
		pair<int, int> pair = { x, y };
		if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) // 다음 머리가 벽에 부딪힌 경우 끝냄
			break;
		if (find(snake.begin(), snake.end(), pair) != snake.end())
			break; // 뱀 몸통에 닿았느냐
		// 머리가 도착하는 곳에 사과가 있냐
		auto it = find(apples.begin(), apples.end(), pair);
		
		if (it != apples.end())
		{// 사과 있음
			snake.push_front(pair);
			apples.erase(it); // 사과 제거
		}
		else
		{	// 사과 없음
			snake.push_front(pair);
			snake.pop_back();
		}
		// 머리를 snake deque에 넣고 꼬리 연산 처리
		if (!dq.empty())
		{
			if (time == dq.front().first)
			{
				//TODO
				auto now = dq.front();
				dq.pop();
				if (now.second == 'D')
				{
					currentdir++;
					if (currentdir > 3) currentdir = 0;
				}
				else
				{
					currentdir--;
					if (currentdir < 0) currentdir = 3;
				}
			}
		}
		
	}

	// 정답출력
	cout << time << "\n";
}

