// 백준 1593 문자 해독
// 2포인터 및 슬라이딩 윈도우를 활용한 방법으로 풀 다
// 힌트 확인 다른 방법으로 응용
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

// A~Z: 65~90, a~z: 97~122
string w;
string s;
vector<int> wcount(100,0);
vector<int> scan(100,0);
int g, sl;
int answer;
int main()
{
    cin >> g >> sl >> w >> s;
    for (auto c : w)
    {
        wcount[c - 'A']++; // W에 들어가는 횟수 파악
    }

    // 길이가 같고 문자별 count가 일치 할 때 해당하는 문자열임
     
    // count의 수를 넘어버리거나 길이가 같은데 count가 다른 부분이 있으면 안됨 
    int stindex = 0;
    for (int i = 0; i < sl; ++i)
    {
       char c = s[i];
       // 순열안에 있는 문자 이면서, 개수를 초과하지 않았을경우
       if (wcount[c - 'A'] > scan[c - 'A'])
       {
           scan[c - 'A']++;
       }
       else// 순열안에 없거나 개수를 초과하려는 경우
       {// 검사 시작 index 부터 조회하면서 다시 체크
           for (int k = stindex; k <= i; ++k)
           {
               // 이번에 들어온 문자가 점검하던 문자열에서 다시 발견되는 경우
               // 점검 갱신: 점검 시작부분을 같은 것이 나온것 다음부분으로 변경후 진행
               // 또는 아예 없는 단어들의 연속인 경우=> 계속해서 점검 인덱스 증가
               if (s[k] == c)
               {
                   stindex = k + 1;
                   break;
               }
                // 시작한 지점부터 셈했던 것들 전부 감소시키기
               scan[s[k] - 'A']--;
           }
       }

       if (i - stindex + 1 == g) answer++;// 일정한 길이에 알맞는 알파벳의 반복 => 순열을 찾음
    }
    cout << answer;
}


//틀린풀이
/*

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int wl, sl;
    cin >> wl >> sl;
    vector<char> s;
    unordered_multiset<char> os;
    for (int i = 0; i < wl; ++i)
    {
        char c;
        cin >> c;
        os.insert(c);
    }
    int stindex=0;

    unordered_multiset<char> ws=os;
    char lstc = '?';
    int answer = 0;
    for (int i = 0; i < sl; ++i)
    {
        char c;
        cin >> c;
        s.push_back(c);
        // 현재 1개이상의 문자열을 찾은 "Combo" 상태인가.
        if (lstc != '?')
        {
            if (s[i] == lstc) // 새로들어온 녀석이 아까 나갔던 문자이다.
            {
                lstc = s[stindex]; // 문자 갱신
                stindex++;// 앞으로 한칸
                answer++;// 순열개수 한개 증가
            }
            else// 생판 새로운 놈이 와버림~
            {
                stindex = i + 1;
                lstc = '?';// 콤보상태 제거
            }
        }
        else// 하나도 못찾거나 중간에 끊김
        {
            if (find(ws.begin(), ws.end(), s[i]) != ws.end())
            {
                ws.erase(s[i]);
                if (ws.size() == 0)
                {// count + 1
                    answer++;
                    lstc = s[stindex];// 시작 문자 저장=>콤보시작
                    stindex++;
                    ws = os; // 초기화
                }
            }
            else
            {
                if (ws.size() != os.size()) ws = os;// 초기화
                stindex = i + 1;
            }
        }

        if (stindex > sl - wl)// 길이가 모자람
        {
            break;
        }
    }
    cout << answer;
}
*/