// 프로그래머스 아이템 줍기
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <queue>
using namespace std;

struct Pos {
    int x;
    int y;
    Pos(int a, int b) : x(a), y(b) {};
};
int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    
for (vector<int>& v : rectangle)
        for (int& pos : v)
            pos *= 2;

    characterX *= 2;
    characterY *= 2;
    itemX *= 2;
    itemY *= 2;

    vector<vector<int>> board(102, vector<int>(102, 0));

    for (auto r : rectangle)
    {
        for (int x = r[0]; x <= r[2]; x++)
            for (int y = r[1]; y <= r[3]; y++)
                board[x][y] = 1;
    }

    for (auto r : rectangle)
        for (int x = r[0] + 1; x < r[2]; x++)
            for (int y = r[1] + 1; y < r[3]; y++)
                board[x][y] = 0;

    queue<pair<Pos, int>> q;   //coord, depth
    q.push(make_pair(Pos(characterX, characterY), 0));
    int temp[2] = { -1,1 };

    while (!q.empty())
    {
        Pos cur(q.front().first.x, q.front().first.y);
        int depth = q.front().second;
        q.pop();

        for (int i = 0; i < 2; i++)
        {
            if (board[cur.x + temp[i]][cur.y] == 1)
            {   
                if (cur.x + temp[i] == itemX && cur.y == itemY)  return (depth + 1) / 2;
                else
                {
                    board[cur.x][cur.y] = 0;
                    q.push(make_pair(Pos(cur.x + temp[i], cur.y), depth + 1));
                }
            }
            if (board[cur.x][cur.y + temp[i]] == 1)
            {   
                if (cur.x == itemX && cur.y + temp[i] == itemY) return (depth + 1) / 2;
                else
                {
                    board[cur.x][cur.y] = 0;
                    q.push(make_pair(Pos(cur.x, cur.y + temp[i]), depth + 1));
                }
            }
        }
    }
}

int main()
{
    int answer = solution({ {1,1,7,4},{3,2,5,5},{4,3,6,9},{2,6,8,8} }, 1, 3, 7, 8);
    cout << answer;
}

