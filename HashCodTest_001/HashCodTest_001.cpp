#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;
string solution(vector<string> participant, vector<string> completion);
int main()
{
    auto _answer = solution(vector<string>{ "mislav", "stanko", "mislav", "ana"}, vector<string>{"stanko", "ana", "mislav" });
    std::cout << _answer;
}

string solution(vector<string> participant, vector<string> completion) {

    unordered_multiset<string> s(participant.begin(),participant.end());
    
    for (string finisher : completion)
    {
        auto it = s.find(finisher);
        s.erase(it);
    }

    
    string answer = "";
    answer = *(s.begin());
    return answer;
}