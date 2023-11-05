#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>

using namespace std;
//["I 16", "I -5643", "D -1", "D 1", "D 1", "I 123", "D -1"] => 	[0,0]
// ["I -45", "I 653", "D 1", "I -642", "I 45", "I 97", "D 1", "D -1", "I 333"] => [333, -45]
// "명령어+공백+숫자
vector<int> solution(vector<string> operations) {
    vector<int> answer;
    char c;
    int num = 0;
    int count = 0;
    priority_queue<int> max;
    priority_queue<int, vector<int>, greater<int>> min;
    for (int i = 0; i < operations.size(); ++i)
    {
        stringstream ss(operations[i]);
        ss >> c;
        ss >> num;
        if (count == 0)
        {
            while (!max.empty()) max.pop();
            while (!min.empty()) min.pop();
        }

        if (c == 'I')
        {
            max.push(num);
            min.push(num);
            ++count;
        }
        else
        {
            if (c == 'D' && num == -1 && count != 0)
            {
                min.pop();
                --count;
            }
            else if (c == 'D' && num == 1 &&  count != 0)
            {
                max.pop();
                --count;
            }
        }

    }
    //if (count == 0)
    //{
    //    while (!max.empty()) max.pop();
    //    while (!min.empty()) min.pop();
    //}
    if (count == 0)
    {
        answer.push_back(0);
        answer.push_back(0);
    }
    else
    {
        answer.push_back(max.top());
        answer.push_back(min.top());
    }

    return answer;
}

int main()
{
    vector<int> answer = solution(vector<string>{"I -45", "I 653", "D 1", "I -642", "I 45", "I 97", "D 1", "D -1", "I 333"});
    //vector<int> answer = solution(vector<string>{"I 16", "I -5643", "D -1", "D 1", "D 1", "I 123", "D -1"});
    for (auto ans : answer)
    {
        cout << ans << endl;
    }
    return 0;
}

/* 오답노트 용 다른 사람의 풀이 Multiset
#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> solution(vector<string> arguments) {
    vector<int> answer;
    multiset<int> que;
    multiset<int>::iterator iter;
    string sub;

    for(auto s : arguments) {
        sub =s.substr(0, 2);
        if(sub=="I ") que.insert(stoi(s.substr(2,s.length()-2))); 
        else if(s.substr(2,1)=="1"&&que.size()>0) { que.erase(--que.end()); }
        else if(que.size()>0) { que.erase(que.begin()); }
    }

    if(que.size()==0) { answer.push_back(0); answer.push_back(0); }
    else { 
        iter = --que.end(); answer.push_back(*iter); 
        iter = que.begin(); answer.push_back(*iter);
    }

    return answer;
}*/