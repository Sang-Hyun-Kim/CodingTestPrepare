// 백준 구간 합 구하기 5
// 누적합 사용
// (X,Y)를 0,0~X,Y 좌표까지의 값의 총합이라고 했을때
// (X,Y) = (X - 1,Y) + (X,Y-1) - (X-1,Y-1)이라는 공식이 나옴 (누적합 - 겹치는 값 빼기)
// 좌표 [a][b] ~ [x][y]의 합은
// (x,y) - (a-1,y) - (x,b-1) + (a-1,b-1)
#include <iostream>
#include <vector>
// 그냥 (N+1) * (N+1) 배열로 선언해놓고 했으면 index range 오류 관련으로 이렇게 신경쓸 필요가 없었음..
// 전부 0으로 초기화하면 덧셈할때 큰 문제가 없으니까...
using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int num, calnum;
    cin >> num;
    cin >> calnum;
    vector<vector<int>> board(num,vector<int>(num, -1));
    vector<vector<int>> sum(num, vector<int>(num, -1));
    for (int i = 0; i < num; ++i)
    {
        for (int j = 0; j < num; ++j)
        {
            int value;
            cin >> value;

            board[i][j] = value;
            if (i == 0 && j == 0) sum[i][j] = value;
            else if (i == 0) sum[i][j] = sum[i][j - 1] + value;
            else if (j == 0) sum[i][j] = sum[i - 1][j] + value;
        }
        
    }

    for (int i = 1; i < num; ++i)
    {
        for (int j = 1; j < num; ++j)
        {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + board[i][j];
        }
    }
    
    for (int i = 0; i < calnum; ++i)
    {
        int a, b, x, y;
        int result;
        cin >> a >> b >> x >> y;
        if(a == 1 && b == 1) result = sum[x - 1][y - 1];
        else if(a == 1)
        {
            result = sum[x - 1][y - 1] - sum[x - 1][b - 2];
        }
        else if(b == 1)
        {
            result = sum[x - 1][y - 1] - sum[a - 2][y - 1];
        }
        else
        {
            result = sum[x - 1][y - 1] - sum[a - 2][y - 1] - sum[x - 1][b - 2] + sum[a - 2][b - 2];
        }
        cout << result << '\n';
    }
}
