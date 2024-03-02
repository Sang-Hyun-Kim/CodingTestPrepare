// ����  1717 ������ ǥ��
#include <iostream>
#include <vector>
using namespace std;
void Union(vector<int>& _parents, vector<int>& _degree, int a, int b);
int Find(vector<int>& _parents, int num);
// �и�����
// ��� ����(��ȸ�� ���ÿ� ����)
// Ʈ�� ���̿� ���� ���� ����=>�ӵ� ����
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<int> parents(n + 1);
    vector<int> degree(n + 1, 1);
    for (int i = 0; i < n + 1; ++i)
    {
        parents[i] = i;
    }
    for (int i = 0; i < m; ++i)
    {
        int input, a, b;
        cin >> input >> a >> b;
        if (input == 0)
        {
            Union(parents, degree, a, b);
        }
        else
        {
            if (Find(parents, a) == Find(parents, b))
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
}
void Union(vector<int>& _parents, vector<int>& _degree, int a, int b)
{
    int ap = Find(_parents, a);
    int bp = Find(_parents, b);
    if (ap != bp)
    {
        int newdegree = _degree[ap] + _degree[bp];
        if (_degree[ap] >= _degree[bp])
        {// a�� b ���̱�, degree ����, parents ����
            _parents[bp] = ap;
            _degree[ap] = newdegree;
        }
        else
        {// b�� a ���̱�, degree ����, parents ����
            _parents[ap] = bp;
            _degree[bp] = newdegree;
        }
    }
}
int Find(vector<int>& _parents, int num)
{
    if (num == _parents[num]) return num;
    else
    {
        return _parents[num] = Find(_parents, _parents[num]);
    }

}