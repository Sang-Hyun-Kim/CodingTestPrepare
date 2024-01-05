// 백준 1937 욕심쟁이 판다
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

array<int, 4> dx{ -1, 1, 0, 0};
array<int, 4> dy{ 0, 0, -1, 1 };

int Caching(int i, int j, vector<vector<int>>& _field, vector<vector<int>>& _cache);
int main()
{
    // 입력 	
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int num;
    cin >> num;
    vector<vector<int>> field(num, vector<int>(num, 0));
    for (int i = 0; i < num; ++i)
        for (int j = 0; j < num; ++j)
            cin >> field[i][j];
    vector<vector<int>> cache(num, vector<int>(num, -1));
    int maximum = 0;
    for (int i = 0; i < num; ++i)
    {
        for (int j = 0; j < num; ++j)
        {
            maximum = max(maximum, Caching(i, j,field,cache));
        }
    }
    
    cout << maximum;

}

int Caching(int i, int j, vector<vector<int>>& _field, vector<vector<int>>& _cache)
{
  
    if (_cache[i][j] != -1) return _cache[i][j]; // 이미 계산된 것에 대해 예외처리를 해줘야함!!!
    // 오래걸린 이유 => 다른 좌표에 의해 계산된 좌표의 값을 그대로 반환해야했으나 그대로 한번더 DFS 처리를 해서 값이 또 늘어나게 되었었음 수정완료
    // 들어왔으니까 1 추가;
    if (_cache[i][j] == -1) _cache[i][j] = 1;
    
    int maximum = 0;
    for (int k = 0; k < 4; ++k)
    {
        int nx = i + dx[k];
        int ny = j + dy[k];
        if (nx < 0 || ny < 0 || nx >= _field.size() || ny >= _field.size()) continue; // 범위 벗어나면 초과
        // 다음 좌표의 값이 현재 위치의 값보다 크면 진행
        if (_field[nx][ny] > _field[i][j])
        {
            // 해당 위치에 대해 이전에 DFS가 진행되었었다면
            if (_cache[nx][ny] != -1)
            {
                maximum = max(_cache[nx][ny], maximum); // 해당 위치에 대한 계산 값을 넣기
            }
            else
            {   // 아니라면 새롭게 _caching 해서 진행
                // 다음 좌표에 대한 4방향 DFS 진행
                _cache[nx][ny] = Caching(nx, ny, _field, _cache);
                maximum = max(_cache[nx][ny], maximum);
            }
        }
        
    }
    // 4방향의 최대값을 더해서 저장;
    _cache[i][j] += maximum;
    return _cache[i][j];
}


