// 프로그래머스 연습문제 광물 캐기
// DP +DFS 또는 백트래킹 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int CalFat(string min, int picknum);
void Caching(int chunknum, int picknum, vector<int> picks, vector<vector<int>>& cache, vector<vector<int>>& chunk, vector<string>& minerals);
void BackTrack(vector<vector<int>>& cache, vector<int> picks, int chunknum, int curval);
int Min = 10000;
int solution(vector<int> picks, vector<string> minerals) {
    int answer = 0;
    int v = minerals.size() / 5;
    int m = minerals.size() % 5 != 0 ? 1 : 0;
    vector<vector<int>> chunk(v + m);
    int fc = 0;
    int ci = 0;
    for (int i = 0; i < minerals.size(); ++i)
    {
        fc++;
        chunk[ci].push_back(i);
        if (fc >= 5)
        {
            ci++;
            fc = 0;
        }
    }
    vector<vector<int>> cache(v + m, vector<int>(3, 10000));
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < v + m; ++j)
        {
            Caching(j, i, picks, cache, chunk, minerals);
        }
    }
    BackTrack(cache, picks, 0, 0);
    return Min;
}
void Caching(int chunknum, int picknum, vector<int> picks, vector<vector<int>>& cache, vector<vector<int>>& chunk, vector<string>& minerals)
{

    int curfat = 0;
    for (int i = 0; i < chunk[chunknum].size(); ++i)
    {
        auto curmin = minerals[chunk[chunknum][i]];
        curfat += CalFat(curmin, picknum);
    }

    cache[chunknum][picknum] = curfat;

}

int CalFat(string min, int picknum)
{
    if (picknum == 0)
    {
        return 1;
    }
    else if (picknum == 1)
    {
        if (min == "diamond")
        {
            return 5;
        }
        else
        {
            return 1;
        }
    }
    else// 돌 곡
    {
        if (min == "diamond")
        {
            return 25;
        }
        else if (min == "iron")
        {
            return 5;
        }
        else
        {
            return 1;
        }
    }
}
void BackTrack(vector<vector<int>>& cache, vector<int> picks, int chunknum, int curval)
{
    if (curval > Min)
    {
        return;
    }
    if (chunknum >= cache.size())
    {// 마지막도달=> 성공 최소값 갱신
        Min = min(Min,curval);
        return;
    }
    if (picks[0] + picks[1] + picks[2] == 0)
    {
        Min = min(Min, curval); return;
    }
    for (int i = 0; i < 3; ++i)
    {
        int newval = curval;
        if (picks[i] > 0) // 인자로 받은 남은 곡갱이중 해당 곡갱이가 있을 경우
        {
            picks[i]--;
            newval += cache[chunknum][i];
            BackTrack(cache, picks, chunknum + 1, newval);
            picks[i]++;
        }
    }
    // 도달전에 곡갱이를 전부 사용;
    return;
}

int main()
{
    int answer = solution({ 1,1,1 }, {"iron","iron" ,"iron" ,"iron" ,"iron" ,"diamond","diamond","diamond","diamond","diamond"});
    cout << answer;
}
