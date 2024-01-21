// 카카오2024 산모양 타일링

// DP[n의 개수][top[n]]을 저장해서 활용
// n이 1늘어 났을때 top[n]이 0이냐 1이냐에따라 계산법이 달라지며 이전 것인 tops[n-1]의 값이 어떻게되냐에 따라 달라짐
// tops[n] = 0 이고 tops[n-1] = 0 일때 dp[n][0] = dp[n-1][tops[n-1]] + dp[n-1][tops[n-1]]  + 
// tops[n] = 0 이고 tops[n-1] = 1 일때
// tops[n] = 1 이고 tops[n-1] = 0 일때
// tops[n] = 1 이고 tops[n-1] = 1 일때
// 삼각형 관련 dp 하나 더만들기
// !!!!!!! 상향식(타뷸레이션) 으로 풀었다가 시간초과남 => 메모이제이션으로 코드 변경
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int Memoization(int n, int roof, vector<int>& _tops, vector<vector<int>>& _cache, vector<int>& _tris);
int Addtri(int n, vector<int>& _tops, vector<vector<int>>& _cache, vector<int>& _tris);
int MOD = 10007;
int solution(int n, vector<int> tops) {
    int answer = 0;
    vector<vector<int>> cache(n+1, vector<int>(2, 0));
    vector<int> tris(n+1,0); // 특정 칸에 삼각형을 붙였을 때의 값 tris[3] => 3번까지의 모양에 삼각형을 붙였을 때의 경우의 수
    cache[1][0] = 3; // n=1, tops[n] = 0(지붕없음)
    cache[1][1] = 4; // n=1, tops[n] = 1
    if (tops[0] == 0)
    {
        cache[2][1] = cache[1][tops[0]] + cache[1][tops[0]] + cache[1][tops[0]] + 2;
        cache[2][0] = cache[1][tops[0]] + cache[1][tops[0]] + 2;
        tris[1] = 5;
    }
    if (tops[0] == 1)
    {
        cache[2][1] = cache[1][tops[0]] + cache[1][tops[0]] + cache[1][tops[0]] + 3;
        cache[2][0] = cache[1][tops[0]] + cache[1][tops[0]] + 3;
        tris[1] = 7;
    }

    answer = Memoization(n,tops[n-1], tops, cache, tris);
    return answer;
}
int Memoization(int n, int roof, vector<int>& _tops, vector<vector<int>>& _cache, vector<int>& _tris)
{
    if (n == 1 && _tops[0] == 0) return 3;
    if (n == 1 && _tops[0] == 1) return 4;

    if (_cache[n][roof] == 0)
    {
        
        if (_tops[n - 2] == 0)
        {// 이전칸의 지붕 유무에 따라 달라짐
            _cache[n][0] = (Memoization(n - 1, _tops[n - 2], _tops, _cache, _tris) * 2 + Addtri(n - 2, _tops, _cache, _tris)) % MOD;
            _cache[n][1] = (Memoization(n - 1, _tops[n - 2], _tops, _cache, _tris) * 3 + Addtri(n - 2, _tops, _cache, _tris)) % MOD;
        }
        else
        {
            _cache[n][0] = (Memoization(n - 1, _tops[n - 2], _tops, _cache, _tris) * 2 + Memoization(n - 1, 0, _tops, _cache, _tris) ) % MOD;
            _cache[n][1] = (Memoization(n - 1, _tops[n - 2], _tops, _cache, _tris) * 3 + Memoization(n - 1, 0, _tops, _cache, _tris)) % MOD;
        }
        return _cache[n][roof];
    }
    else
    {
        return _cache[n][roof];
    }
}
int Addtri(int n, vector<int>& _tops, vector<vector<int>>& _cache, vector<int>& _tris) // n개까지의 모양에서 삼각형을 하나 붙인다면 나오는 개수
{
    if (n == 1 && _tops[0] == 0) return 5;  // 기저 조건: 첫번째 칸에 삼각형을 하나 붙인 모양
    if (n == 1 && _tops[0] == 1) return 7;
    //
   //n>2~
    if (_tops[n - 1] == 0)
    {
        if (_tris[n] == 0) // 아직 없는 경우
        {
            _tris[n] = (Memoization(n,_tops[n-1],_tops,_cache,_tris) + Addtri(n - 1, _tops, _cache, _tris)) % MOD;
        }
        return _tris[n]; // 해당 칸까지의 값 + 겹치는 마름모를 뺐을때의 경우의 수 => 이는 또다시 이전칸에 삼각형을 붙인 모습
    }
    else
    {
        if (_tris[n] == 0)
        {
            _tris[n] = (Memoization(n,_tops[n-1],_tops,_cache,_tris)+ Memoization(n,0,_tops,_cache,_tris)) % MOD;
        }
        return _tris[n];  // 지붕이 있었을때의 값 + 지붕을 끌어내려 붙여 지붕을 없앤 모습의 값;
    }
}
int main()
{
    auto answer = solution(4, {1,1,0,1});
    cout << answer;
}

/*

// 카카오2024 산모양 타일링

// DP[n의 개수][top[n]]을 저장해서 활용
// n이 1늘어 났을때 top[n]이 0이냐 1이냐에따라 계산법이 달라지며 이전 것인 tops[n-1]의 값이 어떻게되냐에 따라 달라짐
// tops[n] = 0 이고 tops[n-1] = 0 일때 dp[n][0] = dp[n-1][tops[n-1]] + dp[n-1][tops[n-1]]  +
// tops[n] = 0 이고 tops[n-1] = 1 일때
// tops[n] = 1 이고 tops[n-1] = 0 일때
// tops[n] = 1 이고 tops[n-1] = 1 일때
// 삼각형 관련 dp 하나 더만들기
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int Addtri(int n, vector<int>& _tops, vector<vector<int>>& _cache, vector<int>& _tris);
int MOD = 10007;
int solution(int n, vector<int> tops) {
    int answer = 0;
    vector<vector<int>> cache(n+1, vector<int>(n+1, 0));
    vector<int> tris(n+1,0); // 특정 칸에 삼각형을 붙였을 때의 값 tris[3] => 3번까지의 모양에 삼각형을 붙였을 때의 경우의 수
    cache[1][0] = 3; // n=1, tops[n] = 0(지붕없음)
    cache[1][1] = 4; // n=1, tops[n] = 1
    if (tops[0] == 0)
    {
        cache[2][1] = cache[1][tops[0]] + cache[1][tops[0]] + cache[1][tops[0]] + 2;
        cache[2][0] = cache[1][tops[0]] + cache[1][tops[0]] + 2;
        tris[1] = 5;
    }
    if (tops[0] == 1)
    {
        cache[2][1] = cache[1][tops[0]] + cache[1][tops[0]] + cache[1][tops[0]] + 3;
        cache[2][0] = cache[1][tops[0]] + cache[1][tops[0]] + 3;
        tris[1] = 7;
    }



    // n: 3 ~ n번까지 tops: 0~n-1까지
    for (int i = 3; i < n + 1; ++i)
    {
        if (tops[i - 2] == 0)
        {//이전칸도 지붕이 없는 경우
            cache[i][0] = (cache[i - 1][tops[i - 2]] * 2 + Addtri(i - 2, tops, cache, tris)) % MOD; // 전칸의 지붕이 없는 경우엔 전전칸에 삼각형을 붙인 모양의 수를 계산
            cache[i][1] = (cache[i - 1][tops[i - 2]] * 3 + Addtri(i - 2, tops, cache, tris)) % MOD;
        }
        else
        {// 이전칸에 지붕이 있는 경우
            cache[i][0] = (cache[i - 1][tops[i - 2]] * 2 + cache[i - 1][0]) % MOD; // 이전 칸까지의 수 * 2 + 이전칸이 지붕이 없는 경우
            cache[i][1] = (cache[i - 1][tops[i - 2]] * 3 + cache[i - 1][0]) % MOD; //  이전 칸까지의 수 * 3 + 이전칸이 지붕이 없는 경우
        }

    }
    answer = cache[n][tops[n - 1]];
    return answer;
}
int Addtri(int n, vector<int>& _tops, vector<vector<int>>& _cache, vector<int>& _tris) // n개까지의 모양에서 삼각형을 하나 붙인다면 나오는 개수
{
    if (n == 1 && _tops[0] == 0) return 5;  // 기저 조건: 첫번째 칸에 삼각형을 하나 붙인 모양
    if (n == 1 && _tops[0] == 1) return 7;
    //
   //n>2~
    if (_tops[n - 1] == 0)
    {
        if (_tris[n] == 0) // 아직 없는 경우
        {
            _tris[n] = (_cache[n][_tops[n - 1]] + Addtri(n - 1, _tops, _cache, _tris)) % MOD;
        }
        return _tris[n]; // 해당 칸까지의 값 + 겹치는 마름모를 뺐을때의 경우의 수 => 이는 또다시 이전칸에 삼각형을 붙인 모습
    }
    else
    {
        if (_tris[n] == 0)
        {
            _tris[n] = (_cache[n][_tops[n - 1]] + _cache[n][0]) % MOD;
        }
        return _tris[n];  // 지붕이 있었을때의 값 + 지붕을 끌어내려 붙여 지붕을 없앤 모습의 값;
    }
}
*/