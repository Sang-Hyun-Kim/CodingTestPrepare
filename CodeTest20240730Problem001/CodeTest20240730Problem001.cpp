// 
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
int cand = 0;
int pick = 0;
int tot = 0;
int maxi = -1;
void BackT(int num, int left, set<int> curcan, vector<vector<int>>& candis);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> cand >> pick >> tot;

    vector<vector<int>> candis(tot, vector<int>(2, 0));
    for (int i = 0; i < cand; ++i)
    {
        cin >> candis[i][0] >> candis[i][1];
    }
    set<int> curcan;
    BackT(0, pick, curcan, candis);

    cout << maxi << endl;
}

void BackT(int num, int left, set<int> curcan, vector<vector<int>>& candis)
{
    if (num >= cand)
    {// 마지막 후보까지 끝
        return;
    }

    // 이번 후보 넣기
    curcan.insert(num);
    left -= 1;
    if (left == 0)
    {// k개의 후보를 다 골랐다면
        // 계산
        int pow = 0;
        int speed = 0;
        for (auto& a : curcan)
        {
            pow += candis[a][0];
            speed += candis[a][1];

        }
        int sum = pow * speed;
        maxi = max(maxi, sum);
    }
    else
    {
        BackT(num + 1, left, curcan, candis);
    }
    // 이전 계산 롤백
    curcan.erase(curcan.find(num));
    left += 1;
    // 이번 후보 거르기 => 다음 후보 탐색 시작
    BackT(num + 1, left, curcan, candis);

}