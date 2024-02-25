// 백준 공항 10775
#include <iostream>
#include <vector>
// 유니온 파인드 Union find 연습, 못 풀어서 다른사람 풀이로 힌트 봄
// 분리집합에 대한 이해가 필요함, 추가 공부하기
using namespace std;
int finding(vector<int>& _docking, int num);
void join(vector<int>& _docking, int cnum, int pnum);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int gates;
    int planes;
    cin >> gates >> planes;
    int count = 0;
    vector<int> docking(gates +1);
    for (int i = 0; i < gates + 1; ++i) docking[i] = i;
  
    while (planes--)
    {
        int curdock;
        cin >> curdock;
        if (finding(docking,curdock) == 0) break;
        else
        {
            count++;
            join(docking, finding(docking, curdock), finding(docking, curdock)-1);
        }
    }
    cout << count;
}

int finding(vector<int>& _docking, int num)
{
    if (_docking[num] == num) return num;
    else
    {
        return _docking[num] = finding(_docking,_docking[num]);
    }
}
void join(vector<int>& _docking, int cnum, int pnum )
{
    int cp = finding(_docking, cnum);
    int pp = finding(_docking, pnum);
    if (cp != pp)
    {
        _docking[cp] = pp;
    }
}

