// 프로그래머스 고득점 킷 여행 경로
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 첫값 
// DFS를 모든 항공권을 수행함 
bool smaller(vector<string>& a, vector<string>& b)
{
    if (a[0] == b[0])
        return a[1] < b[1];
    return a[0] < b[0];
}
vector<string> solution(vector<vector<string>> tickets);
bool DFS(string start, vector<bool>& usedTicket, vector<string>& answer, vector<vector<string>>& tickets, int usedTicket_num);
int main()
{
    auto answer = solution(vector<vector<string>> {{"ICN", "SFO"}, { "ICN", "ATL" }, { "SFO", "ATL" }, { "ATL", "ICN"}, { "ATL", "SFO"}});
    int r = 3;
}

vector<string> solution(vector<vector<string>> tickets)
{

	std::sort(tickets.begin(), tickets.end(), smaller);
    vector<bool> usedTicket(tickets.size(), false);
    vector<string> answer;
    int usedTicket_num = 0;
    DFS("ICN", usedTicket, answer, tickets, usedTicket_num);

    return answer;
}

bool DFS(string start, vector<bool>& usedTicket,vector<string>& answer, vector<vector<string>>& tickets, int usedTicket_num)
{
    // ICN 넣기
    answer.push_back(start);
    if (usedTicket_num == tickets.size()) // 마지막 티켓 순환시 탈출
        return true;
    
    //ICN으로 시작하는 항공권 출발후 해당 항공권 사용 체크
    for(int i = 0; i<tickets.size() ; ++i)
    {
        if (usedTicket[i] != true && tickets[i][0] == start) // 출발지 일치 + 사용한적 있는지
        {
            usedTicket[i] = true;
            bool success = DFS(tickets[i][1], usedTicket, answer, tickets, usedTicket_num + 1); // 출발지->도착지, 재귀호출
            if (success == true) return true; // 만약 해당 회차가 맞는 회차가 아니라면 사용을 취소해야함
            usedTicket[i] = false;
        }
    }

    answer.pop_back();
    return false;
}
