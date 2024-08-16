// 프로그래머스 고득점 Kit 스택/큐 5번 다리를 지나는 트럭
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    int curweight = 0;//현재 다리가 버티는 무게
    int curtime = 1; // 시간 재는중 1초에 한번 트럭들이 이동가능
    // 트럭 한대는 다리 길이만큼의 시간을 소모해서 다리를 건넘
    // 트럭이 다리에 올라온 시간+다리길이의 시간에 해당 트럭이 다리를 건넘
    // 1+2=3에 예시의 7t 트럭이 끝남
    // 무거운거 부터 빨리 끝내는게? 
    queue<pair<int, int>> bt;//다리 타이머
    // 1초가 지나면 ------------
    // 트럭이 내릴 수 있다면 트럭을 먼저 내림
    // 다리의 현재 무게와 최대 대수 미만으로 트럭이 진행중인 경우 트럭을 추가함
    // 트럭을 추가했다면 index를 하나 넘김
    // 1초가 지남

    int index = 0;
    int curtruck = 0;

    curweight += truck_weights[index];
    bt.push({ curtime + bridge_length,truck_weights[index] });
    index++;
    curtruck++;
    curtime++;
    while (!bt.empty())
    {
        if (curtime == bt.front().first)
        { // 목표 도달 시간 도달 시 하차
            auto desttruck = bt.front();
            bt.pop();
            curtruck--; // 현재 트럭 수 체크
            curweight -= desttruck.second;// 현재 하중에서 제거
        }
        // 추가적인 트럭 운행이 가능한지 점검
        if (index >= truck_weights.size())
        {
            answer = bt.back().first;
            return answer;
        }
        if (curtruck < bridge_length && index < truck_weights.size())
        {
            if (curweight + truck_weights[index] <= weight)
            {
                curtruck++;
                curweight += truck_weights[index];
                bt.push({ curtime + bridge_length,truck_weights[index] });
                index++;
            }

        }
        curtime++;
    }
}


int main()
{
    int answer = solution(2, 10, { 7,4,5,6 });
    cout << answer;
}