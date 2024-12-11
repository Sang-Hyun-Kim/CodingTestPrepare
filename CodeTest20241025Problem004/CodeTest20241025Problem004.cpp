// HackerRank RoadandLibraries
// Find-Union 응용 후 가중치 계산
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
int Find(int x, vector<int>& parent)
{
    if (x == parent[x])
        return x;
    return parent[x] = Find(parent[x], parent); // 부모 갱신을 동시에 처리
}

void Union(int x, int y, vector<int>& parent)
{
    x = Find(x, parent); // px,py라는 새 변수를 선정해버렸던 실수 1
    y = Find(y, parent);

    if (x > y)
    {
        parent[y] = x;
    }
    else
    {
        parent[x] = y;
    }

}
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {

    map<int, int> citygroup;
    vector<int> cp(n, 0); // 도시는 1부터 시작하는 것을 꼭꼭 우ㅠ의하기

    for (int i = 0; i < n; ++i)
    {
        cp[i] = i;
    }

    for (auto c : cities)
    {
        int srt = c[0] - 1;
        int dst = c[1] - 1;
        if (Find(srt, cp) == Find(dst, cp)) // srt끼리 찾아버리는 대참사
        {
            continue;
        }
        else
        {
            Union(srt, dst, cp);
        }
    }
    for (int i = 0; i < n; ++i)
    {
        citygroup[Find(i, cp)]++;
    }

    if (c_lib <= c_road)
    {
        long costs = 0;
        for (auto g : citygroup)
        {
            int cn = g.second;
            costs += long(c_lib * cn);
        }
        return costs;
    }
    else
    {
        long costs = 0;
        for (auto g : citygroup)
        {
            int cn = g.second;
            costs += long(c_lib) + long((cn - 1) * c_road);
        }
        return costs;
    }
}
int main()
{
    int answer = roadsAndLibraries(5, 6, 1, { {1,2},{1,3},{1,4} });
    cout << answer;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
