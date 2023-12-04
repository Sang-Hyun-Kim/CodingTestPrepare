#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int solution(int n, vector<int> lost, vector<int> reserve);
int main()
{
    int answer = solution(5, vector<int>{2,4}, vector<int>{1,3,5});
    cout << answer << endl;
}
int solution(int n, vector<int> lost, vector<int> reserve) {

   
    int answer = 0;

    vector<int> cloth(n, 1);
    
    for (auto l : lost)
    {
        cloth[l - 1]--;
    }
    for (auto r : reserve)
    {
        cloth[r - 1]++;
    }

    for (int i = 0 ; i < cloth.size();++i)
    {
        if (cloth[i] == 0)
        {
            if (i > 0)
            {
                if (cloth[i - 1] == 2)
                {
                    cloth[i]++;
                    cloth[i - 1]--;
                    continue;
                }
            }

            if (i != cloth.size() - 1)
            {
                if (cloth[i + 1] == 2)
                {
                    cloth[i]++;
                    cloth[i + 1]--;
                    continue;
                }
            }


        }
    }

    for (auto i : cloth)
    {
        if (i !=0) answer++;
    }


    
    return answer;
}