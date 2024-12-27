#include <string>
#include <vector>
#include <array>
#include <iostream>
// 프로그래머스 공원산책
using namespace std;
array<int, 4> dx = { -1,1,0,0 };
array<int, 4> dy = { 0,0,-1,1 };
int R, C;
bool InRange(int x, int y)
{
    if (0 <= x && 0 <= y && x < R && y < C)
    {
        return true;
    }
    return false;
}

vector<int> solution(vector<string> park, vector<string> routes) {
    vector<int> answer;

    R = park.size();
    C = park[0].size();
    pair<int, int> srt;
    for (int i = 0; i < R; ++i)
    {
        for (int j = 0; j < C; ++j)
        {
            if (park[i][j] == 'S')
            {
                srt = { i,j };
            }
        }
    }
    int cx = srt.first;
    int cy = srt.second;
    for (auto r : routes)
    {

        auto way = r[0];
        auto valc = r[2]-48;//'0'
        int wi = 0;
        if (way == 'N')
        {
            wi = 0;
        }
        else if (way == 'S')
        {
            wi = 1;
        }
        else if (way == 'W')
        {
            wi = 2;
        }
        else
        {
            wi = 3;
        }
        bool flag = true;
        int nx = cx;
        int ny = cy;
        for (int i = 0; i < valc; ++i)
        {
            nx+= dx[wi];
            ny+= dy[wi];
            if (!InRange(nx, ny))
            {
                flag = false;
            }
            else
            {
                if (park[nx][ny] == 'X')
                {
                    flag = false;
                }
            }
        }
        if (flag)
        {
            cx = nx;
            cy = ny;
        }
    }
    answer.push_back(cx);
    answer.push_back(cy);
    return answer;
}

int main()
{
    vector<int> a = solution({"OSO", "OOO", "OXO","000"
        }, { "E 2", "S 3", "W 1" });
    int f = 3;
}