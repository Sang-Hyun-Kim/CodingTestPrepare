// 프로그래머스
// 시작접 정렬로 카메라 위치 갱신 조건 설정
// 끝점 정렬시 조건 분기를 하나 더 없앨 수 있음(다른사람 풀이 참고)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> routes) {
    int answer = 0;

    sort(routes.begin(), routes.end(), [&](vector<int> a, vector<int> b) {if (a[0] == b[0])return a[1] < b[1]; return a[0]<b[0]; });

    int rs = routes.size();
    int cx = -30001;
    int cy = -30001;
    int camera= - 30001;
    for (int i = 0; i < rs; ++i)
    {  
        int nx = routes[i][0];
        int ny = routes[i][1];
        if (camera < nx)
        {
            camera = ny;
            answer++;
        }
        else
        {
            if (camera > ny)
                camera = ny;
        }

    }
    
    return answer;
}
int main()
{
    int answer =   solution({ {-24,-15}, {-14,-5},{-18,-13} ,{-5,-3} });
    cout << answer;
}
